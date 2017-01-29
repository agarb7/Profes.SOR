#ifndef MAPPINGBLOCK_H
#define MAPPINGBLOCK_H

#include "block.h"

#include "mptypes.h"

#include <boost/mpl/map.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/back.hpp>
#include <boost/mpl/front.hpp>
#include <boost/mpl/pop_front.hpp>

#include <array>
#include <type_traits>

namespace Core {

template <class IdType, IdType Id, class NodeType>
using IdMapItem = MplPair<
    Ic<IdType, Id>,
    NodeType
>;

template<class IdType>
struct IdMap;

//todo add max int value
template<class ...IdMapItems>
struct IdMapBase
{
    using IdType = typename MplBack<
        MplVector<IdMapItems...>
    >::first::value_type;

    using Map = MplMap<IdMapItems...>;

    static constexpr SizeType size = MplSize<Map>::value;

    template<IdType Id>
    using NodeType = MplAt<
        Map,
        Ic<IdType, Id>
    >;
};

template <class Ics>
using DescendantNodeType = typename IdMap<
    typename MplBack<Ics>::value_type
>::template NodeType<
    MplBack<Ics>::value
>;

template <class IdType>
class MappingBlock: public Block
{
public:
    template <IdType Id>
    using NodeType = typename IdMap<IdType>::template NodeType<Id>;

    template <IdType Id>
    NodeType<Id> *child() const
    {
        return static_cast<NodeType<Id>*>(m_childrenMap[SizeType(Id)]);
    }

    template <class Ics, typename std::enable_if<(MplSize<Ics>::value > 1)>::type* = nullptr>
    DescendantNodeType<Ics> *descendant() const
    {
        auto block = child<MplFront<Ics>::value>();

        if (!block)
            return 0;

        return block->descendant<MplPopFront<Ics>>();
    }

    template <class Ics, typename std::enable_if<(MplSize<Ics>::value == 1)>::type* = nullptr>
    DescendantNodeType<Ics> *descendant() const
    {
        return child<MplFront<Ics>::value>();
    }

protected:            
    using Block::createChild;
    using Block::addChild;

    template <IdType Id>
    void addChild(NodeType<Id> *node)
    {
        m_childrenMap[SizeType(Id)] = node;
        addChild(node);
    }    

    template <IdType Id>
    NodeType<Id> *createChild()
    {
        auto node = new NodeType<Id>;
        addChild<Id>(node);
        return node;
    }

private:
    using ChildrenMap = std::array<Node*, IdMap<IdType>::size>;

    ChildrenMap m_childrenMap;
};

} // namespace Core

#endif // MAPPINGBLOCK_H
