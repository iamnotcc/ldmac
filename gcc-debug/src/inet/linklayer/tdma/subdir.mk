################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../src/inet/linklayer/tdma/ApAllocationPkOfTDMA_m.cc \
../src/inet/linklayer/tdma/HostReqPkOfTDMA_m.cc \
../src/inet/linklayer/tdma/TdmaApMac.cc \
../src/inet/linklayer/tdma/TdmaHostMac.cc 

CC_DEPS += \
./src/inet/linklayer/tdma/ApAllocationPkOfTDMA_m.d \
./src/inet/linklayer/tdma/HostReqPkOfTDMA_m.d \
./src/inet/linklayer/tdma/TdmaApMac.d \
./src/inet/linklayer/tdma/TdmaHostMac.d 

OBJS += \
./src/inet/linklayer/tdma/ApAllocationPkOfTDMA_m.o \
./src/inet/linklayer/tdma/HostReqPkOfTDMA_m.o \
./src/inet/linklayer/tdma/TdmaApMac.o \
./src/inet/linklayer/tdma/TdmaHostMac.o 


# Each subdirectory must supply rules for building sources it contributes
src/inet/linklayer/tdma/%.o: ../src/inet/linklayer/tdma/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C++ Compiler'
	g++ -O2 -g -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


