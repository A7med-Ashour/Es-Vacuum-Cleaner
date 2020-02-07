/* 
    *** FILE   : LED.c
    *** AUTHOR : AHMED GALAL ASHOUR 
    *** DATE   : 18/8/2019
 
 */

/* *** DIRECTIVES *** */

#include "LED.h"
#include "GPIO.h"
#include "HARDWARE.h"

/* *** PRIVATE CONSTANTS *** */

#define   N_LED                 (1)
#define   LED_DUST_INDEX        (0)
#define   LED_UPDATE_PERIOD     (20) /* *** 20 MS BECUASE OF IT DEPENDS ON DUST SWITCH THAT IS UPDATED EVERY 20 MS *** */

/* *** PRIVATE DATATYPES *** */

typedef struct led{
    
    volatile tByte * dirReg;
    volatile tByte * dataReg;
    tByte pin;
    tLedState state;
    
}tLedObj;

/* *** PRIVATE FUNCTIONS PROTOTYPE *** */

static void LED_create(void);

/* *** PRIVATE VARIBLES *** */

static tLedObj LedDB[N_LED];  /* *** LED DRIVERS DATABASE *** */


/* *** PUBLIC FUNCTIONS IMPLEMENTATION *** */

void LED_init(tLed led){
    
    LED_create();
    
    /* *** MAKE CTRL PIN OUTPUT *** */
    
    GPIO_PIN_WRITE(*LedDB[led].dirReg,LedDB[led].pin,GPIO_OUTPUT);
    
    /* *** PUT STATE ON DATA PIN *** */
    
    LED_show(led);
    
    
}

void LED_setState(tLed led, tLedState state){
    
    LedDB[led].state = state;
}

void LED_getState(tLed led , tLedState * state){
    
    *state = LedDB[led].state;
}

void LED_show(tLed led){
    
    GPIO_PIN_WRITE(*LedDB[led].dataReg,LedDB[led].pin,LedDB[led].state);
}

void LED_update(void) {
    
    static tByte LED_counter = ZERO;
    tLed index;
    
    LED_counter += SYSTEM_TICK;
    
    if (LED_counter < LED_UPDATE_PERIOD){
        return;
    }
    
    for(index = 0 ; index < N_LED; index++){
        LED_show(index);
    }
}
/* *** PRIVATE FUNCTIONS IMPLEMENTATIONS *** */

static void LED_create(void){
    
    LedDB[LED_DUST_INDEX] = (tLedObj) { &GPIO_B_CTRL , &GPIO_B_DATA , GPIO_PIN_3 , LED_OFF };
}
