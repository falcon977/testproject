#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>

#include "mqtt.h"

using namespace std;

static std::string message_received;
static int flag_message_received = 0;
mqtt_client* iot_client;

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

TEST(MessageProcessingTest, ProcessMessageTest)
{
    message_received = "56000";
    Processing_message(message_received);
    EXPECT_EQ("56000", message_received);
}

int main(int argc, char **argv)
{
    int rc;
    testing::InitGoogleTest(&argc, argv);
    iot_client = new mqtt_client(CLIENT_ID, BROKER_ADDRESS, MQTT_PORT);
    do {
        std::cout << "trying to subscribe to the topic test_transfert\n";
        rc = iot_client -> subscribe(NULL, TOPIC, PUBSUBQOS);
        if (rc != 0)
        {
            std::cout << "error while subscribing\n";
        }
        else
        {
            std::cout << "subscribing successfully done\n";
        }
    } while (rc != 0);

    return RUN_ALL_TESTS();
}
