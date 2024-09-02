//guyes134@gmail.com

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Node.hpp"
#include "Tree.hpp"
#include "Complex.hpp"

// Node Class Tests
TEST_CASE("Node Class - Basic Functionality") {
    Node<int> node(5, 3);  // A node with value 5 and 3 possible children

    SUBCASE("Testing value retrieval") {
        CHECK(node.get_value() == 5);
    }

    SUBCASE("Testing number of children when empty") {
        CHECK(node.getNumOfChildren() == 0);
    }

    SUBCASE("Testing number of children after adding children") {
        auto child1 = std::make_shared<Node<int>>(10, 3);
        auto child2 = std::make_shared<Node<int>>(15, 3);
        node.addChildAt(child1, 0);
        node.addChildAt(child2, 1);

        CHECK(node.getNumOfChildren() == 2);
    }

    SUBCASE("Testing child retrieval at specific index") {
        auto child = std::make_shared<Node<int>>(10, 3);
        node.addChildAt(child, 1);
        CHECK(node.getChildAt(1)->get_value() == 10);
    }

    SUBCASE("Testing out-of-bounds access throws exception") {
        CHECK_THROWS_AS(node.getChildAt(3), std::out_of_range);
        CHECK_THROWS_AS(node.addChildAt(std::make_shared<Node<int>>(20, 3), 5), std::out_of_range);
    }

    SUBCASE("Testing addChildAt overwrites existing child") {
        auto child1 = std::make_shared<Node<int>>(10, 3);
        auto child2 = std::make_shared<Node<int>>(20, 3);
        node.addChildAt(child1, 0);
        node.addChildAt(child2, 0);

        CHECK(node.getChildAt(0)->get_value() == 20);  // The second child should overwrite the first
    }

    SUBCASE("Testing edge case: Adding nullptr as a child") {
        CHECK_THROWS_AS(node.addChildAt(nullptr, 0), std::invalid_argument);
        CHECK(node.getNumOfChildren() == 0);
    }

    SUBCASE("Testing multiple children addition beyond capacity") {
        auto child1 = std::make_shared<Node<int>>(10, 3);
        auto child2 = std::make_shared<Node<int>>(15, 3);
        auto child3 = std::make_shared<Node<int>>(20, 3);
        auto child4 = std::make_shared<Node<int>>(25, 3);

        node.addChildAt(child1, 0);
        node.addChildAt(child2, 1);
        node.addChildAt(child3, 2);
        CHECK_THROWS_AS(node.addChildAt(child4, 3), std::out_of_range);
        CHECK(node.getNumOfChildren() == 3);
    }
}

// Test cases for iterators with k_ary != 2
TEST_CASE("Non-Binary Tree (k_ary != 2) Iterator Restrictions") {
    Tree<int, 3> tree;  // Create a 3-ary tree
    tree.add_root(1);
    tree.add_sub_node(1, 2);
    tree.add_sub_node(1, 3);
    tree.add_sub_node(1, 4);

    SUBCASE("Pre-order iterator with k_ary != 2 throws exception") {
        CHECK_THROWS_AS(tree.begin_pre_order(), std::invalid_argument);
    }

    SUBCASE("Post-order iterator with k_ary != 2 throws exception") {
        CHECK_THROWS_AS(tree.begin_post_order(), std::invalid_argument);
    }

    SUBCASE("In-order iterator with k_ary != 2 throws exception") {
        CHECK_THROWS_AS(tree.begin_in_order(), std::invalid_argument);
    }

    SUBCASE("BFS iterator with k_ary != 2 works correctly") {
        std::vector<int> expected = {1, 2, 3, 4};
        std::vector<int> result;
        for (auto it = tree.begin_bfs_scan(); it != tree.end_bfs_scan(); ++it) {
            result.push_back(*it);
        }
        CHECK(result == expected);
    }

    SUBCASE("DFS iterator with k_ary != 2 works correctly") {
        std::vector<int> expected = {1, 2, 3, 4};
        std::vector<int> result;
        for (auto it = tree.begin_dfs_scan(); it != tree.end_dfs_scan(); ++it) {
            result.push_back(*it);
        }
        CHECK(result == expected);
    }
}


