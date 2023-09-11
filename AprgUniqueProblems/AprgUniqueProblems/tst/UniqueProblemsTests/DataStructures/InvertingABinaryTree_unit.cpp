#include <UniqueProblems/DataStructures/InvertingABinaryTree.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba::InvertingABinaryTree {

TEST(InvertingABinaryTreeTest, ThreeNodes) {
    std::unique_ptr<Node> node1(new Node{1, nullptr, nullptr});
    std::unique_ptr<Node> node2(new Node{2, nullptr, nullptr});
    std::unique_ptr<Node> node3(new Node{3, nullptr, nullptr});
    node2->leftPointer = std::move(node1);
    node2->rightPointer = std::move(node3);

    std::unique_ptr<Node> const result = invertABinaryTree(std::move(node2));

    EXPECT_EQ(2, result->value);
    EXPECT_EQ(3, result->leftPointer->value);
    EXPECT_EQ(1, result->rightPointer->value);
    EXPECT_FALSE(result->leftPointer->leftPointer);
    EXPECT_FALSE(result->leftPointer->rightPointer);
    EXPECT_FALSE(result->rightPointer->leftPointer);
    EXPECT_FALSE(result->rightPointer->rightPointer);
}

TEST(InvertingABinaryTreeTest, SevenNodes) {
    std::unique_ptr<Node> node1(new Node{1, nullptr, nullptr});
    std::unique_ptr<Node> node2(new Node{2, nullptr, nullptr});
    std::unique_ptr<Node> node3(new Node{3, nullptr, nullptr});
    std::unique_ptr<Node> node4(new Node{4, nullptr, nullptr});
    std::unique_ptr<Node> node5(new Node{5, nullptr, nullptr});
    std::unique_ptr<Node> node6(new Node{6, nullptr, nullptr});
    std::unique_ptr<Node> node7(new Node{7, nullptr, nullptr});
    node2->leftPointer = std::move(node1);
    node2->rightPointer = std::move(node3);
    node6->leftPointer = std::move(node5);
    node6->rightPointer = std::move(node7);
    node4->leftPointer = std::move(node2);
    node4->rightPointer = std::move(node6);

    std::unique_ptr<Node> const result = invertABinaryTree(std::move(node4));

    EXPECT_EQ(4, result->value);
    EXPECT_EQ(6, result->leftPointer->value);
    EXPECT_EQ(2, result->rightPointer->value);
    EXPECT_EQ(7, result->leftPointer->leftPointer->value);
    EXPECT_EQ(5, result->leftPointer->rightPointer->value);
    EXPECT_EQ(3, result->rightPointer->leftPointer->value);
    EXPECT_EQ(1, result->rightPointer->rightPointer->value);
}

}  // namespace alba::InvertingABinaryTree
