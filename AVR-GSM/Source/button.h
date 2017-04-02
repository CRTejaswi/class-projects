#ifndef button
#define button

#include "GSM.h"
#include "lcd.h"


void button_init(void);
void check_buttons(void);


void button_init()
{

	//setting PortA pin 0 high and 
	PORTA |=  (1<<PA0);
	//setting it as an input
	DDRA  &= ~(1<<DDA0);
	
	//setting PortA pin 1 high and 
	PORTA |=  (1<<PA1);
	//setting it as an input
	DDRA  &= ~(1<<DDA1);
	
	//Setting other pins on portA as output
	DDRA  |= (1<<PA2);
	DDRA  |= (1<<PA3);
	DDRA  |= (1<<PA4);
	DDRA  |= (1<<PA5);
	DDRA  |= (1<<PA6);
	DDRA  |= (1<<PA7);
	
}

void check_buttons()
{
	if(bit_is_clear(PINA,0))
	{
		clearscreen();
		location(1,1);
		sendstring("Deleting all... ");
		for(i=1;i<=20;i++)
		{
			gsm_delete_byindex(i);
		}
	}
	if(bit_is_clear(PINA,1))
	{
		clearscreen();
		location(1,1);
		sendstring(" Sending status  ");
		location(1,2);
		sendstring("  to Operator...");
		
		check_ports();
		_delay_ms(1000);
		
	}
	
	
}



#endif
