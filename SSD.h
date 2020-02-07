/* 
 * File:   SSD.h
 * Author: A7med.G.Ashour
 *
 * Created on 31 ?????, 2019, 04:06 ?
 */

#ifndef SSD_H
#define	SSD_H
#include "MICRO_CONTROLLER.h"

typedef enum  {
    SSD_0 ,
    SSD_1,
    SSD_2,
    SSD_3,
    SSD_4,
    SSD_5,
    SSD_6,
    SSD_7,
    SSD_8,
    SSD_9,
    SSD_NULL
}tSSD_SYMBOL;

typedef enum {
    SSD_LOW = 0,
    SSD_MID,
    SSD_HIGH
}tSSD;



void SSD_init(tSSD);
void SSD_setSymbol(tSSD, tSSD_SYMBOL);
tSSD_SYMBOL SSD_getSymbol(tSSD);
void SSD_setVal(tSSD ,tByte);
void SSD_update(void);
void SSD_display(tSSD ssd , tByte data);

#endif	/* SSD_H */

