//guyes134@gmail.com

#ifndef NODE_HPP
#define NODE_HPP

#include <memory>
#include <vector>
#include <algorithm>


// * all the implementation are in the tree.hpp file
// * when we use templates we cannot create implementation in cpp file.


/**
 * i have multiple iterators (PreOrderIterator, PostOrderIterator, InOrderIterator, etc.)
 * that traverse the tree. These iterators need to keep references to nodes as they iterate. If i wiil used std::unique_ptr,
 * it would be challenging to maintain these references without transferring ownership of the nodes,
 * which would disrupt the tree structure.
 */


/**
 * @brief A class representing a node in a k-ary tree.
 *
 * @tparam T The type of the value stored in the node.
 */
template<typename T>
class Node {
private:
    T value;  ///< The value stored in the node.
    std::vector<std::shared_ptr<Node<T>>> children;  ///< The children of the node.

public:
    /**
     * @brief Constructs a node with the given value and a fixed number of children.
     */
    Node(const T& value, size_t k = 2) : value(value), children(k, nullptr) {}

    /**
     * @brief Gets the value stored in the node.
     */
    T& get_value() {  // Return a non-const reference to the value
        return value;
    }

    /**
     * @brief Gets the value stored in the node (const version).
     *
     * @return A const reference to the value.
     */
    const T& get_value() const {  // Return a const reference to the value
        return value;
    }

    /**
     * @brief Gets the number of non-null children the node has.
     *
     * @return The number of non-null children.
     */
    int getNumOfChildren() const {
        return std::count_if(children.begin(), children.end(), [](const std::shared_ptr<Node<T>>& child) {
            return child != nullptr;
        });
    }

    /**
     * @brief Adds a child node at the specified index.
     *
     * @param child The child node to add.
     * @param index The index at which to add the child.
     */
    void addChildAt(const std::shared_ptr<Node<T>>& child, size_t index) {
        if (child == nullptr) {
            throw std::invalid_argument("Cannot add nullptr as a child");
        }
        if (index >= children.size()) {
            throw std::out_of_range("Index out of range");
        }
        children[index] = child;
    }

    /**
     * @brief Gets the children of the node.
     *
     * @return A const reference to the vector of children.
     */
    const std::vector<std::shared_ptr<Node<T>>>& get_children() const {
        return children;
    }

    /**
     * @brief Gets the child node at the specified index.
     *
     * @param index The index of the child to get.
     * @return A shared pointer to the child node.
     */
    std::shared_ptr<Node<T>> getChildAt(size_t index) const {
        if (index >= children.size()) {
            throw std::out_of_range("Index out of range");
        }
        return children[index];
    }
};

#endif // NODE_HPP