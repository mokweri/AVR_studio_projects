/*
 * ST7920.c
 *
 * Created: August 2017
 *  Author: OBED
 */ 
#define F_CPU 16000000UL
#include <stdlib.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include <string.h>

#include "ST7920.h"
#include "font5x7.h"


void GLCD_Init(void)
{
	DATA_PORT_OUT();    // set data port for output
	COMMAND_OUT();
	E_LOW;
	RS_LOW;
	RW_LOW;
	/* Switch display toParallel mode */
	//COMMAND_PORT |= PSB;
	/* Reset display */
	COMMAND_PORT &= ~RST;
	_delay_us(1);
	COMMAND_PORT |= RST;
	
	_delay_ms(40);
	#ifdef GLCD_4bit
		GLCD_Write(COMMAND,FUNCTION|FUNCTION_4BIT);
	#else
		GLCD_Write(COMMAND,FUNCTION|FUNCTION_8BIT);
	#endif
	GLCD_Write(COMMAND,DISPLAY|DISPLAY_ON); 
	GLCD_Write(COMMAND,CLEAR);
	GLCD_Write(COMMAND,0x06);
	GLCD_Write(COMMAND,HOME);
	
	GLCD_enable(ON);	
}

void GLCD_Write(unsigned char type, unsigned char data)
{
	GLCD_checkBusy();	
	if (type == DATA)
	{
		RS_HIGH;
	}
	else
	{
		RS_LOW;
	}
	RW_LOW;
	
	#ifdef GLCD_4bit	
		Write_2Nibbles(data);
	#else
		DATA_PORT = data;
		toggle_E;
	#endif	
}

void Write_2Nibbles(unsigned char ch)
{
	E_HIGH;
	if (ch & 0x10) D4_HIGH; else D4_LOW;
	if (ch & 0x20) D5_HIGH; else D5_LOW;
	if (ch & 0x40) D6_HIGH; else D6_LOW;
	if (ch & 0x80) D7_HIGH; else D7_LOW;	
	E_LOW;
	
	E_HIGH;
	if (ch & 0x01) D4_HIGH; else D4_LOW;
	if (ch & 0x02) D5_HIGH; else D5_LOW;
	if (ch & 0x04) D6_HIGH; else D6_LOW;
	if (ch & 0x08) D7_HIGH; else D7_LOW;
	E_LOW;	
}

void GLCD_checkBusy()
{
	DATA_IN();
	RS_LOW;	//Instruction
	RW_HIGH; //Read mode
		
	#ifdef GLCD_4bit
		unsigned char highbyte, lowbyte;
		do
		{
			E_HIGH;
			highbyte = DATA_GET(); _delay_us(5);
			E_LOW;
				
			E_HIGH;
			lowbyte = DATA_GET(); _delay_us(5);
			E_LOW;
		} while (highbyte & BUSY_FLAG);
	#else
		uint8_t temp;
		toggle_E;
		do
		{
			temp = DATA_GET();
		}while( (temp & 0x7F)== BUSY_FLAG); 
	#endif
	DATA_PORT_OUT();
	RS_LOW;
	RW_LOW;
}

void GLCD_TextDisplayString(unsigned char line, char* string)
{
	unsigned char addr,i,length;
	if(line==1)
	addr=0x80; //The first line address
	else if(line==2)
	addr=0x90; //The second line address
	else if(line==3)
	addr=0x88;   //The third line address
	else if(line==4)
	addr=0x98;    //The fourth line address

	GLCD_Write(COMMAND,addr);

	length = strlen(string);
	
	for(i=0;i<length;i++)
	GLCD_Write(DATA,*string++);
}

void GLCD_enable(unsigned char on_off)
{
	if(on_off)
	{
		GLCD_Write(COMMAND,GRAPHIC_ON);
	}
	else
	{
		GLCD_Write(COMMAND,GRAPHIC_OFF);
	}
}

void GLCD_FillScreenGraphics(const unsigned char* graphic)
{
	unsigned char x, y;
	for(y = 0; y < 64; y++)
	{
		if(y < 32)
		{
			for(x = 0; x < 8; x++)
			{
				GLCD_Write(COMMAND,0x80 | y);
				GLCD_Write(COMMAND,0x80 | x);
				GLCD_Write(DATA,pgm_read_byte(&(graphic[2*x + 16*y])));
				GLCD_Write(DATA,pgm_read_byte(&(graphic[2*x+1 + 16*y])));
			}
		}
		else
		{
			for(x = 0; x < 8; x++)
			{
				GLCD_Write(COMMAND,0x80 | (y-32));
				GLCD_Write(COMMAND,0x88 | x);
				GLCD_Write(DATA,pgm_read_byte(&(graphic[2*x + 16*y])));
				GLCD_Write(DATA,pgm_read_byte(&(graphic[2*x+1 + 16*y])));
			}
		}
		
	}
}

