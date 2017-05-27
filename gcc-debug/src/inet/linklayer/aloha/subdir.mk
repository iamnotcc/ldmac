################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../src/inet/linklayer/aloha/AlohaApMac.cc \
../src/inet/linklayer/aloha/AlohaHostMac.cc 

CC_DEPS += \
./src/inet/linklayer/aloha/AlohaApMac.d \
./src/inet/linklayer/aloha/AlohaHostMac.d 

OBJS += \
./src/inet/linklayer/aloha/AlohaApMac.o \
./src/inet/linklayer/aloha/AlohaHostMac.o 


# Each subdirectory must supply rules for building sources it contributes
src/inet/linklayer/aloha/%.o: ../src/inet/linklayer/aloha/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C++ Compiler'
	g++ -O2 -g -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


