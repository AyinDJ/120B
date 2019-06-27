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
	DDRC = 0x00;
	DDRD = 0XFF;
	PORTA = 0xFF;
	PORTB = 0xFF;
	PORTC = 0xFF;
	PORTD = 0x00;
	unsigned char tempA = 0x00;
	unsigned char tempB = 0x00;
	unsigned char tempC = 0x00;
	unsigned char tempD = 0x00;
	unsigned char weightDifferent = 0x00;
	unsigned long total = 0x0000;
    /* Insert your solution below */
    while (1) {
	tempA = PINA;
	tempB = PINB;
	tempC = PINC;
	tempD = PIND;

	if(total>0x008C){
		tempD = tempD|0x01;
	}
	if(tempA>=tempC){
		weightDifferent = tempA - tempC;
	}else{
		weightDifferent = tempC - tempA;
	}
	
	if(weightDifferent>0x50){
		tempD = tempD|0x02;
	}
	
	PORTD = tempD;
    }
    return 1;
}
