
//#include "stm32f4xx.h"
#include "stm32_gpio.h"
#include "stm32_rcc.h"
#include "stm32_uart.h"
#include "stm32_i2c.h"
#include "stm32_i2s.h"


#define DELAY 1000000

#define UART_BUFF_SIZE 50
volatile uint8_t UART_buff[UART_BUFF_SIZE];

volatile uint8_t uart_receive_ready = 0;
volatile uint8_t uart_transmit_ready = 1;

volatile uint32_t count;

void SystemClock_Config(void);

void UART_RX_comp(void)
{
   uart_receive_ready = 1;
}

void UART_TX_comp(void)
{
   uart_transmit_ready = 1;
}

void i2c_test(void)
{
   //i2c_stop(I2C1);
   //i2c_stop(I2C2);
#if 1
   if (0 != i2c_checkReady(I2C1))
   {
      while(0 == uart_transmit_ready);
      UART_Transmit_DMA(UART4, (uint8_t*)"I2C1 ready timed out\n", sizeof("I2C1 ready timed out"));
      uart_transmit_ready = 0;
   }
   else
   {
      while(0 == uart_transmit_ready);
      UART_Transmit_DMA(UART4, (uint8_t*)"I2C1 ready\n", sizeof("I2C1 ready"));
      uart_transmit_ready = 0;
   }
   if (0 != i2c_checkReady(I2C2))
   {
      while(0 == uart_transmit_ready);
      UART_Transmit_DMA(UART4, (uint8_t*)"I2C2 ready timed out\n", sizeof("I2C2 ready timed out"));
      uart_transmit_ready = 0;
   }
   else
   {
      while(0 == uart_transmit_ready);
      UART_Transmit_DMA(UART4, (uint8_t*)"I2C2 ready\n", sizeof("I2C2 ready"));
      uart_transmit_ready = 0;
   }
#endif
   if (0 != i2c_start(I2C1))
   {
#if 1
      while(0 == uart_transmit_ready);
      if (1 == uart_transmit_ready)
      {
         UART_Transmit_DMA(UART4, (uint8_t*)"I2C1 start timed out\n", sizeof("I2C1 start timed out"));
         uart_transmit_ready = 0;
      }
#endif
   }
   else
   {
      while(0 == uart_transmit_ready);
      UART_Transmit_DMA(UART4, (uint8_t*)"I2C1 start valid\n", sizeof("I2C1 start valid"));
      uart_transmit_ready = 0;
   }

   if (0 != i2c_sendAddress(I2C1, 0x68 << 1))
   {
      while(0 == uart_transmit_ready);
      UART_Transmit_DMA(UART4, (uint8_t*)"I2C1 address timed out\n", sizeof("I2C1 address timed out"));
      uart_transmit_ready = 0;
   }
   else
   {
      while(0 == uart_transmit_ready);
      UART_Transmit_DMA(UART4, (uint8_t*)"I2C1 address valid\n", sizeof("I2C1 address valid"));
      uart_transmit_ready = 0;
   }


   if (0 != i2c_start(I2C2))
   {
      while(0 == uart_transmit_ready);
      if (1 == uart_transmit_ready)
      {
         UART_Transmit_DMA(UART4, (uint8_t*)"I2C2 start timed out\n", sizeof("I2C2 start timed out"));
         uart_transmit_ready = 0;
      }
   }
   else
   {
      while(0 == uart_transmit_ready);
      UART_Transmit_DMA(UART4, (uint8_t*)"I2C2 start valid\n", sizeof("I2C2 start valid"));
      uart_transmit_ready = 0;
   }
   if (0 != i2c_sendAddress(I2C2, 0x34 << 1))
   {
      while(0 == uart_transmit_ready);
      UART_Transmit_DMA(UART4, (uint8_t*)"I2C2 address timed out\n", sizeof("I2C2 address timed out"));
      uart_transmit_ready = 0;
   }
   else
   {
      while(0 == uart_transmit_ready);
      UART_Transmit_DMA(UART4, (uint8_t*)"I2C2 address valid\n", sizeof("I2C2 address valid"));
      uart_transmit_ready = 0;
   }

   // Address:0x34
/*
   if (0 != i2c_sendAddress(I2C1, 0x34 << 1))
   {
      if (1 == uart_transmit_ready)
      {
         UART_Transmit_DMA(UART4, (uint8_t*)"I2C address timed out\n", sizeof("I2C address timed out"));
         uart_transmit_ready = 0;
      }
   }
*/
}

void i2c_test_init(void)
{
   i2c1_init(I2C1);
   i2c2_init(I2C2);
}

volatile uint32_t cnt = 0;
void delay_dummy(uint32_t delay_cnt)
{
   cnt = 0;
   while(++cnt <= delay_cnt);
}


void sysclk_init(void)
{
   clock_conf_t clk_conf;

   clk_conf.source = HSE_CLK;
   clk_conf.PLL_enable = enable;
   clk_conf.PLLM = 16;
   clk_conf.PLLN = 336;
   clk_conf.PLLP = 2;
   clk_conf.PLLQ = 7;
   clk_conf.AHB_prescaler = AHB_DIV_NO_DIV; /* 168 MHz */
   clk_conf.APB1_prescaler = APB_DIV_4; /* 42 MHz */
   clk_conf.APB2_prescaler = APB_DIV_2; /* 84 MHz */

   RCC_PLL_config(RCC, &clk_conf);
}

