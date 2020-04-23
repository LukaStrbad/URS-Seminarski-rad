#include <time.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "functions.h"
#define LED_COUNT 5
#define DELAY 200

int elapsed_from_0 = 0;
int prev_SW_state = -1;

void loop();
void left();
void right();

int main(void)
{
	// Tipkala
	//pinMode(8, INPUT_PULLUP);
	//pinMode(9, INPUT_PULLUP);
	DDRB &= 0b111100;
	PORTB |= 0b000011;
	
	// LED-ice
	//pinMode(2, OUTPUT);
	//...
	//pinMode(6, OUTPUT);
	DDRD |= 0b01111100;
	
	//Serial.begin(9600);
	uart_init();
	
	while (1)
	{
		loop();
	}
}

void loop()
{
	int SW_state = PINB & 0b000011;
	uart_write("SW1:\t");
	uart_writeNum(SW_state % 0b10); // Desni bit
	uart_write("\tSW2:\t");
	uart_writeNumLn(SW_state / 0b10); // Lijevi bit
	
	if (SW_state != prev_SW_state)
	{
		prev_SW_state = SW_state;
		PORTD &= 0b10000011;
		elapsed_from_0 = 0;
	}
	
	switch (SW_state)
	{
		case 0b01:
		right();
		break;
		case 0b10:
		left();
		break;
		case 0b00:
		PORTD |= 0b01111100;
		break;
		case 0b11:
		PORTD |= 0b00010000;
		break;
		default: break;
	}
	
	_delay_ms(1000);
}


void left()
{
	switch ((int)round((float)elapsed_from_0 / DELAY) % LED_COUNT)
	{
		case 0:
		PORTD &= 0b10000011;
		PORTD |= 0b00000100;
		elapsed_from_0 = 0;
		break;
		case 1:
		PORTD &= 0b10000011;
		PORTD |= 0b00001000;
		break;
		case 2:
		PORTD &= 0b10000011;
		PORTD |= 0b00010000;
		break;
		case 3:
		PORTD &= 0b10000011;
		PORTD |= 0b00100000;
		break;
		case 4:
		PORTD &= 0b10000011;
		PORTD |= 0b01000000;
		break;
		default: break;
	}
	elapsed_from_0 += DELAY;
	_delay_ms(DELAY);
}

void right()
{
	switch ((int)round((float)elapsed_from_0 / DELAY) % LED_COUNT)
	{
		case 0:
		PORTD &= 0b10000011;
		PORTD |= 0b01000000;
		elapsed_from_0 = 0;
		break;
		case 1:
		PORTD &= 0b10000011;
		PORTD |= 0b00100000;
		break;
		case 2:
		PORTD &= 0b10000011;
		PORTD |= 0b00010000;
		break;
		case 3:
		PORTD &= 0b10000011;
		PORTD |= 0b00001000;
		break;
		case 4:
		PORTD &= 0b10000011;
		PORTD |= 0b00000100;
		break;
		default: break;
	}
	elapsed_from_0 += DELAY;
	_delay_ms(DELAY);
}

