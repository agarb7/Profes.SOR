#ifndef LITTLEUINT16VECTORFIELD_H
#define LITTLEUINT16VECTORFIELD_H

#include "../field.h"

#include "../types.h"

namespace Core {

class AbstractInputBuffer;

class LittleUInt16VectorField: public Field
{
public:
    using ValueType = LeUInt16Vector;

    virtual SizeType size() const;

    virtual const char *data() const;    

    bool read(AbstractInputBuffer &buffer, SizeType count);

    LeUInt16Vector value() const;
    void setValue(const LeUInt16Vector &value);

    Signal<void(SizeType)> countChanged;
    Signal<void(const LeUInt16Vector&)> valueChanged;

private:
    void swapData(LeUInt16Vector& value);

    LeUInt16Vector m_data;
};

} // namespace Core

#endif // LITTLEUINT16VECTORFIELD_H
