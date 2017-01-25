#ifndef INTFIELD_H
#define INTFIELD_H

#include "../field.h"
#include "../abstractinputbuffer.h"

namespace Core {

template <class Int>
class IntField: public Field
{
public:
    using ValueType = Int;

    virtual SizeType size() const
    {
        return sizeof(Int);
    }

    virtual const char *data() const
    {
        return reinterpret_cast<const char*>(&m_data);
    }

    bool read(AbstractInputBuffer& buffer)
    {
        Int oldData = m_data;

        bool readed = buffer.read(reinterpret_cast<char*>(&m_data), sizeof(Int));
        if (!readed)
            return false;

        if (oldData != m_data) {
            dataChanged();
            valueChanged(m_data);
        }

        return true;
    }

    Int value() const
    {
        return m_data;
    }

    void setValue(Int value)
    {
        if (m_data != value) {
            m_data = value;

            dataChanged();
            valueChanged(m_data);
        }
    }

    Signal<void(Int)> valueChanged;

private:
    Int m_data;
};

using LittleInt16Field = IntField<LittleInt16>;
using LittleUInt16Field = IntField<LittleUInt16>;

using LittleInt32Field = IntField<LittleInt32>;
using LittleUInt32Field = IntField<LittleUInt32>;

} // namespace Core

#endif // INTFIELD_H
