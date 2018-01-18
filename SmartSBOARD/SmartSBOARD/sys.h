/*
 * sys.h
 *
 * Created: September 2017
 *  Author: OBED
 */ 


#ifndef SYS_H_
#define SYS_H_

#include "keypad/keypad.h"
#include "switcher.h"

#define PRESCALER 8
#define CTC_MATCH_OVERFLOW ((F_CPU / 1000) / PRESCALER)

void timer_init();
void draw_splash();
void draw_menu();
void draw_frame();
void draw_pointer(unsigned char draw);
void draw_cursor(unsigned char x,unsigned char y, unsigned char color);
void pop_up_window();
int keyInput(int digits,unsigned char use);
void set_rtc();
void set_alarm(uint8_t alarm);
void keypress();
char *ftoa(char *buffer, double d, int precision);

	
void timer_init()
{
	cli();
	
	TCCR1B |= (1<<CS11)|(1<<WGM12);
	TIMSK |=(1<<OCIE1A);
	OCR1A = CTC_MATCH_OVERFLOW;//1200;
	TCNT1 = 0;	
	
	//External Interrupt
	GICR |=1<<INT0; //Enable External Interrupt INT0
	MCUCR |=1<<ISC01; //Falling edge on INT0 triggers interrupt.
	
	sei();
	return;
}

void draw_splash()
{
	GLCD_ScreenGraphics(splash);
	GLCD_Draw_String(4,55,"Tech 2017",BLACK);
	state = MENU;
}

void draw_menu()
{
	keypress();
	if (timer1_millis > 3000)
	{
		draw_pointer(TRUE);
		switch (state)
		{
			case MENU:
			if(pointer < 5)
			{
				draw_frame();
				GLCD_Draw_String(2,1,"MAIN-MENU",WHITE);
				GLCD_Draw_Char(15,1,'0',WHITE);
				GLCD_Draw_String(2,10,on_off,BLACK);
				GLCD_Draw_String(2,19,timer,BLACK);
				GLCD_Draw_String(2,29,meter,BLACK);
				GLCD_Draw_String(2,39,wifi,BLACK);			
			}
			break;
			case SWITCH:
			if(pointer < 5)
			{
				draw_frame();
				GLCD_Draw_String(2,1,"SWITCH-MENU",WHITE);
				GLCD_Draw_Char(15,1,'1',WHITE);
				GLCD_Draw_String(2,10,Lcir1,BLACK);
				GLCD_Draw_String(2,19,Lcir2,BLACK);
				GLCD_Draw_String(2,29,Scir1,BLACK);
				GLCD_Draw_String(2,39,Scir2,BLACK);
			
			}
			break;
			case TIMER:
			if(pointer < 5)
			{
				draw_frame();
				GLCD_Draw_String(2,1,"TIMER-MENU",WHITE);
				GLCD_Draw_Char(15,1,'2',WHITE);
				GLCD_Draw_String(2,10,clock_buffer,BLACK);
				GLCD_Draw_String(2,19,set_clock,BLACK);
				GLCD_Draw_String(2,29,timer1,BLACK);
				GLCD_Draw_String(2,39,timer2,BLACK);		  		
			}
			break;	
			case POPUP:
				pop_up_window();
			break;
			default:break;		
		}		
	}
}
void draw_pointer(unsigned char draw)
{
	if (timer1_millis > 3100)
	{
		if(draw == TRUE){GLCD_Draw_Char(1 ,(pointer*10)+10,'>',BLACK);}
		else if(draw == FALSE){GLCD_Draw_Char(1,(pointer*10)+10,' ',BLACK);}
	}
	return;
}

void draw_switch(uint8_t switchNo)
{
	GLCD_Draw_String(4,25,"ON",WHITE);
	GLCD_Draw_String(9,25,"OFF",WHITE);
	for (int w=50;w<70;w++)
	{
		for (int h=25; h<35;h++)
		{GLCD_Draw_Pixel(w,h,WHITE);}
	}
	if (switchNo == ON)
	{
		for (int w=51;w<60;w++)
		{
			for (int h=26; h<34;h++)
			{GLCD_Draw_Pixel(w,h,BLACK);}
		}
		GLCD_Draw_Char(8,38,'>',WHITE);
	} 
	else
	{
		for (int w=60;w<69;w++)
		{
			for (int h=26; h<34;h++)
			{GLCD_Draw_Pixel(w,h,BLACK);}
		}
		GLCD_Draw_Char(7,38,'<',WHITE);
	}
}

void draw_cursor(unsigned char x,unsigned char y, unsigned char color)
{
	GLCD_Draw_HorizLine(x,x+5,y,color);
}

void draw_frame()
{
		GLCD_ClearBuffer(WHITE);
		GLCD_Draw_HorizLine(0,128,0,BLACK);
		GLCD_Draw_HorizLine(0,128,63,BLACK);
		GLCD_Draw_VertcLine(0,0,64,BLACK);
		GLCD_Draw_VertcLine(127,0,64,BLACK);
		GLCD_Clear_Row(1,BLACK);
}

