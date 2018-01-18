/*
 * SPI_GLCD_Controller.c
 *
 * Created: December 2017
 
 * Author : OBED
 */ 
#define F_CPU 16000000UL

#include <avr/io.h>
#include <stdlib.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <string.h>
#include <util/delay.h>
#include "ST7920.h"
#include "bitmaps.h"
#include "SPI_slave.h"
#include "Flags.h"
#include "Functions.h"

volatile int r=0;
int main(void)
{
	GLCD_Init();	
    SPI_Init();
	
    while (1) 
    {
// 		pointer=2;
// 		STATE =MENU;
// 		event = SET_TIME;		
		switch (STATE)
		{
			case HOMESCREEN: clock_display(); break;
			case MENU: 	draw_menu(); break;
			case VIEW_SCHEDULE: draw_frame(); drawSchedule(); break;
			case POPUP: pop_up_window(); break;
			case clock: clock_display(); break;
			case splash: draw_splash();  break;
		}
		//draw_pointer(TRUE);
		//GLCD_Draw_Char(0,1,key,BLACK);		
		GLCD_Render();
    }
}
ISR(SPI_STC_vect)
{
	char received = SPDR;
	
	if (waiting == ON)
	{
		switch (waiter)
		{
			case rtc_hour : hour =received; waiting =OFF; break;
			case rtc_min : 	min =received;	waiting =OFF; break;
			case rtc_sec : 	sec =received; 	waiting =OFF; break;
			case rtc_ampm : ampm =received; waiting =OFF; break;
			case set_hour1: hour1 = received; waiting =OFF; break;
			case set_hour2: hour2 = received; waiting =OFF; break;
			case set_min1: min1 = received; waiting =OFF; break;
			case set_min2: min2 = received; waiting =OFF; break;      
      
			case menu_flag:
				if (received == UP)	{ if(pointer>0) {pointer--;}} 
				else if (received == DOWN){ if(pointer<2) {pointer++;}}
				else if (received == SELECT)
				{
					switch(pointer)
					{
						case 0: STATE = POPUP; event = SET_TIME; break;
						case 1: STATE = VIEW_SCHEDULE; 	break;
						case 2: STATE = HOMESCREEN; 	break;      
					} 
					waiting = OFF;        
				}
			break;
		}	
	} else{	//New interrupt
		switch (received)
		{
			case rtc_hour:	waiting=ON;	waiter =rtc_hour; break;
 			case rtc_min:	waiting=ON;	waiter =rtc_min;  break;
			case rtc_sec:	waiting=ON;	waiter =rtc_sec;  break;
			case rtc_ampm:	waiting=ON;	waiter =rtc_ampm; break;
			case splash_flag: STATE = splash;	break;
			case clock_flag:  STATE = clock; 	break;
			case menu_flag:   STATE = MENU;	waiting= ON; waiter = menu_flag; break;
			case set_hour1: waiting = ON; waiter = set_hour1; break;
			case set_hour2: waiting = ON; waiter = set_hour2; break;
			case set_min1: waiting = ON; waiter = set_min1; break;
			case set_min2: waiting = ON; waiter = set_min2; break;
			default:			 		
			break;
		}
		key=received;	
	}
}