// Tree Class Tests
TEST_CASE("Tree Class - Basic Functionality") {
    Tree<int> tree;

    SUBCASE("Testing adding a root") {
        tree.add_root(10);
        CHECK(tree.getRoot()->get_value() == 10);
    }

    SUBCASE("Testing k-ary property") {
        CHECK(tree.getK_Ary() == 2);  // Default k value
    }

    SUBCASE("Testing adding a subtree node") {
        tree.add_root(10);
        tree.add_sub_node(10, 20);
        CHECK(tree.getRoot()->getChildAt(0)->get_value() == 20);
    }

    SUBCASE("Testing adding multiple children") {
        tree.add_root(10);
        tree.add_sub_node(10, 20);
        tree.add_sub_node(10, 30);

        CHECK(tree.getRoot()->getChildAt(0)->get_value() == 20);
        CHECK(tree.getRoot()->getChildAt(1)->get_value() == 30);
    }

    SUBCASE("Testing adding a child when no slots are available") {
        tree.add_root(10);
        tree.add_sub_node(10, 20);
        tree.add_sub_node(10, 30);

        CHECK_THROWS_AS(tree.add_sub_node(10, 40), std::out_of_range);
    }

    SUBCASE("Testing adding a child to a non-existent parent throws exception") {
        tree.add_root(10);
        CHECK_THROWS_AS(tree.add_sub_node(50, 20), std::invalid_argument);
    }

    SUBCASE("Testing tree traversal with PreOrderIterator") {
        tree.add_root(10);
        tree.add_sub_node(10, 20);
        tree.add_sub_node(10, 30);
        tree.add_sub_node(20, 40);
        tree.add_sub_node(20, 50);

        auto it = tree.begin_pre_order();
        CHECK(*it == 10); ++it;
        CHECK(*it == 20); ++it;
        CHECK(*it == 40); ++it;
        CHECK(*it == 50); ++it;
        CHECK(*it == 30); ++it;
    }

    SUBCASE("Testing tree traversal with PostOrderIterator") {
        tree.add_root(10);
        tree.add_sub_node(10, 20);
        tree.add_sub_node(10, 30);
        tree.add_sub_node(20, 40);
        tree.add_sub_node(20, 50);

        auto it = tree.begin_post_order();
        CHECK(*it == 40); ++it;
        CHECK(*it == 50); ++it;
        CHECK(*it == 20); ++it;
        CHECK(*it == 30); ++it;
        CHECK(*it == 10); ++it;
    }

    SUBCASE("Testing tree traversal with InOrderIterator") {
        tree.add_root(10);
        tree.add_sub_node(10, 20);
        tree.add_sub_node(10, 30);
        tree.add_sub_node(20, 40);
        tree.add_sub_node(20, 50);

        auto it = tree.begin_in_order();
        CHECK(*it == 40); ++it;
        CHECK(*it == 20); ++it;
        CHECK(*it == 50); ++it;
        CHECK(*it == 10); ++it;
        CHECK(*it == 30); ++it;
    }

    SUBCASE("Testing tree traversal with BFSIterator") {
        tree.add_root(10);
        tree.add_sub_node(10, 20);
        tree.add_sub_node(10, 30);
        tree.add_sub_node(20, 40);
        tree.add_sub_node(20, 50);

        auto it = tree.begin_bfs_scan();
        CHECK(*it == 10); ++it;
        CHECK(*it == 20); ++it;
        CHECK(*it == 30); ++it;
        CHECK(*it == 40); ++it;
        CHECK(*it == 50); ++it;
    }

    SUBCASE("Testing tree traversal with DFSIterator") {
        tree.add_root(10);
        tree.add_sub_node(10, 20);
        tree.add_sub_node(10, 30);
        tree.add_sub_node(20, 40);
        tree.add_sub_node(20, 50);

        auto it = tree.begin_dfs_scan();
        CHECK(*it == 10); ++it;
        CHECK(*it == 20); ++it;
        CHECK(*it == 40); ++it;
        CHECK(*it == 50); ++it;
        CHECK(*it == 30); ++it;
    }


    SUBCASE("Testing edge case: Empty tree traversal") {
        Tree<int, 2> emptyTree;
        CHECK(emptyTree.begin_bfs_scan() == emptyTree.end_bfs_scan());
        CHECK(emptyTree.begin_dfs_scan() == emptyTree.end_dfs_scan());
        CHECK(emptyTree.begin_in_order() == emptyTree.end_in_order());
    }

    SUBCASE("Testing edge case: Single node tree traversal") {
        tree.add_root(10);

        CHECK(*tree.begin_bfs_scan() == 10);
        CHECK(*tree.begin_dfs_scan() == 10);
        CHECK(*tree.begin_in_order() == 10);
        CHECK(*tree.begin_post_order() == 10);
    }
}

