################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../src/inet/common/Compat.cc \
../src/inet/common/InitStages.cc \
../src/inet/common/ModuleAccess.cc \
../src/inet/common/PatternMatcher.cc 

CC_DEPS += \
./src/inet/common/Compat.d \
./src/inet/common/InitStages.d \
./src/inet/common/ModuleAccess.d \
./src/inet/common/PatternMatcher.d 

OBJS += \
./src/inet/common/Compat.o \
./src/inet/common/InitStages.o \
./src/inet/common/ModuleAccess.o \
./src/inet/common/PatternMatcher.o 


# Each subdirectory must supply rules for building sources it contributes
src/inet/common/%.o: ../src/inet/common/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C++ Compiler'
	g++ -O2 -g -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


