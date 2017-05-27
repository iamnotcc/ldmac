################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../src/inet/nic/ld/LdAck_m.cc \
../src/inet/nic/ld/LdApMac.cc \
../src/inet/nic/ld/LdHostMac.cc \
../src/inet/nic/ld/LdReq_m.cc 

CC_DEPS += \
./src/inet/nic/ld/LdAck_m.d \
./src/inet/nic/ld/LdApMac.d \
./src/inet/nic/ld/LdHostMac.d \
./src/inet/nic/ld/LdReq_m.d 

OBJS += \
./src/inet/nic/ld/LdAck_m.o \
./src/inet/nic/ld/LdApMac.o \
./src/inet/nic/ld/LdHostMac.o \
./src/inet/nic/ld/LdReq_m.o 


# Each subdirectory must supply rules for building sources it contributes
src/inet/nic/ld/%.o: ../src/inet/nic/ld/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C++ Compiler'
	g++ -O2 -g -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


