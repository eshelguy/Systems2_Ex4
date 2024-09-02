#guyes134@gmail.com

# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++23 -Wall

# SFML libraries
LIBS = -lsfml-graphics -lsfml-window -lsfml-system

VALGRIND_FLAGS = --leak-check=full --show-leak-kinds=all

# Source files
SOURCES = Complex.cpp main.cpp
OBJECTS = Complex.o main.o
TOBJECTS = Complex.o Test.o

# Executables
EXECUTABLES = tree test run_test run_tree

all: tree test

tree: run_tree
	./run_tree

run_tree: $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) $(LIBS) -o $@

test: run_test
	./run_test

run_test: $(TOBJECTS)
	$(CXX) $(CXXFLAGS) $^ $(LIBS) -o $@

main.o: main.cpp Node.hpp Tree.hpp TreeDrawer.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

Complex.o: Complex.cpp Complex.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

Test.o: Test.cpp Complex.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run tests with Valgrind
valgrind: run_tree run_test
	valgrind  $(VALGRIND_FLAGS) ./run_tree
	valgrind  $(VALGRIND_FLAGS) ./run_test

# Clean up generated files
clean:
	rm -f *.o $(EXECUTABLES)

# Phony targets
.PHONY: all clean
