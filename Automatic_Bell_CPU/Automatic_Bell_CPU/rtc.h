/*
 * rtc.h
 *
 * Created: 1/27/2017 7:25:56 AM
 *  Author: Obed
 */ 


#ifndef RTC_H_
#define RTC_H_

///////////********I2C******** //////////////////////////
void I2CInit();
void I2CClose();

void I2CStart();
void I2CStop();

uint8_t I2CWriteByte(uint8_t data);
uint8_t I2CReadByte(uint8_t *data,uint8_t ack);

///////////////////////////////////////////////////////////////
uint8_t  ClockInit();

uint8_t DS1307Read(uint8_t address,uint8_t *data);
uint8_t DS1307Write(uint8_t address,uint8_t data);
uint8_t GetSecond();
uint8_t GetMinute();
uint8_t GetHour();
uint8_t GetAmPm();

uint8_t GetDate();
uint8_t GetMonth();
uint8_t GetYear();


//Set Function
uint8_t SetSecond(uint8_t sec);
uint8_t SetMinute(uint8_t min);
uint8_t SetHour(uint8_t hr);
uint8_t SetAmPm(uint8_t pm);

uint8_t SetDate(uint8_t date);
uint8_t SetMonth(uint8_t month);
uint8_t SetYear(uint8_t year);


//Time as string e.g. "12:45:33 PM"
uint8_t GetTimeString(char *Time);
//Date as string e.g. "12/03/2015"
uint8_t GetDateString(char *Date);

//Ask user to enter Current Time using LCD and Keypad
//Then saves them to DS1307 RTC module.

#endif /* RTC_H_ */