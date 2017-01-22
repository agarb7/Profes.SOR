#include "rawfield.h"

#include "../abstractinputbuffer.h"

SizeType RawField::size() const
{
    return m_data.size();
}

const char *RawField::data() const
{
    return m_data.data();
}

bool RawField::read(AbstractInputBuffer &buffer, SizeType size)
{
    Data newData(size);

    if (!buffer.read(newData.data(), size))
        return false;

    if (m_data != newData) {
        SizeType oldSize = m_data.size();
        m_data.swap(newData);

        if (oldSize != size)
            sizeChanged(oldSize, size);

        dataChanged();
    }

    return true;
}
