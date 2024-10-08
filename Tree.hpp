//guyes134@gmail.com

#ifndef TREE_HPP
#define TREE_HPP

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <memory>
#include "Node.hpp"


// * all the implementation are in the tree.hpp file
// * when we use templates we cannot create implementation in cpp file.


/**
 * @brief A generic k-ary tree class.
 *
 * @tparam T The type of the values stored in the nodes.
 * @tparam k The maximum number of children each node can have. Defaults to 2 (binary tree).
 */

template<typename T, int k = 2>
class Tree {
private:
    std::shared_ptr<Node<T>> root;  ///< Pointer to the root node.
    int k_ary;  ///< Maximum number of children per node.

public:
    /**
    * @brief Constructs an empty k-ary tree.
    */
    Tree() : root(nullptr), k_ary(k) {}

    /**
    * @brief Destructor that resets the root.
    */
    ~Tree() {
        root.reset();
    }

    /**
    * @brief Gets the root of the tree.
    *
    * @return A shared pointer to the root node.
    */
    std::shared_ptr<Node<T>> getRoot() const {
        return root;
    }

    /**
     * @brief Gets the k-ary value (maximum number of children per node).
     *
     * @return The k-ary value.
     */
    int getK_Ary() const {
        return k_ary;
    }

    /**
     * @brief Adds a root node to the tree.
     *
     * @param key The value of the root node.
     */
    void add_root(const T& key) {
        root = std::make_shared<Node<T>>(key, k);
    }

    /**
     * @brief Adds a child node to a specified parent node.
     *
     * @param parent_key The value of the parent node.
     * @param child_key The value of the child node to add.
     */
    void add_sub_node(const T& parent_key, const T& child_key) {
        auto parent_node = find(root, parent_key);
        if (parent_node != nullptr) {
            // Find the first available slot for the child
            for (size_t i = 0; i < parent_node->get_children().size(); ++i) {
                if (!parent_node->getChildAt(i)) {
                    parent_node->addChildAt(std::make_shared<Node<T>>(child_key, k), i);
                    return;
                }
            }
            throw std::out_of_range("No available slot for a new child");
        } else {
            throw std::invalid_argument("Parent node not found");
        }
    }


// Iterators for various tree traversals

/**-----------------------------------Pre Order Iterator-------------------------------------------**/

/**
 * @brief An iterator for traversing the tree in pre-order.
 *
 * In pre-order traversal, the current node is visited before its children.
 * This iterator uses a stack to keep track of the nodes to be visited.
 */
    class PreOrderIterator {
    private:
        std::stack<std::shared_ptr<Node<T>>> stack;  ///< Stack to hold nodes for traversal.

    public:
        /**
         * @brief Constructs a PreOrderIterator starting at the given root.
         *
         * @param root The root node to start the traversal from.
         */
        PreOrderIterator(std::shared_ptr<Node<T>> root, int k_ary) {
            if (k_ary != 2) {
                throw std::invalid_argument("PreOrderIterator can only be used with a binary tree (k_ary = 2).");
            }
            if (root) stack.push(root);
        }

        /**
         * @brief Dereferences the iterator to access the current node's value.
         *
         * @return A reference to the value of the current node.
         */
        T& operator*() const {
            return stack.top()->get_value();
        }

        /**
         * @brief Advances the iterator to the next node in pre-order.
         *
         * @return A reference to the updated iterator.
         */
        PreOrderIterator& operator++() {
            auto node = stack.top();
            stack.pop();
            for (int i = node->get_children().size() - 1; i >= 0; --i) {
                if (node->getChildAt(i)) stack.push(node->getChildAt(i));
            }
            return *this;
        }

        /**
         * @brief Checks if two iterators are not equal.
         *
         * @param other The other iterator to compare with.
         * @return True if the iterators are not equal, false otherwise.
         */
        bool operator!=(const PreOrderIterator& other) const {
            return !(*this == other);
        }

        /**
         * @brief Checks if two iterators are equal.
         *
         * @param other The other iterator to compare with.
         * @return True if the iterators are equal, false otherwise.
         */
        bool operator==(const PreOrderIterator& other) const {
            return stack.empty() == other.stack.empty();
        }
    };

/**
 * @brief Returns an iterator pointing to the beginning of the pre-order traversal.
 *
 * @return A PreOrderIterator pointing to the root of the tree.
 */
    PreOrderIterator begin_pre_order() const {
        return PreOrderIterator(root, k_ary);
    }

/**
 * @brief Returns an iterator representing the end of the pre-order traversal.
 *
 * @return A PreOrderIterator that represents the end of the traversal.
 */
    PreOrderIterator end_pre_order() const {
        return PreOrderIterator(nullptr, k_ary);
    }


/**-----------------------------------Post Order Iterator-------------------------------------------**/

/**
 * @brief An iterator for traversing the tree in post-order.
 *
 * In post-order traversal, the current node is visited after its children.
 * This iterator uses a stack to keep track of the nodes to be visited.
 */
    class PostOrderIterator {
    private:
        std::stack<std::shared_ptr<Node<T>>> node_stack;  ///< Stack to hold nodes for traversal.

