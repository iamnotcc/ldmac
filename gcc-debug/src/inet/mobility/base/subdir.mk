################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../src/inet/mobility/base/LineSegmentsMobilityBase.cc \
../src/inet/mobility/base/MobilityBase.cc \
../src/inet/mobility/base/MovingMobilityBase.cc 

CC_DEPS += \
./src/inet/mobility/base/LineSegmentsMobilityBase.d \
./src/inet/mobility/base/MobilityBase.d \
./src/inet/mobility/base/MovingMobilityBase.d 

OBJS += \
./src/inet/mobility/base/LineSegmentsMobilityBase.o \
./src/inet/mobility/base/MobilityBase.o \
./src/inet/mobility/base/MovingMobilityBase.o 


# Each subdirectory must supply rules for building sources it contributes
src/inet/mobility/base/%.o: ../src/inet/mobility/base/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C++ Compiler'
	g++ -O2 -g -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


