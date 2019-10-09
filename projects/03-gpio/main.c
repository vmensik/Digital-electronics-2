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
#include <GPIO.h>

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
    /*
    DDRB |= _BV(LED_GREEN);         
    DDRB |= _BV(LED_STANDALONE);
    DDRD &= ~_BV(BTN); 
    */
    GPIO_config_output(&DDRB, LED_GREEN);
    GPIO_config_output(&DDRB, LED_STANDALONE);
    GPIO_config_input_pullup(&DDRD, BTN);
    /* Turn LED off */
    GPIO_write(&PORTB, LED_GREEN, 0);
    GPIO_write(&PORTB, LED_STANDALONE, 0);

    /*
    PORTB &= ~_BV(LED_GREEN);       
    PORTB |= _BV(LED_STANDALONE);
    PORTD |= _BV(BTN);
    */
    /* Infinite loop */
    for (;;)
    {
        /* Invert LED and delay */

        if(!GPIO_read(&PIND, BTN)) {
          GPIO_toggle(&PORTB, LED_GREEN);
          GPIO_toggle(&PORTB, LED_STANDALONE);
          _delay_ms(BLINK_DELAY);
        }
    /*    
        if (bit_is_clear(PIND, BTN))  {

          PORTB ^= _BV(LED_GREEN);    
          PORTB ^= _BV(LED_STANDALONE);
          _delay_ms(BLINK_DELAY); 
        }
    */  
    }

    return (0);
}
