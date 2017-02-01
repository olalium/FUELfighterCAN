#include "deffinitions.h""
#include <avr/io.h>
#include <avr/interrupt.h>
#include "can.h"
#include <util/delay.h>
volatile int state = 0;
//#include "tim.h"


int main(void)
{
	
	cli();			//Setup CAN
	init_can();		//start_timer();
	sei();
		
	union can_frame CAN_test;
	CAN_test.id = 3;				//ID	
	CAN_test.data[0] = 1;			//DATA
	CAN_test.length = 1;			//LENGDE
	
	DDRB |= 0b11111111;
	PORTB |= (1 << PB5)|(1<<PB6)|(1<<PB7);
	toggleLed();
	_delay_ms(TID);
	toggleLed();
	
	
	// MAIN CONTROL LOOP
	while(1) {
		for(int i =0; i< 100;i++){ //delay
			_delay_ms(TID);	
		}
		send_can_message(CAN_test.id, CAN_test.data, &CAN_test);
	}
	
	// MAIN CONTROL LOOP
	for (;;) {
		if (new_can_frame()) {
			union can_frame *CAN_test;		//temporaraly declare space on stack
			CAN_test = read_can_frame();
			if (CAN_test->id == 1) {
				toggleLed();
			}
			next_can_frame();
		}
	}
}

void toggleLed(){
	if (state == 0)
	{
		PORTB &= ~((1 << PB5)|(1<<PB6)|(1<<PB7));
		state = 1;
		} else {
		PORTB |= (1 << PB5)|(1<<PB6)|(1<<PB7);
		state = 0;
	}
}