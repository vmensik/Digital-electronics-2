/*
 * ---------------------------------------------------------------------
 * Author:      Tomas Fryza
 *              Dept. of Radio Electronics, Brno Univ. of Technology
 * Created:     2018-09-27
 * Last update: 2019-09-26
 * Platform:    ATmega328P, AVR 8-bit Toolchain 3.6.2
 * ---------------------------------------------------------------------
 * Description: Blink a LED with delay function.
 * TODO: Verify functionality of LED blinker.
 * NOTE: Macro _BV converts a bit number into a byte value (see AVR Libc
 * Reference Manual).
 */

/* Includes ----------------------------------------------------------*/
#include <avr/io.h>
#include <util/delay.h>

/* Typedef -----------------------------------------------------------*/
/* Define ------------------------------------------------------------*/
#define LED_GREEN   PB5
#define LED_STANDALONE   PB0
#define BTN PD2
#define BLINK_DELAY 200

/* Variables ---------------------------------------------------------*/
/* Function prototypes -----------------------------------------------*/

/* Functions ---------------------------------------------------------*/
/**
  * Brief:  Main program. Blink a LED with delay function.
  * Input:  None
  * Return: None
  */
int main(void)
{
    /* Set output pin */
    DDRB |= _BV(LED_GREEN);         /* DDRB = DDRB or (0010 0000) */
    DDRB |= _BV(LED_STANDALONE);
    DDRD &= ~_BV(BTN); 


    /* Turn LED off */
    PORTB &= ~_BV(LED_GREEN);       /* PORTB = PORTB and (0010 0000) */
    PORTB |= _BV(LED_STANDALONE);
    PORTD |= _BV(BTN);
    /* Infinite loop */
    for (;;)
    {
        /* Invert LED and delay */
        
        if (bit_is_clear(PIND, BTN))  {
          PORTB ^= _BV(LED_GREEN);    /* PORTB = PORTB xor (0010 0000) */
          PORTB ^= _BV(LED_STANDALONE);
          _delay_ms(BLINK_DELAY); /* Wait for several milisecs */
        }
      
    }

    return (0);
}
