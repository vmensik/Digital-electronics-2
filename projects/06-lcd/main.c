/*
 * ---------------------------------------------------------------------
 * Author:      Tomas Fryza
 *              Dept. of Radio Electronics, Brno Univ. of Technology
 * Created:     2018-10-16
 * Last update: 2019-10-25
 * Platform:    ATmega328P, 16 MHz, AVR 8-bit Toolchain 3.6.2
 * ---------------------------------------------------------------------
 * Description:
 *    Decimal counter with data output on LCD display.
 * 
 * Note:
 *    Modified version of Peter Fleury's LCD library with R/W pin 
 *    connected to GND. Newline symbol "\n" is not implemented, use
 *    lcd_gotoxy() function instead.
 */

/* Includes ----------------------------------------------------------*/
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>             // itoa() function
#include "timer.h"
#include "lcd.h"

/* Typedef -----------------------------------------------------------*/
/* Define ------------------------------------------------------------*/
/* Variables ---------------------------------------------------------*/
uint8_t counter;
char buf2[9];
char buf10[4];
char buf16[3];
/* Function prototypes -----------------------------------------------*/

/* Functions ---------------------------------------------------------*/


/**
 *  Brief:  Main program. Shows decimal values ​​on LCD display.
 *  Input:  None
 *  Return: None
 */
int main(void)
{
    /* LCD display
     * TODO: See Peter Fleury's online manual for LCD library 
     * http://homepage.hispeed.ch/peterfleury/avr-software.html
     * Initialize display and test different types of cursor */
    lcd_init(LCD_DISP_ON);
    uploadCustomChars();
    TIM_config_prescaler(TIM1, TIM_PRESC_8);
    TIM_config_interrupt(TIM1, TIM_OVERFLOW_ENABLE);

    // Display string without auto linefeed
    lcd_puts("Counter: ");
    lcd_gotoxy(0,1);
    lcd_putc('$');
    lcd_gotoxy(6,1);
    lcd_puts("0b");
    counter = 0;
    // TODO: Display variable value in decimal, binary, and hexadecimal

    /* Timer1
     * TODO: Configure Timer1 clock source and enable overflow 
     *       interrupt */

    /* TODO: Design at least two user characters and store them in 
     *       the display memory */

    // Enables interrupts by setting the global interrupt mask
    sei();
    
    // Infinite loop
    for (;;) {
        }

    // Will never reach this
    return (0);
}

/**
 *  Brief: Timer1 overflow interrupt routine. Increment counter value.
 */




void emptyDisplayNumbers() {
    for(int i = 0; i < 8; i++) {
            buf2[i] = ' ';
        } 
        buf2[8] = '\0';
        for(int i = 0; i < 3; i++) {
            buf10[i] = ' ';
        } 
        buf10[3] = '\0';
        for(int i = 0; i < 2; i++) {
            buf10[i] = ' ';
        } 
        buf16[2] = '\0';
        lcd_gotoxy(9,0);
        lcd_puts(buf10);
        lcd_gotoxy(1,1);
        lcd_puts(buf16);
        lcd_gotoxy(8,1);
        lcd_puts(buf2);
}

ISR(TIMER1_OVF_vect)
{
    if(counter == 0) {
        emptyDisplayNumbers();
    } 
    counter++;
    
    
    lcd_gotoxy(9,0);
    lcd_puts(itoa(counter, buf10, 10));
    lcd_gotoxy(1,1);
    lcd_puts(itoa(counter, buf16, 16));

    lcd_gotoxy(8,1);
    lcd_puts(itoa(counter, buf2, 2));
}
