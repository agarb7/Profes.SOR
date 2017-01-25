#ifndef RAWFIELD_H
#define RAWFIELD_H

#include "../field.h"

#include <vector>

namespace Core {

class AbstractInputBuffer;

class RawField: public Field
{
public:
    virtual SizeType size() const;

    virtual const char *data() const;

    bool read(AbstractInputBuffer &buffer, SizeType size);

private:
    using Data = std::vector<char>;

    Data m_data;
};

} // namespace Core

#endif // RAWFIELD_H
