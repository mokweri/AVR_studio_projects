/*
 * switcher.h
 *
 * Created: 11/7/2017 6:00:51 PM
 *  Author: OBED
 */ 


#ifndef SWITCHER_H_
#define SWITCHER_H_

void switcher(unsigned char ON_OFF, uint8_t switcher);

void switcher(unsigned char ON_OFF, uint8_t switcher)
{
	switch (switcher)
	{
		case SWITCHER_1: switch1 = ON_OFF; EEPROM_WriteNBytes(switch1_addr,(uint8_t *)&ON_OFF,1);
			if (ON_OFF==ON){ transmitAndWait(switch1_ON);}else{transmitAndWait(switch1_OFF);} break;
		case SWITCHER_2: switch2 = ON_OFF; EEPROM_WriteNBytes(switch2_addr,(uint8_t *)&ON_OFF,1);
			if (ON_OFF==ON){ transmitAndWait(switch2_ON);}else{transmitAndWait(switch2_OFF);} break;
		case SWITCHER_3: switch3 = ON_OFF; EEPROM_WriteNBytes(switch3_addr,(uint8_t *)&ON_OFF,1); 
			if (ON_OFF==ON){ transmitAndWait(switch3_ON);}else{transmitAndWait(switch3_OFF);} break;
		case SWITCHER_4: switch4 = ON_OFF; EEPROM_WriteNBytes(switch4_addr,(uint8_t *)&ON_OFF,1); 
			if (ON_OFF==ON){ transmitAndWait(switch4_ON);}else{transmitAndWait(switch4_OFF);} break;
		default: break;
	}
}

void check_alarm()
{
// 	uint8_t am_pm=0;
// 	if (hour1>=12)
// 	{ am_pm =1;}
// 	if (hour2>=12)
// 	{ am_pm =1;}
// 		
// 	if (hour1>12)
// 	{ hour1 -=12;}
// 	if (hour2>12)
// 	{ hour2 -=12;}

	// check alarm1 first
	if ( hour1 == GetHour() && min1== GetMinute() )/* (am_pm == GetAmPm())*/
	{
			state = POPUP;
			PORTC |=1<<PC7;
			
		//switcher(ON,SWITCHER_1);
	}
	//check alarm2
// 	if (h==hour2 && m == min2 && am_pm1 == am_pm2)
// 	{
// 		switcher(ON,SWITCHER_2);
// 	}
	
}

#endif /* SWITCHER_H_ */