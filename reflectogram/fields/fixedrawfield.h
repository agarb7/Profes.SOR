#ifndef FIXEDRAWFIELD_H
#define FIXEDRAWFIELD_H

#include "../field.h"

class AbstractInputBuffer;

template <SizeType Size>
class FixedRawField: public Field
{
public:
    FixedRawField(): m_data(Size) {}

    virtual SizeType size() const {return Size;}

    virtual const char *data() const
    {
        return m_data.data();
    }

    bool read(AbstractInputBuffer &buffer)
    {
        Data newData(Size);

        if (!buffer.read(newData.data(), Size))
            return false;

        if (m_data != newData) {
            m_data.swap(newData);

            dataChanged();
        }

        return true;
    }

private:
    using Data = std::vector<char>;

    Data m_data;
};

#endif // FIXEDRAWFIELD_H
