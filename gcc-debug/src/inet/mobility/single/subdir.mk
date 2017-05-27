################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../src/inet/mobility/single/RandomWPMobility.cc 

CC_DEPS += \
./src/inet/mobility/single/RandomWPMobility.d 

OBJS += \
./src/inet/mobility/single/RandomWPMobility.o 


# Each subdirectory must supply rules for building sources it contributes
src/inet/mobility/single/%.o: ../src/inet/mobility/single/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C++ Compiler'
	g++ -O2 -g -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


