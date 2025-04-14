# Configurations
CXX = g++
CXXFLAGS = -std=c++11 -Iinclude -I/usr/include/SDL2 -D_REENTRANT
LDFLAGS = -lSDL2 -lSDL2_ttf -lSDL2_image

#Directories
SRC_DIR = src
INC_DIR = include

# Name of the executable
TARGET = The_Backlands

# Source files
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
HEADERS = $(wildcard $(INC_DIR)/*.h)

# Default rule
all: $(TARGET)

# Build the executable
$(TARGET): $(SRCS) $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Clean rule
clean:
	rm -f $(TARGET)