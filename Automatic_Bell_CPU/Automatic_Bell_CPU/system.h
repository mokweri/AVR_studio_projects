/*
 * system.h
 *
 * Created: 12/28/2017 10:32:00 AM
 *  Author: OBED
 */ 


#ifndef SYSTEM_H_
#define SYSTEM_H_


#include "keypad.h"

#define PRESCALER 8
#define CTC_MATCH_OVERFLOW ((F_CPU / 1000) / PRESCALER)

void timer_init();
void draw_splash();
void draw_menu();
void keypress();

void timer_init()
{
	cli();	
	TCCR1B |= (1<<CS11)|(1<<WGM12);
	TIMSK1 |=(1<<OCIE1A);
	OCR1A = CTC_MATCH_OVERFLOW;//1200;
	TCNT1 = 0;

	sei();
	return;
}
void draw_splash()
{
	SPI_Transmit(splash_flag); //Send flag/command to display
}
void keypress()
{
  if (key_int>=0 && Active == FALSE)
  {
    Active = TRUE;
  }else if (key_int>=0 && Active == TRUE)
  {
    switch(STATE)
    {
      case MENU:        
		SPI_Transmit(menu_flag);
		if (multi_press == TRUE)
		{
			if (key == KEYUP) {	SPI_Transmit(UP); if(pointer>0) {pointer--;}}
			if (key == KEYDOWN) { SPI_Transmit(DOWN);if(pointer<2) {pointer++;}}
			if (key == KEYSELECT) 
			{ 
				SPI_Transmit(SELECT);
				switch(pointer)
				{
  					case 0:/*STATE = POPUP*/ STATE = SET_TIME;break;
  					case 1: STATE = VIEW_SCHEDULE;	break;
  					case 2:	STATE = HOMESCREEN;		break;
				}
			}
			//if (key == KEYBACK) { SPI_Transmit(BACK);}
		}
		multi_press = TRUE;
      break;
      case SET_TIME:
		set_rtc();      
      break;
      case HOMESCREEN:
		if (key_int>0) {STATE = MENU; multi_press =TRUE;}
      break;
    }

  }
}
#endif /* SYSTEM_H_ */