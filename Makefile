CC = g++
CFLAGS = -g -c -std=c++14
TARGET = smrtlink
SOURCEDIR = src
BUILDDIR = bin

SOURCES = $(wildcard $(SOURCEDIR)/*.cpp)
OBJECTS = $(patsubst $(SOURCEDIR)/%.cpp,$(BUILDDIR)/%.o,$(SOURCES))

all: $(TARGET)


$(TARGET): $(OBJECTS)
	$(CC) $^ -o $@


$(OBJECTS): $(BUILDDIR)/%.o : $(SOURCEDIR)/%.cpp
	$(CC) $(CFLAGS) $< -o $@


clean:
	rm -f $(BUILDDIR)/*o $(TARGET)
