#include "node.h"

#include "block.h"
#include "field.h"

namespace Core {

Block *Node::parent() const
{
    return m_parent;
}

Node::DataIterator Node::dataBegin() const
{
    return DataIterator::makeIter(this);
}

Node::DataIterator Node::dataEnd() const
{
    return DataIterator::makeIterAfter(this);
}

//child must be not null. and child (but not nessasary)
Node::DataIterator Node::dataIterator(const Node *child) const
{
    return DataIterator::makeIter(child);
}

// DataIterator

Node::DataIterator &Node::DataIterator::operator++()
{
    ++m_charPtr;    

    const char *fieldEnd = m_field->data() + m_field->size();
    if (m_charPtr == fieldEnd) {
        m_field = nextFilledField(m_field); 
        m_charPtr = m_field ? m_field->data() : 0;        
    }

    return *this;
}

bool Node::DataIterator::operator==(DataIterator other) const
{
    return m_charPtr == other.m_charPtr
            && m_field == other.m_field;
}

Node::DataIterator::reference Node::DataIterator::operator*() const
{
    return *m_charPtr;
}

//node must be not null
Node::DataIterator Node::DataIterator::makeIter(const Node *node)
{
    DataIterator it;

    it.m_field = firstFilledField(node);
    it.m_charPtr = it.m_field ? it.m_field->data() : 0;

    return it;
}

//node must be not null
Node::DataIterator Node::DataIterator::makeIterAfter(const Node *node)
{
    const Node *sibling = lowestNextSibling(node);

    return sibling
            ? makeIter(sibling)
            : DataIterator();
}

//node can be null
const Node *Node::DataIterator::firstChild(const Node *node)
{
    if (auto block = dynamic_cast<const Block*>(node)) {
        auto childrenBegin = block->childrenBegin();
        if (childrenBegin != block->childrenEnd())
            return *childrenBegin;
    }

    return 0;
}

//node must be not null
const Node *Node::DataIterator::nextSibling(const Node *node)
{
    const Block *par = node->parent();
    if (!par)
        return 0;    

    auto nodeIt = par->childIterator(node);
    ++nodeIt;
    if (nodeIt == par->childrenEnd())
        return 0;    

    return *nodeIt;
}

//node must be not null
const Node *Node::DataIterator::lowestNextSibling(const Node *node)
{    
    do {
        if (const Node *sibling = nextSibling(node))
            return sibling;        
    } while ((node = node->parent()));

    return 0;
}

//node must be not null
const Node *Node::DataIterator::nextNode(const Node *node)
{
    if (const Node *child = firstChild(node))
        return child;    

    return lowestNextSibling(node);
}

//node must be not null
const Field *Node::DataIterator::firstFilledField(const Node *node)
{
    do {
        auto field = dynamic_cast<const Field*>(node);
        if (field && field->size())
            return field;
    } while ((node = nextNode(node)));

    return 0;
}

//node must be not null
const Field *Node::DataIterator::nextFilledField(const Node *node)
{    
    if ((node = nextNode(node)))
        return firstFilledField(node);

    return 0;
}

} // namespace Core
