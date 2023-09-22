#pragma once

namespace alba::algorithm {

template <typename BaseTree>
class BaseSetWithBaseTree : public BaseTree {
public:
    using Key = typename BaseTree::Key;
    using Node = typename BaseTree::Node;
    using NodeUniquePointer = typename BaseTree::NodeUniquePointer;
    using TraverseFunction = typename BaseTree::TraverseFunction;
    // virtual destructor because of virtual functions (vtable exists)
    ~BaseSetWithBaseTree() override = default;
    BaseSetWithBaseTree(BaseSetWithBaseTree const&) = default;
    BaseSetWithBaseTree(BaseSetWithBaseTree&&) = default;
    BaseSetWithBaseTree& operator=(BaseSetWithBaseTree const&) = default;
    BaseSetWithBaseTree& operator=(BaseSetWithBaseTree&&) = default;
    BaseSetWithBaseTree() : b_root(BaseTree::m_root) {}
    // overrides in BaseSet
    void put(Key const& key) override { putStartingOnThisNode(b_root, key); }

protected:
    virtual void putStartingOnThisNode(NodeUniquePointer& nodePointer, Key const& key) = 0;

    // overrides in BaseTree
    void copyNodeContents(Node& destinationNode, Node const& sourceNode) const override {
        destinationNode.key = sourceNode.key;
    }

private:
    NodeUniquePointer& b_root;
};

}  // namespace alba::algorithm
