#include <avr/io.h>
#include <util/delay.h>

#define PIN_CAP PB1     // Must be connected to AIN1
#define PIN_OUT PB0

#define GET_BIT(TGT, PIN)   ((TGT) & (1 << (PIN)))
#define SET_BIT(TGT, PIN)   do { TGT |=  (1 << (PIN)); } while(0)
#define CLEAR_BIT(TGT, PIN) do { TGT &= ~(1 << (PIN)); } while(0)

int main(void)
{
    // Set debug pin as an output
    SET_BIT(DDRB, PIN_OUT);

    // Set AIN1 as input, with internal pull-up resistor
    CLEAR_BIT(DDRB, PIN_CAP);
    CLEAR_BIT(PORTB, PIN_CAP);

    // Set up Analog Comparator to compare PIN_CAP to 1.1V bandgap
    CLEAR_BIT(ACSR, ACD);
    SET_BIT(ACSR, ACBG);
    CLEAR_BIT(ADCSRB, ACME);

    while(1) {
        if(!ACO) {
            SET_BIT(PORTB, PIN_OUT);
        } else {
            CLEAR_BIT(PORTB, PIN_OUT);
        }
    }
}
