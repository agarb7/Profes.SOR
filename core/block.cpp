#include "block.h"

#include "abstractinputbuffer.h"

namespace Core {

Block::~Block()
{
    for (auto child: m_children)
        delete child;
}

SizeType Block::size() const
{
    return m_size;
}

Block::ChildIterator Block::childrenBegin() const
{
    return m_children.begin();
}

Block::ChildIterator Block::childrenEnd() const
{
    return m_children.end();
}

//node must be a child
Block::ChildIterator Block::childIterator(const Node *node) const
{    
    return childrenBegin() + node->m_position;
}

void Block::addChild(Node *child)
{
    addChildImpl(child);
}

void Block::addChild(int id, Node *child)
{
    addChildImpl(child, id);
}

void Block::idIndex(int id, Node *child)
{
    if (id < 0)
        return;

    SizeType index = id;
    if (index >= m_idChildrenMap.size())
        m_idChildrenMap.resize(index+1);

    m_idChildrenMap[index] = child;
}

template <class ...Ids>
void Block::addChildImpl(Node *child, Ids ...ids)
{
    SizeType pos = m_children.size();
    m_children.push_back(child);

    child->m_parent = this;
    child->m_position = pos;

    SizeType oldSize = m_size;
    m_size += child->size();

    idIndex(ids..., child);

    child->sizeChanged.connect([this](SizeType oldChildSize, SizeType newChildSize) {
        SizeType oldSize = m_size;

        m_size -= oldChildSize;
        m_size += newChildSize;

        sizeChanged(oldSize, m_size);
    });

    child->dataChanged.connect([this](){
        dataChanged();
    });

    if (m_size != oldSize)
        sizeChanged(oldSize, m_size);
}

} // namespace Core
