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
	DDRB = 0X00;
	DDRC = 0xFF;
	PORTA = 0xFF;
	PORTB = 0xFF;
	PORTC = 0x00;
	unsigned char tempA = 0x00;
	unsigned char tempB = 0x00;
	unsigned char totalA = 0x00;
	unsigned char totalB = 0x00;
	unsigned char temp = 0x00;
	unsigned char i;
    /* Insert your solution below */
    while (1) {
	tempA = PINA;
	tempB = PINB;
	totalA = 0x00;
	totalB = 0x00;
	
	for(i=0;i<8;i++){
		totalA = tempA + ((tempA & (0x01<<i))>>i);
	}
	for(i=0;i<8;i++){
                totalB = tempB + ((tempB & (0x01<<i))>>i);
        }
	PORTC = totalA + totalB;

    }
    return 1;
}
