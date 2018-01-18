/*
 * RTC.cpp
 *
 * Created: 5/12/2017 5:11:07 AM
 * Author : OBED
 */ 

#define F_CPU 1000000UL

#include <avr/io.h>
#include <stdlib.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include <string.h>
#include "myLCD.c"
#include "rtc.c"
#include "keypad.h"

void menu_control();
void myalarm();
void setMyDate();
void setMyTime();
int intFrmKeypad(int digits);
int menu_item =0;


void delay1s(void)
{
	uint8_t i;
	for(i=0;i<100;i++)
	{
		_delay_ms(10);
	}
}

int main(void)
{
	LCDinit();
	LCDclr();
	I2CInit();	
	ClockInit();	
	DDRA = 0x0f;  //Initialize Keypad Port
	PORTA = 0xff;
	
	DDRB |=1<<PINB0;  // Relay/switch pin
	PORTB |=1<<PINB0;

	char time_buffer[11];
	char buffer1[10];
				
	while(1)
	{
		menu_item =read_keypad_int();
		itoa(menu_item,buffer1,10);
		//LCD_PrintString(buffer1,0,1);
		while (menu_item ==255)
		{
			GetTimeString(time_buffer);
			//itoa(m,buffer1,10);
			LCD_PrintString("CLOCK++",0,0);
			LCD_PrintString(time_buffer,0,1);
			myalarm();
		}
		menu_control();
		myalarm();
	}
	return 0;
}

void menu_control()
{
	menu_item =read_keypad_int();
	
	LCDclr();
	LCD_PrintString("MENU: 1-SetDate,",0,0);
	LCD_PrintString("2-tTime 3-setAlam",0,1);
	
	
	while (menu_item>0) //Menu Driver
	{
		switch(menu_item)
		{
			case 1: //set date
			setMyDate();
			break;
			case 2:
			setMyTime();
			break;
			case 3:
			break;
			default:
			menu_item = 0;
			break;
		}
		menu_item = 0;
	}
	
}
void setMyDate()
{
	//set date, month and year
	//Use keypad input
	int date=0,month=0,year=0;
	int loop=0;
			
	while (loop<3)
	{
		switch (loop)
		{
			case 0:
				LCDclr();
				LCD_PrintString("Enter Date:",0,0);
				date = intFrmKeypad(2);
				SetDate(date);
						
			break;
			case 1:
				LCDclr();
				LCD_PrintString("Enter Month:",0,0);
				month = intFrmKeypad(2);
				SetMonth(month);
			break;
			case 2:
				LCDclr();
				LCD_PrintString("Enter Year(17):",0,0);
				year = intFrmKeypad(2);
				SetYear(year);
				
			break;
			default:
			break;
		}		
		loop++;
	}	
	LCDclr();
	LCD_PrintString("OK: Date set.",0,0);
	_delay_ms(2000);
	LCDclr();
	menu_item =0;
}
void setMyTime()
{
	//set hour, minute and AM/PM
	//Use keypad input
	int hour=0,minute=0,AM_PM=0;
	int loop=0;
	
	while (loop<3)
	{
		switch (loop)
		{
			case 0:
			LCDclr();
			LCD_PrintString("Enter Hour:",0,0);
			hour = intFrmKeypad(2);
			SetHour(hour);
			
			break;
			case 1:
			LCDclr();
			LCD_PrintString("Enter Minute:",0,0);
			minute = intFrmKeypad(2);
			SetMinute(minute);
			break;
			case 2:
			LCDclr();
			LCD_PrintString("Select 0:AM, 1:PM",0,0);
			AM_PM = intFrmKeypad(1);
			SetAmPm(AM_PM);
			
			break;
			default:
			break;
		}
		loop++;
	}
	LCDclr();
	LCD_PrintString("OK: Time set.",0,0);
	_delay_ms(2000);
	LCDclr();
}
int intFrmKeypad(int digits)  //gives up to 4 digits for now
{
	int i=0, num=0;
	char s[4];
	 
	while ( i < digits)
	{
		int key =read_keypad_int();
		if (key != 0xff)
		{
			switch (i)
			{
				case 0:
					num=key; //one digit
				break;
				case 1:
					num = (num*10)+(key); //2 digit
				break;
				case 2:
					num = (num*10)+(key);// 3 digit
				break;
				case 3:
					num = (num*10)+(key);
				break;
				default:
				break;
			 }
			int k = key;
			itoa(k,s,10);
			LCD_PrintString(s,i,1);
			_delay_ms(200);	
			i++;		
		}		
	}
	return num;
}

void myalarm()
{
	uint8_t hh=5,mm=04,ampm=1;
			
	if ((hh==GetHour()) && (mm==GetMinute()))
	{
		PORTB &=~1<<PINB0; // Close the relay. ON SWITCH
		
	}
}