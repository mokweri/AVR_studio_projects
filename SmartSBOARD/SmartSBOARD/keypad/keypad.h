/*
 * keypad.h
 *
 * Created: 5/5/2017 4:54:08 PM
 *  Author: OBED
 */ 

#ifndef KEYPAD_H_
#define KEYPAD_H_

#include <avr/io.h>
#include <util/delay.h>


#ifndef KEYPAD_PORT
	# define KEYPAD_PORT PORTA
#endif
#ifndef KEYPAD_DIR
	# define KEYPAD_DIR	DDRA
#endif
#ifndef KEYPAD_PIN
	# define KEYPAD_PIN	PINA
#endif


char read_keypad(void);
void keypad_init (void);


void keypad_init (void)
{
	KEYPAD_DIR = 0x0f;  //Initialize Keypad Port
	KEYPAD_PORT = 0xff;
}
char read_keypad(void)
{
	unsigned char keypad_input=0xff,keypad_output=' ';
	KEYPAD_PORT=0xfe;
	_delay_us(2);
	keypad_input=KEYPAD_PIN & 0xf0;

	if(keypad_input==0xe0)
	keypad_output = '1';
	else if(keypad_input==0xd0)
	keypad_output= '2';
	else if(keypad_input==0xb0)
	keypad_output= '3';
	else if(keypad_input==0x70)
	keypad_output= 'A';
	else
	;

	KEYPAD_PORT=0xfd;
	_delay_us(2);
	keypad_input=KEYPAD_PIN & 0xf0;

	if(keypad_input==0xe0)
	keypad_output= '4';
	else if(keypad_input==0xd0)
	keypad_output= '5';
	else if(keypad_input==0xb0)
	keypad_output= '6';
	else if(keypad_input==0x70)
	keypad_output= 'B';
	else
	;

	KEYPAD_PORT=0xfb;
	_delay_us(2);
	keypad_input=KEYPAD_PIN & 0xf0;

	if(keypad_input==0xe0)
	keypad_output= '7';
	else if(keypad_input==0xd0)
	keypad_output= '8';
	else if(keypad_input==0xb0)
	keypad_output= '9';
	else if(keypad_input==0x70)
	keypad_output= 'C';
	else
	;
	
	KEYPAD_PORT=0xf7;
	_delay_us(2);
	keypad_input=KEYPAD_PIN & 0xf0;

	if(keypad_input==0xe0)
	keypad_output= '*';
	else if(keypad_input==0xd0)
	keypad_output= '0';
	else if(keypad_input==0xb0)
	keypad_output= '#';
	else if(keypad_input==0x70)
	keypad_output='D';
	else
	;
	return keypad_output;
}

#endif /* KEYPAD_H_ */