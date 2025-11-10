#include "ecu1_sensor.h"
#include "adc.h"
#include "can.h"
#include "msg_id.h"
#include "uart.h"
#include "clcd.h"
#include "matrix.h"

char event[9][3]={"ON","GN","G1","G2","G3","G4","G5","GR","C_"};
uint16_t get_speed()
{
    unsigned char tx_speed[3];
    unsigned int speed=read_adc(CHANNEL4)/10.33;
    tx_speed[0]=((speed/10)+48);
    tx_speed[1]=((speed%10)+48);
    tx_speed[2]='\0';
    can_transmit(SPEED_MSG_ID,tx_speed,2);
    for(unsigned long int delay=500;delay--;);
    return speed;
}

unsigned char get_gear_pos()
{
    unsigned char key;
    static int index=0;
   key = read_digital_keypad(STATE_CHANGE);
    if(key==SWITCH1)
    {
        if(index<7)
        {
            index++;
        }
        if(index==8)
        {
            index=1;
        }
    }
    else if(key==SWITCH2)
    {
        if(index>1 && index!=8)
        {
            index--;
        }
        if(index==8)
        {
            index=1;
        }
    }
    else if(key==SWITCH3)
    {
        index=8;
    }
    can_transmit(GEAR_MSG_ID,event[index],2);
    for(unsigned long int delay=500;delay--;);
    return index;
}