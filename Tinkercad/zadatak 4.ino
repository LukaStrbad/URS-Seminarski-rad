#define F_CPU 16000000UL
#define BAUD 9600

#include <util/setbaud.h>
#include <math.h>
#include <stdlib.h>

class serial {
public:
    // Funkcija koja inicijalizira UART serijsku komunikaciju
    static void uart_init(void)
    {
        // Registri UBRR0H I UBRR0L zajedno čine djelitelj brzine komunikacije
        // UBRRH_VALUE je vrijednost gornjeg bajta djelitelja koji je izračunat u 
        // biblioteci setbaud.h
        UBRR0H = UBRRH_VALUE;
        // UBBRL_VALUE je vrijednost donjeg bajta djelitelja koji je izračunat u 
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
        // Omogućavanje 8-bitnih podataka
        UCSR0C = _BV(UCSZ01) | _BV(UCSZ00);
        // Omogućavanje RX i TX pinova
        UCSR0B = _BV(RXEN0) | _BV(TXEN0);
    }

    // Funkcija koja postavlja znak u podatkovni registar
    static void uart_putchar(char c)
    {
        // Petlja koja čeka dok podatkovni registar nije prazan
        // Kada se registar isprazni nastavlja se izvršavanje koda
        while (!(UCSR0A & (1 << UDRE0)));
        
        // Postavlja znak u podatkovni registar
        UDR0 = c;
    }
    // Funkcija koja prihvaća string te ispisuje sadržaj
    static void uart_write(char* c)
    {
        // Petlja kreće od 0 te se povećava za 1 svakim prolaskom
        // Ako je i-ti znak string-a \0 (znak za završetak string-a u C/C++) 
        // program izlazi iz petlje
        for (int i = 0; c[i] != '\0'; i++) {
            // Za svaki znak se poziva funkcija uart_putchar
            uart_putchar(c[i]);
        }
    }

    // Funkcija ispisuje string iz argumenta i dodaje znak nove linije na kraj
    static void uart_writeln(char* c)
    {
        uart_write(c);
        uart_write("\n");
    }
    // Drugi oblik funkcije koji prihvaća kao argument broj umjesto string-a
    static void uart_write(int number)
    {
        // Pozivanjem metode int_to_charptr se broj pretvara u niz znakova/string
        uart_write(int_to_charptr(number));
    }
    // Funkcija ispisuje broj i dodaje znak nove linije
    static void uart_writeln(int number)
    {
        uart_write(number);
        uart_write("\n");
    }
};

// Funkcija za pretvaranje cijelih brojeva u string
char* int_to_charptr(int number)
{
    // Ako je broj 0 funkcija vraća string "0"
    if (number == 0)
        return (char*)"0";
    // Bool varijabla koja oznaćava je li broj negativan (zadano je false)
    bool is_negative = false;
    if (number < 0) {
        // Ako je broj negativan vrijednost varijable je true
        is_negative = true;
        // Pretvaranje negativnog broja u pozitivan
        number = -number;
    }
    // Korištenjem matematike možemo izračunati koliko broj ima znamenaka
    // Log10 nekog broja će uvijek biti u skupu vrijednosti [brojZnamenki – 1, 
    // brojZnamenki>, zaokruživanjem vrijednosti na niži cijeli broj i dodavanjem 
    // broja 1 dobijemo broj znamenki
    int size = (int)log10(number) + 1;
    // Varijabla output je pokazivač kojem je alocirano memorije koliko broj ima 
    // znamenaka (+1 ako je broj negativan zbog minusa)
    char* output = (char*)malloc(sizeof(char) * (size + (is_negative ? 1 : 0)));
    // Ako je broj negativan na prvo mjesto postavljamo znak "-"
    if (is_negative)
        output[0] = '-';

    // Petlja se ponavlja onaj broj puta koliko broj ima znamenaka
    // Svakim prolaskom petlje broj se dijeli sa 10 zato što upisujemo zadnju 
    // desnu znamenku u polje
    for (int i = size - 1; i >= 0; i--, number /= 10) {
        // Na prvo slobodno mjesto s desne upisujemo znak koji predstavlja 
        // krajnju desnu znamenku
        // Broj povećamo za '0' jer to označava ASCII broj znamenke 0
        output[i + (is_negative ? 1 : 0)] = number % 10 + '0';
    }
    // Vraćanje pokazivača na znakovno polje
    return output;
}

void setup()
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
    serial::uart_init();
}

void loop()
{
    // Stanje SW1
    serial::uart_write("SW1:\t");
    serial::uart_write((PIND & 0b10000000) >> 7);
    // Stanje SW2
    serial::uart_write("\tSW2:\t");
    serial::uart_write((PIND & 0b01000000) >> 6);

    if ((PIND & 0b11000000) >> 6 != 0b11) {
        //digitalWrite(5, HIGH);
        PORTD |= 0b00100000;
        serial::uart_writeln("\tUvjet Zadovoljen!");
    }
    else {
        //digitalWrite(5, LOW);
        PORTD &= 0b11011111;
        serial::uart_writeln("\tUvjet nije zadovoljen!");
    }
}
