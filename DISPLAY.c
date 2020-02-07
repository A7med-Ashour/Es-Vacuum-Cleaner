/* 
    *** FILE    : DISPLAY.c
    *** AUTHOR  : AHMED GALAL ASHOUR
    *** DATE    : 18 / 8 / 2019
 */

/* *** DIRECTIVE *** */

#include "DISPLAY.h"
#include "VACCUM.h"
#include "HARDWARE.h"
#include "SSD.h"
#include "LED.h"
#include "SWITCH.h"

/* *** PRIVATE CONSTANT *** */

#define             DSP_UPDATE_PERIOD           (20) /* *** UPDATE EVREY 10 MS *** */


static tSpeed  DSP_speed;
static tByte DSP_speed_patterns [3] [3] = {
    {0x08,0x00,0x00},
    {0x08,0x48,0x00},
    {0x08,0x48,0x49}
};



void DSP_init(void){
    
    /* *** INTIALIZE ALL SSD *** */
    
    SSD_init(SSD_LOW);
    SSD_init(SSD_MID);
    SSD_init(SSD_HIGH);
    
    /* *** INTIALIZE DUST LED *** */
    
    LED_init(LED_DUST);
    
}
void DSP_update(void){
    static tByte DSP_counter = ZERO;
    
    DSP_counter += SYSTEM_TICK;
    
    if(DSP_counter != DSP_UPDATE_PERIOD){
        return;
    }
    
    DSP_counter = ZERO;
    
    /* ** GET SPEED FROM VACCUM *** */
    
    VC_getSpeed(&DSP_speed);
    
    /* *** PREPARE CURRENT PATTERN ***  */
  
    /* BUT EVERY SSD VAL ACCORDING CURRENT PATTERN */
    SSD_setVal(SSD_LOW,DSP_speed_patterns[DSP_speed][0]);
    SSD_setVal(SSD_MID,DSP_speed_patterns[DSP_speed][1]);
    SSD_setVal(SSD_HIGH,DSP_speed_patterns[DSP_speed][2]);
    
    /* *** SET DUST_LED STATE ACCORDING DUST_SWITCH STATE *** */
    
    tLedState led_state = (switch_getState(sw_dust) == sw_pressed);
    
    LED_setState(LED_DUST,led_state);
    
    /* *** BECAUSE DSP_UPDATE_PERIOD == LED_UPDATE_PERIOD WE CAN PUT LED_UPDATE INSIDE DSP_UPDATE *** */
    
    LED_update();
    
}
#include    "DISPLAY.h"
