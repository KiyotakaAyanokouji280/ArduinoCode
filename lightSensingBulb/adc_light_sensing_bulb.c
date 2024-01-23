#include <avr/io.h>
#include <avr/interrupt.h>


void setup () {
    //enable the adc, enable interrupt on conversion complete, set clock divider = 128 (8Mhz/128 = 62.5Khz)
    ADCSRA |= (1 << ADEN) | (1 << ADIE) | (1 << ADSC) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);

    // vcc reference voltage and result as XXXXXXRR-RRRRRRRR (ADCH-ADCL)
    ADMUX |= (1 << REFS0) | (0 << REFS1) | (0 << ADLAR);
}

int main () {
    // pin 13 is output
    DDRB |= (1 << PB5);
    PORTB &= ~(1 << PB5);
    // PORTB |= (1 << PB5);
    // set interrupts globally
    sei();
    
    //adc setup
    setup ();

    //program runs forever
    while (1);

}


ISR(ADC_vect) {
    uint16_t value = ADC;


    // if there's less/no light turn on led
    if (value < 650) {
        PORTB |= (1 << PB5);
    }

    //if there's light turn off led
    else {
        PORTB &= ~(1 << PB5);
    }

    ADCSRA |= 1<<ADSC;

}
