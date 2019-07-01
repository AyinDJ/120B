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
enum States {Start, Init, INC, DEC, Wait, Reset} temp;
void Tick();
#endif

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00;
	DDRC = 0XFF;
	PORTA = 0xFF;
	PORTC = 0x00;

	temp = Start;	
 /* Insert your solution below */
	while (1) {
	Tick();
	}

}

void Tick(){
	
	switch(temp){
		case Start:{
			temp = Init;
		}

		case Init:{
			PORTC = 0x07;
			if((PINA & 0x03)==0x01){
				temp = INC;
				break;
			}else if ((PINA & 0x03)==0x02){
				temp = DEC;
				break;
			}else if((PINA & 0x03)==0x03){
				temp = Reset;
				break;
			}else{
				temp =Init;
				break; 
			}
		}

		case INC:{
			if(PORTC >= 0x09){
				PORTC = 0x09;
				temp = Wait;
				break;
			}else{
				PORTC = PORTC + 0x01;
				temp = Wait;
				break;
			}
		}

		case DEC:{
			if(PORTC <= 0x00){
				PORTC = 0x00;
				temp = Wait;
				break;
			}else{
				PORTC = PORTC - 0x01;
				temp = Wait;
				break;
			}
		}

		case Wait:{
			if((PINA & 0x03)==0x01){
				temp = INC;
				break;
			}else if ((PINA & 0x03)==0x02){
				temp = DEC;
				break;
			}else if ((PINA & 0x03)==0x03){
				temp = Reset;
				break;
			}else{
				temp = Wait;
				break;
			}
		}

		case Reset:{
			if((PINA & 0x03)==0x03){
				temp = Reset;
				PORTC = 0x07;
				break;
			}else{
				temp = Init;
				break;
			}
		}
		
		default:
		break;

	}






}

