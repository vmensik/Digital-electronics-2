#include "gpio.h"

/*
 * Configures given GPIO pin to output mode. 
 * @param reg_name DD registry address
 * @param pin_num pin number
 */
void GPIO_config_output(volatile uint8_t *reg_name, uint8_t pin_num) {
    *reg_name |= _BV(pin_num);
}

/*
 * Configures given GPIO pin to input mode using the internal pull-up resistor. 
 * @param reg_name DD registry address
 * @param pin_num pin number
 */

void GPIO_config_input_nopull(volatile uint8_t *reg_name, uint8_t pin_num) {
    *reg_name &= ~_BV(pin_num);
    volatile uint8_t *reg_name2 = reg_name+1;
    *reg_name2 &= ~_BV(pin_num);
}

/*
 * Configures given GPIO pin to input mode without using the internal pull-up resistor. 
 * @param reg_name DD registry address
 * @param pin_num pin number
 */
void GPIO_config_input_pullup(volatile uint8_t *reg_name, uint8_t pin_num) {
    *reg_name &= ~_BV(pin_num);
    volatile uint8_t *reg_name2 = reg_name+1;
    *reg_name2 |= _BV(pin_num);
}

/*
 * Writes pin_val as output to given GPIO pin. 
 * @param reg_name DD registry address
 * @param pin_num pin number
 */
void GPIO_write(volatile uint8_t *reg_name, uint8_t pin_num, uint8_t pin_val) {
    if(pin_val) {
        *reg_name |= _BV(pin_num);
    }
    else {
        *reg_name &= ~_BV(pin_num);
    }
}

/*
 * Inverts the value of a given output GPIO pin. 
 * @param reg_name DD registry address
 * @param pin_num pin number
 */

void GPIO_toggle(volatile uint8_t *reg_name, uint8_t pin_num) {
    *reg_name ^= _BV(pin_num);
}

/*
 * Reads and returns value if a given input GPIO pin. 
 * @param reg_name DD registry address
 * @param pin_num pin number
 */

uint8_t GPIO_read(volatile uint8_t *reg_name, uint8_t pin_num) {
    return (bit_is_set(*reg_name, pin_num));
}
