#ifndef GPIO_H_INCLUDED
#define GPIO_H_INCLUDED

#include <avr/io.h>

/*
 * Configures given GPIO pin to output mode. 
 * @param reg_name DD registry address
 * @param pin_num pin number
 */
void GPIO_config_output(volatile uint8_t *reg_name, uint8_t pin_num);

/*
 * Configures given GPIO pin to input mode using the internal pull-up resistor. 
 * @param reg_name DD registry address
 * @param pin_num pin number
 */
void GPIO_config_input_nopull(volatile uint8_t *reg_name, uint8_t pin_num);
/*
 * Configures given GPIO pin to input mode without using the internal pull-up resistor. 
 * @param reg_name DD registry address
 * @param pin_num pin number
 */
void GPIO_config_input_pullup(volatile uint8_t *reg_name, uint8_t pin_num);
/*
 * Writes pin_val as output to given GPIO pin. 
 * @param reg_name DD registry address
 * @param pin_num pin number
 */
void GPIO_write(volatile uint8_t *reg_name, uint8_t pin_num, uint8_t pin_val);

/*
 * Inverts the value of a given output GPIO pin. 
 * @param reg_name DD registry address
 * @param pin_num pin number
 */
void GPIO_toggle(volatile uint8_t *reg_name, uint8_t pin_num);
/*
 * Reads and returns value if a given input GPIO pin. 
 * @param reg_name DD registry address
 * @param pin_num pin number
 */
uint8_t GPIO_read(volatile uint8_t *reg_name, uint8_t pin_num);

#endif
