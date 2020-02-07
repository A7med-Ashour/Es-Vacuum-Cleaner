/* 
 * File:   LED.h
 * Author: A7med.G.Ashour
 *
 * Created on 18 ?????, 2019, 10:23 ?
 */

#ifndef LED_H
#define	LED_H

/* *** PUBLIC DATATYPES *** */

typedef enum {
    LED_DUST = 0,
}tLed;

typedef enum {
    LED_OFF = 0,
    LED_ON,
    LED_TOGGLE
            
}tLedState;

/* *** PUBLIC FUNCTIONS PROTOTYPE *** */

void LED_init(tLed);
void LED_setState(tLed,tLedState);
void LED_getState(tLed, tLedState * );
void LED_show(tLed);
void LED_update(void);

#endif	/* LED_H */

