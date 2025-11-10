#include "ecu2_sensor.h"
#include "adc.h"
#include "can.h"
#include "msg_id.h"
#include "uart.h"
#include "digital_keypad.h"

extern IndicatorStatus cur_ind_status;
uint16_t get_rpm()
{
    //Implement the rpm function
    //unsigned long int rpm = ((read_adc(CHANNEL4))/10.23) * 60;
    uint16_t rpm = ((read_adc(CHANNEL4))/1023.0) * 6000.0;
    unsigned char tx_rpm[4];
    tx_rpm[0]=(rpm/1000)%10+'0'; 
    tx_rpm[1]=(rpm/100)%10+'0'; 
    tx_rpm[2]=(rpm/10)%10+'0';
    tx_rpm[3]=(rpm%10)+'0';
    tx_rpm[4]='\0';
    can_transmit(RPM_MSG_ID,tx_rpm,4);
    for(unsigned long int delay=500;delay--;);
    return rpm;
}
void process_indicator()
{
    static unsigned int delay;

    if (cur_ind_status == e_ind_left) //left
    {
        if (delay < 1000) 
        {
            LEFT_IND_ON();
            RIGHT_IND_OFF();
        }
        else if (delay < 2000) 
        {
            LEFT_IND_OFF();
        }
        else 
        {
            delay = 0;
        }
        delay++;
    }
    else if (cur_ind_status == e_ind_right) //right 
    {
        if (delay < 1000) 
        {
            RIGHT_IND_ON();
            LEFT_IND_OFF();
        }
        else if (delay < 2000) 
        {
            RIGHT_IND_OFF();
        }
        else 
        {
            delay = 0;
        }
        delay++;
    }
    else // OFF
    {
        LEFT_IND_OFF();
        RIGHT_IND_OFF();
    }
}
