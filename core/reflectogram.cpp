#include "reflectogram.h"

#include "blocks/supplierparametersblock.h"
#include "blocks/fixedparametersblock.h"
#include "blocks/keyeventsblock.h"
#include "blocks/datapointsblock.h"
#include "blocks/checksumblock.h"

#include "fields/stringfield.h"
#include "fields/intfield.h"
#include "fields/littleuint16vectorfield.h"

#include <type_traits>

namespace Core {

bool Reflectogram::read(AbstractInputBuffer &buffer)
{
    m_mainBlock.reset(new MainBlock);

    if (!m_mainBlock->readChildren(buffer)) {
        m_mainBlock.reset();
        return false;
    }

    return true;
}

bool Reflectogram::empty() const
{
    return !m_mainBlock;
}

void Reflectogram::clear()
{
    m_mainBlock.reset();
}

Reflectogram::DataIterator Reflectogram::dataBegin() const
{
    return m_mainBlock
            ? m_mainBlock->dataBegin()
            : DataIterator();
}

Reflectogram::DataIterator Reflectogram::dataEnd() const
{
    return m_mainBlock
            ? m_mainBlock->dataEnd()
            : DataIterator();
}

void Reflectogram::calculateChecksum()
{
    if (!m_mainBlock)
        return;

    ChecksumBlock *chksum
            = m_mainBlock->child<Main::Checksum>();

    chksum->calculate(m_mainBlock->dataBegin(), m_mainBlock->dataIterator(chksum));
}

} // namespace Core
