#ifndef ABSTRACTCOLUMN_H
#define ABSTRACTCOLUMN_H

#include <QVariant>
#include <QString>
#include <QFlags>

namespace Core {
    class Reflectogram;
}

namespace Model {

class AbstractColumn
{
public:
    enum SetResult {
        NotAccepted = 0x0,
        Accepted = 0x1,
        Changed = 0x2
    };

    Q_DECLARE_FLAGS(SetResults, SetResult)

    AbstractColumn(const QString &header) :
        m_header(header)
    {}

    QVariant headerData() const
    {
        return m_header;
    }

    virtual QVariant data(const Core::Reflectogram &r) const = 0;
    virtual SetResults setData(Core::Reflectogram &r, const QVariant &value) const = 0;

private:
    QString m_header;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(AbstractColumn::SetResults)

} // namespace Model

#endif // ABSTRACTCOLUMN_H
