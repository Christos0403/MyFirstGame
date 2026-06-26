# Compiler
CXX      := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -Werror $(shell pkg-config --cflags raylib) -IWindow -ISetUp

# Linker flags / libraries
LDLIBS   := $(shell pkg-config --libs raylib)

# Project structure
SRC_DIR  := .
SRC      := \
    game.cpp \
    SetUp/State.cpp 

OBJ      := $(SRC:.cpp=.o)
TARGET   := game

# Default build
all: $(TARGET)

# Link step
$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $@ $(LDLIBS)

# Compile step
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run
run: $(TARGET)
	./$(TARGET)

# Clean
clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all run clean