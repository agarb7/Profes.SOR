#ifndef MAPITEMBLOCK_H
#define MAPITEMBLOCK_H

#include "../block.h"

#include <unordered_map>

namespace Core {

class MapItemBlock: public Block
{
public:
    enum {
        Name,
        Version,
        Size
    };

    virtual bool readChildren(AbstractInputBuffer &buffer);

    int reflectogramChildId() const;

private:
    using IdMap = std::unordered_map<String, int>;

    static const IdMap m_reflectogramChildIdMap;
};

} // namespace Core

#endif // MAPITEMBLOCK_H
