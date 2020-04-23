#include "functions.h"

void loop();

int button = 0;


int main(void)
{
	// ARDUINO NAREDBA: pinMode(2, INPUT_PULLUP);
	// Inicijalizacija pina 2 da bude ulazni sa ukljuèenim unutrašnjim otpornikom
	// Postavljanje DDR registra u 0
	DDRD &= 0b11111011;
	// Postavljanje PORT registra u 1
	PORTD |= 0b00000100;
	
	// ARDUINO NAREDBA: Serial.begin(9600);
	// Inicijalizacija UART serijske komunikacije
	uart_init();
	
	while (1)
	{
		loop();
	}
}

void loop()
{
	// ARDUINO NAREDBA: button = digitalRead(pin_SW1);
	// Èitanje vrijednosti pina 2
	button = (PIND & 0b00000100) >> 2;
	
	
	// ARDUINO NAREDBA: Serial.print("SW1: \t");
	// Ispis teksta
	uart_write("SW1: \t");
	// ARDUINO NAREDBA: Serial.println(button1);
	// 0 - pritisnuto
	// 1 - nije pritisnuto
	// Ispis stanja pina
	uart_writeNumLn(button);
}