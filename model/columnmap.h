#ifndef COLUMNMAP_H
#define COLUMNMAP_H

#include "abstractcolumn.h"
#include "reflectogramcolumn.h"

#include <QCoreApplication>

#include <array>
#include <memory>

namespace Model {

class ColumnMap
{    
    Q_DECLARE_TR_FUNCTIONS(ColumnMap)

public:
    static const ColumnMap& instance();

    AbstractColumn *column(ReflectogramColumn id) const;

private:
    ColumnMap();

    using ColumnPtr = std::unique_ptr<AbstractColumn>;

    void setup(ReflectogramColumn id, AbstractColumn *column);

    static constexpr std::size_t m_arraySize = ReflectogramColumnCount;

    std::array<ColumnPtr, m_arraySize> m_map{};
};

} // namespace Model

#endif // COLUMNMAP_H
