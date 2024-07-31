################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/Lora_Gnss/lora_gnss_main.c \
../Core/Src/Lora_Gnss/protokol.c \
../Core/Src/Lora_Gnss/ringbuffer.c \
../Core/Src/Lora_Gnss/rtcm_decoder.c \
../Core/Src/Lora_Gnss/uart_dma.c 

OBJS += \
./Core/Src/Lora_Gnss/lora_gnss_main.o \
./Core/Src/Lora_Gnss/protokol.o \
./Core/Src/Lora_Gnss/ringbuffer.o \
./Core/Src/Lora_Gnss/rtcm_decoder.o \
./Core/Src/Lora_Gnss/uart_dma.o 

C_DEPS += \
./Core/Src/Lora_Gnss/lora_gnss_main.d \
./Core/Src/Lora_Gnss/protokol.d \
./Core/Src/Lora_Gnss/ringbuffer.d \
./Core/Src/Lora_Gnss/rtcm_decoder.d \
./Core/Src/Lora_Gnss/uart_dma.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/Lora_Gnss/%.o Core/Src/Lora_Gnss/%.su Core/Src/Lora_Gnss/%.cyclo: ../Core/Src/Lora_Gnss/%.c Core/Src/Lora_Gnss/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-Lora_Gnss

clean-Core-2f-Src-2f-Lora_Gnss:
	-$(RM) ./Core/Src/Lora_Gnss/lora_gnss_main.cyclo ./Core/Src/Lora_Gnss/lora_gnss_main.d ./Core/Src/Lora_Gnss/lora_gnss_main.o ./Core/Src/Lora_Gnss/lora_gnss_main.su ./Core/Src/Lora_Gnss/protokol.cyclo ./Core/Src/Lora_Gnss/protokol.d ./Core/Src/Lora_Gnss/protokol.o ./Core/Src/Lora_Gnss/protokol.su ./Core/Src/Lora_Gnss/ringbuffer.cyclo ./Core/Src/Lora_Gnss/ringbuffer.d ./Core/Src/Lora_Gnss/ringbuffer.o ./Core/Src/Lora_Gnss/ringbuffer.su ./Core/Src/Lora_Gnss/rtcm_decoder.cyclo ./Core/Src/Lora_Gnss/rtcm_decoder.d ./Core/Src/Lora_Gnss/rtcm_decoder.o ./Core/Src/Lora_Gnss/rtcm_decoder.su ./Core/Src/Lora_Gnss/uart_dma.cyclo ./Core/Src/Lora_Gnss/uart_dma.d ./Core/Src/Lora_Gnss/uart_dma.o ./Core/Src/Lora_Gnss/uart_dma.su

.PHONY: clean-Core-2f-Src-2f-Lora_Gnss