void keypress()
{
	switch(state)
	{
		case MENU:
			draw_pointer(TRUE);
			if (keys[0] == KEY_DOWN)
			{
				if(pointer >= menuend){ pointer = menuend;}
				else{pointer++;}
				draw_pointer(TRUE);
				
			} 
			else if(keys[0] == KEY_UP)
			{
				if(pointer <= 0){ pointer = 0;}
				else{pointer--;}
				draw_pointer(TRUE);
			}else if(keys[0] == KEY_SELECT)
			{
				switch(pointer)
				{
					case 0:	state=SWITCH;pointer = 0; break;
					case 1: state=TIMER;pointer = 1; break;
					case 2: state=POPUP;draw_pointer(TRUE);event= METER; break;
					case 3: state=CONNECTION;pointer = 0; break;
					default:break;
				}
				
			}
		break;
		case SWITCH:
			draw_pointer(TRUE);
			if (keys[0] == KEY_DOWN)
			{
				if(pointer >= menuend){ pointer = menuend;}
				else{pointer++;}
				draw_pointer(TRUE);
			}
			else if(keys[0] == KEY_UP)
			{
				if(pointer <= 0){ pointer = 0;}
				else{pointer--;}
				draw_pointer(TRUE);
			}
			else if(keys[0] == KEY_BACK)
			{
				state = MENU;
			}
			else if(keys[0] == KEY_SELECT)
			{
				state = POPUP;
				switch(pointer)
				{
	 				case 0:	event = SWITCHER_1; break;
					case 1: event = SWITCHER_2; break;
					case 2: event = SWITCHER_3; break;
					case 3: event = SWITCHER_4; break;
					default:break;
				}
				pointer = 0;
			}
		break;
		case TIMER:
			draw_pointer(TRUE);
			if (keys[0] == KEY_DOWN)
			{
				if(pointer >= menuend){ pointer = menuend;}
				else{pointer++;}
				draw_pointer(TRUE);
			}
			else if(keys[0] == KEY_UP)
			{
				if(pointer <= 0){ pointer = 0;}
				else{pointer--;}
				draw_pointer(TRUE);
			}
			else if(keys[0] == KEY_BACK)
			{
				state = MENU;
			}
			else if(keys[0] == KEY_SELECT)
			{
				state = POPUP;
				switch(pointer)
				{
					case 1:	event = SET_TIME ; break;
					case 2: event = ALARM_1; break; 
					case 3: event = ALARM_2; break;
					default:break;
				}
				pointer = 0;
			}
		break;
		case METER:
			if (keys[0] == KEY_BACK)
			{
				state = MENU;
			}
		break;
		case CONNECTION:
		break;
		case BOOT: break;
		default:
		break;
	}
	
	 if (state == POPUP)
	 {
		 switch (event)
		 {
			 case SET_TIME:
				if (keys[0] == KEY_BACK)
				{state = TIMER;}
			 break;
			 case SWITCHER_1: case SWITCHER_2: case SWITCHER_3: case SWITCHER_4:
				 if (keys[0] == KEY_LEFT)
				 { switcher(ON,event);}
				 else if (keys[0] == KEY_RIGHT)
				 { switcher(OFF,event);/*switch1 = OFF;*/}
				 else if (keys[0] == KEY_BACK)
				 {state = SWITCH;}
			 break;
			 case METER:
				if (keys[0] == KEY_BACK)
				{ state = MENU;}
			 break;
			 default: break;
		 }
	 }
}
void pop_up_window()
{
	draw_pointer(FALSE);
	for (int w=23;w<112;w++)
	{
		for (int h=10; h<56;h++)
		{
			GLCD_Draw_Pixel(w,h,BLACK);
		}
	}	
	char watts_buffer[5];
	char Kwatts_buffer[5];
	switch (event)
	{
		case SET_TIME:
			GLCD_Draw_String(5,25,"HH:MM",WHITE); 
			set_rtc();
		break;
		case ALARM_1:
			GLCD_Draw_String(5,25,"HH:MM",WHITE);
			set_alarm(ALARM_1);
		break;			
		case ALARM_2:
			GLCD_Draw_String(5,25,"HH:MM",WHITE);
			set_alarm(ALARM_2);
		break;
		case SWITCHER_1:
			GLCD_Draw_String(5,15,"Lights1",WHITE); 
			draw_switch(switch1);
		break;
		case SWITCHER_2:
			GLCD_Draw_String(5,15,"Lights2",WHITE);
			draw_switch(switch2);
		break;
		case SWITCHER_3:
			GLCD_Draw_String(4,15,"Sockets1",WHITE);
			draw_switch(switch3);
		break;
		case SWITCHER_4:
			GLCD_Draw_String(4,15,"Sockets2",WHITE);
			draw_switch(switch4);
		break;
		case METER:
			ftoa(watts_buffer,watts,2);
			ftoa(Kwatts_buffer,kilo_watts,2);
			GLCD_Draw_String(3,15,"Energy Used",WHITE);
			
			GLCD_Draw_String(10,25,"KW",WHITE);
			GLCD_Draw_String(4,25,Kwatts_buffer,WHITE);
			
			GLCD_Draw_String(4,35,watts_buffer,WHITE);
			GLCD_Draw_String(10,35,"W",WHITE);
		break;
		default:
		break;
	}		
}

