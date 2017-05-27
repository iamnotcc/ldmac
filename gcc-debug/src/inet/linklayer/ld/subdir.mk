################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../src/inet/linklayer/ld/ApAllocationPacket_m.cc \
../src/inet/linklayer/ld/HostReqPacket_m.cc \
../src/inet/linklayer/ld/LdApMac.cc \
../src/inet/linklayer/ld/LdHostMac.cc 

CC_DEPS += \
./src/inet/linklayer/ld/ApAllocationPacket_m.d \
./src/inet/linklayer/ld/HostReqPacket_m.d \
./src/inet/linklayer/ld/LdApMac.d \
./src/inet/linklayer/ld/LdHostMac.d 

OBJS += \
./src/inet/linklayer/ld/ApAllocationPacket_m.o \
./src/inet/linklayer/ld/HostReqPacket_m.o \
./src/inet/linklayer/ld/LdApMac.o \
./src/inet/linklayer/ld/LdHostMac.o 


# Each subdirectory must supply rules for building sources it contributes
src/inet/linklayer/ld/%.o: ../src/inet/linklayer/ld/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C++ Compiler'
	g++ -O2 -g -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


