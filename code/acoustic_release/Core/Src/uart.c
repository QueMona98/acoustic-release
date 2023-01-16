#include "main.h"
#include "uart.h"

void write_char(uint8_t ch) {
	while (!(LPUART1->ISR & (1 << 7)));
	LPUART1->TDR = ch;
	while (!(LPUART1->ISR & (1 << 6)));
}

void write_str(char *str) {
	while (str) {
		write_char(*str);
		str++;
	}
}
