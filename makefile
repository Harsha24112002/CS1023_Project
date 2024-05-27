# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++17 -Wall -Iinclude -Ilibs/gtest/include

# Linker flags
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-network -lsfml-system -lpthread

# Directories
SRC_DIR = src
BUILD_DIR = build
INCLUDE_DIR = include
TEST_DIR = tests

# Source files
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)

# Test files
TEST_FILES = $(wildcard $(TEST_DIR)/*.cpp)

# Object files
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRC_FILES))

# Test object files
TEST_OBJ_FILES = $(patsubst $(TEST_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(TEST_FILES))

# Executable names
TARGET = $(BUILD_DIR)/Run2Win
TEST_TARGET = $(BUILD_DIR)/test

# Default target
all: $(TARGET) $(TEST_TARGET)
game: $(TARGET)
test: $(TEST_TARGET)

# Build target
$(TARGET): $(OBJ_FILES)
	$(CXX) $(OBJ_FILES) -o $(TARGET) $(LDFLAGS)

# Build test target
$(TEST_TARGET): $(OBJ_FILES) $(TEST_OBJ_FILES) $(BUILD_DIR)/gtest_main.o
	$(CXX) $(OBJ_FILES) $(TEST_OBJ_FILES) $(BUILD_DIR)/gtest_main.o -o $(TEST_TARGET) $(LDFLAGS)

# Compile source files into object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile test files into object files
$(BUILD_DIR)/%.o: $(TEST_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile gtest_main into object file
$(BUILD_DIR)/gtest_main.o: libs/gtest/src/gtest_main.cc | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Create build directory if it doesn't exist
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Clean up build files
clean:
	rm -rf $(BUILD_DIR)

# Phony targets
.PHONY: all clean
