/*
 * eeprom2.h
 *
 * Created: 11/22/2017 4:14:56 PM
 *  Author: OBED
 */ 


#ifndef EEPROM2_H_
#define EEPROM2_H_

void initial_EEPROM_Read()
{
	EEPROM_ReadNBytes(switch1_addr,(uint8_t *)&switch1,1); //Read 1-bytes of data from 0x00 into switch1
	EEPROM_ReadNBytes(switch2_addr,(uint8_t *)&switch2,1);
	EEPROM_ReadNBytes(switch3_addr,(uint8_t *)&switch3,1);
	EEPROM_ReadNBytes(switch4_addr,(uint8_t *)&switch4,1);
	
	EEPROM_ReadNBytes(pulse_count_addr,(uint8_t *)&pulse_count,3);
}
void initial_EEPROM_Write()
{
	EEPROM_WriteNBytes(switch1_addr,(uint8_t *)&switch1,1); //Write 1-bytes of data from 0x00 into switch1
	EEPROM_WriteNBytes(switch2_addr,(uint8_t *)&switch2,1);
	EEPROM_WriteNBytes(switch3_addr,(uint8_t *)&switch3,1);
	EEPROM_WriteNBytes(switch4_addr,(uint8_t *)&switch4,1);
	EEPROM_WriteNBytes(pulse_count_addr,(uint8_t *)&pulse_count,3);
}
#endif /* EEPROM2_H_ */