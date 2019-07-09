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
#include <avr/interrupt.h>
//enum States {start, Init, INC, DEC, Wait, Reset}temp;
//#include "../header/io.h"
//#include "io.c"
//void TimerISR();
//void TimerOff();
//void TimerOn();
//void TimerSet(unsigned long M);
//void Tick();
void ADC_init();



//volatile unsigned char TimerFlag = 0;

//unsigned long _avr_timer_M = 1;
//unsigned long _avr_timer_cntcurr = 0;

//unsigned char i = 0x00;
//unsigned char c = '0';
//unsigned short AD_convert = 0x00;	
unsigned short MAX = 0xFF;
unsigned short temp = 0x00;


int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00;
	DDRB = 0xFF;
	//DDRD = 0xFF;
	PORTA = 0xFF;
	PORTB = 0x00;
	//PORTD = 0x00;
	
	ADC_init();
	//LCD_init();
	
	//temp = start;
	//TimerSet(50);//easy for demo
	//TimerSet(300);
	//TimerOn();
	//unsigned char tmpB = 0x00;
	
 /* Insert your solution below */
 
 	//tmpB = ~tmpB;
	//PORTB = tmpB;
	
	while (1) {
		temp = ADC;
		
		if(temp >=(MAX/2)){
			PORTB = 0x01;
		}else{
			PORTB = 0x00;
		}
		
			
	}
	return 1;

}

void ADC_init(){
	ADCSRA |= (1 << ADEN) | (1 <<ADSC) | (1 << ADATE);
}

/*
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
		case start:{
			LCD_Cursor(1);
			LCD_WriteData('0');
			temp = Init;
			break;
		}
		
		case Init:{
			if((~PINA & 0x03) == 0x01){
				temp = INC;￼
				break;
			}else if ((~PINA & 0x03) == 0x02){
				temp = DEC;
				break;
			}else if ((~PINA & 0x03) == 0x03){
				temp = Reset;
				break;
			}else{
				temp = Init;
				break;
			}
		}
		
		case INC:{
			if(i>=9){
				i=9;
			}else{
				++i;
			}
			LCD_Cursor(1);
			LCD_WriteData(i+'0');
			temp = Wait;
			break;
		}
		
		case DEC:{
			if(i<=0){
				i=0;
			}else{
				--i;
			}
			LCD_Cursor(1);
			LCD_WriteData(i+'0');
			temp = Wait;
			break;
		}
		
		case Wait:{
			if((~PINA & 0x03) == 0x01){
				temp = INC;￼
				break;
			}else if((~PINA & 0x03) == 0x02){
				temp = DEC;
				break;
			}else if((~PINA & 0x03) == 0x03){
				temp = Reset;
				break;
			}else{
				temp = Wait;
				break;
			}
		}
		
		case Reset:{		
			i = 0;
			LCD_Cursor(1);
			LCD_WriteData(i + '0');
			
			if((~PINA & 0x03) == 0x00){
				temp = Init;
				break;
			}else{
				temp = Reset;
				break;
			}
			
			
		}
		
		default:
		break;
	}
	
}
 */
