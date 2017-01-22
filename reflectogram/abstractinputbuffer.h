#ifndef ABSTRACTINPUTBUFFER_H
#define ABSTRACTINPUTBUFFER_H

#include "definitions.h"

class AbstractInputBuffer
{
public:
    virtual bool read(char *data, SizeType size) = 0;
    virtual bool getChar(char *c) = 0;    
};

#endif // ABSTRACTINPUTBUFFER_H
