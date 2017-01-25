#ifndef FIELD_H
#define FIELD_H

#include "node.h"

namespace Core {

class Field: public Node
{
public:
    virtual const char *data() const = 0;
};

} // namespace Core

#endif // FIELD_H
