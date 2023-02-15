#include "mqtt.h"
#include "main.h"
#include <iostream>

#define MAX_PAYLOAD 50
#define DEFAULT_KEEP_ALIVE 60

mqtt_client::mqtt_client(const char *id, const char *host, int port) : mosquittopp(id)
{
    this->isConnected = 0;
    mosqpp::lib_init();
    this->connect_async(host, port, DEFAULT_KEEP_ALIVE);
    if (this->loop_start() != MOSQ_ERR_SUCCESS)
    {
        std::cout << "loop start failed\n";
    }
}

mqtt_client::~mqtt_client()
{
    this->disconnect();
    if (this->loop_stop() != MOSQ_ERR_SUCCESS)
    {
        std::cout << "disconnect failed\n";
    }
    mosqpp::lib_cleanup();
    this->isConnected = 0;
}

void mqtt_client::on_connect(int rc)
{
    if (rc == 0)
    {
        this->isConnected = 1;
        std::cout << "successful connection to MQTT broker\n";
    }
    else
    {
        std::cout << "UNsuccessful connection to MQTT broker\n";
    }
}

void mqtt_client::on_subscribe(int mid, int qos_count, const int *granted_qos)
{
    std::cout << "successful subscription\n";
}

void mqtt_client::on_message(const struct mosquitto_message *message)
{
    if (message->payloadlen > 0)
    {
        if (!strcmp(message->topic, TOPIC))
        {
            message_received_Isr(message->payload, message->payloadlen);
        }
    }
}
