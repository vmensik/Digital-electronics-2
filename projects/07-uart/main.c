/*
 * ---------------------------------------------------------------------
 * Author:      Tomas Fryza
 *              Dept. of Radio Electronics, Brno Univ. of Technology
 * Created:     2018-10-23
 * Last update: 2019-11-01
 * Platform:    ATmega328P, 16 MHz, AVR 8-bit Toolchain 3.6.2
 * ---------------------------------------------------------------------
 * Description:
 *    Analog-to-digital conversion with displaying result on LCD and 
 *    transmitting via UART.
 * 
 * Note:
 *    Peter Fleury's UART library.
 */

/* Includes ----------------------------------------------------------*/
#include <stdlib.h>             // itoa() function
#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer.h"
#include "lcd.h"
#include "uart.h"

/* Typedef -----------------------------------------------------------*/
/* Define ------------------------------------------------------------*/
#define UART_BAUD_RATE 9600

/* Variables ---------------------------------------------------------*/
int adc_value;
/* Function prototypes -----------------------------------------------*/

/* Functions ---------------------------------------------------------*/
/**
 *  Brief:  Main program. Read ADC result and transmit via UART.
 *  Input:  None
 *  Return: None
 */


int main(void)
{
    // LCD display
    lcd_init(LCD_DISP_ON);
    lcd_clrscr();
    lcd_puts("ADC VALUE:");

    /* ADC
     * TODO: Configure ADC reference, clock source, enable ADC module, 
     *       and enable conversion complete interrupt */
    ADMUX |= _BV(REFS0);
    ADMUX &= ~_BV(REFS1);

    ADMUX &= ~(_BV(MUX0) | _BV(MUX1) | _BV(MUX2) | _BV(MUX3));
    

    ADCSRA |= _BV(ADEN);

    ADCSRA |= _BV(ADIE);

    ADCSRA |= _BV(ADPS0) | _BV(ADPS1) | _BV(ADPS2);
    
    /* Timer1
     * TODO: Configure Timer1 clock source and enable overflow 
     *       interrupt */
    TIM_config_prescaler(TIM1, TIM_PRESC_64);
    TIM_config_interrupt(TIM1, TIM_OVERFLOW_ENABLE);
    // UART: asynchronous, 8-bit data, no parity, 1-bit stop
    uart_init(UART_BAUD_SELECT(UART_BAUD_RATE, F_CPU));

    // Enables interrupts by setting the global interrupt mask
    sei();

    // Put string to ringbuffer for transmitting via UART.
    uart_puts("UART testing\r\n");

    // Infinite loop
    for (;;) {
    }

    // Will never reach this
    return (0);
}

/**
 *  Brief: Timer1 overflow interrupt routine. Start ADC conversion.
 */
ISR(TIMER1_OVF_vect)
{
    ADCSRA |= _BV(ADSC);
    
}

/**
 *  Brief: ADC complete interrupt routine. Update LCD and UART 
 *         transmiter.
 */
ISR(ADC_vect)
{
    uint16_t value = 0;
    static uint16_t last_value = 0;
    char uart_string[4];
    

	// Read 10-bit ACD value
    value = ADC;

    // TODO: Update LCD and UART transmiter
    lcd_gotoxy(0,1);
    

    itoa(value, uart_string, 10);

    lcd_gotoxy(0,1);
    lcd_puts(uart_string);

    lcd_gotoxy(0,6);
    switch(value) {
        case 0: 
            itoa(value, uart_string, 10);

            lcd_gotoxy(0,1);
            lcd_puts("                ");
            lcd_gotoxy(0,1);
            lcd_puts(uart_string);

            lcd_gotoxy(6,1);
            lcd_puts("RIGHT");
            break;
        case 99:
            itoa(value, uart_string, 10);
            lcd_gotoxy(0,1);
            lcd_puts("                ");
            lcd_gotoxy(0,1);
            lcd_puts(uart_string);
            lcd_gotoxy(6,1);
            lcd_puts("UP");
            break;
        case 257:
            itoa(value, uart_string, 10);
            lcd_gotoxy(0,1);
            lcd_puts("                ");
            lcd_gotoxy(0,1);
            lcd_puts(uart_string);
            lcd_gotoxy(6,1);
            lcd_puts("DOWN");
            break;
        case 410:
            itoa(value, uart_string, 10);
            lcd_gotoxy(0,1);
            lcd_puts("                ");
            lcd_gotoxy(0,1);
            lcd_puts(uart_string);
            lcd_gotoxy(6,1);
            lcd_puts("LEFT");
            break;
        case 639:
            itoa(value, uart_string, 10);
            lcd_gotoxy(0,1);
            lcd_puts("                ");
            lcd_gotoxy(0,1);
            lcd_puts(uart_string);
            lcd_gotoxy(6,1);
            lcd_puts("SELECT");
            break;
        default:
            lcd_gotoxy(0,1);
            lcd_puts("                ");
    }

    if(value != last_value
        && value != 1023) {
            switch(value) {
        case 0:
            uart_puts("\033[4;32m");          
            // 4:  underline  style; 32:  green  foreground
            uart_puts("RIGHT");
            uart_puts("\033[0m");    
 
            //uart_puts("RIGHT");
            uart_putc('\n');
            uart_putc('\r');
            break;
        case 99:
            uart_puts("\033[4;36m");          
            // 4:  underline  style; 32:  green  foreground
            uart_puts("UP");
            uart_puts("\033[0m");
            uart_putc('\n');
            uart_putc('\r');
            break;
        case 257:
            uart_puts("\033[4;29m");          
            // 4:  underline  style; 32:  green  foreground
            uart_puts("DOWN");
            uart_puts("\033[0m");
            
            uart_putc('\n');
            uart_putc('\r');
            break;
        case 410:
            uart_puts("\033[4;41m");          
            // 4:  underline  style; 32:  green  foreground
            uart_puts("LEFT");
            uart_puts("\033[0m");
            uart_putc('\n');
            uart_putc('\r');
            break;
        case 639:
            uart_puts("\033[4;28m");          
            // 4:  underline  style; 32:  green  foreground
            uart_puts("SELECT");
            uart_puts("\033[0m");
            uart_putc('\n');
            uart_putc('\r');
            break;
        default:
            break;
    }
    }
    last_value = value;

}

// RIGHT: 0
// DOWN 257
// UP 99
// LEFT 410
// SELECT 639
