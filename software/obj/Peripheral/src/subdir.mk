################################################################################
# MRS Version: 2.2.0
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Peripheral/src/ch32v00X_adc.c \
../Peripheral/src/ch32v00X_dbgmcu.c \
../Peripheral/src/ch32v00X_dma.c \
../Peripheral/src/ch32v00X_exti.c \
../Peripheral/src/ch32v00X_flash.c \
../Peripheral/src/ch32v00X_gpio.c \
../Peripheral/src/ch32v00X_i2c.c \
../Peripheral/src/ch32v00X_iwdg.c \
../Peripheral/src/ch32v00X_misc.c \
../Peripheral/src/ch32v00X_opa.c \
../Peripheral/src/ch32v00X_pwr.c \
../Peripheral/src/ch32v00X_rcc.c \
../Peripheral/src/ch32v00X_spi.c \
../Peripheral/src/ch32v00X_tim.c \
../Peripheral/src/ch32v00X_usart.c \
../Peripheral/src/ch32v00X_wwdg.c 

C_DEPS += \
./Peripheral/src/ch32v00X_adc.d \
./Peripheral/src/ch32v00X_dbgmcu.d \
./Peripheral/src/ch32v00X_dma.d \
./Peripheral/src/ch32v00X_exti.d \
./Peripheral/src/ch32v00X_flash.d \
./Peripheral/src/ch32v00X_gpio.d \
./Peripheral/src/ch32v00X_i2c.d \
./Peripheral/src/ch32v00X_iwdg.d \
./Peripheral/src/ch32v00X_misc.d \
./Peripheral/src/ch32v00X_opa.d \
./Peripheral/src/ch32v00X_pwr.d \
./Peripheral/src/ch32v00X_rcc.d \
./Peripheral/src/ch32v00X_spi.d \
./Peripheral/src/ch32v00X_tim.d \
./Peripheral/src/ch32v00X_usart.d \
./Peripheral/src/ch32v00X_wwdg.d 

OBJS += \
./Peripheral/src/ch32v00X_adc.o \
./Peripheral/src/ch32v00X_dbgmcu.o \
./Peripheral/src/ch32v00X_dma.o \
./Peripheral/src/ch32v00X_exti.o \
./Peripheral/src/ch32v00X_flash.o \
./Peripheral/src/ch32v00X_gpio.o \
./Peripheral/src/ch32v00X_i2c.o \
./Peripheral/src/ch32v00X_iwdg.o \
./Peripheral/src/ch32v00X_misc.o \
./Peripheral/src/ch32v00X_opa.o \
./Peripheral/src/ch32v00X_pwr.o \
./Peripheral/src/ch32v00X_rcc.o \
./Peripheral/src/ch32v00X_spi.o \
./Peripheral/src/ch32v00X_tim.o \
./Peripheral/src/ch32v00X_usart.o \
./Peripheral/src/ch32v00X_wwdg.o 


EXPANDS += \
./Peripheral/src/ch32v00X_adc.c.253r.expand \
./Peripheral/src/ch32v00X_dbgmcu.c.253r.expand \
./Peripheral/src/ch32v00X_dma.c.253r.expand \
./Peripheral/src/ch32v00X_exti.c.253r.expand \
./Peripheral/src/ch32v00X_flash.c.253r.expand \
./Peripheral/src/ch32v00X_gpio.c.253r.expand \
./Peripheral/src/ch32v00X_i2c.c.253r.expand \
./Peripheral/src/ch32v00X_iwdg.c.253r.expand \
./Peripheral/src/ch32v00X_misc.c.253r.expand \
./Peripheral/src/ch32v00X_opa.c.253r.expand \
./Peripheral/src/ch32v00X_pwr.c.253r.expand \
./Peripheral/src/ch32v00X_rcc.c.253r.expand \
./Peripheral/src/ch32v00X_spi.c.253r.expand \
./Peripheral/src/ch32v00X_tim.c.253r.expand \
./Peripheral/src/ch32v00X_usart.c.253r.expand \
./Peripheral/src/ch32v00X_wwdg.c.253r.expand 



# Each subdirectory must supply rules for building sources it contributes
Peripheral/src/%.o: ../Peripheral/src/%.c
	@	riscv-wch-elf-gcc -march=rv32ec_zmmul_xw -mabi=ilp32e -msmall-data-limit=0 -msave-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized -g -I"/Users/ronanmingon/Documents/just-a-dice/software/Debug" -I"/Users/ronanmingon/Documents/just-a-dice/software/Core" -I"/Users/ronanmingon/Documents/just-a-dice/software/User" -I"/Users/ronanmingon/Documents/just-a-dice/software/Peripheral/inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"

