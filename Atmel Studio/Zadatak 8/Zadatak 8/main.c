#include "functions.h"

#define DELAY 200
#define LED_COUNT 5

void loop();

int svjetlina = 128;

int main(void)
{
	// Tipkala
	//pinMode(8, INPUT_PULLUP);
	//pinMode(9, INPUT_PULLUP);
	DDRB &= 0b111100;
	PORTB |= 0b000011;

	// LED-ice
	//pinMode(3, OUTPUT);
	DDRD |= 0b00001000;

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

	// Lijevo tipkalo pritisnuto
	if (SW_state == 0b01) {
		svjetlina -= 10;
		if (svjetlina < 0)
		svjetlina = 0;
	}
	else if (SW_state == 0b10) {
		svjetlina += 10;
		if (svjetlina > 255)
		svjetlina = 255;
	}
	uart_write("Svjetlina: ");
	uart_writeln(svjetlina);

	TCCR2A = _BV(COM2A1) | _BV(COM2B1) | _BV(WGM21) | _BV(WGM20);
	TCCR2B = _BV(CS22);
	// Postavljanje duty cycle
	OCR2A = 255 - svjetlina;
	OCR2B = svjetlina;
}