/*
 * eeprom.c
 *
 * Created: 11/22/2017 3:27:38 PM
 *  Author: OBED
 */ 
#include <avr/io.h>
#include "eeprom.h"

/***************************************************************************************************
  void EEPROM_WriteByte(uint16_t v_eepromAddres_u16, uint8_t v_eepromData_u8)
 ***************************************************************************************************
 * I/P Arguments: uint16_t: eeprom_address at which eeprom_data is to be written
                  uint8_t: byte of data to be to be written in eeprom.
 * Return value	: none

 * description: This function is used to write the data at specified EEPROM_address..
 **************************************************************************************************/
void EEPROM_WriteByte(uint16_t v_eepromAddress_u16, uint8_t v_eepromData_u8)
{
	while(util_IsBitSet(EECR,EEWE)); // Wait for completion of previous write.
	                                 // EEWE will be cleared by hardware once Eeprom write is completed.

	EEAR = v_eepromAddress_u16;  //Load the eeprom address and data
	EEDR = v_eepromData_u8;

	util_BitSet(EECR,EEMWE);    // Eeprom Master Write Enable
	util_BitSet(EECR,EEWE);     // Start eeprom write by setting EEWE
}






/***************************************************************************************************
               uint8_t EEPROM_ReadByte(uint16_t v_eepromAddres_u16)
 ***************************************************************************************************
 * I/P Arguments: uint16_t: eeprom_address from where eeprom_data is to be read.
 * Return value	: uint8_t: data read from Eeprom.

 * description: This function is used to read the data from specified EEPROM_address.        
 ***************************************************************************************************/
uint8_t EEPROM_ReadByte(uint16_t v_eepromAddress_u16)
{
	while(util_IsBitSet(EECR,EEWE));  //Wait for completion of previous write if any.

	EEAR = v_eepromAddress_u16;    //Load the address from where the data needs to be read.
	util_BitSet(EECR,EERE);   // start eeprom read by setting EERE

	return EEDR;             // Return data from data register
}






/***************************************************************************************************
void EEPROM_WriteNBytes(uint16_t v_eepromAddress_u16, uint8_t *ptr_ramAddress_u8, uint16_t v_numOfBytes_u16)
 ***************************************************************************************************
 * I/P Arguments: uint16_t,: eeprom_address from where the N-bytes are to be written.
                  uint8_t*: Buffer(Pointer) containing the N-Bytes of data to be written in Eeprom.
                  uint16_t :  Number of bytes to be written

 * Return value	: none

 * description:
            This function is used to write N-bytes of data at specified EEPROM_address.
 ***************************************************************************************************/
#if ( ENABLE_EEPROM_WriteNBytes == 1)
void EEPROM_WriteNBytes(uint16_t v_eepromAddress_u16, uint8_t *ptr_ramAddress_u8, uint16_t v_numOfBytes_u16)
{
	while(v_numOfBytes_u16 !=  0)
	{
		EEPROM_WriteByte(v_eepromAddress_u16,*ptr_ramAddress_u8); //Write a byte from RAM to EEPROM
		v_eepromAddress_u16++;					   //Increment the Eeprom Address
		ptr_ramAddress_u8++;						   //Increment the RAM Address
		v_numOfBytes_u16--;					   //Decrement NoOfBytes after writing each Byte
	}
}
#endif



/***************************************************************************************************
void EEPROM_ReadNBytes(uint16_t v_eepromAddress_16, uint8_t *ptr_ramAddress_u8, uint16_t v_numOfBytes_u16)
 ***************************************************************************************************
 * I/P Arguments: uint16_t,: eeprom_address from where the N-bytes is to be read.
                  uint8_t*: Pointer to copy the N-bytes read from Eeprom.
                  uint16_t :  Number of bytes to be Read

 * Return value	: none

 * description:
            This function is used to Read N-bytes of data from specified EEPROM_address.
            The data read from the eeprom will be copied into the specified RamAddress.

	##Note:	Care should be taken to allocate enough buffer to read the data.
 ***************************************************************************************************/
#if ( ENABLE_EEPROM_ReadNBytes == 1)
void EEPROM_ReadNBytes(uint16_t v_eepromAddress_16, uint8_t *ptr_ramAddress_u8, uint16_t v_numOfBytes_u16)
{
	while(v_numOfBytes_u16 !=  0)
	{
		*ptr_ramAddress_u8 = EEPROM_ReadByte(v_eepromAddress_16);//Read a byte from EEPROM to RAM
		v_eepromAddress_16++;						//Increment the EEPROM Address
		ptr_ramAddress_u8++;							//Increment the RAM Address
		v_numOfBytes_u16--;						//Decrement NoOfBytes after Reading each Byte

	}
}
#endif


/***************************************************************************************************
 void EEPROM_WriteString(uint16_t v_eepromAddress_u16, uint8_t *ptr_stringPointer_u8)
 ***************************************************************************************************
 * I/P Arguments: uint16_t,: eeprom_address where the String is to be written.
                  char*: Pointer to String which has to be written.

 * Return value	: none

 * description:This function is used to Write a String at specified EEPROM_address.

   NOTE: Null char is also written into the eeprom.
 ***************************************************************************************************/
#if ( ENABLE_EEPROM_WriteString == 1)
void EEPROM_WriteString(uint16_t v_eepromAddress_u16, uint8_t *ptr_stringPointer_u8)
{
	do
	{
		EEPROM_WriteByte(v_eepromAddress_u16,*ptr_stringPointer_u8); //Write a byte from RAM to EEPROM
		ptr_stringPointer_u8++;								//Increment the RAM Address
		v_eepromAddress_u16++;								//Increment the Eeprom Address
	}while(*(ptr_stringPointer_u8-1) !=0);
}
#endif

/***************************************************************************************************
void EEPROM_ReadString(uint16_t v_eepromAddress_u16, uint8_t *ptr_destStringAddress_u8)
 ***************************************************************************************************
 * I/P Arguments: uint16_t,: eeprom_address from where the String is to be read.
                  char*: Pointer into which the String is to be read.

 * Return value	: none

 * description:This function is used to Read a String from specified EEPROM_address.
           The string read from eeprom will be copied to specified buffer along with NULL character
 ***************************************************************************************************/
#if ( ENABLE_EEPROM_ReadString == 1)
void EEPROM_ReadString(uint16_t v_eepromAddress_u16, uint8_t *ptr_destStringAddress_u8)
{
	char eeprom_data;

	do
	{
		eeprom_data = EEPROM_ReadByte(v_eepromAddress_u16); //Read a byte from EEPROM to RAM
		*ptr_destStringAddress_u8 = eeprom_data;			 //Copy the data into String Buffer
		ptr_destStringAddress_u8++;						 //Increment the RAM Address
		v_eepromAddress_u16++;							 //Increment the Eeprom Address
	}while(eeprom_data!=0);
}
#endif


/***************************************************************************************************
                                   void EEPROM_Erase()
 ***************************************************************************************************
 * I/P Arguments: none

 * Return value	: none

 * description: This function is used to erase the entire Eeprom memory.
               Complete Eeprom(C_MaxEepromSize_U16) is filled with 0xFF to accomplish the Eeprom Erase.
 ***************************************************************************************************/
#if ( ENABLE_EEPROM_Erase == 1)
void EEPROM_Erase()
{
	uint16_t v_eepromAddress_u16;

	for(v_eepromAddress_u16=0;v_eepromAddress_u16<C_MaxEepromSize_U16;v_eepromAddress_u16++)
	{
		EEPROM_WriteByte(v_eepromAddress_u16,0xffu); // Write Each memory location with OxFF
	}
}
#endif
