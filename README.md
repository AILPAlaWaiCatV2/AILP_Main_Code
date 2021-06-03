# AILP_Main_Code
## Project Synopsis
The main objective of this project is to create an autonomous catamaran that will deploy bouys that collect temperature, pH, conductivity, and dissolved oxygen to better understand the Ala Wai. There are three parts to this projects programming aspect. The first part is the autonomous coding and relaying of GPS data from the catamaran. The second portion cosists of the bouys and the data transmition to a google sheet. The third aspect is the getting and pushing of data from google sheet into a website that is user interactive and displays data received form the bouys and catamaran. In this repository, the second aspect, being the bouys, is used to transmit data from the buoy to a access point and then to the internet, making this project not only a LoRa project but also an IoT project. 

## Getting Started 
This section describes the materials and software needed to create this project. these are just the basic needs to creat the buoy data collection system. other software and sensors can be added if needed. 

### Materials Needd
These are the supplies needed to create this project:

#### Boards
* Arduino Uno Board
* Altas Scientific Tentacle Shiel
* LoRa RFM95 Transceiver
* SparkFun Monster Moto Shield

#### Sensors
* Atlas Temperature Sensor
* Atlas Temperature Circuit Chip
* Atlas pH Sensor
* Atlas pH Circuit Chip
* Altas Dissolved Oxygen Sensor
* Atlas Dissolved Oxygen Circuit Chip
* Atlas Conductivity Sensor
* Altas Conductivity Circuit Chip

#### Motors
* BlueRobotics ESC (Electronic Servo Controller)
* Blue Robotics Thruster
* ServoCity Motor

#### Buoy
* Buoy Housing
* Buoy Electronics Plate

#### Receiver Hub
* NodeMCU
* LoRa Feather

### Prerequisites
The prerequisities for this project consist of libraries, an IDE (Integrated Development Enviroment), and a website account that will be used to hold the data coming from the mounted monitoring system. The project also requires that the electronics (more specifically the NodeMCU) has a WiFi network to connect to.

