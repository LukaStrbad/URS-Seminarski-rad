#include "functions.h"
#include  <util/delay.h>

#define DELAY 200
#define LED_COUNT 5

void loop();

int elapsed_from_0 = 0;

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
	switch ((int)round((float)elapsed_from_0 / DELAY) % LED_COUNT) {
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
		default:
		break;
	}
	elapsed_from_0 += DELAY;
	_delay_ms(DELAY);
}