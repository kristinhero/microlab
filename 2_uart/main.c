#include "gpio.h"
#include "uart.h"
#include <stdio.h>

ssize_t _write(int fd, const void *buf, size_t count){
    char * letter = (char *)(buf);
    for(int i = 0; i < count; i++){
        uart_send(*letter);
        letter++;
    }
    return count;
}

ssize_t _read(int fd, void *buf, size_t count){
    char *str = (char *)(buf);
    char letter;
    do {
        letter = uart_read();
    } while(letter == '\0');
        *str = letter;
        return 1;
    }

int main(){
    for(int i = 4; i <= 15; i++){
		GPIO->DIRSET = (1 << i);
		GPIO->OUTCLR = (1 << i);
	}

    GPIO->PIN_CNF[17] = 0;
	GPIO->PIN_CNF[26] = 0;

    GPIO->PIN_CNF[25] = 0;
    GPIO->PIN_CNF[24] = 1;

    uart_init();

    iprintf("The chemical formula for Ketamine is C%dH%dClNO\n\r",13,16);

    while(1){
        if(!(GPIO->IN & (1 << 17))){
			uart_send('A');
		}
        if(!(GPIO->IN & (1 << 26))){
			uart_send('B');
		}

        if(uart_read() != '\0'){
            uart_send(uart_read());
            for(int i = 13; i <= 15; i++){
                GPIO->OUT ^= (1 << i);
            }
        }

        int sleep = 10000;
        while(sleep--);
    }

    return 0;
}