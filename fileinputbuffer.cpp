#include "fileinputbuffer.h"

FileInputBuffer::FileInputBuffer(QFile &file) :
    m_file(file)
{
}

bool FileInputBuffer::getChar(char *c)
{
    return m_file.getChar(c);
}

bool FileInputBuffer::read(char *data, SizeType size)
{
    return m_file.read(data, size) == size;
}
