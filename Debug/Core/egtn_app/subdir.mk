################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/egtn_app/egtn_app_blecomm.c \
../Core/egtn_app/egtn_app_charging.c \
../Core/egtn_app/egtn_app_nonos_loop.c \
../Core/egtn_app/egtn_app_safetyfunc.c \
../Core/egtn_app/egtn_app_sys.c 

OBJS += \
./Core/egtn_app/egtn_app_blecomm.o \
./Core/egtn_app/egtn_app_charging.o \
./Core/egtn_app/egtn_app_nonos_loop.o \
./Core/egtn_app/egtn_app_safetyfunc.o \
./Core/egtn_app/egtn_app_sys.o 

C_DEPS += \
./Core/egtn_app/egtn_app_blecomm.d \
./Core/egtn_app/egtn_app_charging.d \
./Core/egtn_app/egtn_app_nonos_loop.d \
./Core/egtn_app/egtn_app_safetyfunc.d \
./Core/egtn_app/egtn_app_sys.d 


# Each subdirectory must supply rules for building sources it contributes
Core/egtn_app/egtn_app_blecomm.o: ../Core/egtn_app/egtn_app_blecomm.c Core/egtn_app/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F030xC -c -I../Core/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Drivers/CMSIS/Include -I../Core/egtn_config -I../Core/egtn_app -I../Core/egtn_lib -I../Core/egtn_mw -O2 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/egtn_app/egtn_app_blecomm.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Core/egtn_app/egtn_app_charging.o: ../Core/egtn_app/egtn_app_charging.c Core/egtn_app/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F030xC -c -I../Core/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Drivers/CMSIS/Include -I../Core/egtn_config -I../Core/egtn_app -I../Core/egtn_lib -I../Core/egtn_mw -O2 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/egtn_app/egtn_app_charging.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Core/egtn_app/egtn_app_nonos_loop.o: ../Core/egtn_app/egtn_app_nonos_loop.c Core/egtn_app/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F030xC -c -I../Core/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Drivers/CMSIS/Include -I../Core/egtn_config -I../Core/egtn_app -I../Core/egtn_lib -I../Core/egtn_mw -O2 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/egtn_app/egtn_app_nonos_loop.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Core/egtn_app/egtn_app_safetyfunc.o: ../Core/egtn_app/egtn_app_safetyfunc.c Core/egtn_app/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F030xC -c -I../Core/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Drivers/CMSIS/Include -I../Core/egtn_config -I../Core/egtn_app -I../Core/egtn_lib -I../Core/egtn_mw -O2 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/egtn_app/egtn_app_safetyfunc.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Core/egtn_app/egtn_app_sys.o: ../Core/egtn_app/egtn_app_sys.c Core/egtn_app/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F030xC -c -I../Core/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Drivers/CMSIS/Include -I../Core/egtn_config -I../Core/egtn_app -I../Core/egtn_lib -I../Core/egtn_mw -O2 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/egtn_app/egtn_app_sys.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