void GLCD_ScreenGraphics(const unsigned char* graphic)
{
	unsigned char x, y;
	for (y = 0; y < 64; y++)
	{
		for (x = 0; x < 16; x++)
		{
			Buffer[x][y] = pgm_read_byte(&(graphic[x+y*16]));
		}
	}
}

void GLCD_GOTO_XY(unsigned char x, unsigned char y)
{
		if(y < 32)
		{										
				GLCD_Write(COMMAND,0x80 | y);
				GLCD_Write(COMMAND,0x80 | x);
		}
		else
		{
				GLCD_Write(COMMAND,0x80 | (y-32));
				GLCD_Write(COMMAND,0x88 | x);
		}		
}

void GLCD_GraphicsDisplayString(unsigned char line, char* str)
{
	unsigned char row;
	unsigned char colInd;
	unsigned char shouldContinue = 1;
	unsigned char count = 0;

	while(*str && shouldContinue)
	{
		unsigned char character = *str++;		
		unsigned char colList[5];
		
		colList[4] = pgm_read_byte(&(font5x7[(character-START_CHAR)][0]));
		colList[3] = pgm_read_byte(&(font5x7[(character-START_CHAR)][1]));
		colList[2] = pgm_read_byte(&(font5x7[(character-START_CHAR)][2]));
		colList[1] = pgm_read_byte(&(font5x7[(character-START_CHAR)][3]));
		colList[0] = pgm_read_byte(&(font5x7[(character-START_CHAR)][4]));

		for (row=0;row<8;row++)
		{
			if (line < 4)
			{
				GLCD_Write(COMMAND,0x80 | (line * 8 + row));
				GLCD_Write(COMMAND,0x80 | count);
			}
			else
			{
				GLCD_Write(COMMAND,0x80 | ( (line-4) * 8 + row));
				GLCD_Write(COMMAND,0x88 | count);
			}
			
			unsigned char dataA = 0x00;
			for (colInd=0;colInd<5;colInd++)
			{
				if (colList[colInd] & (1 << row))
				{
					dataA = dataA | (1 << (colInd+3));
				}			
			}
			GLCD_Write(DATA,dataA);
		}
		count++;
	}
}

void GLCD_Draw_Char(unsigned char x,unsigned char y, char character,unsigned char color)
{
	unsigned char row;
	unsigned char colInd;	
	unsigned char colList[5];
	
	colList[4] = pgm_read_byte(&(font5x7[(character-START_CHAR)][0]));
	colList[3] = pgm_read_byte(&(font5x7[(character-START_CHAR)][1]));
	colList[2] = pgm_read_byte(&(font5x7[(character-START_CHAR)][2]));
	colList[1] = pgm_read_byte(&(font5x7[(character-START_CHAR)][3]));
	colList[0] = pgm_read_byte(&(font5x7[(character-START_CHAR)][4]));
	
		/*colList[7] = pgm_read_byte(&(font_6x8[(character-START_CHAR)][0]));
		colList[6] = pgm_read_byte(&(font_6x8[(character-START_CHAR)][1]));
		colList[5] = pgm_read_byte(&(font_6x8[(character-START_CHAR)][2]));
		colList[4] = pgm_read_byte(&(font_6x8[(character-START_CHAR)][3]));
		colList[3] = pgm_read_byte(&(font_6x8[(character-START_CHAR)][4]));
		colList[2] = pgm_read_byte(&(font_6x8[(character-START_CHAR)][5]));
		colList[1] = pgm_read_byte(&(font_6x8[(character-START_CHAR)][6]));
		colList[0] = pgm_read_byte(&(font_6x8[(character-START_CHAR)][7]));
		*/
	for (row=0;row<8;row++)
	{			
		unsigned char dataA = 0x00;
		for (colInd=0;colInd<5;colInd++)
		{
			if (colList[colInd] & (1 << row))
			{
				dataA = dataA | (1 << (colInd+3));
			}
		}
		if(color == BLACK){}
		else{dataA ^= 0xFF;}
		Buffer[x][row+y] = dataA;					
	}
}

void GLCD_Draw_String(unsigned char x,unsigned char y, const char *str,unsigned char color)
{
	unsigned char length = strlen(str);
	
	for( ;  length ; length -- )
	{GLCD_Draw_Char(x,y,*(str++),color);x++;}
		
	return;
}

void GLCD_ClearBuffer(unsigned char color)
{
	unsigned char x, y;
	for(y = 0; y < 64; y++)
	{		
		for(x = 0; x < 16; x++)
		{
			if (color)
			{
				Buffer[x][y]= BLACK;
			} 
			else
			{
				Buffer[x][y]= WHITE;
			}			
		}
	}
}

