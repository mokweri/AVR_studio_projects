/*
 * Vars.h
 *
 * Created: 9/3/2017 4:20:26 PM
 *  Author: OBED
 */ 


#ifndef VARS_H_
#define VARS_H_
//---------------------Status---------------------
#define home	0

//---------------------State---------------------
#define BOOT		0
#define MENU		1
#define SWITCH		2
#define TIMER		3
#define METER		4
#define CONNECTION	5
#define POPUP		6
#define OFFMENU		7

//---------------- Events----------------------
#define SET_TIME	10
#define ALARM_1		11
#define ALARM_2		12
#define SWITCHER_1	13
#define SWITCHER_2	14
#define SWITCHER_3	15
#define SWITCHER_4	16

//----------------------------------------

#define KEY_UP		'A'
#define KEY_DOWN	'B'
#define KEY_LEFT	'C'
#define KEY_RIGHT	'D'
#define KEY_SELECT	'#'
#define KEY_BACK	'*'

//--------------Input values----------
#define HOUR	15
#define MINUTE	16
#define AMPM	17


#define FALSE		0x00
#define TRUE		0xFF

//-----------Global-----------------
volatile unsigned long system_count = 0;
volatile unsigned long timer1_millis = 0;
volatile unsigned long pulse_count = 0;
volatile float watts=0;
volatile float kilo_watts=0;


volatile unsigned short	pointer  = 0;
volatile unsigned char	status = home;
volatile unsigned char state = BOOT;
volatile char	keys[] = "255";
unsigned char menuend = 3;
volatile unsigned char event;
volatile unsigned char blink_state;

volatile int key;
// Switch states
#define sw1 1
#define sw2 2
#define sw3 3
#define sw4 4
volatile uint8_t switch1 =0;
volatile uint8_t switch2 = 0;
volatile uint8_t switch3 = 0;
volatile uint8_t switch4 = 0;
volatile uint8_t switch5 = 0;

//Alarm values
volatile uint8_t hour1;  //Alarm1 hour value
volatile uint8_t min1;
volatile uint8_t hour2;  //Alarm1 hour value
volatile uint8_t min2;

volatile uint8_t beep_state = 0;
volatile uint8_t beep_counter=0;

//----input values buffers------------------
char s1[1],s2[1],s3[1],s4[1];

//------EEPROM Locations Addresses---------------
#define switch1_addr 0x00
#define switch2_addr 0x01
#define switch3_addr 0x02
#define switch4_addr 0x03
#define switch5_addr 0x04

#define hour1_addr 0x05
#define hour2_addr 0x06
#define min1_addr  0x07
#define min2_addr  0x08

#define pulse_count_addr 0x09   //Take like 3 bytes


//------SPI Flags--------------------
    /*Switches*/
#define switch1_ON	'a'
#define switch1_OFF 'b'
#define switch2_ON	'c'
#define switch2_OFF 'd'
#define switch3_ON	'e'
#define switch3_OFF 'f'
#define switch4_ON	'g'
#define switch4_OFF 'h'
#define Meter_flag  'i'
	/* Meter readings */





#endif /* VARS_H_ */