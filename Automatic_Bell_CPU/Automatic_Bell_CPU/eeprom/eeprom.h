/*
 * eeprom.h
 *
 * Created: 11/22/2017 3:21:47 PM
 *  Author: OBED
 */ 


#ifndef EEPROM_H_
#define EEPROM_H_

#include <avr/io.h>

#define C_MaxEepromSize_U16 1024

/*PreCompile configuration to enable or disable the API's.
 1.Required interfaces can be enabled/disabled by configuring its respective macros to 1/0.
 2. By default all the API's are disabled. 
***************************************************************************************************/
#define    ENABLE_EEPROM_WriteNBytes   1
#define    ENABLE_EEPROM_ReadNBytes    1
#define    ENABLE_EEPROM_WriteString   1
#define    ENABLE_EEPROM_ReadString    1
#define    ENABLE_EEPROM_Erase         0
/**************************************************************************************************/


/***************************************************************************************************
                             Function Prototypes
 ***************************************************************************************************/
void EEPROM_WriteByte(uint16_t v_eepromAddress_u16, uint8_t v_eepromData_u8);
uint8_t EEPROM_ReadByte(uint16_t v_eepromAddress_u16);
void EEPROM_WriteNBytes(uint16_t v_eepromAddress_u16, uint8_t *ptr_ramAddress_u8, uint16_t v_numOfBytes_u16);
void EEPROM_ReadNBytes(uint16_t v_eepromAddress_16, uint8_t *ptr_ramAddress_u8, uint16_t v_numOfBytes_u16);
void EEPROM_WriteString(uint16_t v_eepromAddress_u16, uint8_t *ptr_stringPointer_u8);
void EEPROM_ReadString(uint16_t v_eepromAddress_u16, uint8_t *ptr_destStringAddress_u8);
void EEPROM_Erase();
/**************************************************************************************************/

/***************************************************************************************************
                                Macros for Bit Manipulation
 ****************************************************************************************************/
#define  util_GetBitMask(bit)          (1<<(bit))
#define  util_BitSet(x,bit)            ((x) |=  util_GetBitMask(bit))
#define  util_BitClear(x,bit)          ((x) &= ~util_GetBitMask(bit))
#define  util_BitToggle(x,bit)         ((x) ^=  util_GetBitMask(bit))
#define  util_UpdateBit(x,bit,val)     ((val)? util_BitSet(x,bit): util_BitClear(x,bit))


#define  util_GetBitStatus(x,bit)      (((x)&(util_GetBitMask(bit)))!=0u)
#define  util_IsBitSet(x,bit)          (((x)&(util_GetBitMask(bit)))!=0u)
#define  util_IsBitCleared(x,bit)      (((x)&(util_GetBitMask(bit)))==0u)


#define  util_AreAllBitsSet(x,BitMask) (((x)&(BitMask))==BitMask)
#define  util_AreAnyBitsSet(x,BitMask) (((x)&(BitMask))!=0x00u)
/**************************************************************************************************/
#endif /* EEPROM_H_ */