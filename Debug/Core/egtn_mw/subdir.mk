################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/egtn_mw/egtn_embd_fs.c \
../Core/egtn_mw/egtn_mw_FC41D.c \
../Core/egtn_mw/egtn_mw_adc.c \
../Core/egtn_mw/egtn_mw_cp.c \
../Core/egtn_mw/egtn_mw_gpio.c \
../Core/egtn_mw/egtn_mw_indiled.c \
../Core/egtn_mw/egtn_mw_it.c \
../Core/egtn_mw/egtn_mw_ntc.c \
../Core/egtn_mw/egtn_mw_pwm.c \
../Core/egtn_mw/egtn_mw_relay.c \
../Core/egtn_mw/egtn_mw_serialflash.c \
../Core/egtn_mw/egtn_mw_uart.c 

OBJS += \
./Core/egtn_mw/egtn_embd_fs.o \
./Core/egtn_mw/egtn_mw_FC41D.o \
./Core/egtn_mw/egtn_mw_adc.o \
./Core/egtn_mw/egtn_mw_cp.o \
./Core/egtn_mw/egtn_mw_gpio.o \
./Core/egtn_mw/egtn_mw_indiled.o \
./Core/egtn_mw/egtn_mw_it.o \
./Core/egtn_mw/egtn_mw_ntc.o \
./Core/egtn_mw/egtn_mw_pwm.o \
./Core/egtn_mw/egtn_mw_relay.o \
./Core/egtn_mw/egtn_mw_serialflash.o \
./Core/egtn_mw/egtn_mw_uart.o 

C_DEPS += \
./Core/egtn_mw/egtn_embd_fs.d \
./Core/egtn_mw/egtn_mw_FC41D.d \
./Core/egtn_mw/egtn_mw_adc.d \
./Core/egtn_mw/egtn_mw_cp.d \
./Core/egtn_mw/egtn_mw_gpio.d \
./Core/egtn_mw/egtn_mw_indiled.d \
./Core/egtn_mw/egtn_mw_it.d \
./Core/egtn_mw/egtn_mw_ntc.d \
./Core/egtn_mw/egtn_mw_pwm.d \
./Core/egtn_mw/egtn_mw_relay.d \
./Core/egtn_mw/egtn_mw_serialflash.d \
./Core/egtn_mw/egtn_mw_uart.d 


# Each subdirectory must supply rules for building sources it contributes
Core/egtn_mw/egtn_embd_fs.o: ../Core/egtn_mw/egtn_embd_fs.c Core/egtn_mw/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F030xC -c -I../Core/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Drivers/CMSIS/Include -I../Core/egtn_config -I../Core/egtn_app -I../Core/egtn_lib -I../Core/egtn_mw -O2 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/egtn_mw/egtn_embd_fs.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Core/egtn_mw/egtn_mw_FC41D.o: ../Core/egtn_mw/egtn_mw_FC41D.c Core/egtn_mw/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F030xC -c -I../Core/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Drivers/CMSIS/Include -I../Core/egtn_config -I../Core/egtn_app -I../Core/egtn_lib -I../Core/egtn_mw -O2 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/egtn_mw/egtn_mw_FC41D.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Core/egtn_mw/egtn_mw_adc.o: ../Core/egtn_mw/egtn_mw_adc.c Core/egtn_mw/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F030xC -c -I../Core/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Drivers/CMSIS/Include -I../Core/egtn_config -I../Core/egtn_app -I../Core/egtn_lib -I../Core/egtn_mw -O2 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/egtn_mw/egtn_mw_adc.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Core/egtn_mw/egtn_mw_cp.o: ../Core/egtn_mw/egtn_mw_cp.c Core/egtn_mw/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F030xC -c -I../Core/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Drivers/CMSIS/Include -I../Core/egtn_config -I../Core/egtn_app -I../Core/egtn_lib -I../Core/egtn_mw -O2 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/egtn_mw/egtn_mw_cp.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Core/egtn_mw/egtn_mw_gpio.o: ../Core/egtn_mw/egtn_mw_gpio.c Core/egtn_mw/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F030xC -c -I../Core/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Drivers/CMSIS/Include -I../Core/egtn_config -I../Core/egtn_app -I../Core/egtn_lib -I../Core/egtn_mw -O2 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/egtn_mw/egtn_mw_gpio.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Core/egtn_mw/egtn_mw_indiled.o: ../Core/egtn_mw/egtn_mw_indiled.c Core/egtn_mw/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F030xC -c -I../Core/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Drivers/CMSIS/Include -I../Core/egtn_config -I../Core/egtn_app -I../Core/egtn_lib -I../Core/egtn_mw -O2 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/egtn_mw/egtn_mw_indiled.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Core/egtn_mw/egtn_mw_it.o: ../Core/egtn_mw/egtn_mw_it.c Core/egtn_mw/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F030xC -c -I../Core/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Drivers/CMSIS/Include -I../Core/egtn_config -I../Core/egtn_app -I../Core/egtn_lib -I../Core/egtn_mw -O2 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/egtn_mw/egtn_mw_it.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Core/egtn_mw/egtn_mw_ntc.o: ../Core/egtn_mw/egtn_mw_ntc.c Core/egtn_mw/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F030xC -c -I../Core/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Drivers/CMSIS/Include -I../Core/egtn_config -I../Core/egtn_app -I../Core/egtn_lib -I../Core/egtn_mw -O2 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/egtn_mw/egtn_mw_ntc.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Core/egtn_mw/egtn_mw_pwm.o: ../Core/egtn_mw/egtn_mw_pwm.c Core/egtn_mw/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F030xC -c -I../Core/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Drivers/CMSIS/Include -I../Core/egtn_config -I../Core/egtn_app -I../Core/egtn_lib -I../Core/egtn_mw -O2 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/egtn_mw/egtn_mw_pwm.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Core/egtn_mw/egtn_mw_relay.o: ../Core/egtn_mw/egtn_mw_relay.c Core/egtn_mw/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F030xC -c -I../Core/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Drivers/CMSIS/Include -I../Core/egtn_config -I../Core/egtn_app -I../Core/egtn_lib -I../Core/egtn_mw -O2 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/egtn_mw/egtn_mw_relay.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Core/egtn_mw/egtn_mw_serialflash.o: ../Core/egtn_mw/egtn_mw_serialflash.c Core/egtn_mw/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F030xC -c -I../Core/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Drivers/CMSIS/Include -I../Core/egtn_config -I../Core/egtn_app -I../Core/egtn_lib -I../Core/egtn_mw -O2 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/egtn_mw/egtn_mw_serialflash.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Core/egtn_mw/egtn_mw_uart.o: ../Core/egtn_mw/egtn_mw_uart.c Core/egtn_mw/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F030xC -c -I../Core/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Drivers/CMSIS/Include -I../Core/egtn_config -I../Core/egtn_app -I../Core/egtn_lib -I../Core/egtn_mw -O2 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/egtn_mw/egtn_mw_uart.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

