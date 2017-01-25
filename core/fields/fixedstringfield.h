#ifndef FIXEDSTRINGFIELD_H
#define FIXEDSTRINGFIELD_H

#include "../field.h"

namespace Core {

class AbstractInputBuffer;

template <SizeType Size>
class FixedStringField: public Field
{
public:
    using FixedString = Core::FixedString<Size>;
    using ValueType = FixedString;

    virtual SizeType size() const
    {
        return m_data.size();
    }

    virtual const char *data() const
    {
        return m_data.data();
    }

    bool read(AbstractInputBuffer &buffer)
    {
        FixedString newData;
        if (!buffer.read(newData.data(), Size))
            return false;

        setValue(newData);

        return true;
    }

    FixedString value() const
    {
        return m_data;
    }

    void setValue(const FixedString &value)
    {
        if (m_data == value)
            return;

        m_data = value;

        dataChanged();
        valueChanged(m_data);
    }

    Signal<void(const FixedString&)> valueChanged;

private:
    FixedString m_data;
};

using String2Field = FixedStringField<2>;

} // namespace Core

#endif // FIXEDSTRINGFIELD_H
