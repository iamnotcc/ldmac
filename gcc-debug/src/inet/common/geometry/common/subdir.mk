################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../src/inet/common/geometry/common/CanvasProjection.cc \
../src/inet/common/geometry/common/Coord.cc \
../src/inet/common/geometry/common/CoordinateSystem.cc \
../src/inet/common/geometry/common/EulerAngles.cc \
../src/inet/common/geometry/common/Rotation.cc 

CC_DEPS += \
./src/inet/common/geometry/common/CanvasProjection.d \
./src/inet/common/geometry/common/Coord.d \
./src/inet/common/geometry/common/CoordinateSystem.d \
./src/inet/common/geometry/common/EulerAngles.d \
./src/inet/common/geometry/common/Rotation.d 

OBJS += \
./src/inet/common/geometry/common/CanvasProjection.o \
./src/inet/common/geometry/common/Coord.o \
./src/inet/common/geometry/common/CoordinateSystem.o \
./src/inet/common/geometry/common/EulerAngles.o \
./src/inet/common/geometry/common/Rotation.o 


# Each subdirectory must supply rules for building sources it contributes
src/inet/common/geometry/common/%.o: ../src/inet/common/geometry/common/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C++ Compiler'
	g++ -O2 -g -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