For an IoT (Internet of Things) interface, we used [Ubidots](https://ubidots.com/education/) to create a platform for the data collected from the buoy into a clean space where teachers and students can see the real time data. With this website, we use it as a house point for the incoming data to be stored so that google sheets can grab this data and place it into table that keep a running history of the data.

Here is the IDE needed to upload and change code for this project:

* [Arduino IDE](https://www.arduino.cc/en/Main/Software)

Libraries needed for this project can be found through the followig path: Source/Buoy/Libraries

## Basic Setup

### Installing the main code
To install the main code, click on the top right corner of the GitHub that says "Clone or download" and download the whole file as a .zip. This will allow you to download all the main code that will be uploaded to the different electronics and all the libraires can be downloaded from the file. 

### Installing and setting up Arduino IDE
First, install the IDE (the link can be found in the prerequisites section). Once that is done, follow the steps bellow to configure the IDE to upload to the different boards with the proper libraries installed.

* Open Arduino IDE 
* Go to File -> Prefrence
* Under the "Additional Boards Manager URLs" paste this link: "https://adafruit.github.io/arduino-board-index/package_adafruit_index.json, http://arduino.esp8266.com/stable/package_esp8266com_index.json" 
* Then press OK on the bottom right corner of that page
* Go to Tools -> Board -> Boards Manager
* In the search box look up "Adafruit AVR" and install that profile (This is the board profile used to upload to the LoRa Feather)
* Once it's done downloading, search for "esp8266 by esp8266 community" and download that profile (This is the board profile used to upload to the NodeMCU)

After all the steps above have been done, the IDE is setup and ready to upload the the designated boards. The following steps will help place the libararies needed in the right area:

* Download the main code file on GitHub (This instruction can be found in the prerequisites)
* Then to locate the library file for Arduino:
For Window users:
* Documents -> Arduino -> Library
* Place the libarries downloaded form the main source file into the Arduino library file

Once this is done, the libraries are installed and ready to be used. 

### Setting up Ubidots
Ubidots is an IoT website that allows data to be sent to it and monitored from any device connected to the internet. Follow the following steps to create an account in Ubidots. This will also show how to create devices and variables that will be used in the project. 

* Go to the Ubidots [Education website](https://ubidots.com/education/) and click Sign Up
* Enter a vaid email, Username, and Password 

Once an account is created, there will be a blank page with three diffrent tabs.

* Click on the "Devices" tab 
* Click on Add Device (Note: Name the device based on the project. e.g LoRa Temp)
* Click on Add Variable 
* Name the variables created Temperature, Dissolved Oxygen, Conductivity, pH, GPSX, GPSY

Once the device and variable is created, Ubidots is setup. But will be reffered to in order to input data into the code to allow the NodeMCU to send data over to Ubidots and for Ubidots to send data over to google sheets. 
*Note: Ubidots is based on a credit system which means more than one device does cost credits being used. 

### Setting up GoogleSheets
Create or log into a Google account that has access to Google Sheets. CLick on the Google Sheets icon and create a new document. Create five tabs that are named after each sensor being used (temperature, pH, conductivity, dissolved oxygen, and GPS). 

## Coding

### Loading the Code
All the code that will be going on the electronics have been premade. Varaibles and changes that are needed from the user is signalled in the comments of the code. To load the main code, follow these steps so that we can upload the code to the electronics.

#### Buoy Sensor and Transmitting Code
* Go to the file downloaded in the prerequisites 
* Go to Source/LoRa/Buoy_with_Tentacle_LoRa
* Open the .ino file in Arduino and the code is ready to upload 

#### Buoy Manual Control
*Note: this code will be uploaded to a seperate Arduino Uno.* 
* Go to the file downloaded in the prerequisites
* Go to Source/Buoy/Active Position Holding/Buoy_Control_Master
* Open the .ino file in Arduino and the code is ready to upload 

#### Hub Receiver LoRa

##### LoRa Feather
* Go to the file downloaded in the r=prerequisites
* Go to Source/Buoy/LoRa/LoRa_Receive_Main
* Open the .ino file in Arduino and the code is ready to upload

##### NodeMCU
* Go to the file downloaded in the r=prerequisites
* Go to Source/Buoy/LoRa/Hub_Node_Main
* Change the variable ID and WiFi credentials 
* The code is ready to upload

### Uploading Code
Once the code is open in the IDE, the following stpes will showcase how to upload code to each board. 

#### Arduino Uno Sensor Collection and LoRa Transmitting Upload and Buoy Manual Motor Control Upload
*Note Before uploading code, check the code comments to see what variables need to be change* 
* Go to Tools -> Boards and scroll down untill Arduin Uno shows up
* Click on that board 
* Plug in the Arduino via USB to USB data cable into the computer
* Go to Tools -> Comm Ports and click on port the board is plugged into 
* Press the upload button on the top left corner of the IDE
*Note: uploading to the board may take time*

#### LoRa Feather 32u4 Receiving Upload
*Note Before uploading code, check the code comments to see what variables need to be change* 
* Go to Tools -> Boards and scroll down untill Feather 32u4 shows up
* Click on that board 
* Plug in the Feather via Micro USB to USB data cable into the computer
* Go to Tools -> Comm Ports and click on port the board is plugged into 
* Press the upload button on the top left corner of the IDE
*Note: uploading to the board may take time*

#### NodeMCU Sending Upload

##### Changing Variables in Code
*Note Before uploading code, check the code comments to see what variables need to be change* 
To find the Token for the code:

* Go to Ubidots and click on your profile
* Click on API Credentials
* Copy the Token and place it into the respected area of the code

To find the variable ID for the code:

* Go to Devices -> Variables
* Click on the varaible "temperature" and click on the i icon
* Copy the Variable ID and place it into the respected area of the code
Replace the WIFIUSERNAME and WIFIPASSWORD with the network security settings that the NodemCU will be connecting

##### Changing Devices and Uploading Code
Once the variables have been changed to it's respected ID's, the following will help upload the code to the NodeMCU

* Go to Tools -> Boards -> 1.0 NodeMCU and click on that device
* Plug in the NodeMCU via Micro USB to USB into a Comm Port
* Select the Comm Port the device is in and click the upload button on the top right of the IDE

### Once these steps are completed, your project is ready to be run. 






