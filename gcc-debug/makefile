################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/inet/visualizer/networknode/subdir.mk
-include src/inet/visualizer/mobility/subdir.mk
-include src/inet/visualizer/base/subdir.mk
-include src/inet/nic/tdma/subdir.mk
-include src/inet/nic/ld/subdir.mk
-include src/inet/nic/csa/subdir.mk
-include src/inet/nic/aloha/subdir.mk
-include src/inet/mobility/static/subdir.mk
-include src/inet/mobility/single/subdir.mk
-include src/inet/mobility/contract/subdir.mk
-include src/inet/mobility/base/subdir.mk
-include src/inet/linklayer/tdma/subdir.mk
-include src/inet/linklayer/ld/subdir.mk
-include src/inet/linklayer/csa/subdir.mk
-include src/inet/linklayer/aloha/subdir.mk
-include src/inet/common/queue/subdir.mk
-include src/inet/common/geometry/common/subdir.mk
-include src/inet/common/figures/subdir.mk
-include src/inet/common/subdir.mk
-include src/inet/application/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: ldmac

# Tool invocations
ldmac: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: Cygwin C++ Linker'
	g++  -o "ldmac" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(CC_DEPS)$(C++_DEPS)$(EXECUTABLES)$(OBJS)$(C_UPPER_DEPS)$(CXX_DEPS)$(CPP_DEPS)$(C_DEPS) ldmac
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
