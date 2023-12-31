#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <avr/interrupt.h>

#define OUTPUT PD7
#define F_CPU 16000000UL
void adcsetup () {
        // Use AVCC
        // Also use a 10 bit result
        // Set channel to ADC0 -> 0000 using MUX[3:0]
        ADMUX |= (0 << REFS1) | (0 << REFS0) | (0 << ADLAR) | (0 << MUX3)  | (0 << MUX2) | (0 << MUX1) | (0 << MUX0);

        // set up clock speed to about 130khz instead of the 16Mhz clock speed
        ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);

        // Enabling the ADEN to start conversion and enable interrupt also
        ADCSRA |= (1 << ADEN) | (1 << ADIE);
}



int main() {
        // Set Pin 7 on arduino as output
        DDRD |= (1 << OUTPUT);
        DDRB |= (1 << PB5);

        //set global interupts
        sei();

        // Setupt ADC
        adcsetup();

        //Program runs forever
        while(1) {};


        return 0;
}




ISR(ADC_vect) {

        uint8_t adclow = ADCL;
        uint16_t analogvalue = (ADCH << 2) | (adclow >> 6);
        PORTB |= (1 << PB5);

        // light on case
        if (analogvalue > 500) {
                PORTD |= (1 << OUTPUT);
        }
        else if (analogvalue <= 500) {
                PORTD &= ~(1 << OUTPUT);
        }

        // Start the conversion again
        ADCSRA |= (1 << ADSC);

}