void GLCD_Clear_Row(unsigned char y, unsigned char color)
{
	for (unsigned char i=y; i<(y+8); i++)
	{
		for(unsigned char x = 0; x<16; x++)
		{Buffer[x][i] = color;}		
	}
	return;
}

void GLCD_Draw_Pixel(unsigned char x, unsigned char y, unsigned char colour)
{
	unsigned char dot = 1<<(7-x%8);
	x = x/8;
	if (colour == BLACK){Buffer[x][y]|=dot;	} 
	else { Buffer[x][y]&=~dot;}
	
	return;
}

void GLCD_Draw_HorizLine(unsigned char x1, unsigned char x2, unsigned char y, unsigned char color)
{
	unsigned char i;
	/* Swap X */
	if (x1 > x2) {
		i = x1;
		x1 = x2;
		x2 = i;
	}
	for (i = x1; i <= x2; i++)
	GLCD_Draw_Pixel(i, y, color);

	return;
}

void GLCD_Draw_VertcLine(unsigned char x, unsigned char y1, unsigned char y2, unsigned char color)
{
	unsigned char i;
	/* Swap Y */
	if (y1 > y2)
	{
		i = y1;
		y1 = y2;
		y2 = i;
	}
	for (i = y1; i <= y2; i++)
	GLCD_Draw_Pixel(x, i, color);
	return;
}

void GLCD_Draw_Sprite(unsigned char x, unsigned char y, const unsigned char *sprite)
{
	short size = 2;
	unsigned char width = 0,height = 0,w = 0,h=0;
	
	w = pgm_read_byte(&(sprite[0]));
	h = pgm_read_byte(&(sprite[1]));
	
	unsigned char posx = 0,posy = 0;	
	width = w/8;
	height= h/8;	
	
	for (unsigned char Y=0; Y<height;Y++)
	{		
		if (Y == 0){posy = y;}else{posy +=8;}	
			
		for (unsigned char X=0; X<width;X++)
		{
			if (X == 0){posx = x;}else{posx +=1;}	
			
			unsigned char row;
			unsigned char colInd;
			unsigned char colList[8];
			
			colList[7] = pgm_read_byte(&(sprite[(size)]));
			colList[6] = pgm_read_byte(&(sprite[(size+1)]));
			colList[5] = pgm_read_byte(&(sprite[(size+2)]));
			colList[4] = pgm_read_byte(&(sprite[(size+3)]));
			colList[3] = pgm_read_byte(&(sprite[(size+4)]));
			colList[2] = pgm_read_byte(&(sprite[(size+5)]));
			colList[1] = pgm_read_byte(&(sprite[(size+6)]));
			colList[0] = pgm_read_byte(&(sprite[(size+7)]));
			size += 8;
			
			
			for (row=0;row<8;row++)
			{
				unsigned char dataA = 0x00;
				for (colInd=0;colInd<8;colInd++)
				{
					if (colList[colInd] & (1 << row))
					{
						dataA = dataA | (1 << (colInd));
					}
				}				
					Buffer[posx][posy+row]	= dataA;					
			}					
		}
		if ( w%8 != 0)
		{
			posx++;
			unsigned char row;
			unsigned char colInd;
			unsigned char colList[7];
			unsigned char i = w%8;
			
			colList[i] = pgm_read_byte(&(sprite[(size)]));
			colList[i-1] = pgm_read_byte(&(sprite[(size+1)]));
			colList[i-2] = pgm_read_byte(&(sprite[(size+2)]));
			colList[i-4] = pgm_read_byte(&(sprite[(size+3)]));
			colList[i-5] = pgm_read_byte(&(sprite[(size+4)]));
			colList[i-6] = pgm_read_byte(&(sprite[(size+5)]));
			colList[i-7] = pgm_read_byte(&(sprite[(size+6)]));
			size += w%8;
			
			for (row=0;row<8;row++)
			{
			unsigned char dataA = 0x00;
			for (colInd=0;colInd<(w%8);colInd++)
			{
				if (colList[colInd] & (1 << row))
				{
					dataA = dataA | (1 << (colInd+(8-y%8)));
				}
			}
				Buffer[posx][posy+row] = dataA;
			}
		}		
	}
	return;
}

void GLCD_Render()
{
	unsigned char x = 0, y = 0, side = 0;
	
	for(;y<64; y++)
	{
		GLCD_GOTO_XY(x,y);		
		for(;x<16; x++)
		{
			if(y>63 && side == 0){GLCD_GOTO_XY(x,y); side=1;}

			GLCD_Write(DATA,Buffer[x][y]);
			//GLCD_Write(DATA,Buffer[x+1][y]);
		}
		x=side = 0;
	}
	return;
}

