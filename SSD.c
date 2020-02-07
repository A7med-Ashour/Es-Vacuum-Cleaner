#include "SSD.h"
#include "GPIO.h"
#include "HARDWARE.h"

#define         ANODE                                                               (1)
#define         CATHODE                                                             (0)
#define         SSD_NUMBERS                                                         (3)
#define         N_SYMBOLS                                                           (11)
#define         SSD_COMMON                                                          (CATHODE)
#define         SSD_ON_LEVEL                                                        (GPIO_HIGH)
#define         SSD_OFF_LEVEL                                                       (GPIO_LOW)
#define         SSD_UPDATE_PERIOD_MS                                                (10) // 10 ms
#define         DOT_PIN                                                             (GPIO_PIN_7)

typedef struct {
    tByte * data_direction_reg;
    tByte * data_value_reg;
    tByte * ctrl_direction_reg;
    tByte * ctrl_value_reg;
    tByte ctrl_pin;
    tByte val;
    tSSD_SYMBOL symbol;
}tSSD_INFO;

/* PRIVATE VARIBLES */

static tSSD_INFO ssd_data[SSD_NUMBERS];
static tSSD current_ssd = SSD_LOW;

#if (SSD_COMMON == CATHODE)
static tByte ssd_decoder[N_SYMBOLS] = {0X3F,0X06,0X5B,0X4F,0X66,0X6D,0X7D,0X07,0X7F,0X6F,0X00};//   COMMON CATHODE
#elif (SSD_COMMON == ANODE)
static tByte ssd_decoder[N_SYMBOLS] = {0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90,0xFF}; //  COMMON  ANODE
#endif


/* **** PRIVATE FUNCTIONS **** */
static void SSD_schematic_init(void);
static void SSD_on(tSSD);
static void SSD_off(tSSD);
/* **** END : PRIVATE FUNCTIONS **** */

void SSD_init(tSSD ssd){
    
     SSD_schematic_init();
    // MAKE DATA PINS OUTPUT
    GPIO_PORT_DIRECTION(*(ssd_data[ssd].data_direction_reg),GPIO_OUTPUT);
    
    // WRITE NOTHING ON DATA PINS;
    SSD_display(ssd , 0x00);
    
    // MAKE CTRL PIN OUTPUT AND MAKE IT OFF
    GPIO_PIN_DIRECTION(*(ssd_data[ssd].ctrl_direction_reg),ssd_data[ssd].ctrl_pin,GPIO_OUTPUT);
    GPIO_PIN_WRITE(*(ssd_data[ssd].ctrl_value_reg),ssd_data[ssd].ctrl_pin,SSD_OFF_LEVEL);
     
    
}
void SSD_setSymbol(tSSD ssd, tSSD_SYMBOL symbol){
    ssd_data[ssd].symbol = symbol;
}
tSSD_SYMBOL SSD_getSymbol(tSSD ssd){
    return ssd_data[ssd].symbol;
}

void SSD_setVal(tSSD ssd, tByte val){
    ssd_data[ssd].val = val;
}
void SSD_update(void){
    static tByte ssd_update_counter = 0;
    
    ssd_update_counter += SYSTEM_TICK;
    
    if (ssd_update_counter == SSD_UPDATE_PERIOD_MS){
        ssd_update_counter = 0;
        
         tByte index = 0;
    
        // TURN OFF ALL SSDS

        for(index = SSD_LOW; index < SSD_NUMBERS; index++){
            SSD_off(index);
        }

        // DISPLAY CURRENT SSD DATA
         
      SSD_display(current_ssd,ssd_data[current_ssd].val);
        
        
        // TURN ON CURRENT SSD

        SSD_on(current_ssd);

        // CURRENT SSD = NEXT SSD

        current_ssd++;
        current_ssd = current_ssd % SSD_NUMBERS;
    
    }else {
        // Do nothing
    }
   
}

static void SSD_schematic_init(void){
    /* *** CREATE YOUR SSD HERE *** */
    
     ssd_data[0] = (tSSD_INFO){&SSD_LOW_DATA_DIR,&SSD_LOW_DATA_VAL,&SSD_LOW_CTRL_DIR,&SSD_LOW_CTRL_VAL,SSD_LOW_CTRL_PIN,0x00,SSD_NULL}; 
     ssd_data[1] = (tSSD_INFO){&SSD_MID_DATA_DIR,&SSD_MID_DATA_VAL,&SSD_MID_CTRL_DIR,&SSD_MID_CTRL_VAL,SSD_MID_CTRL_PIN,0x00,SSD_NULL};
     ssd_data[2] = (tSSD_INFO){&SSD_HIGH_DATA_DIR,&SSD_HIGH_DATA_VAL,&SSD_HIGH_CTRL_DIR,&SSD_HIGH_CTRL_VAL,SSD_HIGH_CTRL_PIN,0x00,SSD_NULL};
     /* *** END : CREATE YOUR SSD HERE *** */
     
}


void SSD_display(tSSD ssd , tByte data){
    GPIO_PORT_WRITE(*(ssd_data[ssd].data_value_reg),data);
}


static void SSD_on (tSSD ssd){
    GPIO_PIN_WRITE(*(ssd_data[ssd].ctrl_value_reg),ssd_data[ssd].ctrl_pin,SSD_ON_LEVEL);
}

static void SSD_off(tSSD ssd){
    GPIO_PIN_WRITE(*(ssd_data[ssd].ctrl_value_reg),ssd_data[ssd].ctrl_pin,SSD_OFF_LEVEL);
}




