//guyes134@gmail.com

#ifndef TREEDRAWER_HPP
#define TREEDRAWER_HPP

#include <SFML/Graphics.hpp>
#include "Tree.hpp"

/**
 * @brief A class to visualize a k-ary tree using SFML.
 *
 * @tparam T The type of the values stored in the nodes.
 * @tparam K The maximum number of children each node can have.
 */
template<typename T, int K>
class TreeDrawer {
public:
    /**
     * @brief Constructs a TreeDrawer object.
     *
     * @param tree A pointer to the tree to visualize.
     * @param window A pointer to the SFML RenderWindow where the tree will be drawn.
     */
    TreeDrawer(Tree<T, K>* tree, sf::RenderWindow* window);

    /**
     * @brief Draws the tree on the window.
     */
    void draw();

    /**
     * @brief Runs the main loop to handle events and draw the tree.
     */
    void run();

private:
    Tree<T, K>* tree;  ///< Pointer to the tree to be visualized.
    sf::RenderWindow* window;  ///< Pointer to the SFML window where the tree will be drawn.

    /**
     * @brief Recursively draws a node and its children.
     *
     * @param node The node to draw.
     * @param x The x-coordinate of the node's position.
     * @param y The y-coordinate of the node's position.
     * @param hGap The horizontal gap between sibling nodes.
     */
    void drawNode(const std::shared_ptr<Node<T>>& node, int x, int y, int hGap);


    /**
     * @brief Draws an edge (a line) between a parent node and a child node.
     *
     * @param parentX The x-coordinate of the parent node.
     * @param parentY The y-coordinate of the parent node.
     * @param childX The x-coordinate of the child node.
     * @param childY The y-coordinate of the child node.
     */
    void drawEdge(int parentX, int parentY, int childX, int childY);
};

// Template class implementation
template<typename T, int K>
TreeDrawer<T, K>::TreeDrawer(Tree<T, K>* tree, sf::RenderWindow* window)
        : tree(tree), window(window) {}

template<typename T, int K>
void TreeDrawer<T, K>::draw() {
    if (tree && tree->getRoot()) {
        int rootX = window->getSize().x / 2;
        int rootY = 50;
        int horizontalGap = 250;
        drawNode(tree->getRoot(), rootX, rootY, horizontalGap);
    }
}

template<typename T, int K>
void TreeDrawer<T, K>::drawNode(const std::shared_ptr<Node<T>>& node, int x, int y, int hGap) {
    if (!node) return;

    // Calculate positions for children
    int childY = y + 100;
    std::vector<int> childX(K);

    for (int i = 0; i < K; ++i) {
        // Adjust horizontal positions of the children to avoid overlap
        childX[i] = x - hGap + (2 * hGap * i) / (K - 1);
    }

    // Draw children and edges
    for (int i = 0; i < K; ++i) {
        if (node->getChildAt(i)) {
            drawEdge(x, y, childX[i], childY);
            drawNode(node->getChildAt(i), childX[i], childY, hGap / 3);
        }
    }

    // Draw the node (a circle)
    sf::CircleShape circle(30);
    circle.setFillColor(sf::Color::White);
    circle.setOutlineColor(sf::Color::Black);
    circle.setOutlineThickness(2);
    circle.setPosition(x - 30, y - 30); // Center the circle
    window->draw(circle);

    // Draw the value inside the node
    sf::Font font;
    if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf")) {
        // Handle error (e.g., print error message)
        return;
    }

    sf::Text text(std::to_string(node->get_value()), font, 20);
    text.setFillColor(sf::Color::Black);
    text.setPosition(x - 20, y - 15); // Adjust position to center text
    window->draw(text);
}

template<typename T, int K>
void TreeDrawer<T, K>::run() {
    // Main loop
    while (window->isOpen()) {
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window->close();
        }

        window->clear(sf::Color::White);
        draw();
        window->display();
    }
}


template<typename T, int K>
void TreeDrawer<T, K>::drawEdge(int parentX, int parentY, int childX, int childY) {
    sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(parentX, parentY + 30), sf::Color::Black),  // Start at the bottom of the parent node
            sf::Vertex(sf::Vector2f(childX, childY - 30), sf::Color::Black)     // End at the top of the child node
    };
    window->draw(line, 2, sf::Lines);
}

#endif // TREEDRAWER_HPP
