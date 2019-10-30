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
uint8_t bar_pos;
uint8_t bar_status;
char buf2[9];
char buf10[4];
char buf16[3];
/* Function prototypes -----------------------------------------------*/

/* Functions ---------------------------------------------------------*/

void uploadCustomChars() {
  uint8_t bar0[] = {
    0b00010000,
    0b00010000,
    0b00010000,
    0b00010000,
    0b00010000,
    0b00010000,
    0b00010000,
    0b00010000
  };

  uint8_t bar1[] = {
    0b00010100,
    0b00010100,
    0b00010100,
    0b00010100,
    0b00010100,
    0b00010100,
    0b00010100,
    0b00010100
  };


  uint8_t bar2[] = {
    0b00010101,
    0b00010101,
    0b00010101,
    0b00010101,
    0b00010101,
    0b00010101,
    0b00010101,
    0b00010101
  };

  lcd_command(1<<LCD_CGRAM);
  for(int i = 0; i < 8; i++) {
    lcd_data(bar0[i]);
  }


  for(int i = 0; i < 8; i++) {
    lcd_data(bar1[i]);
  }


  for(int i = 0; i < 8; i++) {
    lcd_data(bar2[i]);
  }
}

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

    counter = 0;
    bar_pos = 0;
    // TODO: Display variable value in decimal, binary, and hexadecimal

    /* Timer1
     * TODO: Configure Timer1 clock source and enable overflow 
     *       interrupt */

    /* TODO: Design at least two user characters and store them in 
     *       the display memory */

    // Enables interrupts by setting the global interrupt mask
    sei();
    lcd_gotoxy(0,1);
    lcd_putc(0x00);
    lcd_putc(0x01);
    lcd_putc(0x02);
    lcd_putc(0x03);
    lcd_putc(0x04);
    // Infinite loop
    for (;;) {
        }

    // Will never reach this
    return (0);
}

/**
 *  Brief: Timer1 overflow interrupt routine. Increment counter value.
 */

ISR(TIMER1_OVF_vect)
{
  counter++;
  if(counter < 80) {
    if (bar_status < 4) {
      bar_status++;
    }
    else {
      if (bar_pos < 15) {
        bar_pos++;
        bar_status = 0;
      }
    }
  }

  if(counter > 80 && counter < 160) {
    if (bar_status != 0) {
      bar_status--;
    }
    else {
      if (bar_pos != 0) {
        bar_pos--;
        bar_status = 4;
      }
    }
  }
  if (counter >= 160) {
    counter = 0;
  }
  lcd_gotoxy(bar_pos,0);
  if(bar_status == 0) {
    lcd_putc(' ');
  }
  if(bar_status == 1) {
    lcd_putc(0x00);
  }
  if(bar_status == 2) {
    lcd_putc(0x01);
  }
  if(bar_status == 3) {
    lcd_putc(0x02);
  }
    

  }