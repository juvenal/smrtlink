CC = g++
CFLAGS  = -Wall -std=c++11 
TARGET = smrtlink

all: $(TARGET)

$(TARGET): Types.o Program.o
	$(CC) $(CFLAGS) -o $(TARGET) *.o

Types.o: src/Types/*.cpp src/Types*.h
	$(CC) $(CFLAGS) -c src/Types/*.cpp
	
Program.o: src/*.cpp src/*.h
	$(CC) $(CFLAGS) -c src/*.cpp


clean:
	rm *.o

