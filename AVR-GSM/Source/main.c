//Standard Libraries
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
//Customized Libraries
#include "GSM.h"
#include "button.h"
#include "lcd.h"

void gsm_read_all(void);

int main(void)
{
	
	button_init();
	lcd_init();
		clearscreen();
		location(1,1);
			sendstring("Initializing... ");
		location(1,1);
			sendstring("==== BVM ====");
		location(1,2);	
			sendstring("AVRµc Project");
	gsm_init();	
	check_buttons();
	while(1)
	{
		check_buttons();
		gsm_read_all();
	}
	
}

void gsm_read_all()
{
	i=1;
	while(i<2)
	{
		gsm_read_byindex(i);
		i++;
	}
}
