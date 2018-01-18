/*
 * ST7920.h
 *
 * Created: August 2017
 *  Author: OBED
 */ 

#ifndef ST7920_H_
#define ST7920_H_

//Comment this if GLCD 8 bit is used
//****************************************
//#define GLCD_4bit
//****************************************

#define DATA_PORT		PORTD
#define DATAPORT_DIR    DDRD
#define DATA_PIN		PIND
#define COMMAND_PORT    PORTC
#define COMMAND_DIR     DDRC

/* ST7920 Data port*/
#define D4_LOW	 DATA_PORT &=~(1<<4)
#define D5_LOW	 DATA_PORT &=~(1<<5)
#define D6_LOW	 DATA_PORT &=~(1<<6)
#define D7_LOW	 DATA_PORT &=~(1<<7)

#define D4_HIGH	 DATA_PORT |=(1<<4)
#define D5_HIGH	 DATA_PORT |=(1<<5)
#define D6_HIGH	 DATA_PORT |=(1<<6)
#define D7_HIGH	 DATA_PORT |=(1<<7)
/* ST7920 control port*/
#define RS		(1<<0)
#define RW		(1<<1)
#define E		(1<<2)
#define RST		(1<<3)
//#define PSB		(1<<4)

#define delay_time    80     // default settling time in uS after a command is sent

#ifdef RST
#ifdef PSB
#define COMMAND_OUT()	COMMAND_DIR |= (RS)|(RW)|(E)|(RST)|(PSB)
#else
#define COMMAND_OUT()	COMMAND_DIR |= (RS)|(RW)|(E)|(RST)
#endif	//#ifdef LCD_PSB
#else
#ifdef PSB
#define COMMAND_OUT()	COMMAND_DIR |= (RS)|(RW)|(E)|(PSB)
#else
#define COMMAND_OUT()	COMMAND_DIR |= (RS)|(RW)|(E)
#endif	//#ifdef PSB
#endif	//#ifdef RST

#define E_LOW		COMMAND_PORT &= ~E;_delay_us(delay_time)
#define E_HIGH		COMMAND_PORT |= E;_delay_us(delay_time)
#define RS_LOW		COMMAND_PORT &= ~RS;_delay_us(delay_time)
#define RS_HIGH		COMMAND_PORT |= RS;_delay_us(delay_time)
#define RW_LOW		COMMAND_PORT &= ~RW;_delay_us(delay_time)
#define RW_HIGH		COMMAND_PORT |= RW;_delay_us(delay_time)
#define toggle_E	E_HIGH;asm("nop");E_LOW

#ifdef GLCD_4bit
	#define DATA_IN()	DATAPORT_DIR &= ~(1<<4)&(1<<5)&(1<<6)&(1<<7) //4bits
	#define DATA_PORT_OUT()	DATAPORT_DIR |=(1<<4)|(1<<5)|(1<<6)|(1<<7) //4bits
#else
	#define DATA_IN()	DATAPORT_DIR &= ~(1<<0)&(1<<1)&(1<<2)&(1<<3)&(1<<4)&(1<<5)&(1<<6)&(1<<7) //4bits
	#define DATA_PORT_OUT()	DATAPORT_DIR |= (1<<0)|(1<<1)|(1<<2)|(1<<3)|(1<<4)|(1<<5)|(1<<6)|(1<<7) //4bits
#endif

#define DATA_GET()	DATA_PIN

/* Basic instructions */
#define CLEAR				0x01
#define HOME				0x02
#define ENTRY_MODE			0x04
	#define INC_ADDR		0x02
	#define SHIFT			0x01
#define DISPLAY				0x08
	#define DISPLAY_ON		0x04
	#define CURSOR_ON		0x02
	#define BLINK_ON		0x01
#define DISPLAY_ON_NOCURSOR		0x06  //No cursor
#define CURSOR_CTRL			0x10
	#define SHIFT_DISPLAY	0x08
	#define SHIFT_RIGHT		0x04
#define BASIC_FUNCTION	  	0x30
#define FUNCTION			0x20
	#define FUNCTION_8BIT	0x10
	#define FUNCTION_4BIT	0x00
	#define EXT_INSTR		0x04
	#define GRAPHIC			0x02 /* Only with EXT_INSTR */
#define SET_CGRAM			0x40
#define SET_DDRAM			0x80

/* Extended instructions */
#define STANDBY				0x01
#define SCROLL_RAM			0x02
	#define VERT_SCROLL		0x01
#define REVERSE				0x04
#define SET_IRAM_SCROLL		0x40
#define SET_GRAPHIC_RAM		0x80

/*Graphic modes*/
#ifdef GLCD_4bit
	#define GRAPHIC_ON		0x26
	#define GRAPHIC_OFF		0x24
#else
	#define GRAPHIC_ON		0x36
	#define GRAPHIC_OFF		0x34
#endif

#define ON				1
#define OFF				0

#define BUSY_FLAG			0x80
/* Some common defines */
#define COMMAND				0
#define DATA				1

#ifndef COLOR
#define BLACK			0xFF
#define WHITE			0x00
#endif

volatile unsigned char Buffer[16][64];

void GLCD_Init(void);
void GLCD_TextDisplayString(unsigned char line, char* string);
void GLCD_GraphicsDisplayString(unsigned char line, char* str);
void GLCD_GraphicsDisplayChar(unsigned char line, unsigned char col, unsigned char letter);
void GLCD_enable(unsigned char on_off);
void GLCD_FillScreenGraphics(const unsigned char* graphic);  //Writing the Graphic RAM directly
void GLCD_ScreenGraphics(const unsigned char* graphic); // Using Buffer
void GLCD_ClearBuffer(unsigned char color);
void GLCD_Write(unsigned char type, unsigned char data);
void Write_2Nibbles(unsigned char ch);
void GLCD_checkBusy();
void GLCD_GOTO_XY(unsigned char x, unsigned char y);
void GLCD_Draw_Char(unsigned char x,unsigned char y, char character, unsigned char color);
void GLCD_Draw_String(unsigned char x,unsigned char y, const char *str,unsigned char color);
void GLCD_Draw_Pixel(unsigned char x, unsigned char y, unsigned char colour);
void GLCD_Draw_HorizLine(unsigned char x1, unsigned char x2, unsigned char y, unsigned char color);
void GLCD_Draw_VertcLine(unsigned char x, unsigned char y1, unsigned char y2, unsigned char color);
void GLCD_Draw_Sprite(unsigned char x,unsigned char y, const unsigned char *sprite);
void GLCD_Render();


void GLCD_Clear_Row(unsigned char y, unsigned char colour);
#endif /* ST7920_H_ */