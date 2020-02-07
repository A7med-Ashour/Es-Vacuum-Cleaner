/*
    *** FILE   : MOTOR.c
    *** AUTHOR : AHMED GALAL ASHOUR
    *** DATE   : 19/8/2019
 */

/* *** DIRECTIVES *** */

#include    "MOTOR.h"
#include    "HARDWARE.h"
#include    "MICRO_CONTROLLER.h"
#include    "VACCUM.h"
#include    "TIMER0.h"
#include    "TIMER1.h"

/* *** PRIVATE CONSTANTS *** */

#define     MO_UPDATE_PERIOD                    (10) /* *** UPDATE EVERY 10 MS *** */
#define     N_ANGEL                             (4)  /* *** NUMBER OF ANGELS   *** */
#define     MO_FIRE_UPDATE_PERIOD               (20) /* *** FIRE UPDATE EVERY 20 MS *** */
#define     SOFT_SWITCH_PERIOD                  (80) /* *** UPDATE EVREY 80 MS *** */
#define     RH_UPDATE_PERIOD                    (20) /* *** UPDATE EVERY 20 MS *** */
#define     START_ANGEL_INDEX                   (3)
#define     LEFT                                (0)
#define     RIGHT                               (1)
#define     RH_STEP                             (5)  /* *** 5 ANGELS FOR EACH REDUCE HARMONICS STEP *** */
#define     STABLE                              (1)
#define     NOT_STABLE                          (0)

/* *** PRIVATE VARIABLES *** */

static tWord    MO_currentAngel;

static tWord    MO_targetAngel;

static tWord    MO_SingleAngelTime;

static tByte    MO_isStable;

static tWord MO_AngelVal[N_ANGEL] = {140,90,10,170}; /* *** { HIGH , MID , LOW , START } *** */

/* *** PRIVATE FUNCTIONS PROTOTYPE *** */

static void MO_fire_update();

static void MO_softSwitch(void);

static void MO_reduceHARM(void);

/* *** PUBLIC FUNCTIONS IMPLEMENTATION *** */


void MO_init(void){
    
    /* *** MAKE MOTOR CTRL PIN AS OUTPUT AND MAKE IT LOW *** */
    
    GPIO_PIN_WRITE(MOTOR_CTRL,MOTOR_PIN,GPIO_OUTPUT);
    
    GPIO_PIN_WRITE(MOTOR_DATA,MOTOR_PIN,GPIO_LOW);
    
    /* *** INTIALIZE CURRENT ANGEL && TARGET ANGEL TO START ANGEL VALUE *** */
    
    MO_targetAngel  = MO_AngelVal[START_ANGEL_INDEX];
    MO_currentAngel = MO_AngelVal[START_ANGEL_INDEX];
    
    /* *** INTIALIZE MOTOR STATE TO STABLE BECAUSE AT THIS MOMENT THE CURRENT == TARGET *** */
    
    MO_isStable = STABLE;
    
    /* *** INTIALIZE SINGLE ANGEL TIME ACCORDING THE POWER SOURCE FREQUENCY *** */
    /* *** IN CASE FREQUENCY 50 HZ SO 180 ANGELS HAPPEN AFTER 10 MS SO SINGLE ANGEL HAPPENS MAY BE AT 55 US *** */
    /* *** IN CASE FREQUENCY 60 HZ SO 180 ANGELS HAPPEN AFTER 8  MS SO SINGLE ANGEL HAPPENS MAY BE AT 22 US *** */
    
    MO_SingleAngelTime = 55;
}

void MO_setTargetAngel(tMoAngel angel){
    
    /* *** PUT ANGLE INTO TARGET ANGEL AND MAKE MOTOR UNSTABLE *** */
    
    MO_targetAngel = MO_AngelVal[angel];
    
    MO_isStable = NOT_STABLE;
    
}

void MO_getTargetAngel(tMoAngel * pAngel){
    
    /* *** PUT Target ANGEL INTO ANGEL POINTER DATA *** */
    
    for(tMoAngel angel = 0; angel < N_ANGEL; angel++){
        if(MO_AngelVal[angel] == MO_targetAngel){
            *pAngel = angel;
        }
    }
}

