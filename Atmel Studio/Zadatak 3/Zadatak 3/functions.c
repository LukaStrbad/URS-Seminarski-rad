
#include "functions.h"

char* int_to_charptr(int number)
{
	// Ako je broj 0 funkcija vra�a string "0"
	if (number == 0)
	return (char*)"0";
	// Bool varijabla koja ozna�ava je li broj negativan (zadano je false)
	short is_negative = 0;
	if (number < 0) {
		// Ako je broj negativan vrijednost varijable je true
		is_negative = 1;
		// Pretvaranje negativnog broja u pozitivan
		number = -number;
	}
	// Kori�tenjem matematike mo�emo izra�unati koliko broj ima znamenaka
	// Log10 nekog broja �e uvijek biti u skupu vrijednosti [brojZnamenki � 1,
	// brojZnamenki>, zaokru�ivanjem vrijednosti na ni�i cijeli broj i dodavanjem
	// broja 1 dobijemo broj znamenki
	int size = (int)log10(number) + 1;
	// Varijabla output je pokaziva� kojem je alocirano memorije koliko broj ima
	// znamenaka (+1 ako je broj negativan zbog minusa)
	char* output = (char*)malloc(sizeof(char) * (size + (is_negative ? 1 : 0)));
	// Ako je broj negativan na prvo mjesto postavljamo znak "-"
	if (is_negative)
	output[0] = '-';

	// Petlja se ponavlja onaj broj puta koliko broj ima znamenaka
	// Svakim prolaskom petlje broj se dijeli sa 10 zato �to upisujemo zadnju
	// desnu znamenku u polje
	for (int i = size - 1; i >= 0; i--, number /= 10) {
		// Na prvo slobodno mjesto s desne upisujemo znak koji predstavlja
		// krajnju desnu znamenku
		// Broj pove�amo za '0' jer to ozna�ava ASCII broj znamenke 0
		output[i + (is_negative ? 1 : 0)] = number % 10 + '0';
	}
	// Vra�anje pokaziva�a na znakovno polje
	return output;
}

// Funkcija koja inicijalizira UART serijsku komunikaciju
void uart_init(void)
{
	// Registri UBRR0H I UBRR0L zajedno �ine djelitelj brzine komunikacije
	// UBRRH_VALUE je vrijednost gornjeg bajta djelitelja koji je izra�unat u
	// biblioteci setbaud.h
	UBRR0H = UBRRH_VALUE;
	// UBBRL_VALUE je vrijednost donjeg bajta djelitelja koji je izra�unat u
	// biblioteci setbaud.h
	UBRR0L = UBRRL_VALUE;

	// Makro koji ispituje koristi li se dvostruka brzina prijenosa
	#if USE_2X
	// Ako se koristi postavlja se U2X0 registar u 1
	UCSR0A |= _BV(U2X0);
	#else
	// Ako ne postavlja se u 0
	UCSR0A &= ~(_BV(U2X0));
	#endif
	// Omogu�avanje 8-bitnih podataka
	UCSR0C = _BV(UCSZ01) | _BV(UCSZ00);
	// Omogu�avanje RX i TX pinova
	UCSR0B = _BV(RXEN0) | _BV(TXEN0);
}

// Funkcija koja postavlja znak u podatkovni registar
void uart_putchar(char c)
{
	// Petlja koja �eka dok podatkovni registar nije prazan
	// Kada se registar isprazni nastavlja se izvr�avanje koda
	while (!(UCSR0A & (1 << UDRE0)));
	
	// Postavlja znak u podatkovni registar
	UDR0 = c;
}
// Funkcija koja prihva�a string te ispisuje sadr�aj
void uart_write(char* c)
{
	// Petlja kre�e od 0 te se pove�ava za 1 svakim prolaskom
	// Ako je i-ti znak string-a \0 (znak za zavr�etak string-a u C/C++)
	// program izlazi iz petlje
	for (int i = 0; c[i] != '\0'; i++) {
		// Za svaki znak se poziva funkcija uart_putchar
		uart_putchar(c[i]);
	}
}

// Funkcija ispisuje string iz argumenta i dodaje znak nove linije na kraj
void uart_writeln(char* c)
{
	uart_write(c);
	uart_write("\n");
}

// Funkcija koja prihva�a broj i ispisuje ga
void uart_writeNum(int number)
{
	// Pozivanjem metode int_to_charptr se broj pretvara u niz znakova/string
	uart_write(int_to_charptr(number));
}

// Funkcija ispisuje broj i dodaje znak nove linije
void uart_writeNumLn(int number)
{
	uart_write(number);
	uart_write("\n");
}