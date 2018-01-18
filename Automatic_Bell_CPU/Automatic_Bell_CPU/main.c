/*
 * Automatic_Bell_CPU.c
 *
 * Created: 12/24/2017 5:20:10 PM
 * Author : OBED
 */ 
#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "Vars.h"
#include "SPI_Master.h"
#include "keypad.h"
#include "rtc.h"
#include "functions.h"
#include "system.h"
#include "isr.h"
#include "eeprom/eeprom.h" 

void Initialize(void);

int main(void)
{
    Initialize();
	
    while (1) 
    {
      Read_RTC();      
   
		if (STATE == HOMESCREEN)
		{		
			send_rtcToDispaly();			
		}
	///	SPI_Transmit(key);
    }
}
void Initialize(void)
{
	SPI_Init();
	keypad_init();
	ClockInit();
	timer_init();
	draw_splash();
}
