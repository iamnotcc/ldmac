################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../src/inet/common/figures/TrailFigure.cc 

CC_DEPS += \
./src/inet/common/figures/TrailFigure.d 

OBJS += \
./src/inet/common/figures/TrailFigure.o 


# Each subdirectory must supply rules for building sources it contributes
src/inet/common/figures/%.o: ../src/inet/common/figures/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C++ Compiler'
	g++ -O2 -g -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


