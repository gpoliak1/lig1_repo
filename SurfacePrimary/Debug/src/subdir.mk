################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/OpenGL_Auxiliary.cpp \
../src/Utils.cpp \
../src/config.cpp 

OBJS += \
./src/OpenGL_Auxiliary.o \
./src/Utils.o \
./src/config.o 

CPP_DEPS += \
./src/OpenGL_Auxiliary.d \
./src/Utils.d \
./src/config.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


