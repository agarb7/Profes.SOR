#ifndef COLUMNMAP_H
#define COLUMNMAP_H

#include "abstractcolumn.h"
#include "reflectogrammodelcolumn.h"

#include <QCoreApplication>

#include <array>
#include <memory>

class ColumnMap
{    
    Q_DECLARE_TR_FUNCTIONS(ColumnMap)

public:
    static const ColumnMap& instance();

    AbstractColumn *column(ReflectogramModelColumn id) const;

private:
    ColumnMap();

    using ColumnPtr = std::unique_ptr<AbstractColumn>;

    void setup(ReflectogramModelColumn id, AbstractColumn *column);

    static constexpr std::size_t m_arraySize = ReflectogramModelColumnCount;

    std::array<ColumnPtr, m_arraySize> m_map{};
};

#endif // COLUMNMAP_H
