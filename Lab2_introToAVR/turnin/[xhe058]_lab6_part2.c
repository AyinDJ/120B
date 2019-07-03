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
#include <avr/interrupt.h>
enum States{Start,LED1,LED2,LED3,Stop,Reset}temp;
#endif
void TimerISR();
void TimerOff();
void TimerOn();
void TimerSet(unsigned long M);
void Tick();



volatile unsigned char TimerFlag = 0;

unsigned long _avr_timer_M = 1;
unsigned long _avr_timer_cntcurr = 0;

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00;
	DDRB = 0xFF;
	PORTA = 0xFF;
	PORTB = 0x00;
	
	temp = Start;
	TimerSet(50);//easy for demo
	//TimerSet(300);
	TimerOn();
	//unsigned char tmpB = 0x00;
	
 /* Insert your solution below */
 
 	//tmpB = ~tmpB;
	//PORTB = tmpB;
	
	while (1) {
		
		Tick();
		//tmpB = ~tmpB;
		//PORTB = tmpB;
		while (!TimerFlag);
		TimerFlag = 0;
	}
	return 1;

}


void TimerOn() {
	TCCR1B = 0x0B;
	OCR1A = 125;
	TIMSK1 = 0x02;
	TCNT1 = 0;
	_avr_timer_cntcurr = _avr_timer_M;
	SREG |= 0x80;	
}

void TimerOff(){
	TCCR1B = 0x00;
}

void TimerISR(){
	TimerFlag = 1;
}

ISR(TIMER1_COMPA_vect){
	_avr_timer_cntcurr--;
	if(_avr_timer_cntcurr == 0){
		TimerISR();
		_avr_timer_cntcurr = _avr_timer_M;
	}
}

void TimerSet (unsigned long M){
	_avr_timer_M = M;
	_avr_timer_cntcurr = _avr_timer_M;
}

void Tick(){
	
	switch(temp){
		case Start:{
			PORTB = 0x00;
			temp = LED1;
			break;
		}
		
		case LED1:{
			if((~PINA & 0x01) == 0x01){
			temp = Stop;
			break;
			}else{
				PORTB = 0x01;
				temp = LED2;
				break;
			}
		}
		
		case LED2:{
			if((~PINA & 0x01) == 0x01){
				temp = Stop;
				break;
			}else{
				PORTB = 0x02;
				temp = LED3;
				break;
			}
		}
		
		case LED3:{
			if((~PINA & 0x01) == 0x01){
				temp = Stop;
				break;
			}else{
			PORTB = 0x04;
			temp = LED1;
			break;
			}
		}
		
		case Stop:{
			if((~PINA & 0x01) == 0x01){
				temp = Stop;
				break;
			
			}else{
				temp = Reset;
				break;
			}
		}
		
		case Reset:{
			if((~PINA & 0x01) == 0x01){
				if (PORTB == 0x01){
					temp = LED1;
					break;
				}else if (PORTB == 0x02){
					temp = LED2;
					break;
				}else if (PORTB == 0x04){
					temp = LED3;
					break;
				}	
			}else{
				temp = Reset;
				break;
			}
		}
		
		default:
		break;
	}
	
}
