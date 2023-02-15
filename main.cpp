#include "crow.h"
#include <string>
#include <iostream>
#include <crow.h>
#include "mqtt.h"


using namespace std;

mqtt_client *iot_client;

static int flag_message_received = 0;
static std::string message_received;

void message_received_Isr(void* in_payload, int payloadlength)
{
    if (flag_message_received == 0)
    {
        message_received = std::string((char*)in_payload);
        flag_message_received = 1;
    }
    else
    {
        std::cout << "previous message still under process\n";
    }
}
void Processing_message(std::string& in_strmessage)
{
    std::cout << in_strmessage;
}

int temp = 89;
std::string s = "a string";



int main()
{
    int rc;
    std::cout << "connecting to broker\n";
    iot_client = new mqtt_client(CLIENT_ID, BROKER_ADDRESS, MQTT_PORT);
    crow::SimpleApp app;
    CROW_ROUTE(app, "/temperature")
    ([&]{

    do {
        std::cout << "trying to subscribe to the topic test_transfert\n";
        rc = iot_client -> subscribe(NULL, TOPIC, PUBSUBQOS);
        if (rc != 0)
        {
            std::cout << "error while subscribing\n";
        }
        else
        {
            std::cout << "subscribing succesfully done\n";
        }
 
    } while (rc != 0);
    while(1)
    {
        if (flag_message_received == 1) {
            std::cout << "processing...\n";
            Processing_message(message_received);
            flag_message_received = 0;

        }
        else
        {
            break;
        }
    }

        crow::json::wvalue x({{"temperature", std::stof( message_received )/1000}});
        x["status"] = s;
        return x;
    });
    app.port(4000).run();
}




// int main()
// {



// }

