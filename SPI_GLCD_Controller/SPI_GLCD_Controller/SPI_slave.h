/*
 * SPI_slave.h
 *
 * Created: December 2017-Jannuary2018
 *  Author: OBED
 */ 


#ifndef SPI_SLAVE_H_
#define SPI_SLAVE_H_

#define SS		2
#define MOSI	3									/* Define SPI bus pins */
#define MISO	4
#define SCK		5


void SPI_Init();								/* SPI Initialize function */
void SPI_Transmit(char);						/* SPI transmit data function */
char SPI_Receive();								/* SPI Receive data function */

void SPI_Init()									/* SPI Initialize function */
{
	DDRB &=~(1<<MOSI);
	DDRB &=~(1<<SCK);
	DDRB &=~(1<<SS);		/* Make MOSI, SCK, SS pin direction as input pins */
	
	DDRB |=(1<<MISO);							/* Make MISO pin as output pin */
	SPCR = (1<<SPE);	/* Enable SPI in slave mode*/
	SPSR |=(1<<SPIF);
	sei();  //Enable global interrupts
	SPCR |=(1<<SPIE);  //turn on interrupts 
}

char SPI_Receive(void)
{
	/* Wait for reception complete */
	while(!(SPSR & (1<<SPIF)));
	/* Return Data Register */
	return SPDR;
}
#endif /* SPI_SLAVE_H_ */