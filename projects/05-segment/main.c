/*
 * ---------------------------------------------------------------------
 * Author:      Tomas Fryza
 *              Dept. of Radio Electronics, Brno Univ. of Technology
 * Created:     2018-10-11
 * Last update: 2019-10-16
 * Platform:    ATmega328P, AVR 8-bit Toolchain 3.6.2
 * ---------------------------------------------------------------------
 * Description: Decimal counter with data display on 7-segment display.
 * TODO: Create and test functions to operate a 7-segment display using
 *       shift registers.
 * NOTE: Store segment.c and segment.h files in library/src and 
 *       library/inc folders.
 */

/* Includes ----------------------------------------------------------*/
#include <avr/io.h>
#include <util/delay.h>
#include "GPIO.h"
#include "timer.h"
#include "segment.h"
#include <avr/interrupt.h>

/* Typedef -----------------------------------------------------------*/
/* Define ------------------------------------------------------------*/
#define LED_D1          PB5
#define BTN_S1          PC1 // PCINT 9
#define BTN_S2          PC2 // PCINT 10
#define BTN_S3          PC3 // PCINT 11

/* Variables ---------------------------------------------------------*/
uint8_t cnt;
/* Function prototypes -----------------------------------------------*/

/* Functions ---------------------------------------------------------*/
/**
 *  Brief:  Main program. Shows decimal values ​​on 7-segment display.
 *  Input:  None
 *  Return: None
 */
 
int main(void)
{
    /* D1 led */
    // TODO: Configure D1 led at Multi-Function Shield
    GPIO_config_output(&DDRB, LED_D1);
    GPIO_write(&PORTB, LED_D1, 1);
    /* Pin Change Interrupts 11:9 */
    // TODO: Configure Pin Change Interrupts 11, 10, and 9
    PCMSK1 |= _BV(PCINT11) | _BV(PCINT10) | _BV(PCINT9);
    PCICR |= _BV(PCIE1);

    /* 7-segment display interface */
    // TODO: Configure 7-segment display pins
    GPIO_config_output(&DDRD, PD4);
    GPIO_config_output(&DDRD, PD7);
    GPIO_config_output(&DDRB, PB0);

    /* Enable interrupts by setting the global interrupt mask */
    sei();
    cnt = 0;


    /* Infinite loop */
    for (;;) {
        // TODO: Use function to display digit 1 at position 0
        _delay_ms(500);
        cnt++;
        if(cnt > 9) cnt = 0;
        SEG_putc(cnt, 0);

    }

    return (0);
}

/**
 *  Brief: Pin Change Interrupt 11:9 routine. Toggle a LED.
 */

ISR(PCINT1_vect)
{
    //GPIO_toggle(&PORTB, LED_D1);
    
}

