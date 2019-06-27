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
	DDRC = 0xFF;
	PORTA = 0xFF;
	PORTC = 0x00;
	
	unsigned char temp = 0x00;
	unsigned char cntavail = 4;
    /* Insert your solution below */
    while (1) {
	temp = PINA;
	if((temp & 0x01)==1){
		cntavail=cntavail - 0x01;
	}
	if((temp & 0x02)==2){
                cntavail=cntavail - 0x01;
        }
	if((temp & 0x04)==4){
                cntavail=cntavail - 0x01;
        }
	if((temp & 0x08)==8){
                cntavail=cntavail - 0x01;
        }

	if(cntavail == 4){
		PORTC = 0x04;
	}else if(cntavail == 3){
                PORTC = 0x03;
        }else if(cntavail == 2){
                PORTC = 0x02;
        }else if(cntavail == 1){
                PORTC = 0x01;
        }else{
		PORTC = 0x80;
	}
	cntavail = 4;

    }
    return 1;
}
