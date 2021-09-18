################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/i2s.c \
../src/main.c \
../src/rcc.c \
../src/stm32_dma.c \
../src/stm32_gpio.c \
../src/stm32_i2c.c \
../src/stm32_uart.c \
../src/stm32f4xx_it.c \
../src/syscalls.c \
../src/system_stm32f4xx.c 

OBJS += \
./src/i2s.o \
./src/main.o \
./src/rcc.o \
./src/stm32_dma.o \
./src/stm32_gpio.o \
./src/stm32_i2c.o \
./src/stm32_uart.o \
./src/stm32f4xx_it.o \
./src/syscalls.o \
./src/system_stm32f4xx.o 

C_DEPS += \
./src/i2s.d \
./src/main.d \
./src/rcc.d \
./src/stm32_dma.d \
./src/stm32_gpio.d \
./src/stm32_i2c.d \
./src/stm32_uart.d \
./src/stm32f4xx_it.d \
./src/syscalls.d \
./src/system_stm32f4xx.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DSTM32F405RGTx -DSTM32 -DSTM32F4 -DUSE_HAL_DRIVER -DSTM32F405xx -DUSE_RTOS_SYSTICK -I"/Users/Myren/Documents/touch_filter_fx/Project/Software/workspace/touch_filter/inc" -I"/Users/Myren/Documents/touch_filter_fx/Project/Software/workspace/touch_filter/HAL_Driver/Inc" -I"/Users/Myren/Documents/touch_filter_fx/Project/Software/workspace/touch_filter/HAL_Driver/Inc/Legacy" -I"/Users/Myren/Documents/touch_filter_fx/Project/Software/workspace/touch_filter/Middlewares/Third_Party/FreeRTOS/Source/include" -I"/Users/Myren/Documents/touch_filter_fx/Project/Software/workspace/touch_filter/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"/Users/Myren/Documents/touch_filter_fx/Project/Software/workspace/touch_filter/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"/Users/Myren/Documents/touch_filter_fx/Project/Software/workspace/touch_filter/CMSIS/core" -I"/Users/Myren/Documents/touch_filter_fx/Project/Software/workspace/touch_filter/CMSIS/device" -O3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


