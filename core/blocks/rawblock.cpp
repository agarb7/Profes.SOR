#include "rawblock.h"

#include "../fields/rawfield.h"

#include "../abstractinputbuffer.h"

namespace Core {

bool RawBlock::readChildren(AbstractInputBuffer &buffer)
{
    auto field = createChild<RawField>();

    return field->read(buffer, m_readingSize);
}

SizeType RawBlock::readingSize() const
{
    return m_readingSize;
}

void RawBlock::setReadingSize(const SizeType &readingSize)
{
    m_readingSize = readingSize;
}

} // namespace Core
