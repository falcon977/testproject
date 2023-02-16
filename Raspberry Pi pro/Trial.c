#include <wiringPi.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>


int PIN = 26;
//--------------------------------------------------------------------
void setup_custom(int PIN)
{
	wiringPiSetupGpio();
	pinMode(PIN, PWM_OUTPUT);
	pwmSetMode(PWM_MODE_MS);
	pwmSetRange(255);
	pwmSetClock(192);
}
void action_pwm(int pwm_value)
{
	if ((pwm_value>0)&&(pwm_value<256))
		{pwmWrite(26, pwm_value);}
}
//----------------------------------------------------------------
void Conc(int message) 
{
	char message_str[20];
	sprintf(message_str, "%d", message);
	char topic[20] = "test_transfert";
	char order[100] = "mosquitto_pub -h broker.hivemq.com -p 1883 -t ";
	strcat(order, topic);
  	strcat(order, " -m ");
  	strcat(order, message_str);
  	strcat(order, " \n");
	printf("%s \n" , order);
	system(order);
}
int fetch_data()
	{
		char line[20];
  		FILE *file = fopen("/sys/class/thermal/thermal_zone0/temp", "r");
  		if (file == NULL) 
			{
				perror("Error opening file");
			}
  		if (fgets(line, 6, file) != NULL) 
			{
				printf("%s \n", line);
				fclose(file);
				return((line[0]-48)*10000+ (line[1]-48)*1000+(line[2]-48)*100+(line[3]-48)*10+(line[4]-48));
			}
  		else 
			{
				perror("Error reading file");
				fclose(file);
				return(0);
			}
	}
int main()
{
	setup_custom(PIN);
	while(1)
	{
		int value;
		value = fetch_data();
		if (value!=0)
		{
			printf("value found ");
			printf("%d \n",value);
		}
		Conc(value);
		if (value>50000){action_pwm(255);}
		else {
			if (value<30000){action_pwm(0);}
			else {action_pwm(127);}
		}
		usleep(200000);
	}
	return 0;
}
