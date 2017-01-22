#ifndef LITTLEUINT16VECTORFIELD_H
#define LITTLEUINT16VECTORFIELD_H

#include "../field.h"

#include "../definitions.h"

class AbstractInputBuffer;

class LittleUInt16VectorField: public Field
{
public:
    using ValueType = LittleUInt16Vector;

    virtual SizeType size() const;

    virtual const char *data() const;    

    bool read(AbstractInputBuffer &buffer, SizeType count);

    LittleUInt16Vector value() const;
    void setValue(const LittleUInt16Vector &value);

    Signal<void(SizeType)> countChanged;
    Signal<void(const LittleUInt16Vector&)> valueChanged;

private:
    void swapData(LittleUInt16Vector& value);

    LittleUInt16Vector m_data;
};

#endif // LITTLEUINT16VECTORFIELD_H
