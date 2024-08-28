#guyes134@gmail.com

# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++23 -Wall

# SFML libraries
LIBS = -lsfml-graphics -lsfml-window -lsfml-system

VALGRIND_FLAGS = -v --leak-check=full --show-leak-kinds=all  --error-exitcode=99

# Source files
SOURCES = Complex.cpp main.cpp
OBJECTS = Complex.o main.o
TOBJECTS = Complex.o Test.o

# Executables
EXECUTABLES = tree test

all: tree test

tree: $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) $(LIBS) -o tree

test: $(TOBJECTS)
	$(CXX) $(CXXFLAGS) $^ $(LIBS) -o test

main.o: main.cpp Node.hpp Tree.hpp TreeDrawer.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

Complex.o: Complex.cpp Complex.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

Test.o: Test.cpp Complex.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run tests with Valgrind
valgrind: tree test
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./tree 2>&1 | { egrep "lost| at " || true; }
#	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./test 2>&1 | { egrep "lost| at " || true; }

# Clean up generated files
clean:
	rm -f *.o $(EXECUTABLES)

# Phony targets
.PHONY: all clean
