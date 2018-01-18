/*
 * functions.h
 *
 * Created: 12/28/2017 10:54:14 AM
 *  Author: OBED
 */ 


#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

void Read_RTC(void);
void send_rtcToDispaly();
int keyInput(int digits,unsigned char use);
void set_rtc();
void send_ToDispaly(char flag, char data);

//Function to to read RTC values
void Read_RTC()
{
	//Time
	h = GetHour();
	m = GetMinute();
	s = GetSecond();
	ampm = GetAmPm();
	//Date
	date = GetDate();
	month = GetMonth();
	year = GetYear();
}

void send_rtcToDispaly()
{
	SPI_Transmit(rtc_hour); //Set flag first
	SPI_Transmit(h);
   SPI_Transmit(rtc_min);//Set flag first
   SPI_Transmit(m);
   SPI_Transmit('s');//Set flag first
   SPI_Transmit(s);
   SPI_Transmit(rtc_ampm);//Set flag first
   SPI_Transmit(ampm);
   SPI_Transmit(clock_flag);
}
void send_ToDispaly(char flag, char data)
{
  SPI_Transmit(flag); //Set flag first
  SPI_Transmit(data);
 
}
void set_rtc()
{
  while (STATE == SET_TIME)
  {
    int hour=0,minute=0;
    int loop=0;
       
    while (loop<2)
    {
      switch (loop)
      {
        case 0:
			hour = keyInput(2,HOUR);
			if (hour>12) {SetHour(hour-12); 	SetAmPm(1)/*PM*/; }
			else {SetHour(hour);SetAmPm(0);/*AM*/ }
        break;
        case 1:
			minute = keyInput(2,MINUTE); SetMinute(minute);
        break;
        default: ;break;
      }
      loop++;
    }
    //GLCD_Draw_String(4,41,"TIME SET!",WHITE);
    STATE = MENU;
  }
}
int keyInput(int digits,unsigned char use)
{
  int i=0, num=0;
  while ( i < digits )
  {    
    if (key_int >=0)
    {
      switch (i)
      {
        case 0:	num=key_int;   break;
        case 1: num = (num*10)+(key_int); break;
        case 2:	num = (num*10)+(key_int); break;
        case 3: num = (num*10)+(key_int); break;
        default:  break;
      }
      switch (use)
      {
        case HOUR:
			if (i ==0){ send_ToDispaly(set_hour1,key);}
			else if (i==1) {send_ToDispaly(set_hour2,key); }
        break;
        case MINUTE:
			if (i ==0){send_ToDispaly(set_min1,key);}
			else if (i==1) {send_ToDispaly(set_min2,key);}
        break;
      }
      key_int=-1;
      i++;
    }
  }
  return num;
}

#endif /* FUNCTIONS_H_ */