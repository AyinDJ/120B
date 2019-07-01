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
enum States {Start, Init, Releas,Pound, Wait} temp;
void Tick();
#endif

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00;
	DDRB = 0xFF;
	PORTA = 0xFF;
	PORTB = 0x00;

	temp = Start;	
 /* Insert your solution below */
	while (1) {
	Tick();
	}
	return 1;

}

void Tick(){
	
	switch(temp){
		case Start:{
			temp = Init;
			break;
		}

		case Init:{
			if((PINA & 0x04)==0x04){
				temp = Pound;
				break;
			}else if ((PINA & 0x80)==0x80){
				PORTB = 0x00;
				temp = Init;
				break;
			}else{
				temp =Init;
				break; 
			}
		}

		case Pound:{
			if(PINA == 0x00){
				temp = Releas;
				break;
			}else {
				temp = Pound;
				break;
			}
		}

		case Releas:{
			if((PINA & 0x02)==0x02){
				PORTB = 0x01;
				temp = Wait;
				break;
			}else{
				temp = Init;
				break;
			}
		}

		case Wait:{
			if((PINA & 0x80)==0x80){
				PORTB = 0x00;
				temp = Init;
				break;
			}else{
				temp = Wait;
				break;
			}
	
		}
		
		default:
		break;

	}






}

