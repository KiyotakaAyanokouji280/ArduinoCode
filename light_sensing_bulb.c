#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>


// initialize the ADC conversion
void adcinit () {
	// setting REFS1 = 0 and REFS0 = 1 to get Vref as AVCC pin | ADLAR = 0(right adjusted) | MUX 0000 for ADC0 selection
	ADMUX = 0b0100000;
	
	// set ADC status register A to enable ADC conversion(MSB = 1) and prescaler (3 LSB = 111 => divides clock by 128 for conversion speed)
	ADCSRA |= (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);  

}

void adcread (unsigned int channel) {
	// set the interrupts to be enabled
	SREG = 0x40;

	//channel & 00000111 will give the required input to mux in admux and or with REFS1 = 0 and REFS0 = 1 for initialization
	ADMUX |= 0x40 | (channel & 0x07);

	


}

ISR(INT0_vect) {

	PORTD ^= (1 << PD6);
}



int main() {
	
	// initialize adc conversion
	// adcinit();
	
	//chatgpt told that the design of the microcontroller is such that INT0 is related to PD2 and it is implicit relation. For PD3, INT1 and so on is there.
	//set PD2 as input. As soon as it gets high signal, it will trigger interrupt
	DDRD &= ~(1 << PD2);
	//activate internal pullup resistor
	PORTD |= (1 << PD2);
	
	//set PD6 as output
	DDRD|= (1 << PD6);
	


	//enable external interrupt through pin 0 with a positive edge trigger
	EIMSK |= (1 << INT0);
	EICRA |= (1 << ISC00) | (1 << ISC01);

	//enable global interrupts
	sei();	

	//when interrupt is there, blink led
	while (1) {
			

	}

	
	


	
	return 0;
}


