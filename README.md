**PROJECT TITLE**

CAN Automation Dash Board Using PIC18F4580

**Description**

1.This project is implemented using CAN protocol to communicate between three ECUs.

2.ECU1 and ECU2 works as a sensor node and sends vehicle parameters like speed, RPM, and gear and Indicator.

3.ECU3 works as dashboard node and receives CAN data.

4.Dashboard displays the received information on Seven Segment Display / CLCD.

**Files in This Project**

main.c/main.h – Main program

can.c / can.h – CAN initialization, send & receive functions

ecu1_sensor.c/ecu2_sensor.c – Sends speed, gear, and RPM and Indicator values

msg_handler.c/msg_handler.h – Receives CAN data and displays

ssd_display.c / ssd_display.h – Seven segment display functions

clcd.c / clcd.h – LCD display functions 

digital_keypad.c / digital_keypad.h – Keypad input functions

matrix_keypad.c / matrix_keypad.h - keypad input functions

**Features**

1.Uses PIC18F4580 microcontroller with CAN module.

2.Sensor ECU1 & ECU2 sends vehicle parameters continuously.

3.Dashboard ECU3 receives and displays parameters.

4.Demonstrates reliable CAN communication between ECUs.

**Supports**

1.CAN initialization

2.CAN data transmission

3.CAN data reception

4.Data display on SSD/CLCD

**USAGE**

Connect three ECUs through CAN bus.

Sensor ECU1 and ECU2 sends Speed, RPM, Gear and Indicator values.

Dashboard ECU3 receives and displays these values.

**Example**

Sensor Node Sends:

Speed = 60 

RPM   = 3000

Gear  = ON

Indicator = -> or <-


**Dashboard Displays:**

Speed : 60

RPM   : 3000

Gear  : ON

Indicator : -> or <-

**How It Works**

1.Initialize CAN module in three ECUs.

2.Sensor node forms CAN message containing Speed, Gear, RPM, Indicator.

3.CAN message is transmitted on bus.

4.Dashboard ECU3 receives CAN message.

5.Extracts received values.

6.Displays parameters on SSD/CLCD.

**Hardware Used**

1.PIC18F4580 Microcontroller

2.SSD / CLCD display

3.Twisted wires(connect 3 ecus)

4.Power supply(5v)

Author

Chintala Lavanya

Email: chintalalavanya634@gmail.com
