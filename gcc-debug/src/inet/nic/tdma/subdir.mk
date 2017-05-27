################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../src/inet/nic/tdma/TdmaAck_m.cc \
../src/inet/nic/tdma/TdmaApMac.cc \
../src/inet/nic/tdma/TdmaHostMac.cc \
../src/inet/nic/tdma/TdmaReq_m.cc 

CC_DEPS += \
./src/inet/nic/tdma/TdmaAck_m.d \
./src/inet/nic/tdma/TdmaApMac.d \
./src/inet/nic/tdma/TdmaHostMac.d \
./src/inet/nic/tdma/TdmaReq_m.d 

OBJS += \
./src/inet/nic/tdma/TdmaAck_m.o \
./src/inet/nic/tdma/TdmaApMac.o \
./src/inet/nic/tdma/TdmaHostMac.o \
./src/inet/nic/tdma/TdmaReq_m.o 


# Each subdirectory must supply rules for building sources it contributes
src/inet/nic/tdma/%.o: ../src/inet/nic/tdma/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C++ Compiler'
	g++ -O2 -g -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


