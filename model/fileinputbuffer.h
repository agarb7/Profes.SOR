#ifndef FILEINPUTBUFFER_H
#define FILEINPUTBUFFER_H

#include "core/abstractinputbuffer.h"

#include <QFile>

class FileInputBuffer: public Core::AbstractInputBuffer
{
public:
    FileInputBuffer(QFile &file);

    virtual bool read(char *data, Core::SizeType size);
    virtual bool getChar(char *c);

private:
    QFile &m_file;
};

#endif // FILEINPUTBUFFER_H
