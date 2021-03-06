/*
 * stm32_i2c.c
 *
 *  Created on: 28 aug. 2021
 *      Author: Myren
 */

/*
 * i2c_drv.c
 *
 *  Created on: 11 jan. 2020
 *      Author: Myren
 */

#include "stm32f405xx.h"
#include "stm32_i2c.h"
#include "stm32_gpio.h"
#include "stm32_peripherals.h"

/*
 Codec uses I2C2, SCL: PB10 SDA: PB11
 IMU uses I2C1, SCL: PB6 SDA: PB7
*/

void i2c1_init(I2C_TypeDef* hi2c)
{
   // This initializes the I2C1 peripheral
   // and its corresponding GPIOs

   uint32_t pclk1;
   const uint32_t scl_freq = 100000;
   gpio_config_t gpio_conf;


   gpio_conf.mode = gpio_af;
   gpio_conf.output_type = gpio_ood;
   gpio_conf.output_speed = gpio_hs;
   gpio_conf.pull_up_down = gpio_no_pull;
   gpio_conf.alternate_func = gpio_af_4;
   gpio_conf.lock = gpio_lock_off;
   gpio_conf.pins = gpio_pin_10 | gpio_pin_11;

   // Enable GPIOB peripheral clock
   RCC->AHB1ENR |= (1 << 1);

   //gpio_init(GPIOB, &gpio_conf);

#if 1
   // Alternate function
   GPIOB->MODER |= (2 << 14) | (2 << 12);
   // AF4 alternate function
   GPIOB->AFR[0] |= (4 << 28) | (4 << 24);
#endif

   // Enable I2C1 peripheral clock
   RCC->APB1ENR |= (1 << 21);

   // Periperal clock freqiency in MHz, 50MHz >= FREQ >= 2MHz
   hi2c->CR2 |= (0x001f & 42u);

   // Set fast mode (400khz)
   //I2C1->CCR |= (1 << 15);

   // Set fast mode duty
   // I2C1->CCR |= (1 << 14);
   // Get frequency of peripheral clock
   //pclk1 = HAL_RCC_GetPCLK1Freq();
   pclk1 = 42000000;
   // Clock control, for an SCL freq. of approx. 100 kHz
   //hi2c->CCR |= 0x0fff & (2*pclk1/scl_freq);
   /* 100 kHz */
   hi2c->CCR |= 210;

   // Maximum rise time of SCL, programmed with
   // rise =(max_rise_t/T_PCLK1)+1. Where T_PCLK1 is the
   // period time of the peripheral clock and max_rise_t
   // is the maximum rise time of SCL specified by the I2C specification.

   //hi2c->TRISE |= (0x003f & ((pclk1/1000) + 1));
   hi2c->TRISE |= (0x003f & ((pclk1/1000000) + 1));

   // Peripheral enable
   hi2c->CR1 |= (1 << 0);
}

void i2c2_init(I2C_TypeDef* hi2c)
{
   // This initializes the I2C2 peripheral
   // and its corresponding GPIOs

   uint32_t pclk1;
   const uint32_t scl_freq = 100000;
   gpio_config_t gpio_conf;


   gpio_conf.mode = gpio_af;
   gpio_conf.output_type = gpio_ood;
   gpio_conf.output_speed = gpio_hs;
   gpio_conf.pull_up_down = gpio_no_pull;
   gpio_conf.alternate_func = gpio_af_4;
   gpio_conf.lock = gpio_lock_off;
   gpio_conf.pins = gpio_pin_10 | gpio_pin_11;

   // Enable GPIOB peripheral clock
   RCC->AHB1ENR |= (1 << 1);

   //gpio_init(GPIOB, &gpio_conf);

#if 1
   // Alternate function
   GPIOB->MODER |= (2 << 22) | (2 << 20);
   // AF4 alternate function
   GPIOB->AFR[1] |= (4 << 12) | (4 << 8);
#endif

   // Enable I2C2 peripheral clock
   RCC->APB1ENR |= (1 << 22);

   // Periperal clock freqiency in MHz, 50MHz >= FREQ >= 2MHz
   hi2c->CR2 |= (0x001f & 42u);

   // Set fast mode (400khz)
   //I2C1->CCR |= (1 << 15);

   // Set fast mode duty
   // I2C1->CCR |= (1 << 14);
   // Get frequency of peripheral clock
   //pclk1 = HAL_RCC_GetPCLK1Freq();
   pclk1 = 42000000;
   // Clock control, for an SCL freq. of approx. 100 kHz
   /* 100 kHz */
   hi2c->CCR |= 210;

   // Maximum rise time of SCL, programmed with
   // rise =(max_rise_t/T_PCLK1)+1. Where T_PCLK1 is the
   // period time of the peripheral clock and max_rise_t
   // is the maximum rise time of SCL specified by the I2C specification.

   hi2c->TRISE |= (0x003f & ((pclk1/1000000) + 1));

   // Peripheral enable
   hi2c->CR1 |= (1 << 0);
}

uint32_t i2c_start(I2C_TypeDef* hi2c)
{
   uint32_t ret = 0;
   uint32_t timeout_cnt = 0;
   // Start generation
   hi2c->CR1 |= (1 << 8);
   //Check if a start condition has been generated
   while(!(hi2c->SR1 & (1 << 0)))
   {
      timeout_cnt++;
      if (timeout_cnt > TIMEOUT_WAIT_COUNT)
      {
         ret = 1;
         break;
      }
   }
   return ret;
}

void i2c_stop(I2C_TypeDef* hi2c)
{
   // Stop generation
   hi2c->CR1 |= (1 << 9);
}

uint32_t i2c_checkReady(I2C_TypeDef* hi2c)
{
   uint32_t ret = 0;
   uint32_t timeout_cnt = 0;
   // Check so the bus is not busy
   while(hi2c->SR2 & (1 << 1))
   {
      timeout_cnt++;
      if(timeout_cnt > TIMEOUT_WAIT_COUNT)
      {
         ret = 1;
         break;
      }
   }

   return ret;
}

uint32_t i2c_sendAddress(I2C_TypeDef* hi2c, uint8_t addr)
{
   uint32_t ret = 0;
   uint32_t timeout_cnt = 0;

   hi2c->DR = addr;


   // Wait until the ADDR bit is set
   while(!(hi2c->SR1 & (1 << 1)))
   {
      timeout_cnt++;
      if(timeout_cnt > TIMEOUT_WAIT_COUNT)
      {
         ret = 1;
         break;
      }
   }

   volatile uint32_t dummy = I2C1->SR2;
   (void)dummy;

   return ret;
}

uint32_t i2c_sendData(I2C_TypeDef* hi2c, uint8_t data)
{
   uint32_t ret = 0;
   uint32_t timeout_cnt = 0;

   hi2c->DR = data;
   while(!(hi2c->SR1 & (1 << 7)))
   {
      timeout_cnt++;
      if(timeout_cnt > TIMEOUT_WAIT_COUNT)
      {
         ret = 1;
         break;
      }
   }

   return ret;
}

uint32_t i2c_check_ack(I2C_TypeDef* hi2c)
{
   uint32_t ret = 0;

   if (hi2c->SR1 & (1 << 10))
   {
      ret = 1; // Failure
   }

   return ret;
}


