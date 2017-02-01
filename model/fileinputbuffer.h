#ifndef FILEINPUTBUFFER_H
#define FILEINPUTBUFFER_H

#include "core/abstractinputbuffer.h"

#include <QFile>

namespace Model {

class FileInputBuffer: public Core::AbstractInputBuffer
{
public:
    FileInputBuffer(QFile &file);

    virtual bool read(char *data, Core::SizeType size);
    virtual bool getChar(char *c);

private:
    QFile &m_file;
};

} // namespace Model

#endif // FILEINPUTBUFFER_H
