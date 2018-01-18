/*
 * Flags.h
 *
 * Created: December 2017
 *  Author: OBED
 */ 


#ifndef FLAGS_H_
#define FLAGS_H_


// #define SET 1 // use ONN/OFF
// #define CLEAR 0

#define X_Axis	x
#define Y_Axis	y

#define  TRUE  0xFF
#define  FALSE 0x00

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


volatile char waiting =0;
volatile char waiter;

volatile char key;
volatile uint8_t pointer=0;

//STATE
volatile uint8_t STATE = 0;
volatile uint8_t event = 0;
#define clock			50
#define splash			51
#define MENU			52
#define POPUP			53
#define SET_TIME		54
#define VIEW_SCHEDULE	55
#define HOMESCREEN		56

//screen position
volatile char x_axis_flag =0 ;
volatile char y_axis_flag =0 ;

//Time
volatile char hour =0;
volatile char min =0;
volatile char sec =0;
volatile char ampm =0;
//set time inputs
volatile char hour1 ='0';
volatile char hour2 ='0';
volatile char min1 ='0';
volatile char min2 ='0';


//Date
volatile char date =0;
volatile char day =0;
volatile char month =0;
volatile char year = 0;

// Schedule Array
volatile char scheduleTable[30][2]={{'0','1'},
	                                {'0','2'}};







#endif /* FLAGS_H_ */