/*NAME:Chintala Lavanya
 Project Name: CAN based Automotive dash board*/


#include "adc.h"
#include "can.h"
#include "ecu1_sensor.h"
#include "msg_id.h"
#include "uart.h"
#include "clcd.h"
#include "matrix.h"
void init_config_uart(void)
{
    init_uart();
   /* Enabling peripheral interrupt */
   PEIE = 1;
    
    /* Enabling global interrupt */
   GIE = 1;
}
int main()
{
    init_adc();
    init_digital_keypad();
    init_config_uart();
    init_can();
    unsigned int msg_id,len;
    unsigned char data[3];
    while(1)
    {
         //Call the functions
        get_speed();
        get_gear_pos();
    }
}