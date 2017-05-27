################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../src/inet/visualizer/mobility/MobilityCanvasVisualizer.cc 

CC_DEPS += \
./src/inet/visualizer/mobility/MobilityCanvasVisualizer.d 

OBJS += \
./src/inet/visualizer/mobility/MobilityCanvasVisualizer.o 


# Each subdirectory must supply rules for building sources it contributes
src/inet/visualizer/mobility/%.o: ../src/inet/visualizer/mobility/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C++ Compiler'
	g++ -O2 -g -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


