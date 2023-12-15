#include <avr/io.h>
#include <util/delay.h>

#define OUT PB5

int main(void) {
        DDRB |= (1 << OUT);

        while (1) {
                PORTB ^= (1 << OUT);

                _delay_ms(10000);
        }
        return 0;
}