        /**
         * @brief Pushes all leftmost nodes onto the stack.
         *
         * This function is used to ensure that the leftmost children are visited first.
         *
         * @param node The current node to start pushing from.
         */
        void push_leftmost_nodes(std::shared_ptr<Node<T>> node) {
            while (node) {
                node_stack.push(node);
                if (!node->get_children().empty()) {
                    node = node->getChildAt(0);  // Go left
                } else {
                    break;
                }
            }
        }

    public:
        /**
         * @brief Constructs a PostOrderIterator starting at the given root.
         *
         * @param root The root node to start the traversal from.
         */
        PostOrderIterator(std::shared_ptr<Node<T>> root, int k_ary) {
            if (k_ary != 2) {
                throw std::invalid_argument("PostOrderIterator can only be used with a binary tree (k_ary = 2).");
            }
            if (root) {
                push_leftmost_nodes(root);
            }
        }

        /**
         * @brief Checks if two iterators are not equal.
         *
         * @param other The other iterator to compare with.
         * @return True if the iterators are not equal, false otherwise.
         */
        bool operator!=(const PostOrderIterator& other) const {
            return !node_stack.empty();
        }

        /**
         * @brief Advances the iterator to the next node in post-order.
         *
         * @return A reference to the updated iterator.
         */
        PostOrderIterator& operator++() {
            if (node_stack.empty()) return *this;

            auto current = node_stack.top();
            node_stack.pop();

            // Check if the stack is not empty and the top of the stack is the parent of the current node
            if (!node_stack.empty()) {
                auto parent = node_stack.top();

                // If the current node is the left child, move to the right child
                if (parent->get_children().size() > 1 &&
                    parent->getChildAt(0).get() == current.get()) {
                    push_leftmost_nodes(parent->getChildAt(1));
                }
            }

            return *this;
        }

        /**
         * @brief Dereferences the iterator to access the current node's value.
         *
         * @return A reference to the value of the current node.
         */
        T& operator*() const {
            return node_stack.top()->get_value();
        }

        /**
         * @brief Provides a pointer-like interface to access the current node's value.
         *
         * @return A pointer to the value of the current node.
         */
        T* operator->() const {
            return &(node_stack.top()->get_value());
        }
    };

/**
 * @brief Returns an iterator pointing to the beginning of the post-order traversal.
 *
 * @return A PostOrderIterator pointing to the root of the tree.
 */
    PostOrderIterator begin_post_order() const {
        return PostOrderIterator(root, k_ary);
    }

/**
 * @brief Returns an iterator representing the end of the post-order traversal.
 *
 * @return A PostOrderIterator that represents the end of the traversal.
 */
    PostOrderIterator end_post_order() const {
        return PostOrderIterator(nullptr, k_ary);
    }


/**---------------------------------------In Order Iterator-------------------------------------------**/

/**
 * @brief An iterator for traversing the tree in in-order.
 *
 * In in-order traversal, the current node is visited after its left children and before its right children.
 * This iterator uses a stack to keep track of the nodes to be visited.
 */
    class InOrderIterator {
    private:
        std::stack<std::shared_ptr<Node<T>>> stack;  ///< Stack to hold nodes for traversal.
        std::shared_ptr<Node<T>> current;  ///< The current node being processed.

    public:
        /**
         * @brief Constructs an InOrderIterator starting at the given root.
         *
         * @param root The root node to start the traversal from.
         */
        InOrderIterator(std::shared_ptr<Node<T>> root, int k_ary) : current(root) {
            if (k_ary != 2) {
                throw std::invalid_argument("InOrderIterator can only be used with a binary tree (k_ary = 2).");
            }            while (current) {
                stack.push(current);
                current = current->get_children().size() > 0 ? current->getChildAt(0) : nullptr;
            }
        }

        /**
         * @brief Dereferences the iterator to access the current node's value.
         *
         * @return A reference to the value of the current node.
         */
        T& operator*() const {
            return stack.top()->get_value();
        }

        /**
         * @brief Advances the iterator to the next node in in-order.
         *
         * @return A reference to the updated iterator.
         */
        InOrderIterator& operator++() {
            auto node = stack.top();
            stack.pop();
            if (node->get_children().size() > 1) {
                node = node->getChildAt(1);
                while (node) {
                    stack.push(node);
                    node = node->get_children().size() > 0 ? node->getChildAt(0) : nullptr;
                }
            }
            return *this;
        }

