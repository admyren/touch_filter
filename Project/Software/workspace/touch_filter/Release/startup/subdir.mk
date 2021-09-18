################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../startup/startup_stm32.s 

OBJS += \
./startup/startup_stm32.o 


# Each subdirectory must supply rules for building sources it contributes
startup/%.o: ../startup/%.s
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Assembler'
	@echo $(PWD)
	arm-none-eabi-as -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -I"/Users/Myren/Documents/touch_filter_fx/Project/Software/workspace/touch_filter/inc" -I"/Users/Myren/Documents/touch_filter_fx/Project/Software/workspace/touch_filter/HAL_Driver/Inc" -I"/Users/Myren/Documents/touch_filter_fx/Project/Software/workspace/touch_filter/HAL_Driver/Inc/Legacy" -I"/Users/Myren/Documents/touch_filter_fx/Project/Software/workspace/touch_filter/Middlewares/Third_Party/FreeRTOS/Source/include" -I"/Users/Myren/Documents/touch_filter_fx/Project/Software/workspace/touch_filter/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"/Users/Myren/Documents/touch_filter_fx/Project/Software/workspace/touch_filter/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"/Users/Myren/Documents/touch_filter_fx/Project/Software/workspace/touch_filter/CMSIS/core" -I"/Users/Myren/Documents/touch_filter_fx/Project/Software/workspace/touch_filter/CMSIS/device" -g -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


