/*
 * Jayraj.c
 *
 * Created: 04-02-2016 7.25.45 PM
 * Author : Kartik Nighania
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#define datalines PORTA
#define addressbus PORTC
#define flor PORTB
int cube[8][8][8]={{0}},x=0,y=0;
static  int z=0;

int main(void)
{
	DDRA=0b11111111;										// 1 DATA LINES WE SET AS INPUT RATHER THAN OUTPUT
	DDRB=0b11111111;
	DDRC=0b11111111; 
	TCCR2|=(1<<CS20)| (1<<CS22)|(1<<WGM21);
	TIMSK|=(1<<OCIE2);
	OCR2=10;
	sei();
	
    while (1) 
    {														 // 2 no values in cube were set as one.. due to which no led can be...
		cube[1][2][3]=1;
		cube[2][6][3]=1;
		cube[4][3][3]=1;
		cube[5][1][3]=1;
		cube[6][5][3]=1;
		cube[7][4][3]=1;
		
		
		
		

		
		
		
    }
}
ISR(TIMER2_COMP_vect)
{
	switch (z)
	{
		
		case 0: flor=0b00000001; break;
		case 1: flor=0b00000010; break;
		case 2: flor=0b00000100; break;
		case 3: flor=0b00001000; break;
		case 4: flor=0b00010000; break;
		case 5: flor=0b00100000; break;
		case 6: flor=0b01000000; break;
		case 7: flor=0b10000000; break;
		
	}
	
	
	addressbus=0b00000000;
	for (y=0;y<8;y++)
	{
		datalines=0b00000000;
		for (x=0;x<8;x++)
		{
			if (cube[z][y][x]==1)
			{
				switch (x)
				{
					case 0: datalines|=1<<PINA0; break;
					case 1: datalines|=1<<PINA1; break;
					case 2: datalines|=1<<PINA2; break;
					case 3: datalines|=1<<PINA3; break;
					case 4: datalines|=1<<PINA4; break;
					case 5: datalines|=1<<PINA5; break;
					case 6: datalines|=1<<PINA6; break;
					case 7: datalines|=1<<PINA7; break;
				}
			}
		}
		switch(y)
		{
			case 0: addressbus=0b00000001; break;
			case 1: addressbus=0b00000010; break;
			case 2: addressbus=0b00000011; break;
			case 3: addressbus=0b00000100; break;
			case 4: addressbus=0b00000101; break;
			case 5: addressbus=0b00000110; break;
			case 6: addressbus=0b00000111; break;
			case 7: addressbus=0b00000000; break;
		}
													// 3_delay_ms(0.5); // delay in interrupt may cause problems. mostly thatswhy prescalar are provided.
	}
	
	z++;
	if (z==8)										 // 4 u have written if(z==0) { z=0; }
	{
		z=0;
	}
}
