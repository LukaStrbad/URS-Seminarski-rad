#include "functions.h"
#include <util/delay.h>

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
	int led_num = (int)round((float)elapsed_from_0 / DELAY) % LED_COUNT;
	PORTD &= 0b10000011;
	PORTD |= 1 << (6 - led_num);

	elapsed_from_0 += DELAY;
	_delay_ms(DELAY);
}