################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../src/inet/visualizer/networknode/NetworkNodeCanvasVisualization.cc \
../src/inet/visualizer/networknode/NetworkNodeCanvasVisualizer.cc 

CC_DEPS += \
./src/inet/visualizer/networknode/NetworkNodeCanvasVisualization.d \
./src/inet/visualizer/networknode/NetworkNodeCanvasVisualizer.d 

OBJS += \
./src/inet/visualizer/networknode/NetworkNodeCanvasVisualization.o \
./src/inet/visualizer/networknode/NetworkNodeCanvasVisualizer.o 


# Each subdirectory must supply rules for building sources it contributes
src/inet/visualizer/networknode/%.o: ../src/inet/visualizer/networknode/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C++ Compiler'
	g++ -O2 -g -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


