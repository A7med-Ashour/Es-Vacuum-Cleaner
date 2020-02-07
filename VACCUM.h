/* 
 * File:   VACCUM.h
 * Author: A7med.G.Ashour
 *
 * Created on 18 ?????, 2019, 02:33 ?
 */

#ifndef VACCUM_H
#define	VACCUM_H

/* *** PUBLIC DATA TYPES *** */

typedef enum {
    LOW_SPEED = 0,
    MID_SPEED,
    HIGH_SPEED
}tSpeed;


/* *** PUBLIC FUNCTIONS PROTOTYPES *** */

void VC_init(void);

void VC_getSpeed(tSpeed *);

void VC_update(void);


#endif	/* VACCUM_H */

