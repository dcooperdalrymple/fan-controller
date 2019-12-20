/**
 * Title: ATtiny13 PWM Fan Controller
 * Author: D Cooper Dalrymple
 * Created: 19/12/2019
 * Updated: 19/12/2019
 * https://dcooperdalrymple.com/
 *
 * Hardware: 10K linear pot to PB2, 1K resistor from PB1 PWM output to fan control pin, 10uF and 0.1uF decoupling capacitors recommended
 * Based on: https://gist.github.com/HybridAir/bae9214f31dd2d5e7c697416614eab25
 */

#ifndef F_CPU
#define F_CPU 9600000UL
#endif

#include <avr/io.h>
#include <util/delay.h>

#define FAN_LOW     9
#define FAN_HIGH    48

#define POT_LIMIT   235

static void pwm_init(void) {
    TCCR0B |= (1 << CS01) | (1 << WGM02); // Set timer 0 prescaler (CS01) to div 8; set fast PWM mode 7 (WGM02)

    TCCR0A |= (1 << WGM01) | (1 << WGM00); // Set fast PWM mode 7
    TCCR0A |= (1 << COM0B1); // Clear OC0B output on compare match

    DDRB |= (1 << PB1); // Enable PWM output pin
    OCR0A = 47; // TOP value used to set 25khz pwm freq (9600000 / (8*(47+1)) = 25000

    OCR0B = FAN_LOW; // PWM duty cycle, 0 to 48 due to reduced pwm resolution
}

static void pwm_set(uint8_t value) { // value: 0 -> 255
    OCR0B = ((FAN_HIGH - FAN_LOW) * (uint16_t)value) / 255 + FAN_LOW;
}

static void adc_init(void) {
    // Set the ADC input to PB2/ADC1
    ADMUX |= (1 << MUX0);
    ADMUX |= (1 << ADLAR);

    // Set the prescaler to clock / 128 and enable ADC
    ADCSRA |= (1 << ADPS1) | (1 << ADPS0) | (1 << ADEN);
}

static uint8_t adc_read(void) {
    // Start the ADC read
    ADCSRA |= (1 << ADSC);

    // Wait for the ADC read to finish
    while (ADCSRA & (1 << ADSC));

    return (255 * (uint16_t)ADCH) / POT_LIMIT;
}

int main(void) {
    pwm_init();
    adc_init();

    pwm_set(0);

    while (1) {
        _delay_ms(250);

        // Read ADC value and set PWM duty cycle
        pwm_set(adc_read());
    }
}
