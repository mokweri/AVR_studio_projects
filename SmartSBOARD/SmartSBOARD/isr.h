/*
 * isr.h
 *
 * Created: 9/3/2017 3:46:44 PM
 *  Author: OBED
 */ 


#ifndef ISR_H_
#define ISR_H_

ISR(TIMER1_COMPA_vect)
{
	timer1_millis++;
	keys[0] = read_keypad();
	
	if (timer1_millis%165 == 0)
	{keypress();}
	
	
	//Energy calculations
	if (timer1_millis%1000 == 0) //1second
	{watts +=((pulse_count)/3600);
	kilo_watts += ((pulse_count/1000)/3600);
	//transmitAndWait(Meter_flag);
	//transmitAndWait(watts);
	}
	
	switch(keys[0])
	{
		case '0': key =0; break;
		case '1': key =1; break;
		case '2': key =2; break;
		case '3': key =3; break;
		case '4': key =4; break;
		case '5': key =5; break;
		case '6': key =6; break;
		case '7': key =7; break;
		case '8': key =8; break;
		case '9': key =9; break;
		case 'C': key =10; break;
		default: key=-1; break; //No input
	}	
}

ISR(INT0_vect)
{
	pulse_count++;
	EEPROM_WriteNBytes(pulse_count_addr,(uint8_t *)&pulse_count,2);
}
#endif /* ISR_H_ */