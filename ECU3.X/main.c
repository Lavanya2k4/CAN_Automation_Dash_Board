/*  NAME: Chintala Lavanya
    Project Name: CAN based automotive dash board
    Description: A car dashboard system is developed to monitor parameters like speed, gear position, 
    RPM, and LED indicators using the CAN communication protocol.multiple ECUs send this data over 
    the CAN bus to the dashboard ECU.
    The dashboard ECU processes the incoming messages, decodes the data, and displays  information on an LCD screen.*/

#include <xc.h>
#include <stdint.h>
#include "can.h"
#include "clcd.h"
#include "msg_id.h"
#include "message_handler.h"

int init_leds()
{
    TRISB = 0x08; // Set RB2 as output, RB3 as input, remaining as output
    PORTB = 0x00;
}

static void init_config(void)
{
    // Initialize CLCD and CANBUS
    init_can();
    init_leds();
    init_clcd();

}
void main(void) 
{
    // Initialize peripherals
    init_config();
    
    /* ECU1 main loop */
    while (1) 
    {
        // Read CAN Bus data and handle it
        process_canbus_data();
    }
        

}


