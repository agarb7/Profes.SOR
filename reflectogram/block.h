#ifndef BLOCK_H
#define BLOCK_H

#include "node.h"

#include <vector>

class AbstractInputBuffer;

class Block: public Node
{
    using ChildrenContainer = std::vector<Node*>;
    using IdChildrenMap = std::vector<Node*>;

public:
    using ChildIterator = ChildrenContainer::const_iterator;

    virtual ~Block();

    virtual SizeType size() const;

    virtual bool readChildren(AbstractInputBuffer &buffer) = 0;

    template <class Child = Node>
    Child *child(int id) const
    {
        SizeType index = id;
        if (index >= m_idChildrenMap.size())
            return 0;

        return static_cast<Child*>(m_idChildrenMap[index]);
    }

    template <class Child = Node>
    Child *descendant(int id) const
    {
        return child<Child>(id);
    }

    template <class Child = Node, class ...Ids>
    Child *descendant(int id, Ids ...ids) const
    {
        auto block = dynamic_cast<Block*>(child(id));
        if (!block)
            return 0;

        return block->descendant<Child>(ids...);
    }

    ChildIterator childrenBegin() const;
    ChildIterator childrenEnd() const;

    ChildIterator childIterator(const Node *node) const;

protected:
    template <class Child>
    class CastingChildIterator;

    void addChild(Node *child);
    void addChild(int id, Node *child);

    template <class Child, class ...Ids>
    Child *createChild(Ids ...ids)
    {
        auto child = new Child;
        addChild(ids..., child);

        return child;
    }

private:
    void idIndex(Node *) {}
    void idIndex(int id, Node *child);

    template <class ...Ids>
    void addChildImpl(Node *child, Ids ...ids);

    SizeType m_size = 0;

    IdChildrenMap m_idChildrenMap;
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

#endif // BLOCK_H