void set_rtc()
{
	while (state == POPUP)
	{
		int hour=0,minute=0;
		int loop=0;
		GLCD_Draw_String(3,15,clock_buffer,WHITE);
		draw_cursor(40,41,WHITE);
		draw_cursor(48,41,WHITE);
		draw_cursor(64,41,WHITE);
		draw_cursor(72,41,WHITE);
		
		GLCD_Render();
		while (loop<2)
		{
			switch (loop)
			{
				case 0:
					GLCD_Draw_String(3,15,clock_buffer,WHITE);
					hour = keyInput(2,HOUR);
					if (hour>12) {SetHour(hour-12);
						SetAmPm(1)/*PM*/; }
					else {SetHour(hour);
						SetAmPm(0);/*AM*/ }
				break;
				case 1:
					GLCD_Draw_String(3,15,clock_buffer,WHITE);
					minute = keyInput(2,MINUTE);
					SetMinute(minute);
				break;
				default: ;break;
			}
			loop++;
		}
		GLCD_Draw_String(4,41,"TIME SET!",WHITE);
		state = MENU;		
	}
}
int keyInput(int digits,unsigned char use)
{
	int i=0, num=0;
	while ( i < digits )
	{
				
		if (key >=0)
		{
			switch (i)
			{
				case 0:	num=key; //one digit
				break;
				case 1: num = (num*10)+(key); //2 digit
				break;
				case 2:	num = (num*10)+(key);// 3 digit
				break;
				case 3: num = (num*10)+(key);
				break;
				default:  break;
			}
			switch (use)
			{
				case HOUR:
				if (i ==0)
				{	itoa(key,s1,10);
					GLCD_Render();
					GLCD_Draw_String(5,33,s1,WHITE);
					GLCD_Render();
				}
				else if (i==1) { itoa(key,s2,10);
					GLCD_Draw_String(6,33,s2,WHITE);
					GLCD_Render();
				}
				break;
				case MINUTE:
				if (i ==0){itoa(key,s3,10);
					GLCD_Draw_String(8,33,s3,WHITE);
					GLCD_Render();
				}
				else if (i==1) { itoa(key,s4,10);
					GLCD_Draw_String(9,33,s4,WHITE);
					GLCD_Render();
				}
				break;
			}
			key=-1;
			i++;
		}
	}
	return num;
}
void set_alarm(uint8_t alarm)
{
	while (state == POPUP)
	{
		int loop=0;
// 		char h[2];
// 		itoa(hour1,h,10);
//		GLCD_Draw_String(3,15,h,WHITE);
		GLCD_Draw_String(3,15,clock_buffer,WHITE);
		draw_cursor(40,41,WHITE);
		draw_cursor(48,41,WHITE);
		draw_cursor(64,41,WHITE);
		draw_cursor(72,41,WHITE);
		
		GLCD_Render();
		
		while (loop<2)
		{
			switch (loop)
			{
				case 0:					
					if (alarm == ALARM_1)
					{ hour1 = keyInput(2,HOUR);	EEPROM_WriteNBytes(hour1_addr,(uint8_t *)&hour1,1);} 
					else if (alarm == ALARM_2)
					{ hour2 = keyInput(2,HOUR); EEPROM_WriteNBytes(hour2_addr,(uint8_t *)&hour2,1);	}
									
				break;
				case 1:
					if (alarm == ALARM_1)
					{ min1 = keyInput(2,MINUTE);EEPROM_WriteNBytes(min1_addr,(uint8_t *)&min1,1);}
					else if (alarm == ALARM_2)
					{ min2 = keyInput(2,MINUTE);EEPROM_WriteNBytes(min2_addr,(uint8_t *)&min2,1);}					
				break;
				default: ;break;
			}
			loop++;
		}
		GLCD_Draw_String(3,41,"ALARM1 SET",WHITE);
		state = TIMER;
	}
}
char *ftoa(char *buffer, double d, int precision)
{

	long wholePart = (long) d; 	// Deposit the whole part of the number.

	itoa(wholePart,buffer,10);

	// Now work on the faction if we need one.
	if (precision > 0) {

		// We do, so locate the end of the string and insert a decimal point.

		char *endOfString = buffer;
		while (*endOfString != '\0') endOfString++;
		*endOfString++ = '.';
		// Now work on the fraction, be sure to turn any negative
		// values positive.

		if (d < 0) {
			d *= -1;
			wholePart *= -1;
		}
		
		double fraction = d - wholePart;
		while (precision > 0) {

			// Multiply ten and pull out the digit.
			fraction *= 10;
			wholePart = (long) fraction;
			*endOfString++ = '0' + wholePart;

			// Update the fraction and move on to the next digit.
			fraction -= wholePart;
			precision--;
		}
		// Terminate the string.
		*endOfString = '\0';
	}
	return buffer;
}

#endif /* SYS_H_ */