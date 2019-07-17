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
#include "../header/io.h"
#include "io.c"
//#include "keypad.h"
#include "../header/timer.h"
#include "../header/scheduler.h"
#include "bit.h"
//enum pauseButtonSM_States{ pauseButton_wait, pauseButton_press, pauseButton_release};
//enum states{Wait, Keypair}temp;
//void K_tick;


//unsigned char key;
/*
int pauseButtonSMTick(int state){
	unsigned char x = GetKeypadKey();
	switch(state){
		case pauseButton_wait:
			state = x == '\0'? pauseButton_wait : pauseButton_press;
			break;
		case pauseButton_press:
			state = pauseButton_release;
			break;
		case pauseButton_release:
			state = x == '\0'? pauseButton_wait : pauseButton_press;
			break;
		default:
			state = pauseButton_wait;
			break;
	}
	switch(state){
		case pauseButton_wait:
			
			break;
		case pauseButton_press:
			LCD_Cursor(1);
			LCD_WriteData(x);
			break;
		case pauseButton_release:
			break;
	}
	return state;
}
*/

unsigned char message[] = "CS120B is Legend... wait for it DARY!";
enum Tick{start};
int Tick(int state){
	static unsigned char scroll = 16;
	static unsigned char disp = 0;
	static unsigned long crusor = 0;
	static unsigned long offset_trigger = 0;
	static unsigned long offset = 0;
	static unsigned long counter = 0;
	static unsigned int i = 16;
	unsigned long length = sizeof(message)/sizeof(message[0]);
	switch (state){
		case start:{
			LCD_ClearScreen();
            LCD_Cursor(16);
				if(counter < (length +15)){
					++counter;
					for(i= 16;i > scroll; --i){
						if ((crusor = (i-scroll-1 + offset)) >= (length -1)) {
							disp = 32;
						}else{
							disp = message[crusor];
						}
						LCD_Cursor(i);
						LCD_WriteData(disp);
					}
					if(scroll){
						scroll--;
						offset_trigger++;
					}
					if(offset_trigger >= 16){
						++offset;
					}
				}else{
					counter =0;
					scroll = 15;
					offset = 0;
					offset_trigger = 0;
				}
			}
        default: 
			state = start;
			break;
	}
	return state;
}



int main(void) {
    /* Insert DDR and PORT initializations */
    //DDRA = 0x00;

	//DDRA = 0xF0;
	DDRC = 0xFF;
	DDRD = 0xFF;
	//PORTA = 0xFF;

	//PORTA = 0x0F;
	PORTC = 0x00;
	PORTD = 0x00;
	
	//unsigned char x;
	static task task1;
	task *tasks[] = {&task1};
	const unsigned short numTasks = sizeof(tasks)/sizeof(task*);
	
	task1.state = 0;
	task1.period = 50;
	task1.elapsedTime = task1.period;
	task1.TickFct = &Tick;
	
	LCD_init();
	LCD_ClearScreen();
	unsigned short i;
	unsigned long GCD = tasks[0]->period;
		for(i=1;i<numTasks;i++){
			GCD = findGCD(GCD,tasks[i]->period);
		}
	
	TimerSet(GCD);
	TimerOn();
//	TimerFlag = 0;

	
	while (1) {
		for (i = 0; i< numTasks;i++){
			if(tasks[i]->elapsedTime == tasks[i] ->period){
				tasks[i]->state = tasks[i]->TickFct(tasks[i]->state);
				tasks[i]->elapsedTime = 0;
			}
			tasks[i]->elapsedTime +=GCD;
		}
		while(!TimerFlag);
		TimerFlag = 0;
	}

/*
		x = GetKeypadKey();
		switch(x){
			case '\0': 
				PORTB = 0x1F;
				break;
			case '1': 
				PORTB = 0x01; 
				break;
			case '2': 
				PORTB =0x02; 
				break;
			case '3': 
				PORTB =0x03; 
				break;
			case '4': 
				PORTB =0x04; 
				break;
			case '5': 
				PORTB =0x05; 
				break;
			case '6': 
				PORTB =0x06; 
				break;
			case '7': 
				PORTB =0x07; 
				break;
			case '8': 
				PORTB =0x08; 
				break;
			case '9': 
				PORTB =0x09; 
				break;
			case 'A': 
				PORTB =0x0A; 
				break;
			case 'B': 
				PORTB =0x0B; 
				break;
			case 'C': 
				PORTB =0x0C; 
				break;
			case 'D': 
				PORTB =0x0D; 
				break;
			case '*': 
				PORTB =0x0E; 
				break;
			case '0': 
				PORTB =0x00; 
				break;
			case '#': 
				PORTB =0x0F; 
				break;
			default: 
				PORTB = 0x1B; 
				break;
		}
			
	}
	*/
	return 1;

}




