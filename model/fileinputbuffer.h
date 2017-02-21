#ifndef FILEINPUTBUFFER_H
#define FILEINPUTBUFFER_H

#include "core/abstractinputbuffer.h"

#include <QFile>

namespace Model {

class FileInputBuffer: public Core::AbstractInputBuffer
{
public:
    FileInputBuffer(QFile &file);

    bool read(char *data, Core::SizeType size) override;
    bool getChar(char *c) override;

private:
    QFile &m_file;
};

} // namespace Model

#endif // FILEINPUTBUFFER_H
