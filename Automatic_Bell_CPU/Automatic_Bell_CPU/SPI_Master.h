/*
 * SPI.h
 *
 * Created: 11/26/2017 6:02:40 AM
 *  Author: OBED
 */ 


#ifndef SPI_H_
#define SPI_H_
#define F_CPU 16000000UL
#include <util/delay.h>

/* Include AVR std. library file */
#define SS		2
#define MOSI	3									/* Define SPI bus pins */
#define MISO	4
#define SCK		5


void SPI_Init();								/* SPI Initialize function */
void SPI_Transmit(char);						/* SPI transmit data function */
char SPI_Receive();								/* SPI Receive data function */
char transmitAndWait(char data);

#define SS_Enable PORTB &= ~(1<<SS)			/* Define Slave enable */
#define SS_Disable PORTB |= (1<<SS)			/* Define Slave disable */

void SPI_Init()									/* SPI Initialize function */
{
	DDRB |= ((1<<MOSI)|(1<<SCK)|(1<<SS));		/* Make MOSI, SCK, SS pin direction as output pins */
	DDRB &=~(1<<MISO);							/* Make MISO pin as INPUT pin */
	PORTB |=(1<<SS);						    /* Disable slave initially by making high on SS pin */
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);		/* Enable SPI in slave mode, Master mode, with Fosc/16 SCK frequency */
	
}
void SPI_Transmit(char data)					/* SPI transmit data function */
{
	//cli();
	SS_Enable;
	SPDR = data;								/* Write data to SPI data register */
	while(!(SPSR & (1<<SPIF)));					/* Wait till transmission complete */								/* return received data */
	//sei();
}

char SPI_Receive()								/* SPI Receive data function */
{
	while(!(SPSR & (1<<SPIF)));					/* Wait till reception complete */
	return(SPDR);								/* return received data */
}

char transmitAndWait(char data)
{
	SS_Enable;
	char a;
	SPI_Transmit(data);
	_delay_us(20);
	a=SPI_Receive();
	SS_Disable;
	return a;	
}
#endif /* SPI_H_ */
