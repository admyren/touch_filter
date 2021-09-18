/*
 * stm32_i2c.h
 *
 *  Created on: 28 aug. 2021
 *      Author: Myren
 */

#ifndef STM32_I2C_H_
#define STM32_I2C_H_

void i2c1_init(I2C_TypeDef* hi2c);
void i2c2_init(I2C_TypeDef* hi2c);

uint32_t i2c_start(I2C_TypeDef* hi2c);
void i2c_stop(I2C_TypeDef* hi2c);
uint32_t i2c_checkReady(I2C_TypeDef* hi2c);
uint32_t i2c_sendAddress(I2C_TypeDef* hi2c, uint8_t addr);
uint32_t i2c_sendData(I2C_TypeDef* hi2c, uint8_t data);


#endif /* STM32_I2C_H_ */
