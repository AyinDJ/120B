/*	Author: xhe058
 *  Partner(s) Name: zhangcheng liang
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00;
	DDRB = 0xFF;
	PORTA = 0x00;
	PORTB = 0x00;
	
	unsigned char temp = 0x00;
    /* Insert your solution below */
    while (1) {
	temp = PINA;
	if(temp == 0x01){
		PORTB = 0x01;
	}else{
		PORTB = 0x00;
	}

	


    }
    return 1;
}
