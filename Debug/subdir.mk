################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Board\ -\ Copy.cpp \
../Board.cpp \
../Board1.cpp \
../Chess.cpp \
../main.cpp \
../unittest.cpp 

O_SRCS += \
../Board.o \
../Chess.o \
../main.o 

OBJS += \
./Board\ -\ Copy.o \
./Board.o \
./Board1.o \
./Chess.o \
./main.o \
./unittest.o 

CPP_DEPS += \
./Board\ -\ Copy.d \
./Board.d \
./Board1.d \
./Chess.d \
./main.d \
./unittest.d 


# Each subdirectory must supply rules for building sources it contributes
Board\ -\ Copy.o: ../Board\ -\ Copy.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -std=c++0x -MMD -MP -MF"Board - Copy.d" -MT"Board\ -\ Copy.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -std=c++0x -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


