#include <xc.h>
#include <string.h>
#include "message_handler.h"
#include "msg_id.h"
#include "can.h"
#include "clcd.h"


volatile unsigned char led_state = LED_OFF, status = e_ind_off;


void handle_speed_data(uint8_t *data, uint8_t len)
{
    // Implement the speed function
    clcd_print("SPD:",LINE1(0));

    data[2] = '\0';
    clcd_print(data, LINE1(4));
}

void handle_gear_data(uint8_t *data, uint8_t len) 
{
    // Implement the gear function
     clcd_print("GEAR:",LINE2(0));

    data[2] = '\0';
    clcd_print(data, LINE2(5));
}

void handle_rpm_data(uint8_t *data, uint8_t len) 
{
    // Implement the rpm function
    clcd_print("RPM:",LINE1(8));

    data[4] = '\0';  
    clcd_print(data, LINE1(12));
}

void handle_indicator_data(uint8_t *data, uint8_t len) 
{
    // Implement the indicator function
    clcd_print("IND:",LINE2(8));
    static unsigned int delay = 0;

    switch (data[0])
    {
        case 1: // LEFT
            if (delay < 200) 
            {
                LEFT_IND_ON();
                RIGHT_IND_OFF();
                clcd_print("-> ", LINE2(12));
            }
            else if (delay < 400) 
            {
                LEFT_IND_OFF();
                CLEAR_DISP_SCREEN;
            }
            else 
            {
                delay = 0;
            }
            delay++;
            break;

        case 2: // RIGHT
            if (delay < 200) 
            {
                RIGHT_IND_ON();
                LEFT_IND_OFF();
                clcd_print("<- ", LINE2(12));
            }
            else if (delay < 400) 
            {
                RIGHT_IND_OFF();
                CLEAR_DISP_SCREEN;
            }
            else 
            {
                delay = 0;
            }
            delay++;
            break;

        case 0: // INDICATOR OFF
            clcd_print("OFF", LINE2(12));
            LEFT_IND_OFF();
            RIGHT_IND_OFF();
            delay = 0;
            break;

        default:
            break;
    }
}
void process_canbus_data()
{
    uint16_t msg_id;
    uint8_t len;
    unsigned char data[10];
    can_receive(&msg_id,data,&len);
    if (msg_id == SPEED_MSG_ID)
    {
        handle_speed_data(data,len);  

    }
    else if(msg_id == RPM_MSG_ID)
    {
        handle_rpm_data(data,len);

    }
    else if(msg_id == GEAR_MSG_ID)
    {
        handle_gear_data(data,len);

    }
    else if (msg_id == INDICATOR_MSG_ID)
    {
        handle_indicator_data(data, len);
    }
}