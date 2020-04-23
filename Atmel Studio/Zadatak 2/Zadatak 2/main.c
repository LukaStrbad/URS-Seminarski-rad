#include "functions.h"

void loop();

int main(void)
{
	// Tipkala
	// ARDUINO NAREDBA: pinMode(6, INPUT_PULLUP);
	// ARDUINO NAREDBA: pinMode(7, INPUT_PULLUP);
	// Postavljanje registra DDR u 0 za pinove 6 i 7
	DDRD &= 0b00111111;
	// Postavljanje registra PORTD u 1 za pinove 6 i 7
	PORTD |= 0b11000000;

	// LED
	// ARDUINO NAREDBA: pinMode(5, OUTPUT);
	// Postavljanje registra DDR u 1 za pin 5 (postavljanje kao izlazni pin)
	DDRD |= 0b00100000;

	// ARDUINO NAREDBA: Serial.begin(9600);
	// Inicijalizacija uart serijske komunikacije
	uart_init();

	while (1)
	{
		loop();
	}
}

void loop()
{
	// Stanje SW1
	// Ispisivanje stanja prvog tipkala
	uart_write("SW1:\t");
	// Oèitavamo stanje 7. PIN registra
	uart_write((PIND & 0b10000000) >> 7);
	// Stanje SW2
	// Ispisivanje stanja drugog tipkala
	uart_write("\tSW2:\t");
	// Oèitavamo stanje 6. PIN registra
	uart_write((PIND & 0b01000000) >> 6);

	// Sa logièkom I (AND) operacijom uèitavamo stanje 6. i 7. PIN registra kao
	// jedan broj
	// Ako je taj broj 0 to znaèi da su oba tipkala pritisnuta
	if ((PIND & 0b11000000) >> 6 == 0) {
		// ARDUINO NAREDBA: digitalWrite(5, HIGH);
		// Postavljanje 5. PORT registra u 1 / najveæu vrijednosti / 5V
		PORTD |= 0b00100000;
		uart_writeln("\tUvjet Zadovoljen!");
	}
	// Ako je broj veæi od 0 to znaèi da je barem jedno tipkalo pritisnuto
	else {
		// ARDUINO NAREDBA: digitalWrite(5, LOW);
		// Postavljanje 5. PORT reigstra u 0V
		PORTD &= 0b11011111;
		uart_writeln("\tUvjet nije zadovoljen!");
	}
}