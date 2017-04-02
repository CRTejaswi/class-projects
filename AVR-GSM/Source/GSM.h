#ifndef GSM
#define GSM

#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include <avr/wdt.h>
#include <avr/interrupt.h>


#include "lcd.h"

char operator_phone[] = "+919427140794"; //Customized Ph No.
char status[50]="";
char msg[7];
char number[14];
int i,j;


/*********************** UART FUNCTIONS ************************/
void UART_Init( unsigned int baud );
void UART_Transmit_char( unsigned char data );
unsigned char UART_Receive( void );
void UART_Transmit_string( char *string );
/***************************************************************/

void UART_Init( unsigned int baud )
{
   /* Set baud rate */
   UBRRH = (unsigned char)(baud>>8);
   UBRRL = (unsigned char)baud;
   /* Enable receiver and transmitter */
   UCSRB = (1<<RXEN)|(1<<TXEN);
   /* Set frame format: 8-bit data, 1 stop bit */
   UCSRC = (1<<URSEL)|(0<<USBS)|(3<<UCSZ0);
}

void UART_Transmit_char( unsigned char data )
{
   /* Wait for empty transmit buffer */
   while ( !( UCSRA & (1<<UDRE)) )
   ;
   /* Put data into buffer, sends the data */
   UDR = data;
}

unsigned char UART_Receive( void )
{
   /* Wait for data to be received */
   while ( !(UCSRA & (1<<RXC)) )
   ;
   /* Get and return received data from buffer */
   return UDR;
}
void UART_Transmit_string( char string[] )
{
   int i=0;
   while ( string[i] > 0)
   UART_Transmit_char(string[i++]);
}
/************************ GSM FUNCTIONS ************************/
void gsm_init(void);
void gsm_read_byindex(int i);
void gsm_send(char *number,char *string);
void gsm_delete(void);
void gsm_delete_byindex(int i);
void gsm_waitfor(char c);
void check_ports(void);
/***************************************************************/
char temp;
void gsm_waitfor(char c)
{
	//enabling watchdogtimer with a time of 2.1secs
	wdt_enable(7);
	//waiting for the byte to be received
	while(UART_Receive()!= c);
	//resetting watchdogtimer and turning off the watchdogtimer
	wdt_reset();
	wdt_disable();
}

void gsm_init()
{
	
	UART_Init(71);
	location(1,2);
	sendstring(" Testing Modem  ");
	_delay_ms(500);
	UART_Transmit_string("AT\r");
	gsm_waitfor('O');
	gsm_waitfor('K');
	location(1,2);
	sendstring("   Modem : OK   ");
	_delay_ms(1000);
	
	INS:
		location(1,2);
		sendstring(" Checking SIM   ");
		_delay_ms(500);
		UART_Transmit_string("AT+CSMINS?\r");
	   gsm_waitfor( '\n');
	   gsm_waitfor(',');
	   if(UART_Receive() == '2')
		{	
			location(1,2);
			sendstring("  SIM NOTFOUND  ");
			_delay_ms(1000);
			goto INS;
		}
		else if(UART_Receive() == '1');
		gsm_waitfor( 'K');
		gsm_waitfor( '\n');
		location(1,2);
		sendstring("   SIM FOUND    ");
		_delay_ms(1000);
		
	REG:
	   
	   
	   location(1,2);
		sendstring(" Network Status ");
		_delay_ms(500);
		UART_Transmit_string("AT+CREG?\r");
	   gsm_waitfor( '\n');
	   gsm_waitfor(',');
	   if(UART_Receive() == '2')
		{
			location(1,2);
			sendstring("Network Not Found");
			_delay_ms(1000);
			goto REG;
		}
		else if(UART_Receive() == '1');
		gsm_waitfor( 'K');
		gsm_waitfor( '\n');
		location(1,2);
		sendstring(" Network Found  ");
		_delay_ms(1000);
		
	location(1,2);
	sendstring(" Turn on Echo  ");
	_delay_ms(500);
	UART_Transmit_string("ATE1\r");
	gsm_waitfor('O');
	gsm_waitfor('K');
	location(1,2);
	sendstring(" Echo turned on ");
	_delay_ms(1000);
	
	UART_Transmit_string("AT+CMGF=1\r");
	location(1,2);
	sendstring("Setting Textmode");
	gsm_waitfor('O');
	gsm_waitfor('K');
	location(1,2);
	sendstring("  Textmode set  ");
	_delay_ms(1000);

}

