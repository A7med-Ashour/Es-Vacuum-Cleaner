/*
    *** NAME   : VACCUM.C
    *** AUTHOR : AHMED GALAL ASHOUR
    *** DATE   : 18 / 8 / 2019
 */

/* **** DIRECTIVES **** */

#include "VACCUM.h"
#include "SWITCH.h"
#include "GPIO.h"
#include "HARDWARE.h"
#include "MICRO_CONTROLLER.h"
#include "MOTOR.h"

/* *** PRIVATE CONSTANTS *** */

#define     VC_UPDATE_PERIOD            (20) /* UPDATE EVERY 20 MS */
#define     N_SPEED                     (3) /* NUMBER OF SPEEDS */
#define     STEP_ONE                    (2)
#define     STEP_TWO                    (1)
#define     STEP_ONE_TIME               (30)
#define     STEP_TWO_TIME               (60)

/* *** PRIVATE FUNCTIONS PROTOTYPE *** */

static void sw_plus_handler(void);
static void sw_minus_handler(void);
static void sw_dust_handler(void);
static void VC_SpeedIncrease(void);
static void VC_SpeedDecrease(void);

/* *** PRIVATE VARIABLES *** */

static tSpeed VC_current_speed;

/* *** PUBLIC FUNCTIONS IMPLEMENTATION *** */

void VC_init(void){
    
    /* *** SET CURRENT SPEED TO MID SPEED *** */
    
    VC_current_speed = MID_SPEED;
    
    
}

void VC_getSpeed(tSpeed * ps){
    *(ps) = VC_current_speed;
}

void VC_update(void){
    static tByte vc_counter = ZERO;
    
    vc_counter += SYSTEM_TICK;
    
    if(vc_counter != VC_UPDATE_PERIOD){
        return;
    }
    
    vc_counter = ZERO;
    
    tByte sw_index;
    
    /* *** HANDEL SWITHCES STATE *** */
    
    for (sw_index = sw_plus; sw_index < N_SWITCHES; sw_index++){
        switch(sw_index){
            
            case sw_plus :
                sw_plus_handler();
                break;
            case sw_minus :
                sw_minus_handler();
                break;
            case sw_dust :
                sw_dust_handler();
                break;
            default :
                /* DO NOTHING */
                break;
        }
    }
    
    /* *** SEND TARGET ANGEL TO MOTOR ACCORDING CURRENT SPEED *** */
    
    /* *** IF WE GURRENTEE THAT THE ORDER IN SPEED TYPE IS THE SAME AS IN ANGEL TYPE WE CAN USE THIS WAY OTHERWISE WE USE SWITCH CASES *** */
    
    
    MO_setTargetAngel(VC_current_speed);
}

/* *** PRIVATE FUNCTIONS IMPLEMENTATION *** */

static void sw_plus_handler(void){
    if(  (switch_getState(sw_plus) == sw_prepressed) && (switch_getState(sw_dust) == sw_released) ){
       
        /* *** INCREASE SPEED ONE STEP *** */
        
         VC_SpeedIncrease();
         
    }else {/* DO NOTHING */}
}

static void sw_minus_handler(void){
     if( (switch_getState(sw_minus) == sw_prepressed) && (switch_getState(sw_dust) == sw_released) ){
        
        /* *** DECREASE SPEED ONE STEP *** */   
         
        VC_SpeedDecrease();
        
     }else{/* DO NOTHING */}
}

static void sw_dust_handler(void){
    
    static tByte step = STEP_ONE;
    
    if (SW_getPressedTime(sw_dust) == STEP_ONE_TIME && step == STEP_ONE )
    {
        VC_SpeedDecrease();
        step--;
        
    }else if ( SW_getPressedTime(sw_dust) == STEP_TWO_TIME && step == STEP_TWO ){
        
        VC_SpeedDecrease();
        step--;
        
    }else if (switch_getState(sw_dust) == sw_released ){
        step = 2;
    }else {/* DO NOTHING */}
}

static void VC_SpeedIncrease(void){
    
    VC_current_speed = (VC_current_speed < HIGH_SPEED) ? ++VC_current_speed : VC_current_speed; 
}

static void VC_SpeedDecrease(void){
    
    VC_current_speed = (VC_current_speed > LOW_SPEED) ? --VC_current_speed : VC_current_speed; 
}