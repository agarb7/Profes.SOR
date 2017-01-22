#include "stringfield.h"

#include "../abstractinputbuffer.h"

#include <algorithm>

SizeType StringField::size() const
{
    return fieldSize(m_data);
}

const char *StringField::data() const
{
    return m_data.data();
}

bool StringField::read(AbstractInputBuffer &buffer)
{
    String newData;

    char ch;
    while(buffer.getChar(&ch)) {
        if (ch == 0)
            break;

        newData.push_back(ch);
    }

    if (m_data != newData)
        swapData(newData);

    return true;
}

String StringField::value() const
{
    return m_data;
}

void StringField::setValue(const String &value)
{
    if (m_data == value)
        return;

    String temp = value;
    swapData(temp);
}

void StringField::swapData(String &value)
{
    SizeType oldSize = fieldSize(m_data);
    SizeType newSize = fieldSize(value);

    m_data.swap(value);

    if (oldSize != newSize)
        sizeChanged(oldSize, newSize);

    dataChanged();
    valueChanged(m_data);
}

StringField::fieldSize(const String &data)
{
    return data.size()+1;
}
