/* 

	Kartik Nighania
 for any help feel free to contact on  - 

 www.KartikNighania.com
 kkstrack@gmail.com
 www.github.com/Kartik-Nighania to get codes of other projects as well :)
 
 Have Fun!

 */


#include "main.h"
#include "effect.h"
#include "launch_effect.h"
#include "draw.h"

/* We have a data line, a uln layer line which has 8 layers and an address line to
 switch D-flipFlop ic  as written in pdf in git hub
 */
  
#define dataDDR   DDRA
#define ulnDDR    DDRC
#define dataPort  PORTA
#define ulnPort   PORTC

/*
lower  fuse  bit 0xEF
Higher fuse  bit  0xC9
*/

int main (void)
{

// initializing the ports 
  dataDDR  = 0xff;	
  ulnDDR   = 0xff;	
  dataPort = 0x00; 
  ulnPort  = 0x00; 


  // Wave form generation Mode - clear on timer compare 
  // clear when OCR reaches 10
OCR2 = 10; 
TCCR2 |= (1 << CS20) | (1 << CS22) | (1 << WGM21); 
TCNT2 = 0x00;

// Enable interrupts
	TIMSK |= (1 << OCIE2);
	sei();

	current_layer = 1;	

	while (1)
	{
		for (int i=0; i<EFFECTS_TOTAL; i++) //show time
			launch_effect(i);
	}

}


ISR(TIMER2_COMP_vect)
{
	int i;

	LAYER_SELECT = 0x00; // all uln layers off

	for (i = 0; i < 8; i++) // latch data 
	{
		
		dataPort = cube[current_layer][i]; // placing data

		LATCH_ADDR = (LATCH_ADDR & LATCH_MASK_INV) | (LATCH_MASK & (i+1)); // placing data on latch
	}

	LAYER_SELECT = (0x01 << current_layer); // uln layer on for that layer


	current_layer++; // go to next later for the next time

	if (current_layer == 8) // taking care of overflow
		current_layer = 0;
}