void MO_fire(void){
    
    /* *** OUT PULSE AT FIRE ANGEL TIME  *** */
    
    /* ??????????????????????????????? *** WHY FOLLOWING WAY WORKS ONLY IN PROTEUS *** ???????????????????????????????? */
    
    /*
   tWord TCount = TMR0_getOneCountTime();
   while(  ( (TMR0_R.Reg - TMR0_RELOAD_VAL) * TCount ) < ( MO_currentAngel * MO_SingleAngelTime ) );
    */
      
    GPIO_PIN_WRITE(MOTOR_DATA,MOTOR_PIN,GPIO_HIGH);
    __delay_us(100);
    GPIO_PIN_WRITE(MOTOR_DATA,MOTOR_PIN,GPIO_LOW);
    TMR1_setState(TMR1_OFF_STATE);
    
}


void MO_update(void){
    
    static tByte MO_counter = ZERO;
    
    
    MO_counter += SYSTEM_TICK;
    
    if(MO_counter != MO_UPDATE_PERIOD){
        return;
    }
    
    MO_counter = ZERO;
    
   MO_fire_update();
   
   MO_softSwitch();
   
   MO_reduceHARM();
    
}

/* *** PRIVATE FUNCTIONS IMPLEMENTATIONS *** */

static void MO_fire_update(void){
    
    
    /* *** INTIALIZE TIMER WITH APPROPRIATE CONFIGURATIONS AND FIRE VALUE *** */
    
    /*
    TMR1_setState(TMR1_OFF_STATE);
    TMR1_init(TMR1_PRS_2,TMR1_TMR_MODE,TMR1_OVF_EN);
    TMR1_reload(TMR1_MAX - fireAngel - 1);
    TMR1_setState(TMR1_ON_STATE);
     */
    
    TMR1_setState(TMR1_OFF_STATE);
    TMR1_init(TMR1_PRS_2,TMR1_TMR_MODE,TMR1_OVF_EN);
    TMR1_reload(TMR1_MAX - (MO_currentAngel * MO_SingleAngelTime));
    TMR1_setState(TMR1_ON_STATE);
}


static void MO_softSwitch(void){
    
    /* *** INCREASE OR DECREASE  CURRENT ANGEL BY SINGLE ANGEL IN THE WAY TO REACH  TARGET ANGEL >>  EVRERY 80 MS *** */
    
    static tByte ss_counter = ZERO;
    
    ss_counter += MO_UPDATE_PERIOD;
    
    if(ss_counter != SOFT_SWITCH_PERIOD){
        return;
    }
    
    ss_counter = ZERO;
    
    if( !MO_isStable && MO_currentAngel < MO_targetAngel){
        
        MO_currentAngel++;
        
    }else if ( !MO_isStable  && MO_currentAngel > MO_targetAngel){
        
        MO_currentAngel--;
        
    }else { 
        
        MO_isStable = STABLE;
        
    }
}

static void MO_reduceHARM(void){
    
    /* *** INCREASE CURRENT ANGEL BY 5 ANGELS AND THEN DECREASE IT BY 5 ANGELS *** */
    
    static tByte RH_counter = ZERO;
    static tByte RH_flag = RIGHT;
    
    RH_counter += MO_UPDATE_PERIOD;
    
    if(RH_counter < RH_UPDATE_PERIOD){
        return ;
    }
    
    RH_counter = ZERO;
    
    /* *** IF SYSTEM IS IN STABLE ANGEL *** */
    
    if( MO_isStable ){
        
        
        if(RH_flag == LEFT){
            
            MO_currentAngel = MO_targetAngel + RH_STEP;
            
            RH_flag = RIGHT;
            
        }else if(RH_flag == RIGHT){
            
            MO_currentAngel = MO_targetAngel - RH_STEP;
            
            RH_flag = LEFT;
        }
    }
}

/* *** SOME DETAILS *** */

/* *** ONE ANGEL MAP TO 55 US TIME *** */
/* *** START FIRE ON %94 OF (FULL PERIOD / 2) = 9 MS **** */
/* *** LOW   FIRE ON %78 OF (FULL PERIOD / 2) = 8 MS **** */
/* *** MID   FIRE ON %50 OF (FULL PERIOD / 2) = 5 MS **** */
/* *** HIGH  FIRE ON %5 OF  (FULL PERIOD / 2) = 0.5 MS **** */