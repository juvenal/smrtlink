CC = g++
CFLAGS = -o0 -g -c -std=c++14
TARGET = smrtlink
SOURCEDIR = src
BUILDDIR = bin

SOURCES = $(wildcard $(SOURCEDIR)/*.cpp)
OBJECTS = $(patsubst $(SOURCEDIR)/%.cpp,$(BUILDDIR)/%.o,$(SOURCES))

all: $(BUILDDIR) $(TARGET)


$(BUILDDIR):
	mkdir -p $(BUILDDIR)


$(TARGET): $(OBJECTS)
	$(CC) $^ -o $(BUILDDIR)/$@ -lboost_filesystem -lboost_system -lpthread


$(OBJECTS): $(BUILDDIR)/%.o : $(SOURCEDIR)/%.cpp
	$(CC) $(CFLAGS) $< -o $@

install: bin/$(TARGET)
	install -m 0755 bin/$(TARGET) $(prefix)/bin

clean:
	rm -f $(BUILDDIR)/*
