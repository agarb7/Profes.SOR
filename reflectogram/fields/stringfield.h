#ifndef STRINGFIELD_H
#define STRINGFIELD_H

#include "../field.h"

#include "../definitions.h"

class AbstractInputBuffer;

class StringField: public Field
{
public:
    using ValueType = String;

    virtual SizeType size() const;

    virtual const char *data() const;

    bool read(AbstractInputBuffer &buffer);

    String value() const;
    void setValue(const String &value);

    Signal<void(const String&)> valueChanged;

private:
    void swapData(String& value);

    static fieldSize(const String& data);

    String m_data;
};

#endif // STRINGFIELD_H
