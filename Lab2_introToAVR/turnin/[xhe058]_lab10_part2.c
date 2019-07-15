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
enum ThreeLEDsSM {T_Start, LED1, LED2, LED3} T_temp;
enum BlinkingLEDSM{B_Start, On, Off} B_temp;
enum CombineLEDsSM{C_Start, Output} C_temp;
#include "../header/io.h"
#include "io.c"
void TimerISR();
void TimerOff();
void TimerOn();
void TimerSet(unsigned long M);
void Tick_T();
void Tick_B();
void Tick_C();
//void ADC_init();
//void set_PWM();
//void PWM_on();
//void PWM_off();

unsigned char LEDs = 0x00;
unsigned short count_T = 0x00;
unsigned char Blink = 0x00;
unsigned short count_B = 0x00;
unsigned char Out = 0x00;




volatile unsigned char TimerFlag = 0;

unsigned long _avr_timer_M = 1;
unsigned long _avr_timer_cntcurr = 0;

//unsigned char i = 0x00;
//unsigned char c = '0';
//unsigned short AD_convert = 0x00;	



int main(void) {
    /* Insert DDR and PORT initializations */
    //DDRA = 0x00;
	DDRB = 0xFF;
	//DDRD = 0xFF;
	//PORTA = 0xFF;
	PORTB = 0x00;
	//PORTD = 0x00;
	T_temp = T_Start;
	B_temp = B_Start;
	C_temp = C_Start;
	
	count_T = 0;
	count_B = 0;
	
	
	//PWM_on();
	
	//ADC_init();
	//LCD_init();
	
	//temp = start;
	//TimerSet(1);//easy for demo
	TimerSet(1);
	TimerOn();
	//unsigned char tmpB = 0x00;
	
 /* Insert your solution below */
 
 	//tmpB = ~tmpB;
	//PORTB = tmpB;
	
	while (1) {
		Tick_T();
		Tick_B();
		Tick_C();
		
		while (!TimerFlag);
        TimerFlag = 0;
			
	}
	return 1;

}
/*
void set_PWM(double frequency){
	static double current_frequency;
	if(frequency != current_frequency){
		if(!frequency){
			TCCR3B &= 0x08;
		}else{
			TCCR3B |=0x03;
		}
		if(frequency < 0.954){
			OCR3A = 0xFFFF;
		}else if (frequency>31250){
			OCR3A = 0x0000;
		}else{
			OCR3A = (short)(8000000 / (128 * frequency))-1;
		}
		TCNT3 = 0;
		current_frequency = frequency;
	}
}

void PWM_on(){
	TCCR3A = (1<<COM3A0);
	TCCR3B = (1<<WGM32) | (1<<CS31) | (1<<CS30);
	set_PWM(0);
}

void PWM_off(){
	TCCR3A = 0x00;
	TCCR3B = 0x00;
}
*/

void Tick_T(){
	
	switch(T_temp){
		case T_Start:{
			T_temp = LED1;
			break;
		}
		
		case LED1:{
			LEDs = 0x01;
			if (count_T<30){
				T_temp = LED1;
				count_T++;
				break;
			}else{
				T_temp = LED2;
				count_T = 0;
				break;
			}
		}
		
		case LED2:{
			LEDs = 0x02;
			if (count_T <30){
				T_temp	= LED2;
				count_T++;
				break;
			}else{
				T_temp = LED3;
				count_T = 0;
				break;
			}
		}
		
		case LED3:{
			LEDs = 0x04;
			if (count_T <30){
				T_temp	= LED3;
				count_T++;
				break;
			}else{
				T_temp = LED1;
				count_T = 0;
				break;
			}
		}
		
		default:
		break;
		
	}
	
}

void Tick_B(){
	switch(B_temp){
		case B_Start:{
			B_temp = On;
			break;
		}
		
		case On:{
			Blink = 0x08;
			if (count_B < 100){
				B_temp = On;
				count_B++;
				break;
			}else{
				B_temp = Off;
				count_B = 0;
				break;
			}
		}
		
		case Off:{
			Blink = 0x00;
			if (count_B <100){
				B_temp = Off;
				count_B++;
				break;
			}else{
				B_temp = On;
				count_B = 0;
				break;
			}
		}
		
		default:
		break;
		
	}
	
}

void Tick_C(){
	
	switch(C_temp){
		case C_Start:{
			C_temp = Output;
			break;
		}
		
		case Output:{
			Out = Blink | LEDs;
			PORTB = Out;
			break;
		}
	}	
	
	
	
}



/*
void ADC_init(){
	ADCSRA |= (1 << ADEN) | (1 <<ADSC) | (1 << ADATE);
}
*/

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
