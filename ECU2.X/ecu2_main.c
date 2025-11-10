/*NAME:chintala lavanya
 Project Name: CAN based Automotive dash board*/


#include "ecu2_sensor.h"
#include "adc.h"
#include "can.h"
#include "msg_id.h"
#include "uart.h"
#include "digital_keypad.h"
#include "clcd.h"

IndicatorStatus cur_ind_status = e_ind_off;

int main()
{
    init_adc();
    init_can();
    init_digital_keypad();

    TRISB = 0x08;
    PORTB = 0x00;

    while (1)
    {
        get_rpm();           
        process_indicator(); 

        unsigned char key = read_digital_keypad(STATE_CHANGE);
        unsigned char data[1];

        if (key == SWITCH1) 
        {
            cur_ind_status = e_ind_left;
            data[0] = 1;
            can_transmit(INDICATOR_MSG_ID, data, 1);
        } 
       else if (key == SWITCH3) 
        {
            cur_ind_status = e_ind_right;
            data[0] = 2;
            can_transmit(INDICATOR_MSG_ID, data, 1);
        } 
        else if (key == SWITCH2) 
        {
            cur_ind_status = e_ind_off;
            data[0] = 0;
            can_transmit(INDICATOR_MSG_ID, data, 1);
        }
    }
}
