//guyes134@gmail.com

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Tree.hpp"
#include "Complex.hpp"
#include "TreeDrawer.hpp"

int main() {

    // Create a binary tree with integer values
    Tree<int, 2> tree;

    // Adding root and sub-nodes using raw int values
    tree.add_root(1);  // Add root node with value 1
    tree.add_sub_node(1, 2);  // Add node with value 2 as a child of node with value 1
    tree.add_sub_node(1, 3);  // Add node with value 3 as a child of node with value 1
    tree.add_sub_node(2, 4);  // Add node with value 4 as a child of node with value 2
    tree.add_sub_node(2, 5);  // Add node with value 5 as a child of node with value 2
    tree.add_sub_node(3, 6);  // Add node with value 6 as a child of node with value 3

    // The tree should look like:
    /**
     *       1
     *     /   \
     *    2     3
     *   / \   /
     *  4   5 6
     */

    // Pre-Order Traversal
    std::cout << "Pre-Order Traversal:" << std::endl;
    for (auto it = tree.begin_pre_order(); it != tree.end_pre_order(); ++it) {
        std::cout << *it << " ";  // Expected output: 1 2 4 5 3 6
    }
    std::cout << std::endl;

    // Post-Order Traversal
    std::cout << "Post-Order Traversal:" << std::endl;
    for (auto it = tree.begin_post_order(); it != tree.end_post_order(); ++it) {
        std::cout << *it << " ";  // Expected output: 4 5 2 6 3 1
    }
    std::cout << std::endl;

    // In-Order Traversal
    std::cout << "In-Order Traversal:" << std::endl;
    for (auto it = tree.begin_in_order(); it != tree.end_in_order(); ++it) {
        std::cout << *it << " ";  // Expected output: 4 2 5 1 6 3
    }
    std::cout << std::endl;

    // BFS Traversal
    std::cout << "BFS Traversal:" << std::endl;
    for (auto it = tree.begin_bfs_scan(); it != tree.end_bfs_scan(); ++it) {
        std::cout << *it << " ";  // Expected output: 1 2 3 4 5 6
    }
    std::cout << std::endl;

    // Creating a 3-ary tree with double values
    Tree<double, 3> three_ary_tree;

    // Adding root and sub-nodes using raw double values
    three_ary_tree.add_root(1.1);
    three_ary_tree.add_sub_node(1.1, 1.2);
    three_ary_tree.add_sub_node(1.1, 1.3);
    three_ary_tree.add_sub_node(1.1, 1.4);
    three_ary_tree.add_sub_node(1.2, 1.5);
    three_ary_tree.add_sub_node(1.3, 1.6);

    // The 3-ary tree should look like:
    /**
     *       1.1
     *     /  |  \
     *   1.2 1.3 1.4
     *   /    |
     * 1.5   1.6
     */

    // Printing 3-ary Tree Structure
    std::cout << "3-ary Tree Structure:" << std::endl;
    std::cout << three_ary_tree; // Should print the 3-ary tree structure.


    // Create a binary tree with Complex values
    Tree<Complex, 2> complex_tree;

    // Adding root and sub-nodes using Complex values
    complex_tree.add_root(Complex(1.0, 2.0));
    complex_tree.add_sub_node(Complex(1.0, 2.0), Complex(3.0, 4.0));
    complex_tree.add_sub_node(Complex(1.0, 2.0), Complex(5.0, 6.0));
    complex_tree.add_sub_node(Complex(3.0, 4.0), Complex(7.0, 8.0));

    // The complex tree should look like:
    /**
     *       (1.0 + 2.0i)
     *       /         \
     *   (3.0 + 4.0i)  (5.0 + 6.0i)
     *      /
     *  (7.0 + 8.0i)
     */

    // Pre-Order Traversal
    std::cout << "Complex Tree Pre-Order Traversal:" << std::endl;
    for (auto it = complex_tree.begin_pre_order(); it != complex_tree.end_pre_order(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // Create the SFML window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Tree Visualization");
    window.setVerticalSyncEnabled(false); // Disable VSync
    window.setFramerateLimit(60); // Limits the frame rate to 60 FPS

    // Create a k-ary tree with integer values, where k = 3
    Tree<int, 3> intTree;

    intTree.add_root(1);
    intTree.add_sub_node(1, 2);
    intTree.add_sub_node(1, 3);
    intTree.add_sub_node(1, 4);

    intTree.add_sub_node(2, 5);
    intTree.add_sub_node(2, 6);
    intTree.add_sub_node(2, 7);

    intTree.add_sub_node(3, 8);
    intTree.add_sub_node(3, 9);
    intTree.add_sub_node(3, 10);

    intTree.add_sub_node(4, 11);
    intTree.add_sub_node(4, 12);
    intTree.add_sub_node(4, 13);

    intTree.add_sub_node(5, 14);
    intTree.add_sub_node(5, 15);
    intTree.add_sub_node(5, 16);

    intTree.add_sub_node(6, 17);
    intTree.add_sub_node(6, 18);
    intTree.add_sub_node(6, 19);

    // Create the tree drawer
    TreeDrawer treeDrawer(&intTree, &window);

    // Main loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White);
        treeDrawer.draw();
        window.display();
    }
    return 0;
}