#include "functions.h"

void loop();

int button = 0;

int main(void)
{
	//pinMode(2, INPUT);
	DDRD &= 0b11111011;
	
	//Serial.begin(9600);
	uart_init();
	
	while (1)
	{
		loop();
	}
}

void loop()
{
	//button1 = digitalRead(2);
	button = (PIND & 0b00000100) >> 2;
	
	
	//Serial.print("SW1: \t");
	uart_write("SW1: \t");
	// 0 - pritisnuto
	// 1 - nije pritisnuto
	//Serial.println(button1);
	uart_writeNumLn(button);
}