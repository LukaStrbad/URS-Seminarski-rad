#define F_CPU 16000000UL
#define BAUD 9600

#include <avr/io.h>
#include <util/setbaud.h>
#include <math.h>
#include <stdlib.h>

#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

char* int_to_charptr(int number);
void uart_putchar(char c);
void uart_init(void);
void uart_write(char *c);
void uart_writeln(char *c);
void uart_writeNum(int number);
void uart_writeNumLn(int number);

#endif /* FUNCTIONS_H_ */