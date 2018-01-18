/*
 * GLCD_128x64.c
 *
 * Created: 8/27/2017 9:29:39 AM
 * Author : OBED
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <stdlib.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <util/delay.h>


#include "display/bitmaps.h"
#include "display/images.h"
#include "Vars.h"
#include "eeprom/eeprom.h"
#include "strings.h"
#include "interface/i2c.h"
#include "interface/SPI_Master.h"
#include "rtc/rtc.h"
#include "display/ST7920.h"
#include "sys.h"
#include "isr.h"
#include "eeprom2.h"

void boot(void);

int main(void)
{
    boot();	
	unsigned char data = 0;
	unsigned char send = 5;
	DDRC |=(1<<PC3);
    while (1) 
    {
// 		uint8_t a,b;
// 		char as[1],bs[1];
 		//check_alarm();
 		GetTimeString(clock_buffer);
 		draw_menu();
		//----------------
		data = transmitAndWait('a');

		if (data == 200)
		{
			PORTC |=(1<<PC3);
		}
		//-----------------
 		
		GLCD_Render();
    }
}

 void boot(void)
 {
	  I2CInit();
	  SPI_Init();
	  ClockInit();
	  GLCD_Init();
	  timer_init();
	  draw_splash();
	  keypad_init();
	  
	  //initial_EEPROM_Write();
	  //initial_EEPROM_Read();
	  state = MENU;	
 }