TEST_CASE("Tree Iterators - PreOrderIterator") {
    Tree<int, 2> tree;
    tree.add_root(1);
    tree.add_sub_node(1, 2);
    tree.add_sub_node(1, 3);
    tree.add_sub_node(2, 4);
    tree.add_sub_node(2, 5);

    SUBCASE("Pre-order traversal") {
        std::vector<int> expected = {1, 2, 4, 5, 3};
        std::vector<int> result;
        for (auto it = tree.begin_pre_order(); it != tree.end_pre_order(); ++it) {
            result.push_back(*it);
        }
        CHECK(result == expected);
    }
}

TEST_CASE("Tree Iterators - PostOrderIterator") {
    Tree<int, 2> tree;
    tree.add_root(1);
    tree.add_sub_node(1, 2);
    tree.add_sub_node(1, 3);
    tree.add_sub_node(2, 4);
    tree.add_sub_node(2, 5);

    SUBCASE("Post-order traversal") {
        std::vector<int> expected = {4, 5, 2, 3, 1};
        std::vector<int> result;
        for (auto it = tree.begin_post_order(); it != tree.end_post_order(); ++it) {
            result.push_back(*it);
        }
        CHECK(result == expected);
    }
}

TEST_CASE("Tree Iterators - InOrderIterator") {
    Tree<int, 2> tree;
    tree.add_root(1);
    tree.add_sub_node(1, 2);
    tree.add_sub_node(1, 3);
    tree.add_sub_node(2, 4);
    tree.add_sub_node(2, 5);

    SUBCASE("In-order traversal") {
        std::vector<int> expected = {4, 2, 5, 1, 3};
        std::vector<int> result;
        for (auto it = tree.begin_in_order(); it != tree.end_in_order(); ++it) {
            result.push_back(*it);
        }
        CHECK(result == expected);
    }
}

TEST_CASE("Tree Iterators - BFSIterator") {
    Tree<int, 2> tree;
    tree.add_root(1);
    tree.add_sub_node(1, 2);
    tree.add_sub_node(1, 3);
    tree.add_sub_node(2, 4);
    tree.add_sub_node(2, 5);

    SUBCASE("BFS traversal") {
        std::vector<int> expected = {1, 2, 3, 4, 5};
        std::vector<int> result;
        for (auto it = tree.begin_bfs_scan(); it != tree.end_bfs_scan(); ++it) {
            result.push_back(*it);
        }
        CHECK(result == expected);
    }
}

TEST_CASE("Tree Iterators - DFSIterator") {
    Tree<int, 2> tree;
    tree.add_root(1);
    tree.add_sub_node(1, 2);
    tree.add_sub_node(1, 3);
    tree.add_sub_node(2, 4);
    tree.add_sub_node(2, 5);

    SUBCASE("DFS traversal") {
        std::vector<int> expected = {1, 2, 4, 5, 3};
        std::vector<int> result;
        for (auto it = tree.begin_dfs_scan(); it != tree.end_dfs_scan(); ++it) {
            result.push_back(*it);
        }
        CHECK(result == expected);
    }
}

TEST_CASE("Tree Iterators - HeapIterator") {
    Tree<int, 2> tree;
    tree.add_root(10);
    tree.add_sub_node(10, 15);
    tree.add_sub_node(10, 20);
    tree.add_sub_node(15, 30);
    tree.add_sub_node(15, 40);
    tree.add_sub_node(20, 50);
    tree.add_sub_node(20, 60);

    SUBCASE("Heap traversal") {
        tree.myHeap(); // Transform the tree into a heap

        std::vector<int> result;
        for (auto it = tree.myHeap(); it != tree.end_heap(); ++it) {
            result.push_back(*it);
        }

        // Since it's a heap, the exact order may depend on the heap implementation,
        // but the root should be the smallest element.
        CHECK(result.front() <= result.back()); // The first element should be the smallest
    }
}


