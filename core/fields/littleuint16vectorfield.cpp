#include "littleuint16vectorfield.h"

#include "../abstractinputbuffer.h"

#include <algorithm>

namespace Core {

SizeType LittleUInt16VectorField::size() const
{
    return m_data.size()*2;
}

const char *LittleUInt16VectorField::data() const
{
    return reinterpret_cast<const char*>(m_data.data());
}

bool LittleUInt16VectorField::read(AbstractInputBuffer &buffer, SizeType count)
{
    SizeType newSize = count*2;

    LittleUInt16Vector newData(count);
    char* newCharData = reinterpret_cast<char*>(newData.data());
    if (!buffer.read(newCharData, newSize))
        return false;

    if (m_data != newData)
        swapData(newData);

    return true;
}

LittleUInt16Vector LittleUInt16VectorField::value() const
{
    return m_data;
}

void LittleUInt16VectorField::setValue(const LittleUInt16Vector &value)
{
    if (m_data == value)
        return;

    LittleUInt16Vector temp = value;
    swapData(temp);
}

void LittleUInt16VectorField::swapData(LittleUInt16Vector &value)
{
    SizeType oldCount = m_data.size();
    SizeType newCount = value.size();

    m_data.swap(value);

    if (oldCount != newCount) {
        sizeChanged(oldCount*2, newCount*2);

        countChanged(newCount);
    }

    dataChanged();
    valueChanged(m_data);
}

} // namespace Core