        /**
         * @brief Checks if two iterators are not equal.
         *
         * @param other The other iterator to compare with.
         * @return True if the iterators are not equal, false otherwise.
         */
        bool operator!=(const InOrderIterator& other) const {
            return !(*this == other);
        }

        /**
         * @brief Checks if two iterators are equal.
         *
         * @param other The other iterator to compare with.
         * @return True if the iterators are equal, false otherwise.
         */
        bool operator==(const InOrderIterator& other) const {
            return stack.empty() == other.stack.empty();
        }
    };

/**
 * @brief Returns an iterator pointing to the beginning of the in-order traversal.
 *
 * @return An InOrderIterator pointing to the root of the tree.
 */
    InOrderIterator begin_in_order() const {
        return InOrderIterator(root, k_ary);
    }

/**
 * @brief Returns an iterator representing the end of the in-order traversal.
 *
 * @return An InOrderIterator that represents the end of the traversal.
 */
    InOrderIterator end_in_order() const {
        return InOrderIterator(nullptr, k_ary);
    }


/**---------------------------------------BFS Iterator-------------------------------------------**/

/**
 * @brief An iterator for traversing the tree in Breadth-First Search (BFS) order.
 *
 * BFS traversal visits nodes level by level, starting from the root. This iterator uses a queue to keep track of the nodes to be visited.
 */
    class BFSIterator {
    private:
        std::queue<std::shared_ptr<Node<T>>> queue;  ///< Queue to hold nodes for traversal.

    public:
        /**
         * @brief Constructs a BFSIterator starting at the given root.
         *
         * @param root The root node to start the traversal from.
         */
        explicit BFSIterator(std::shared_ptr<Node<T>> root) {
            if (root) queue.push(root);
        }

        /**
         * @brief Dereferences the iterator to access the current node's value.
         *
         * @return A reference to the value of the current node.
         */
        T& operator*() const {
            return queue.front()->get_value();
        }

        /**
         * @brief Advances the iterator to the next node in BFS order.
         *
         * @return A reference to the updated iterator.
         */
        BFSIterator& operator++() {
            auto node = queue.front();
            queue.pop();
            for (auto& child : node->get_children()) {
                if (child) queue.push(child);
            }
            return *this;
        }

        /**
         * @brief Checks if two iterators are not equal.
         *
         * @param other The other iterator to compare with.
         * @return True if the iterators are not equal, false otherwise.
         */
        bool operator!=(const BFSIterator& other) const {
            return !(*this == other);
        }

        /**
         * @brief Checks if two iterators are equal.
         *
         * @param other The other iterator to compare with.
         * @return True if the iterators are equal, false otherwise.
         */
        bool operator==(const BFSIterator& other) const {
            return queue.empty() == other.queue.empty();
        }
    };

/**
 * @brief Returns an iterator pointing to the beginning of the BFS traversal.
 *
 * @return A BFSIterator pointing to the root of the tree.
 */
    BFSIterator begin_bfs_scan() const {
        return BFSIterator(root);
    }

/**
 * @brief Returns an iterator representing the end of the BFS traversal.
 *
 * @return A BFSIterator that represents the end of the traversal.
 */
    BFSIterator end_bfs_scan() const {
        return BFSIterator(nullptr);
    }

/**---------------------------------------DFS Iterator-------------------------------------------**/

/**
 * @brief An iterator for traversing the tree in Depth-First Search (DFS) order.
 *
 * DFS traversal visits nodes as far as possible along each branch before backtracking. This iterator uses a stack to keep track of the nodes to be visited.
 */
    class DFSIterator {
    private:
        std::stack<std::shared_ptr<Node<T>>> stack;  ///< Stack to hold nodes for traversal.

    public:
        /**
         * @brief Constructs a DFSIterator starting at the given root.
         *
         * @param root The root node to start the traversal from.
         */
        explicit DFSIterator(std::shared_ptr<Node<T>> root) {
            if (root) stack.push(root);
        }

        /**
         * @brief Dereferences the iterator to access the current node's value.
         *
         * @return A reference to the value of the current node.
         */
        T& operator*() const {
            return stack.top()->get_value();
        }

        /**
         * @brief Advances the iterator to the next node in DFS order.
         *
         * @return A reference to the updated iterator.
         */
        DFSIterator& operator++() {
            auto node = stack.top();
            stack.pop();
            for (int i = node->get_children().size() - 1; i >= 0; --i) {
                if (node->getChildAt(i)) stack.push(node->getChildAt(i));
            }
            return *this;
        }

        /**
         * @brief Checks if two iterators are not equal.
         *
         * @param other The other iterator to compare with.
         * @return True if the iterators are not equal, false otherwise.
         */
        bool operator!=(const DFSIterator& other) const {
            return !(*this == other);
        }

