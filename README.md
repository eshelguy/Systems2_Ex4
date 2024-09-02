# Tree Visualization and Traversal in C++

## Table of Contents
1. [Overview](#overview)
2. [Project Structure](#project-structure)
3. [Class Descriptions](#class-descriptions)
   - [Node](#node)
   - [Tree](#tree)
   - [Iterators](#iterators)
   - [TreeDrawer](#treedrawer)
   - [Complex](#complex)
4. [Usage](#usage)
   - [Compiling the Project](#compiling-the-project)
   - [Running the Program](#running-the-program)
   - [Expected Output](#expected-output)
5. [Examples](#examples)
   - [Traversal Examples](#traversal-examples)
   - [Tree Visualization](#tree-visualization)
6. [Dependencies](#dependencies)

## Overview
This project implements a generic k-ary tree in C++ with various traversal methods and visualizations. It supports different types of nodes, including complex numbers, and allows for pre-order, post-order, in-order, breadth-first search (BFS), depth-first search (DFS), and heap traversal. Additionally, the tree structure can be visualized using the SFML library.

## Project Structure
```
.
├── main.cpp          // Entry point of the application
├── Node.hpp          // Definition of the Node class
├── Tree.hpp          // Definition of the Tree class and iterators
├── TreeDrawer.hpp    // Definition of the TreeDrawer class for visualizing the tree using SFML
├── Complex.hpp       // Definition of the Complex number class
├── Complex.cpp       // Implementation of the Complex number class
├── CMakeLists.txt    // CMake configuration file
└── README.md         // Detailed explanation of the project (this file)
```

## Class Descriptions

### Node
The `Node` class represents a node in a k-ary tree. Each node holds a value of generic type `T` and can have up to `k` children.

- **Constructor**: Initializes a node with a specified value and a fixed number of children.
- **Methods**:
  - `get_value()`: Returns the value stored in the node.
  - `getNumOfChildren()`: Returns the number of non-null children the node has.
  - `addChildAt()`: Adds a child node at a specified index.
  - `getChildAt()`: Retrieves a child node at a specified index.

### Tree
The `Tree` class represents a k-ary tree with nodes of type `T`. It supports adding nodes, traversing the tree using various iterators, and transforming the tree into a min-heap.

- **Constructor**: Initializes an empty tree with a specified maximum number of children per node (`k`).
- **Methods**:
  - `add_root()`: Adds a root node to the tree.
  - `add_sub_node()`: Adds a child node to a specified parent node.
  - `myHeap()`: Transforms the tree into a min-heap and returns an iterator for traversing the heap.
  - `begin_pre_order()`, `begin_post_order()`, `begin_in_order()`, `begin_bfs_scan()`, `begin_dfs_scan()`: Return iterators for various traversal methods.
  - `end_pre_order()`, `end_post_order()`, `end_in_order()`, `end_bfs_scan()`, `end_dfs_scan()`: Return iterators representing the end of the traversal.

### Iterators
The tree supports several iterators for different traversal methods:
- **PreOrderIterator**: Visits the current node before its children.
- **PostOrderIterator**: Visits the current node after its children.
- **InOrderIterator**: Visits the left child, then the current node, and finally the right child (specific to binary trees).
- **BFSIterator**: Visits nodes level by level, starting from the root.
- **DFSIterator**: Visits nodes as far as possible along each branch before backtracking.
- **HeapIterator**: Traverses the tree after it has been transformed into a min-heap.

### TreeDrawer
The `TreeDrawer` class visualizes the tree using the SFML graphics library. It recursively draws each node and its children, creating edges between parent and child nodes.

- **Constructor**: Initializes the `TreeDrawer` with a pointer to a tree and an SFML window.
- **Methods**:
  - `draw()`: Draws the entire tree on the window.
  - `drawNode()`: Recursively draws a node and its children.
  - `drawEdge()`: Draws a line between a parent node and a child node.
  - `run()`: Runs the main loop to handle events and draw the tree.

### Complex
The `Complex` class represents complex numbers and supports basic operations such as comparison and output formatting.

- **Constructor**: Initializes a complex number with specified real and imaginary parts.
- **Methods**:
  - `getReal()`: Returns the real part of the complex number.
  - `getImag()`: Returns the imaginary part of the complex number.
  - **Overloaded Operators**:
    - `<`: Compares the magnitudes of two complex numbers.
    - `==`: Checks if two complex numbers are equal.
    - `<<`: Outputs a complex number in the format `(a + bi)`.

## Usage

### Compiling the Project
To compile the project, you can use `CMake` or directly compile it using `g++`:

Using `CMake`:
```bash
mkdir build
cd build
cmake ..
make
```

Using `g++` directly:
```bash
g++ -std=c++17 -o tree_visualization main.cpp Complex.cpp -lsfml-graphics -lsfml-window -lsfml-system
```

### Running the Program
Once compiled, you can run the program as follows:
```bash
./tree_visualization
```
This will execute the main program, which creates various tree structures, performs different types of traversals, and visualizes a tree using SFML.

### Expected Output
- **Console Output**: The console will display the results of different tree traversals (pre-order, post-order, in-order, BFS, DFS, and heap traversal).
- **SFML Window**: A window will open displaying a visual representation of a k-ary tree. Nodes are drawn as circles with edges connecting parent and child nodes.

## Examples

### Traversal Examples
The main function demonstrates the following traversal methods:
1. **Pre-Order Traversal**: Visits the current node before its children.
   ```
   Pre-Order Traversal:
   1 2 4 5 3 6
   ```
2. **Post-Order Traversal**: Visits the current node after its children.
   ```
   Post-Order Traversal:
   4 5 2 6 3 1
   ```
3. **In-Order Traversal**: Visits the left child, then the current node, and finally the right child (only applicable to binary trees).
   ```
   In-Order Traversal:
   4 2 5 1 6 3
   ```
4. **BFS Traversal**: Visits nodes level by level, starting from the root.
   ```
   BFS Traversal:
   1 2 3 4 5 6
   ```
5. **DFS Traversal**: Visits nodes as far as possible along each branch before backtracking (similar to pre-order).
   ```
   DFS Traversal (Explicit):
   1 2 4 5 3 6
   ```
6. **Heap Traversal**: Traverses the tree after it has been transformed into a min-heap.
   ```
   Heap Order Traversal:
   10 15 20 30 40 50 60
   ```

### Tree Visualization
- The `TreeDrawer` class visualizes the tree in an SFML window. Nodes are drawn as circles, with lines connecting parent and child nodes. The tree is centered in the window, and the visualization is dynamically adjusted based on the tree structure.

## Dependencies
This project relies on the following dependencies:
- **SFML**: Simple and Fast Multimedia Library for 2D graphics. Install it using the package manager of your choice:
  - On Ubuntu: `sudo apt-get install libsfml-dev`
  - On macOS: `brew install sfml`
- **Makefile**: For generating build files.
- **g++**: GCC compiler for compiling the C++ code.

Make sure these dependencies are installed before compiling and running the project.

