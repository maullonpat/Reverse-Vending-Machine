# EcoTech: A Reverse Vending Machine
This repository contains all the source code, including the Arduino Files, object detection, and the database used in the project, Ecotech: Reverse Vending Machine. The Reverse Vending Machine specializes in detecting plastic bottles and aluminum cans. The bottles inserted are saved as credit points in the user's ID card, which can be exchanged for school supplies. The Reverse Vending Machine is deployed in a school setting.

####
In this project, we have utilized Raspberry Pi 4 to handle object detection, running Python scripts, particularly using the EfficientDet0 model. It is connected to Arduino Mega which handles the dispensing of rewards, gathering user data, and displaying information. To send and retrieve data from the database, An ESP8266 was used, which is connected to the Arduino Mega, which communicates using Serial Communication.

####
Hardware Used:
* Raspberry Pi 4
* Arduino Mega
* ESP8266
* RFID Reader
* SG995 Servo Motor 360° and 180°
* Ultrasonic Sensor
* Inductive Sensor
* Nextion LCD Display
* Relay
* HX711 Load Cell Amplifier

Software Used:
* Arduino IDE
* XAMPP(Apache, MySQL,PHP)
* phpMyAdmin
* Postman (for API testing)

####

####
### Schematic Diagram
![Schematic Diagram](https://imgur.com/8TtPSG4.png)

####
### Example Output
![Example Output](https://imgur.com/1FTIs5b.png)

####
### Prototype Design
![Example Output](https://i.imgur.com/IUPy8pV.png)
