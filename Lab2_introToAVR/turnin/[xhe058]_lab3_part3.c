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
	DDRC = 0XFF;
	PORTA = 0xFF;
	PORTC = 0x00;
 	unsigned char tempA = 0x00;
	unsigned char tempC = 0x00;
 /* Insert your solution below */
    while (1) {
	tempA = PINA;
	tempC = PINC;

	if((tempA & 0x00) == 0x00){
		tempC = 0x40;
	}
	if((tempA & 0x01) == 0x01 || (tempA & 0x02) == 0x02){
		tempC = 0x60;
	}
	if((tempA & 0x03) == 0x03 || (tempA & 0x04) == 0x04){
                tempC = 0x70;
        }
	if((tempA & 0x05) == 0x05 || (tempA & 0x06) == 0x06){
                tempC = 0x38;
        }
	if((tempA & 0x07) == 0x07 || (tempA & 0x08) == 0x08 || (tempA & 0x09) == 0x09){
                tempC = 0x3C;
        }
	if((tempA & 0x0A) == 0x0A || (tempA & 0x0B) == 0x0B || (tempA & 0x0C) == 0x0C){
                tempC = 0x3E;
        }
	if((tempA & 0x0D) == 0x0D || (tempA & 0x0E) == 0x0E || (tempA & 0x0F) == 0x0F){
                tempC = 0x3F;
        }

	if ((tempA & 0x30) == 0x30){
		if((tempA & 0x40) == 0x80){
			tempC = (tempC | 0x80);
		}else{
			tempC = tempC;
		}
	}
	PORTC = tempC;

    }
    return 1;
}
