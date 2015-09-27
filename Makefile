CC = g++
CFLAGS  = -g  -Wall -std=c++11
TARGET = smrtlink

all: $(TARGET)

$(TARGET): src/*.cpp
	$(CC) $(CFLAGS) -o $(TARGET) src/*.cpp src/*.h
	
clean:
	rm src/$(TARGET).g

