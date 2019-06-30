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
enum States {Start, Init, On, Off, Wait_1, Wait_2} temp;
#endif

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00;
	DDRB = 0XFF;
	PORTA = 0xFF;
	PORTB = 0x00;

	temp = Start;	
 /* Insert your solution below */
    while (1) {
	
	switch(temp){
		case Start:
		PORTB = 0x01;
		temp = Init;
		break;

		case Init:
		if ((~PINA & 0x01)==0x01){
			temp = Off;
			PORTB = 0x02;
			break;
		}else{
			temp = Init;
			PORTB = 0x01;
			break;
		}

		case On:
		if ((~PINA & 0x01)==0x00){
			temp = Wait_2;
			break;
		}else{
			temp = On;
			PORTB = 0x01;
			break;
		}

		case Off:
		if ((~PINA & 0x01)==0x00){
			temp = Wait_1;
			break;
		}else{
			temp = Off;
			PORTB = 0x02;
			break;
		}

		case Wait_1:
		if((~PINA & 0x01)==0x01){
			temp = On;
			PORTB = 0x01;
			break;
		}else{
			temp = Wait_1;
			break;
		}

		case Wait_2:
		if((~PINA & 0x01)==0x01){
			temp = Off;
			PORTB = 0x02;
			break;
		}else{
			temp = Wait_2;
			break;
		}
		default:
			break;
	}

    }
    return 1;
}
