#include "functions.h"

void loop();

int main(void)
{
	// Tipkala
	//pinMode(6, INPUT_PULLUP);
	//pinMode(7, INPUT_PULLUP);
	DDRD &= 0b00111111;
	PORTD |= 0b11000000;

	// LED
	//pinMode(5, OUTPUT);
	DDRD |= 0b00100000;

	//Serial.begin(9600);
	uart_init();

	while (1)
	{
		loop();
	}
}

void loop()
{
	// Stanje SW1
	uart_write("SW1:\t");
	uart_write((PIND & 0b10000000) >> 7);
	// Stanje SW2
	uart_write("\tSW2:\t");
	uart_write((PIND & 0b01000000) >> 6);

	if ((PIND & 0b11000000) >> 6 != 0b11) {
		//digitalWrite(5, HIGH);
		PORTD |= 0b00100000;
		uart_writeln("\tUvjet Zadovoljen!");
	}
	else {
		//digitalWrite(5, LOW);
		PORTD &= 0b11011111;
		uart_writeln("\tUvjet nije zadovoljen!");
	}
}