################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Src/Clock/Clock.cpp 

OBJS += \
./Src/Clock/Clock.o 

CPP_DEPS += \
./Src/Clock/Clock.d 


# Each subdirectory must supply rules for building sources it contributes
Src/Clock/%.o Src/Clock/%.su Src/Clock/%.cyclo: ../Src/Clock/%.cpp Src/Clock/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F446RETx -c -I../Inc -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src-2f-Clock

clean-Src-2f-Clock:
	-$(RM) ./Src/Clock/Clock.cyclo ./Src/Clock/Clock.d ./Src/Clock/Clock.o ./Src/Clock/Clock.su

.PHONY: clean-Src-2f-Clock

