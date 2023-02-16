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

TEST(MainBlockTest, MainBlockTest)
{
    // Given an iot_client and flag_message_received = 1
    int rc;
    std::cout << "connecting to broker\n";
    iot_client = new mqtt_client(CLIENT_ID, BROKER_ADDRESS, MQTT_PORT);
    flag_message_received = 1;

    // When the main block is executed
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
    if (std::stof( message_received )/1000 > 50)
    {
        x["status"] = "start_cooling";
    }
    else
    {
        x["status"] = "start_heating";
    }

    // Then the output should match the expected result
    EXPECT_EQ("start_cooling", x["status"].s());
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
