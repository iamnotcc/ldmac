################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../src/inet/nic/csa/CsaApMac.cc \
../src/inet/nic/csa/CsaHostMac.cc \
../src/inet/nic/csa/CsaHostPk_m.cc 

CC_DEPS += \
./src/inet/nic/csa/CsaApMac.d \
./src/inet/nic/csa/CsaHostMac.d \
./src/inet/nic/csa/CsaHostPk_m.d 

OBJS += \
./src/inet/nic/csa/CsaApMac.o \
./src/inet/nic/csa/CsaHostMac.o \
./src/inet/nic/csa/CsaHostPk_m.o 


# Each subdirectory must supply rules for building sources it contributes
src/inet/nic/csa/%.o: ../src/inet/nic/csa/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C++ Compiler'
	g++ -O2 -g -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


