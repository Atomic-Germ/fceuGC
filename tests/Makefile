CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -O2 -g
INCLUDES = -Iframework -Imocks -I../source
LDFLAGS = 

# Source files
MOCKS_SRC = mocks/mock_libogc.cpp
UNIT_SOURCES = $(wildcard unit/test_*.cpp)
TEST_MAIN = unit/test_main.cpp

# Object files
MOCKS_OBJ = $(MOCKS_SRC:.cpp=.o)
UNIT_OBJECTS = $(UNIT_SOURCES:.cpp=.o)
TEST_MAIN_OBJ = $(TEST_MAIN:.cpp=.o)

# Executable
TEST_EXECUTABLE = run_tests

.PHONY: all tests clean run

all: tests

tests: $(TEST_EXECUTABLE)

$(TEST_EXECUTABLE): $(MOCKS_OBJ) $(UNIT_OBJECTS) $(TEST_MAIN_OBJ)
	@echo "Linking test executable..."
	$(CXX) $(LDFLAGS) -o $@ $^
	@echo "✓ Test executable built successfully"

%.o: %.cpp
	@echo "Compiling: $<"
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

run: $(TEST_EXECUTABLE)
	@echo "Running unit tests..."
	@./$(TEST_EXECUTABLE)

clean:
	@echo "Cleaning test build artifacts..."
	@rm -f $(MOCKS_OBJ) $(UNIT_OBJECTS) $(TEST_MAIN_OBJ)
	@rm -f $(TEST_EXECUTABLE)
	@echo "✓ Clean complete"
