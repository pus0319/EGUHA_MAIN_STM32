################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/egtn_lib/egtn_lib_LPF.c \
../Core/egtn_lib/egtn_lib_bitop.c \
../Core/egtn_lib/egtn_lib_complement.c \
../Core/egtn_lib/egtn_lib_debouncecheck.c \
../Core/egtn_lib/egtn_lib_littlefs.c \
../Core/egtn_lib/egtn_lib_littlefs_util.c \
../Core/egtn_lib/egtn_lib_logging.c \
../Core/egtn_lib/egtn_lib_string.c \
../Core/egtn_lib/egtn_lib_u8queue.c \
../Core/egtn_lib/egtn_lib_userdelay.c 

OBJS += \
./Core/egtn_lib/egtn_lib_LPF.o \
./Core/egtn_lib/egtn_lib_bitop.o \
./Core/egtn_lib/egtn_lib_complement.o \
./Core/egtn_lib/egtn_lib_debouncecheck.o \
./Core/egtn_lib/egtn_lib_littlefs.o \
./Core/egtn_lib/egtn_lib_littlefs_util.o \
./Core/egtn_lib/egtn_lib_logging.o \
./Core/egtn_lib/egtn_lib_string.o \
./Core/egtn_lib/egtn_lib_u8queue.o \
./Core/egtn_lib/egtn_lib_userdelay.o 

C_DEPS += \
./Core/egtn_lib/egtn_lib_LPF.d \
./Core/egtn_lib/egtn_lib_bitop.d \
./Core/egtn_lib/egtn_lib_complement.d \
./Core/egtn_lib/egtn_lib_debouncecheck.d \
./Core/egtn_lib/egtn_lib_littlefs.d \
./Core/egtn_lib/egtn_lib_littlefs_util.d \
./Core/egtn_lib/egtn_lib_logging.d \
./Core/egtn_lib/egtn_lib_string.d \
./Core/egtn_lib/egtn_lib_u8queue.d \
./Core/egtn_lib/egtn_lib_userdelay.d 


# Each subdirectory must supply rules for building sources it contributes
Core/egtn_lib/egtn_lib_LPF.o: ../Core/egtn_lib/egtn_lib_LPF.c Core/egtn_lib/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F030xC -c -I../Core/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Drivers/CMSIS/Include -I../Core/egtn_config -I../Core/egtn_app -I../Core/egtn_lib -I../Core/egtn_mw -O2 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/egtn_lib/egtn_lib_LPF.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Core/egtn_lib/egtn_lib_bitop.o: ../Core/egtn_lib/egtn_lib_bitop.c Core/egtn_lib/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F030xC -c -I../Core/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Drivers/CMSIS/Include -I../Core/egtn_config -I../Core/egtn_app -I../Core/egtn_lib -I../Core/egtn_mw -O2 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/egtn_lib/egtn_lib_bitop.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Core/egtn_lib/egtn_lib_complement.o: ../Core/egtn_lib/egtn_lib_complement.c Core/egtn_lib/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F030xC -c -I../Core/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Drivers/CMSIS/Include -I../Core/egtn_config -I../Core/egtn_app -I../Core/egtn_lib -I../Core/egtn_mw -O2 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/egtn_lib/egtn_lib_complement.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Core/egtn_lib/egtn_lib_debouncecheck.o: ../Core/egtn_lib/egtn_lib_debouncecheck.c Core/egtn_lib/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F030xC -c -I../Core/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Drivers/CMSIS/Include -I../Core/egtn_config -I../Core/egtn_app -I../Core/egtn_lib -I../Core/egtn_mw -O2 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/egtn_lib/egtn_lib_debouncecheck.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Core/egtn_lib/egtn_lib_littlefs.o: ../Core/egtn_lib/egtn_lib_littlefs.c Core/egtn_lib/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F030xC -c -I../Core/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Drivers/CMSIS/Include -I../Core/egtn_config -I../Core/egtn_app -I../Core/egtn_lib -I../Core/egtn_mw -O2 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/egtn_lib/egtn_lib_littlefs.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Core/egtn_lib/egtn_lib_littlefs_util.o: ../Core/egtn_lib/egtn_lib_littlefs_util.c Core/egtn_lib/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F030xC -c -I../Core/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Drivers/CMSIS/Include -I../Core/egtn_config -I../Core/egtn_app -I../Core/egtn_lib -I../Core/egtn_mw -O2 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/egtn_lib/egtn_lib_littlefs_util.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Core/egtn_lib/egtn_lib_logging.o: ../Core/egtn_lib/egtn_lib_logging.c Core/egtn_lib/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F030xC -c -I../Core/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Drivers/CMSIS/Include -I../Core/egtn_config -I../Core/egtn_app -I../Core/egtn_lib -I../Core/egtn_mw -O2 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/egtn_lib/egtn_lib_logging.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Core/egtn_lib/egtn_lib_string.o: ../Core/egtn_lib/egtn_lib_string.c Core/egtn_lib/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F030xC -c -I../Core/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Drivers/CMSIS/Include -I../Core/egtn_config -I../Core/egtn_app -I../Core/egtn_lib -I../Core/egtn_mw -O2 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/egtn_lib/egtn_lib_string.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Core/egtn_lib/egtn_lib_u8queue.o: ../Core/egtn_lib/egtn_lib_u8queue.c Core/egtn_lib/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F030xC -c -I../Core/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Drivers/CMSIS/Include -I../Core/egtn_config -I../Core/egtn_app -I../Core/egtn_lib -I../Core/egtn_mw -O2 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/egtn_lib/egtn_lib_u8queue.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Core/egtn_lib/egtn_lib_userdelay.o: ../Core/egtn_lib/egtn_lib_userdelay.c Core/egtn_lib/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F030xC -c -I../Core/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Drivers/CMSIS/Include -I../Core/egtn_config -I../Core/egtn_app -I../Core/egtn_lib -I../Core/egtn_mw -O2 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/egtn_lib/egtn_lib_userdelay.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

