#ifndef FILEINPUTBUFFER_H
#define FILEINPUTBUFFER_H

#include "reflectogram/abstractinputbuffer.h"

#include <QFile>

class FileInputBuffer: public AbstractInputBuffer
{
public:
    FileInputBuffer(QFile &file);

    virtual bool read(char *data, SizeType size);
    virtual bool getChar(char *c);

private:
    QFile &m_file;
};

#endif // FILEINPUTBUFFER_H
