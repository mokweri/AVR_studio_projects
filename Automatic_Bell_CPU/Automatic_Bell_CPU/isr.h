
/*
 * isr.h
 *
 * Created: 12/28/2017 10:37:41 AM
 *  Author: OBED
 */ 


#ifndef ISR_H_
#define ISR_H_

ISR(TIMER1_COMPA_vect)
{
	timer1_millis++;
	key = read_keypad();
	
	if (timer1_millis%150 == 0)
	{keypress();}
	
	
	switch(key)
	{
		case '0': key_int =0; break;
		case '1': key_int =1; break;
		case '2': key_int =2; break;
		case '3': key_int =3; break;
		case '4': key_int =4; break;
		case '5': key_int =5; break;
		case '6': key_int =6; break;
		case '7': key_int =7; break;
		case '8': key_int =8; break;
		case '9': key_int =9; break;
		case 'A': key_int =10; break;
		case 'B': key_int =11; break;
		case 'C': key_int =12; break;
		case 'D': key_int =13; break;
		case '*': key_int =14; break;
		case '#': key_int =15; break;
		default: key_int=-1; break; //No input
	}
}
ISR(PCINT1_vect)
{
	// 	key =read_keypad();
	// 	SPI_Transmit(key);
}
#endif /* ISR_H_ */