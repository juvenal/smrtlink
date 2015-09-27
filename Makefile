  # the compiler: gcc for C program, define as g++ for C++
CC = g++

  # compiler flags:
  #  -g    adds debugging information to the executable file
  #  -Wall turns on most, but not all, compiler warnings
CFLAGS  = -g -Wall -lrt -std=c++11

  # the build target executable:
TARGET = smrtlink

all: $(TARGET)

$(TARGET): $(TARGET).o
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).o
	
$(TARGET).o: src/*.cpp
	$(CC) $(CFLAGS) src/*.cpp src/*.h

clean:
	$(RM) $(TARGET)

