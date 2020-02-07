/* 
 * File:   MOTOR.h
 * Author: A7med.G.Ashour
 *
 * Created on 19 ?????, 2019, 12:44 ?
 */

#ifndef MOTOR_H
#define	MOTOR_H

/* *** DIRECTIVES *** */

/* *** PUBLIC DATA TYPES *** */

typedef enum {
    LOW_SPEED_ANGEL = 0,
    MID_SPEED_ANGEL,
    HIGH_SPEED_ANGEL
}tMoAngel;

/* *** PUBLIC FUNCTIONS PROTOTYPE *** */

void MO_init(void);

void MO_setTargetAngel(tMoAngel);

void MO_getTargetAngel(tMoAngel *);

void MO_fire(void);

void MO_update(void);

#endif	/* MOTOR_H */

