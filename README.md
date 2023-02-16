# IoT Project
This is a the test project, a solution that retrieves real time temperature value of a microprocessor (Raspberry Pi 4 Model b) and interface it in a web API.
The Project contains two major parts. The first one, located in the directory named "Raspberry Pi pro", is an embedded C application that aims to extract the actual temperature of the Raspberry Pi board, and here there is three options. If such a value is higher than a fixed threshold (50°C), a small fan, wired to the Raspberry Pi by GPIO, which acts as a cooling station, will start to spin at the highest available speed. 
