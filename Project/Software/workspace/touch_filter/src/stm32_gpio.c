/*
 * stm32_gpio.c
 *
 *  Created on: 24 aug. 2021
 *      Author: Myren
 */

#include "stm32_gpio.h"

uint32_t gpio_init(GPIO_TypeDef* gpio_dev, gpio_config_t* gpio_conf)
{
   uint32_t ret = 0;
   uint32_t i;
   uint32_t af_hl_reg;

   for (i=0; i<0xf; ++i)
   {
      if (gpio_conf->pins & (1 << i))
      {
         // Set MODER to reset state
         gpio_dev->MODER &= ~(0x3 << (i << 1));

         gpio_dev->MODER |= (gpio_conf->mode << (i << 1));

         // Set OTYPER to reset state
         gpio_dev->OTYPER &= ~(0x1 << i);

         gpio_dev->OTYPER |= (gpio_conf->output_type << i);

         // Set OSPEEDR to reset state
         gpio_dev->OSPEEDR &= ~(0x3 << (i << 1));

         gpio_dev->OSPEEDR |= (gpio_conf->output_speed << (i << 1));

         // Set PUPDR to reset state
         gpio_dev->PUPDR &= ~(0x3 << (i << 1));

         gpio_dev->PUPDR |= (gpio_conf->pull_up_down << (i << 1));
#if 0
         // Set LCKR to reset state
         gpio_dev->LCKR &= ~(0x1 << i);

         gpio_dev->LCKR |= (gpio_conf->lock << i);

         af_hl_reg = (i < 0x8) ? 0 : 1;
         // Set AFR to reset state
         gpio_dev->AFR[af_hl_reg] &= ~(0xf << (i << 2));
         // Set AFR to selected function
         gpio_dev->AFR[af_hl_reg] |= (gpio_conf->alternate_func << (i << 2));
#endif
      }
#if 0
      // Activate lock
      if (gpio_lock_on == gpio_conf->lock)
      {
         gpio_dev->LCKR |= (1 << 0x10);
      }
#endif
   }

   return(ret);
}

void gpio_pin_set(GPIO_TypeDef* gpio_dev, uint32_t pins)
{
   gpio_dev->ODR |= (pins & 0xffff);
}

void gpio_pin_reset(GPIO_TypeDef* gpio_dev, uint32_t pins)
{
   gpio_dev->ODR &= ~(pins & 0xffff);
}

void gpio_pin_toggle(GPIO_TypeDef* gpio_dev, uint32_t pins)
{

}

uint32_t gpio_pin_read(GPIO_TypeDef* gpio_dev, gpio_pin_e pin)
{
   return(0);
}

