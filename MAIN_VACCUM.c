/*
 * File:   MAIN_VACCUM.c
 * Author: A7med.G.Ashour
 *
 * Created on 18 ?????, 2019, 11:21 ?
 */


#include <xc.h>
#include    "TIMER0.h"
#include    "SWITCH.h"
#include    "VACCUM.h"
#include    "GPIO.h"
#include    "HARDWARE.h"
#include    "SSD.h"
#include    "DISPLAY.h"
#include    "MOTOR.h"
#include    "TIMER1.h"

/* *** PRIVATE CONATANTS *** */

#define     STOP                (0)
#define     RUN                 (1)

/* *** PRIVATE VARIABLES *** */

static tByte Schedular_State = STOP;

/* *** PRIVATE FUNCTIONS PROTOTYPES *** */

static void OS_init(void);
static void INDICATOR_init(void);
static void OS_schedular(void);

/* *** MAIN PROGRAM *** */

void main(void) {
    
    /* *** SYSTEM PARTS INTIALIZATION *** */
    
    sw_init();              /* *** INPUT *** */
    VC_init();              /* *** PROCESSING *** */
    DSP_init();             /* *** PROCESSING *** */
    MO_init();              /* *** OUTPUT *** */
    INDICATOR_init();       /* *** INTIALIZE INDICATOR PIN *** */
    OS_init();              /* OPERATING SYSTEM INTIALIZATION *** */   
    
    while(1){
        
        while (STOP == Schedular_State);
        OS_schedular();
        Schedular_State = STOP;
    }
    
}

static void OS_init(void){
    
    /* OPERATING SYSTEM INTIALIZATION *** */
    
    timer0_init(T0_PRESCALLER_128,T0_TIMER_MODE,T0_ON);
    timer0_reload(TMR0_RELOAD_VAL);
    T0_timer_mode_state(T0_ON);
}

static void INDICATOR_init(void) {
    
    /* *** INTIALIZE INDICATOR PIN *** */
    
    GPIO_PIN_WRITE(TICK_CTRL,TICK_PIN,GPIO_OUTPUT);
    GPIO_PIN_WRITE(TICK_DATA,TICK_PIN,GPIO_LOW);
}

static void OS_schedular(void){
    
    MO_update();                            /* *** OUTPUT *** */
    SSD_update();                           /* *** OUTPUT *** */
    switch_update();                        /* *** INPUT *** */
    VC_update();                            /* *** PROCESSING *** */
    DSP_update();                           /* *** PROCESSING *** */ 
}

void __interrupt (high_priority) OS_ISR(void){
    
 
    if(TMR0_OVF_FLAG){
        /* **** OPERATING SYSTEM *** */
       GPIO_PIN_TOGGLE(TICK_DATA,TICK_PIN);    /* *** INDICATOR *** */
        timer0_reload(TMR0_RELOAD_VAL);
        TMR0_OVF_FLAG = GPIO_LOW;
        Schedular_State = RUN;
    } 
    
    if(TMR1_OVF_FLAG){
       MO_fire();
       TMR1_OVF_FLAG = GPIO_LOW;
    }

}


    
