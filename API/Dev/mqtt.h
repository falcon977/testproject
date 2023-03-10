#ifndef SIMPLECLIENT_MQTT_H
#define SIMPLECLIENT_MQTT_H

#include <mosquittopp.h>
#include <cstring>
#include <cstdio>

#define CLIENT_ID "wserver_link"
#define BROKER_ADDRESS "broker.hivemq.com"
#define MQTT_PORT 1883
#define MAX_PAYLOAD 50
#define TOPIC "test_transfert"
#define DEFAULT_KEEP_ALIVE 60
#define PUBSUBQOS 2

class mqtt_client : public mosqpp::mosquittopp
{
public:
    mqtt_client (const char *id, const char *host, int port);
    ~mqtt_client();

    void on_connect(int rc);
    void on_message(const struct mosquitto_message *message);
    void on_subscribe(int mid, int qos_count, const int *granted_qos);
private:
    int isConnected;
};

#endif //SIMPLECLIENT_MQTT_H
