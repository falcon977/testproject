# IoT Project
This is a the test project, a solution that retrieves real time temperature value of a microprocessor (Raspberry Pi 4 Model b) and interface it in a web API.
The project contains two major parts. The first one, located in the directory named "Raspberry Pi pro", is an embedded C application that aims to extract the actual temperature of the Raspberry Pi board, and here there are three options. If such a value is higher than a fixed threshold (50°C), a small fan, wired to the Raspberry Pi by GPIO, which acts as a cooling station, will start to spin at the highest available speed. If the temperature is between the maximum threshold and the minimum one (30°C), the fan will continue spinning but with a lower speed. The third case is when such a value is below 30°C, the fan will necessarily stop.
The temperature data, whenever captured, is directly sent to another application using MQTT protocol, by publishing the value to a topic within Hivemq broker.

I used the following tools to develop this project : 

Hardware equipments : 
- L298N 
- Fan
- Raspberry Pi 4 model b

Software tools : 
- Embedded C
- Embedded Linux
- Shell scripting
- WiringPi library
- MQTT (Hivemq broker and client publishing the value to the broker)

The second project is a backend web application (web API endpoint), that is always subscribing to the temperature topic of the hivemq broker. Whenever a client (browser) will request the data, the API will serve him the last retrieved temperature value of the board, coming from the MQTT broker. In brief, the web API interfaces exactly two elements : the temperature of the microprocessor and the station status (Cooling/heating).

Software tools : 
- C++
- MQTT
- Mosquitopp library
- Crow library
- Shell scripting

For each project, I made small shell script that guides you to compile and run the executable file.