        /**
         * @brief Checks if two iterators are equal.
         *
         * @param other The other iterator to compare with.
         * @return True if the iterators are equal, false otherwise.
         */
        bool operator==(const DFSIterator& other) const {
            return stack.empty() == other.stack.empty();
        }
    };

/**
 * @brief Returns an iterator pointing to the beginning of the DFS traversal.
 *
 * @return A DFSIterator pointing to the root of the tree.
 */
    DFSIterator begin_dfs_scan() const {
        return DFSIterator(root);
    }

/**
 * @brief Returns an iterator representing the end of the DFS traversal.
 *
 * @return A DFSIterator that represents the end of the traversal.
 */
    DFSIterator end_dfs_scan() const {
        return DFSIterator(nullptr);
    }


/**---------------------------------------Heap Iterator-------------------------------------------**/

    class HeapIterator {
    private:
        std::queue<std::shared_ptr<Node<T>>> queue;  ///< Queue to hold nodes for traversal.

    public:
        /**
         * @brief Constructs a HeapIterator starting at the given root.
         *
         * @param root The root node to start the traversal from.
         */
        explicit HeapIterator(std::shared_ptr<Node<T>> root) {
            if (root) queue.push(root);
        }

        /**
         * @brief Dereferences the iterator to access the current node's value.
         *
         * @return A reference to the value of the current node.
         */
        T& operator*() const {
            return queue.front()->get_value();
        }

        /**
         * @brief Advances the iterator to the next node in heap order.
         *
         * @return A reference to the updated iterator.
         */
        HeapIterator& operator++() {
            auto node = queue.front();
            queue.pop();
            for (auto& child : node->get_children()) {
                if (child) queue.push(child);
            }
            return *this;
        }

        /**
         * @brief Checks if two iterators are not equal.
         *
         * @param other The other iterator to compare with.
         * @return True if the iterators are not equal, false otherwise.
         */
        bool operator!=(const HeapIterator& other) const {
            return !(*this == other);
        }

        /**
         * @brief Checks if two iterators are equal.
         *
         * @param other The other iterator to compare with.
         * @return True if the iterators are equal, false otherwise.
         */
        bool operator==(const HeapIterator& other) const {
            return queue.empty() == other.queue.empty();
        }
    };


    /**
     * @brief Transforms the tree into a minimum heap and returns an iterator for the heap.
     *
     * @return A HeapIterator pointing to the root of the heap.
     */
    HeapIterator myHeap() {
        heapify(root);  // Convert the tree into a heap
        return HeapIterator(root);
    }

    /**
     * @brief Returns an iterator representing the end of the heap traversal.
     *
     * @return A HeapIterator that represents the end of the traversal.
     */
    HeapIterator end_heap() const {
        return HeapIterator(nullptr);
    }


/**---------------------------------------Helper Functions-------------------------------------------**/
    /**
     * @brief Finds a node with the specified value in the tree.
     *
     * @param node The current node to search.
     * @param key The value to search for.
     * @return A shared pointer to the found node, or nullptr if not found.
     */
    friend std::ostream& operator<<(std::ostream& os, const Tree<T, k>& tree) {
        if (!tree.root) return os << "Tree is empty.";

        std::queue<std::shared_ptr<Node<T>>> q;
        q.push(tree.root);

        while (!q.empty()) {
            auto node = q.front();
            q.pop();

            os << node->get_value() << ": ";
            for (const auto& child : node->get_children()) {
                if (child) {
                    os << child->get_value() << " ";
                    q.push(child);
                }
            }
            os << std::endl;
        }

        return os;
    }

    /**
     * @brief Internal heapify function to convert a subtree into a min-heap.
     *
     * @param root The root of the subtree to heapify.
     */
    void heapify(std::shared_ptr<Node<T>> root) {
        if (!root) return;

        // Use size_t, which is the type returned by std::vector<T>::size()
        for (size_t i = 0; i < root->get_children().size(); ++i) {
            heapify(root->getChildAt(i));
        }

        // Now, check for the smallest child and swap if necessary
        size_t smallest = 0;
        for (size_t i = 1; i < root->get_children().size(); ++i) {
            if (root->getChildAt(i) && root->getChildAt(i)->get_value() < root->getChildAt(smallest)->get_value()) {
                smallest = i;
            }
        }

        if (root->getChildAt(smallest) && root->getChildAt(smallest)->get_value() < root->get_value()) {
            std::swap(root->get_value(), root->getChildAt(smallest)->get_value());
            heapify(root->getChildAt(smallest));  // Heapify the affected subtree
        }
    }

private:
    std::shared_ptr<Node<T>> find(const std::shared_ptr<Node<T>>& node, const T& key) const {
        if (node == nullptr) return nullptr;
        if (node->get_value() == key) return node;
        for (const auto& child : node->get_children()) {
            auto result = find(child, key);
            if (result != nullptr) return result;
        }
        return nullptr;
    }
};

#endif // TREE_HPP
