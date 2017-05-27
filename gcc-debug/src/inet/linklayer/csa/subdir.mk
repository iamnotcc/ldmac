################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../src/inet/linklayer/csa/CsaApMac.cc \
../src/inet/linklayer/csa/CsaHostMac.cc 

CC_DEPS += \
./src/inet/linklayer/csa/CsaApMac.d \
./src/inet/linklayer/csa/CsaHostMac.d 

OBJS += \
./src/inet/linklayer/csa/CsaApMac.o \
./src/inet/linklayer/csa/CsaHostMac.o 


# Each subdirectory must supply rules for building sources it contributes
src/inet/linklayer/csa/%.o: ../src/inet/linklayer/csa/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C++ Compiler'
	g++ -O2 -g -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


