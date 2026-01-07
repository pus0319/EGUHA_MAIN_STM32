################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/egtn_lib/lib_statemachine/egtn_lib_StateMachine.c \
../Core/egtn_lib/lib_statemachine/fb_allocator.c \
../Core/egtn_lib/lib_statemachine/sm_allocator.c \
../Core/egtn_lib/lib_statemachine/x_allocator.c 

OBJS += \
./Core/egtn_lib/lib_statemachine/egtn_lib_StateMachine.o \
./Core/egtn_lib/lib_statemachine/fb_allocator.o \
./Core/egtn_lib/lib_statemachine/sm_allocator.o \
./Core/egtn_lib/lib_statemachine/x_allocator.o 

C_DEPS += \
./Core/egtn_lib/lib_statemachine/egtn_lib_StateMachine.d \
./Core/egtn_lib/lib_statemachine/fb_allocator.d \
./Core/egtn_lib/lib_statemachine/sm_allocator.d \
./Core/egtn_lib/lib_statemachine/x_allocator.d 


# Each subdirectory must supply rules for building sources it contributes
Core/egtn_lib/lib_statemachine/egtn_lib_StateMachine.o: ../Core/egtn_lib/lib_statemachine/egtn_lib_StateMachine.c Core/egtn_lib/lib_statemachine/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F030xC -c -I../Core/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Drivers/CMSIS/Include -I../Core/egtn_config -I../Core/egtn_app -I../Core/egtn_lib -I../Core/egtn_mw -O2 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/egtn_lib/lib_statemachine/egtn_lib_StateMachine.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Core/egtn_lib/lib_statemachine/fb_allocator.o: ../Core/egtn_lib/lib_statemachine/fb_allocator.c Core/egtn_lib/lib_statemachine/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F030xC -c -I../Core/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Drivers/CMSIS/Include -I../Core/egtn_config -I../Core/egtn_app -I../Core/egtn_lib -I../Core/egtn_mw -O2 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/egtn_lib/lib_statemachine/fb_allocator.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Core/egtn_lib/lib_statemachine/sm_allocator.o: ../Core/egtn_lib/lib_statemachine/sm_allocator.c Core/egtn_lib/lib_statemachine/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F030xC -c -I../Core/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Drivers/CMSIS/Include -I../Core/egtn_config -I../Core/egtn_app -I../Core/egtn_lib -I../Core/egtn_mw -O2 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/egtn_lib/lib_statemachine/sm_allocator.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Core/egtn_lib/lib_statemachine/x_allocator.o: ../Core/egtn_lib/lib_statemachine/x_allocator.c Core/egtn_lib/lib_statemachine/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F030xC -c -I../Core/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Drivers/CMSIS/Include -I../Core/egtn_config -I../Core/egtn_app -I../Core/egtn_lib -I../Core/egtn_mw -O2 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/egtn_lib/lib_statemachine/x_allocator.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

