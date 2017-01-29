#ifndef BLOCK_H
#define BLOCK_H

#include "node.h"

namespace Core {

class AbstractInputBuffer;

class Block: public Node
{
    using ChildrenContainer = std::vector<Node*>;    

public:
    using ChildIterator = ChildrenContainer::const_iterator;

    virtual ~Block();

    virtual SizeType size() const;

    virtual bool readChildren(AbstractInputBuffer &buffer) = 0;

    ChildIterator childrenBegin() const;
    ChildIterator childrenEnd() const;

    ChildIterator childIterator(const Node *node) const;

protected:
    template <class Child>
    class CastingChildIterator;

    void addChild(Node *child);

    template <class NodeType>
    NodeType *createChild()
    {
        auto node = new NodeType;
        addChild(node);
        return node;
    }

private:
    SizeType m_size = 0;    
    ChildrenContainer m_children;    
};

template<class Child>
class Block::CastingChildIterator: public ChildIterator
{
public:
    using value_type = const Child*;
    using pointer = const Child**;
    using reference = const Child*;

    explicit CastingChildIterator(const ChildIterator childIt = ChildIterator()) :
        ChildIterator(childIt)
    {}

    reference operator*() const
    {
        return static_cast<reference>(ChildIterator::operator*());
    }
};

} // namespace Core

#endif // BLOCK_H
