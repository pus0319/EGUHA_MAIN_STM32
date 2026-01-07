################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/egtn_config/egtn_jumptoapp.c 

OBJS += \
./Core/egtn_config/egtn_jumptoapp.o 

C_DEPS += \
./Core/egtn_config/egtn_jumptoapp.d 


# Each subdirectory must supply rules for building sources it contributes
Core/egtn_config/egtn_jumptoapp.o: ../Core/egtn_config/egtn_jumptoapp.c Core/egtn_config/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F030xC -c -I../Core/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Drivers/CMSIS/Include -I../Core/egtn_config -I../Core/egtn_app -I../Core/egtn_lib -I../Core/egtn_mw -O2 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/egtn_config/egtn_jumptoapp.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