#if 0
void init_uart(void)
{
   uart_config_t uart_conf;
   gpio_config_t gpio_conf;

   // GPIOC clock enable
   RCC->AHB1ENR |= (1 << 2);
   // UART4 clock enable
   RCC->APB1ENR |= (1 << 19);

   gpio_conf.mode = gpio_af;
   gpio_conf.alternate_func = gpio_af_8;
   gpio_conf.pins = gpio_pin_10 | gpio_pin_11;

   uart_conf.baud_rate = BAUD_115200;
   uart_conf.stop_bits = STOP_BITS_1;
   uart_conf.data_bits = DATA_BITS_8;
   uart_conf.parity_enable = disable;
   uart_conf.TX_enable = enable;
   uart_conf.RX_enable = disable;

   gpio_init(GPIOC, &gpio_conf);

   UART_config(UART4, &uart_conf);

}
#endif
void gpio_init_test(void)
{
#if 0
   RCC->AHB1ENR |= (1 << 2);

   GPIOC->MODER |= (1 << 4);

#else
   gpio_config_t gpio_conf;

   gpio_conf.mode = gpio_gpo;
   gpio_conf.output_type = gpio_opp;
   gpio_conf.output_speed = gpio_ms;
   gpio_conf.pull_up_down = gpio_no_pull;
   gpio_conf.alternate_func = gpio_af_0;
   gpio_conf.lock = gpio_lock_off;
   gpio_conf.pins = gpio_pin_2 | gpio_pin_3;

   RCC->AHB1ENR |= (1 << 2);
   gpio_init(GPIOC, &gpio_conf);
#endif
}


int main(void)
{


   //sysclk_init();
   SystemClock_Config();

   gpio_init_test();
   //init_uart();
   UART_Init(UART4, 115200, (uint8_t*)UART_buff, UART_BUFF_SIZE);

   UART_register_rx_complete_func(UART_RX_comp);
   UART_register_tx_complete_func(UART_TX_comp);

   i2c_test_init();

   if (0 == RCC_PLLI2S_config())
   {
      while(0 == uart_transmit_ready);
      UART_Transmit_DMA(UART4, (uint8_t*)"PLLI2S locked\n", sizeof("PLLI2S locked"));
      uart_transmit_ready = 0;
   }
   else
   {
      while(0 == uart_transmit_ready);
      UART_Transmit_DMA(UART4, (uint8_t*)"PLLI2S not locked\n", sizeof("PLLI2S not locked"));
      uart_transmit_ready = 0;
   }


   i2s_config();

   delay_dummy(10*DELAY);

   i2c_test();

   while(1)
   {


#if 1
      delay_dummy(DELAY);
      gpio_pin_set(GPIOC, gpio_pin_2);
      gpio_pin_reset(GPIOC, gpio_pin_3);
      delay_dummy(DELAY);
      gpio_pin_set(GPIOC, gpio_pin_3);
      gpio_pin_reset(GPIOC, gpio_pin_2);
#endif

#if 0
      if (1 == uart_transmit_ready)
      {
         UART_Transmit_DMA(UART4, (uint8_t*)"hello from DMA\n", sizeof("hello from DMA\n"));
         uart_transmit_ready = 0;
      }
#endif
      //sprintf(tmp_str, "PCKL1: %u\n", APB1_clock);
      //UART_Transmit(UART4, tmp_str, 0);

#if 1
      if (1 == uart_receive_ready)
      {
         //UART_Transmit(UART4, (uint8_t*)"##", 0);
         UART_Transmit(UART4, (uint8_t*)UART_buff, 1);
         //UART_Transmit(UART4, (uint8_t*)"##", 0);
         gpio_pin_reset(GPIOC, gpio_pin_2);
         gpio_pin_reset(GPIOC, gpio_pin_3);
         uart_receive_ready = 0;
      }
#endif

      //UART_tx(UART4, (uint8_t*)"hejhej", 6);

#if 0
      delay_dummy(DELAY);
      GPIOC->ODR ^= (1 << 2);
#endif
   }
}



/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

    /**Configure the main internal regulator output voltage
    */
  __HAL_RCC_PWR_CLK_ENABLE();

  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    /**Initializes the CPU, AHB and APB busses clocks
    */
#if 0
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16; // 1MHz clock input to PLL
  RCC_OscInitStruct.PLL.PLLN = 360; // PLL multiplier, output of PLL = 1*360 = 360MHz
  RCC_OscInitStruct.PLL.PLLP = 2; // System clock = output of PLL / 2 = 180MHz
  RCC_OscInitStruct.PLL.PLLQ = 7;
#else
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  //RCC_OscInitStruct.HSECalibrationValue = 8;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 16; // 1MHz clock input to PLL
  RCC_OscInitStruct.PLL.PLLN = 336; // PLL multiplier, output of PLL = 1*336 = 336MHz
  RCC_OscInitStruct.PLL.PLLP = 2; // System clock = output of PLL / 2 = 168MHz
  RCC_OscInitStruct.PLL.PLLQ = 7;

#endif
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    //_Error_Handler(__FILE__, __LINE__);
  }

  /**Initializes the CPU, AHB and APB busses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK |
                              RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1; // HCLK, 168 MHz
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4; // PCLK1, 42 MHz
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2; // PCLK2, 84 MHz

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    //_Error_Handler(__FILE__, __LINE__);
  }

  SystemCoreClockUpdate();


  /**Configure the Systick
  */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);
  /**Configure the Systick interrupt time
  */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

  /* SysTick_IRQn interrupt configuration */
  //HAL_NVIC_SetPriority(SysTick_IRQn, 15, 0);
}


void dummy_Handler(void)
{
   while(1);
}
