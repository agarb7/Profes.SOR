#include "fileinputbuffer.h"

namespace Model {

FileInputBuffer::FileInputBuffer(QFile &file) :
    m_file(file)
{
}

bool FileInputBuffer::getChar(char *c)
{
    return m_file.getChar(c);
}

bool FileInputBuffer::read(char *data, Core::SizeType size)
{
    return m_file.read(data, size) == size;
}

} // namespace Model
