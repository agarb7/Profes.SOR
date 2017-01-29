#ifndef ABSTRACTINPUTBUFFER_H
#define ABSTRACTINPUTBUFFER_H

#include "types.h"

namespace Core {

class AbstractInputBuffer
{
public:
    virtual bool read(char *data, SizeType size) = 0;
    virtual bool getChar(char *c) = 0;    
};

} // namespace Core

#endif // ABSTRACTINPUTBUFFER_H
