#ifndef NODE_H
#define NODE_H

#include "definitions.h"

namespace Core {

class Block;
class Field;

class Node
{
public:
    class DataIterator;

    virtual ~Node() {}

    virtual SizeType size() const = 0;

    Block *parent() const;

    DataIterator dataBegin() const;
    DataIterator dataEnd() const;

    DataIterator dataIterator(const Node *child) const;

    //old size, new size
    Signal<void(SizeType, SizeType)> sizeChanged;
    Signal<void()> dataChanged;

private:
    Block *m_parent = 0;
    SizeType m_position = 0;

    friend class Block;
};

class Node::DataIterator
{
public:
    using iterator_category = std::input_iterator_tag;
    using value_type = const char;
    using difference_type = void;
    using pointer = const char*;
    using reference = const char&;

    DataIterator() {}

    DataIterator& operator++();

    DataIterator operator++(int)
    {
        DataIterator result = *this;
        ++(*this);
        return result;
    }

    bool operator==(DataIterator other) const;

    bool operator!=(DataIterator other) const
    {
        return !(*this == other);
    }

    reference operator*() const;

private:
    static DataIterator makeIter(const Node *node);
    static DataIterator makeIterAfter(const Node *node);

    static const Node *firstChild(const Node *node);
    static const Node *nextSibling(const Node *node);
    static const Node *lowestNextSibling(const Node *node);
    static const Node *nextNode(const Node *node);

    static const Field *firstFilledField(const Node *node);    
    static const Field *nextFilledField(const Node *node);

    const Field *m_field = 0;
    const char *m_charPtr = 0;

    friend class Node;
};

} // namespace Core

#endif // NODE_H
