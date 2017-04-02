#ifndef lcd
#define lcd

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

#define DataPORT 		PORTC
#define DataPORTdir 	DDRC
#define ControlPORT 	PORTD
#define ControlPORTdir 	DDRD
#define EN 7
#define RW 6
#define RS 5

char firstColumnPositionsForLCD[4] = {0, 64, 20, 84};

/************************ LCD FUNCTIONS ************************/
void check_busy(void);
void LCD_wait(void);
void sendcommand(unsigned char command);
void sendchar(unsigned char character);
void sendstring(char *StringOfCharacters);
void location(uint8_t x, uint8_t y);
void lcd_init(void);
void clearscreen(void);
/***************************************************************/

void check_busy()
{
	DataPORTdir = 0x00;
	ControlPORT |= 1<<RW;
	ControlPORT &= ~(1<<RS);

	while (DataPORT >= 0x80)
	{
	LCD_wait();
	}

	DataPORTdir = 0xFF; 
}

void LCD_wait()
{
	ControlPORT |= 1<<EN;
	ControlPORT &= ~(1<<EN);
}

void sendcommand(unsigned char command)
{
	check_busy();
	DataPORT = command;
	ControlPORT &= ~ ((1<<RW)|(1<<RS));
	LCD_wait();
	_delay_ms(5);
	DataPORT = 0;
}

void sendchar(unsigned char character)
{
	check_busy();
	DataPORT = character;
	ControlPORT &= ~ (1<<RW);
	ControlPORT |= 1<<RS;
	LCD_wait();
	_delay_us(200);
	DataPORT = 0x00;
}

void sendstring(char *StringOfCharacters)
{
	while(*StringOfCharacters > 0)
	{
		sendchar(*StringOfCharacters++);
	}
}

void sendint(int number)
{
char string[3];
itoa(number,string,10);
sendstring(string);
}

void location(uint8_t x, uint8_t y)
{
	sendcommand(0x80 + firstColumnPositionsForLCD[y-1] + (x-1));
}

void lcd_init()
{
	ControlPORTdir |= 1<<EN | 1<<RW | 1<<RS;
	_delay_ms(15);

	sendcommand(0x01); 
	_delay_ms(2);
	sendcommand(0x38);
	_delay_us(50);
	sendcommand(0b00001100);
	_delay_us(50);
}

void clearscreen(void)
{
	sendcommand(0x01);
}


#endif