/*
 * Functions.h
 *
 * Created: 12/26/2017 6:34:53 PM
 *  Author: OBED
 */ 


#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

void clock_display(void);
void draw_splash(void);
void draw_frame();
void draw_menu();
void pop_up_window();
void draw_pointer(unsigned char draw);
void draw_cursor(unsigned char x,unsigned char y, unsigned char color);

void clock_display()
{
	char h[2],m[2],s[2],ampm[2];
	h[0]=0;m[0]=0;s[0]=0;ampm[0]=0;
	
	 itoa(hour,h,10); itoa(min,m,10); itoa(sec,s,10);
	 
	GLCD_ScreenGraphics(abell);
	GLCD_Draw_String(5,18,"TIME NOW:",BLACK);
	if (hour<10) {GLCD_Draw_String(5,43,h,BLACK);	} 
	else{ GLCD_Draw_String(4,43,h,BLACK);}
	GLCD_Draw_String(6,43,":",BLACK);
	if (min<10) {GLCD_Draw_String(7,43,"0",BLACK);GLCD_Draw_String(8,43,m,BLACK);	}
	else{ GLCD_Draw_String(7,43,m,BLACK);}
	GLCD_Draw_String(9,43,":",BLACK);
	if (sec<10) {GLCD_Draw_String(10,43,"0",BLACK);GLCD_Draw_String(11,43,s,BLACK);	}
	else{ GLCD_Draw_String(10,43,s,BLACK);}
	
	if ( ampm ==0)
	{GLCD_Draw_String(12,43,"AM",BLACK);} 
	else
	{GLCD_Draw_String(12,43,"PM",BLACK);}
		
}

void draw_splash()
{
	GLCD_ScreenGraphics(ABELL1);
}
void draw_menu()
{
		switch (STATE)
		{
			case MENU:
				if(pointer < 5)
				{
					draw_frame();
					GLCD_Draw_String(2,1,"MAIN-MENU",WHITE);
					GLCD_Draw_Char(15,1,'0',WHITE);
					GLCD_Draw_String(2,10,"SET TIME",BLACK);
					GLCD_Draw_String(2,19,"VIEW SCHEDULE",BLACK);
 					GLCD_Draw_String(2,29,"HOME",BLACK);
	// 				GLCD_Draw_String(2,39,wifi,BLACK);
				}
			break;
			case POPUP:
				pop_up_window();
			break;
			default:break;
		}
		draw_pointer(TRUE);
}
void draw_frame()
{
	GLCD_ClearBuffer(WHITE);
	GLCD_Draw_HorizLine(0,128,0,BLACK);
	GLCD_Draw_HorizLine(0,128,63,BLACK);
	GLCD_Draw_VertcLine(0,0,64,BLACK);
	GLCD_Draw_VertcLine(127,0,64,BLACK);
	GLCD_Clear_Row(1,BLACK);
}
void draw_pointer(unsigned char draw)
{
		if(draw == TRUE){GLCD_Draw_Char(1 ,(pointer*10)+10,'>',BLACK);}
		else if(draw == FALSE){GLCD_Draw_Char(1,(pointer*10)+10,' ',BLACK);}
	return;
}
void pop_up_window()
{
	draw_pointer(FALSE);
	for (int w=23;w<112;w++)
	{
		for (int h=10; h<56;h++)
		{
			GLCD_Draw_Pixel(w,h,BLACK);
		}
	}
	switch (event)
	{
		case SET_TIME:
		 GLCD_Draw_String(5,25,"HH:MM",WHITE);
		 draw_cursor(40,41,WHITE);
		 draw_cursor(48,41,WHITE);
		 draw_cursor(64,41,WHITE);
		 draw_cursor(72,41,WHITE);
		 GLCD_Draw_Char(5,33,hour1,WHITE);
		 GLCD_Draw_Char(6,33,hour2,WHITE);
		 GLCD_Draw_Char(8,33,min1,WHITE);
		 GLCD_Draw_Char(9,33,min2,WHITE);
		break;
		
		default:
		break;
	}
}
void drawSchedule()
{
	GLCD_Draw_String(2,1,"TIME SCHEDULE",WHITE);
	if (pointer < 6)
	{
		for (uint8_t row=0;row<6;row++)
		{
				//GLCD_Draw_String(2,10+(row*9),"00:00 AM",BLACK);
				GLCD_Draw_Char(2,10+(row*9),scheduleTable[row][0],BLACK);//hour
				GLCD_Draw_Char(4,10+(row*9),':',BLACK);
				GLCD_Draw_Char(5,10+(row*9),scheduleTable[row][1],BLACK);//min
		}
	} else //pointer>5
	{
		GLCD_Draw_Char(14,10,'^',BLACK);
		for (uint8_t row=0;row<6;row++)
		{
			//GLCD_Draw_String(2,10+(row*9),"00:00 AM",BLACK);
			GLCD_Draw_Char(2,10+(row*9),scheduleTable[pointer+row][0],BLACK);//hour
			GLCD_Draw_Char(4,10+(row*9),':',BLACK);
			GLCD_Draw_String(5,10+(row*9),scheduleTable[pointer+row][1],BLACK);//min
		}
	}
}
void draw_cursor(unsigned char x,unsigned char y, unsigned char color)
{
  GLCD_Draw_HorizLine(x,x+5,y,color);
}
#endif /* FUNCTIONS_H_ */