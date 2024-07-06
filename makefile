# Define the compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -I/usr/include/SDL2 -Iinclude
LDFLAGS = -lSDL2

# Define the source and object files
SRCDIR = src
OBJDIR = obj
BINDIR = bin
SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
TARGET = $(BINDIR)/MyProject

# Default target
all: $(TARGET)

# Create the target executable
$(TARGET): $(OBJECTS)
	@mkdir -p $(BINDIR)
	$(CXX) $(OBJECTS) -o $@ $(LDFLAGS)

# Compile source files into object files
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR) $(BINDIR)

# Phony targets
.PHONY: all clean