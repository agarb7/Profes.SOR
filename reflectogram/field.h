#ifndef FIELD_H
#define FIELD_H

#include "node.h"

class Field: public Node
{
public:
    virtual const char *data() const = 0;
};

#endif // FIELD_H
