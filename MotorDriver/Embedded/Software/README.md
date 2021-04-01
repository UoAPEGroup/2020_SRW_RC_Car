# Live-updating Website

This website presents the H-Bridge voltage, H-Bridge current, and power through the wirelessly powered RC car through live-updating graphs. It also indicates the speed range (STOP, MIN, MID, MAX), direction (FORWARD, REVERSE), and which safety parameters (over voltage, over current, lost remote connection) are currently triggered.

![website demo](https://github.com/UoAPEGroup/2020-srw-rc-car/blob/main/MotorDriver/Embedded/Software/Demo/Website%20Scrolling2.gif)

## Features

* Graphs update live-time data relating to the voltage, current, and power of the car (speed is to be implemented)
* Indicates which safety parameter is triggered through button colors (red means that safety is triggered and that the car is stopped)
* Can be updated via bluetooth connection or serial connection to uController (note: serial connection is primarily used for testing)

## Documentation 

A local script (checkNearbyBLE.py) is used to find nearby BLE devices and print out their UUID numbers. 

The upstream script (updateDatabaseBL.py) reads incoming data from the microcontroller on the motor driver PCB. It then updates a PostGreSQL databse hosted on Heroku. This can be done sans bluetooth and with serial connection through (updateDatabseSerial.py).

A downstream script (bluetooth.py) periodically checks for updates in the databse. It generates the webpage and reflects any changes onto the graphs.

The webpage uses the Flask framework and is deployed via Heroku. 

## Key python libraries used: 

* Dash
* Plotly
* Bleak
* Psycopg2
* Asyncio
* Gunicorn
* Serial
