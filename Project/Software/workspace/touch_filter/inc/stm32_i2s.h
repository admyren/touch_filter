/*
 * stm32_i2s.h
 *
 *  Created on: 11 sep. 2021
 *      Author: Myren
 */

#ifndef STM32_I2S_H_
#define STM32_I2S_H_

void i2s_config(uint16_t* rx_buff, uint16_t* tx_buff, uint32_t buff_size);

void I2S_register_rx_complete_callback(void (*func)(void));
void I2S_register_tx_complete_callback(void (*func)(void));

#endif /* STM32_I2S_H_ */
