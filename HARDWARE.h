/* 
 * File:   HARDWARE.h
 * Author: A7med.G.Ashour
 *
 * Created on 30 ?????, 2019, 07:07 ?
 */

#ifndef HARDWARE_H
#define	HARDWARE_H
#include "GPIO.h"

// SYSTEM
#define         SYSTEM_TICK                                                         (10) // 10 ms is HCF OF ALL TASKS

/* **** LED **** */

#define         TICK_CTRL                                                           (GPIO_C_CTRL)
#define         TICK_DATA                                                           (GPIO_C_DATA)
#define         TICK_PIN                                                            (GPIO_PIN_1)


/* *** SWITCHES *** */

#define         SW_PLUS_CTRL                                                        (GPIO_B_CTRL)
#define         SW_PLUS_DATA                                                        (GPIO_B_DATA)
#define         SW_PLUS_PIN                                                         (GPIO_PIN_0)

#define         SW_MINUS_CTRL                                                       (GPIO_B_CTRL)
#define         SW_MINUS_DATA                                                       (GPIO_B_DATA)
#define         SW_MINUS_PIN                                                        (GPIO_PIN_1)

#define         SW_DUST_CTRL                                                        (GPIO_B_CTRL)
#define         SW_DUST_DATA                                                        (GPIO_B_DATA)
#define         SW_DUST_PIN                                                         (GPIO_PIN_2)

/* *** SSD DEFENITIONS ******** */

#define         SSD_LOW_DATA_DIR                                                    (GPIO_D_CTRL)
#define         SSD_LOW_DATA_VAL                                                    (GPIO_D_DATA)
#define         SSD_LOW_CTRL_DIR                                                    (GPIO_B_CTRL)
#define         SSD_LOW_CTRL_VAL                                                    (GPIO_B_DATA)
#define         SSD_LOW_CTRL_PIN                                                    (GPIO_PIN_6)

#define         SSD_MID_DATA_DIR                                                    (GPIO_D_CTRL)
#define         SSD_MID_DATA_VAL                                                    (GPIO_D_DATA)
#define         SSD_MID_CTRL_DIR                                                    (GPIO_B_CTRL)
#define         SSD_MID_CTRL_VAL                                                    (GPIO_B_DATA)
#define         SSD_MID_CTRL_PIN                                                    (GPIO_PIN_5)      

#define         SSD_HIGH_DATA_DIR                                                   (GPIO_D_CTRL)
#define         SSD_HIGH_DATA_VAL                                                   (GPIO_D_DATA)
#define         SSD_HIGH_CTRL_DIR                                                   (GPIO_B_CTRL)
#define         SSD_HIGH_CTRL_VAL                                                   (GPIO_B_DATA)
#define         SSD_HIGH_CTRL_PIN                                                   (GPIO_PIN_4)

/* **** MOTOR **** */

#define         MOTOR_CTRL                                                          (GPIO_C_CTRL)
#define         MOTOR_DATA                                                          (GPIO_C_DATA)
#define         MOTOR_PIN                                                           (GPIO_PIN_2)



#endif	/* HARDWARE_H */

