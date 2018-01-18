/*
 * Vars.h
 *
 * Created: December 2017
 *  Author: OBED
 */ 


#ifndef VARS_H_
#define VARS_H_
//Flags
#define rtc_hour	'h'
#define rtc_min		'm'
#define rtc_sec		's'
#define rtc_ampm	'p'
#define clock_flag	'c'
#define splash_flag	'd'
#define menu_flag	'a'
#define UP			'u'
#define DOWN		'v'
#define SELECT		'k'
#define BACK		'b'
#define set_hour1	'e'
#define set_hour2	'f'
#define set_min1	'g'
#define set_min2	'i'
#define set_ampm	'j'

#define KEYUP		'A'
#define KEYDOWN		'B'
#define KEYSELECT	'#'
#define KEYBACK		'*'

volatile uint8_t pointer=0;

volatile unsigned long timer1_millis = 0;
volatile char key;
volatile int key_int;

#define TRUE	0xFF
#define FALSE	0x00

volatile char Active= FALSE;
volatile char multi_press = FALSE;

//STATE
#define clock			50
#define splash			51
#define MENU			52
#define POPUP			53
#define SET_TIME		54
#define VIEW_SCHEDULE	55
#define HOMESCREEN		56
#define HOUR			57
#define MINUTE			58
#define AMP				59

volatile uint8_t STATE = MENU;
volatile uint8_t event = 0;

//time
volatile uint8_t h;
volatile uint8_t m;
volatile uint8_t s;
volatile uint8_t ampm;

//Date
volatile uint8_t date;
volatile uint8_t day;
volatile uint8_t month;
volatile uint8_t year;

#endif /* VARS_H_ */