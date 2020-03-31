CXX = g++

# Test Definitions
TEST_SRCDIR = test
TEST_SRCFILES = $(wildcard $(TEST_SRCDIR)/*.cpp)
TEST_TARGET = main
TEST_CXXFLAGS = -std=c++17 -Wall -Wextra -g

all: $(TEST_TARGET)
cleanall: clean all

$(TEST_TARGET): $(TEST_SRCFILES) 
	$(CXX) $(TEST_CXXFLAGS) $^ -o $@

clean:
	rm -f $(TEST_TARGET)
