################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F/port.c 

OBJS += \
./Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F/port.o 

C_DEPS += \
./Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F/port.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F/%.o: ../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DSTM32F405RGTx -DSTM32 -DSTM32F4 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F405xx -DUSE_RTOS_SYSTICK -I"/Users/Myren/Documents/touch_filter_fx/Project/Software/workspace/touch_filter/inc" -I"/Users/Myren/Documents/touch_filter_fx/Project/Software/workspace/touch_filter/HAL_Driver/Inc" -I"/Users/Myren/Documents/touch_filter_fx/Project/Software/workspace/touch_filter/HAL_Driver/Inc/Legacy" -I"/Users/Myren/Documents/touch_filter_fx/Project/Software/workspace/touch_filter/Middlewares/Third_Party/FreeRTOS/Source/include" -I"/Users/Myren/Documents/touch_filter_fx/Project/Software/workspace/touch_filter/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"/Users/Myren/Documents/touch_filter_fx/Project/Software/workspace/touch_filter/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"/Users/Myren/Documents/touch_filter_fx/Project/Software/workspace/touch_filter/CMSIS/core" -I"/Users/Myren/Documents/touch_filter_fx/Project/Software/workspace/touch_filter/CMSIS/device" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