void gsm_read_byindex(int index)
{
	int k;
	char string[2];
	itoa(index,string,10);
	clearscreen();
	location(1,1);
	sendstring("Reading Messages");
	location(1,2);
	j++;
	if(j<16)
	{
		for(int a=0;a<j;a++)
			sendstring(".");
	}
	else if(j>=16)
	{
		j=1;
		for(int a=0;a<j;a++)
			sendstring(".");
	}
	UART_Transmit_string("AT+CMGR=");
	UART_Transmit_string(string);
	UART_Transmit_string("\r");
	
	gsm_waitfor('\r');
	gsm_waitfor('\n');		
		if(UART_Receive()=='+')
		{	
			gsm_waitfor('M');
			if(UART_Receive()=='G')
			{
				gsm_waitfor('A');
				gsm_waitfor(',');
				gsm_waitfor('"');
				
				
				for(k=0;k<13;k++)
				number[k] = UART_Receive();
				
				
				gsm_waitfor(',');
				gsm_waitfor(',');
				gsm_waitfor('+');
				gsm_waitfor('\n');
				
				for(k=0;k<6;k++)
				msg[k]=UART_Receive();
				
				gsm_waitfor('K');
				gsm_waitfor('\n');
				
				_delay_ms(300);
				clearscreen();
				location(1,1);
				sendstring("ph:");
				sendstring(number);
				location(1,2);
				sendstring("Message:");
				sendstring(msg);
				_delay_ms(2000);
				
				if(strcmp(number,operator_phone))
				{
				gsm_send(number,"You are not authorized to send this message");
				0}
				else if(!(strcmp(number,operator_phone)))
				{
					if(!strcmp(msg,"1 on  "))
						PORTA |= (1<<PA2);
					if(!strcmp(msg,"2 on  "))
						PORTA |= (1<<PA3);
					if(!strcmp(msg,"3 on  "))
						PORTA |= (1<<PA4);
					if(!strcmp(msg,"4 on  "))
						PORTA |= (1<<PA5);
					if(!strcmp(msg,"5 on  "))
						PORTA |= (1<<PA6);
					if(!strcmp(msg,"6 on  "))
						PORTA |= (1<<PA7);
					if(!strcmp(msg,"1 off "))
						PORTA &= ~(1<<PA2);
					if(!strcmp(msg,"2 off "))
						PORTA &= ~(1<<PA3);
					if(!strcmp(msg,"3 off "))
						PORTA &= ~(1<<PA4);
					if(!strcmp(msg,"4 off "))
						PORTA &= ~(1<<PA5);
					if(!strcmp(msg,"5 off "))
						PORTA &= ~ (1<<PA6);
					if(!strcmp(msg,"6 off "))
						PORTA &= ~(1<<PA7);
					if(!strcmp(msg,"report"))
						check_ports();
				}
				gsm_delete_byindex(index);	
			}			
		}	
	_delay_ms(1000);
}

void gsm_send(char *number,char *string)
{
	UART_Transmit_string("AT+CMGS=\"");
	UART_Transmit_string(number);
	UART_Transmit_string("\"\r");
	
	gsm_waitfor('>');
	
	UART_Transmit_string(string);
	UART_Transmit_char(0x1A);
	
	while(UART_Receive()!= '+');
	while(UART_Receive()!= ' ');
	while(UART_Receive()!= '\n');
	
	_delay_ms(1000);

}

void gsm_delete()
{
	UART_Transmit_string("AT+CMGD=1\r");
	gsm_waitfor('K');
	gsm_waitfor('\n');
	_delay_ms(500);
	
}

void gsm_delete_byindex(int i)
{
	UART_Transmit_string("AT+CMGD=");
	char string[2];
	itoa(i,string,10);
	UART_Transmit_string(string);
	UART_Transmit_string("\r");
	gsm_waitfor('K');
	gsm_waitfor('\n');
	_delay_ms(500);
	
}

void check_ports()
{
	if(bit_is_set(PINA,2))
		strcat(status,"1_on ");
	else 
		strcat(status,"1_off ");

	if(bit_is_set(PINA,3))
		strcat(status,"2_on ");
	else 
		strcat(status,"2_off ");

	if(bit_is_set(PINA,4))
		strcat(status,"3_on ");
	else 
		strcat(status,"3_off ");

	if(bit_is_set(PINA,5))
		strcat(status,"4_on ");
	else 
		strcat(status,"4_off ");

	if(bit_is_set(PINA,6))
		strcat(status,"5_on ");
	else 
		strcat(status,"5_off ");

	if(bit_is_set(PINA,7))
		strcat(status,"6_on ");
	else 
		strcat(status,"6_off ");

	gsm_send(operator_phone,status);
	status[0] = '\0';
	clearscreen();
	location(1,1);
}

#endif