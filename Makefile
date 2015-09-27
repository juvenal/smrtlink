  # the compiler: gcc for C program, define as g++ for C++
CC = g++

  # compiler flags:
  #  -g    adds debugging information to the executable file
  #  -Wall turns on most, but not all, compiler warnings
CFLAGS  = -g -Wall -lrt -lpthread -lc -std=c++11

  # the build target executable:
TARGET = smrtlink

all: $(TARGET)

$(TARGET): src/*.cpp
	$(CC) $(CFLAGS) -o $(TARGET) src/*.cpp src/*.h
	
clean:
	$(RM) $(TARGET)

