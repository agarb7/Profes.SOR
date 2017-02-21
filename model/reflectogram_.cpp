#include "reflectogram_.h"

#include "fileinputbuffer.h"

#include <QFile>
#include <QFileInfo>
#include <QDateTime>
#include <QVector>

#include <algorithm>

namespace Model {

Reflectogram::Reflectogram(QObject *parent) :
    QAbstractTableModel(parent)
{    
}

int Reflectogram::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return m_data.size();
}

int Reflectogram::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return ReflectogramColumnCount;
}

Qt::ItemFlags Reflectogram::flags(const QModelIndex &index) const
{
    if (!inBound(index))
        return 0;

    using ::operator|;
    return Qt::ItemIsEnabled|Qt::ItemIsEditable|Qt::ItemIsSelectable;
}

QVariant Reflectogram::data(const QModelIndex &index, int role) const
{
    if (!inBound(index) || (role != Qt::DisplayRole && role != Qt::EditRole))
        return QVariant();

    auto columnId = static_cast<ReflectogramColumn>(index.column());

    const Row &row = m_data[index.row()];

    if (columnId == ReflectogramColumn::FilePath) {
        return role == Qt::EditRole
                ? row.filePath
                : QFileInfo(row.filePath).fileName();
    }

    const Core::Reflectogram &r = row.reflectogram;

    return ColumnMap::instance().column(columnId)->data(r);
}

QVariant Reflectogram::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation != Qt::Horizontal || role != Qt::DisplayRole)
        return QAbstractTableModel::headerData(section, orientation, role);

    if (!columnInBound(section))
        return QVariant();

    auto columnId = static_cast<ReflectogramColumn>(section);
    if (columnId == ReflectogramColumn::FilePath)
        return tr("File path");

    return ColumnMap::instance().column(columnId)->headerData();
}

bool Reflectogram::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!inBound(index) || role != Qt::EditRole)
        return false;    

    auto columnId = static_cast<ReflectogramColumn>(index.column());

    Row &row = m_data[index.row()];

    if (columnId == ReflectogramColumn::FilePath) {
        if (!value.canConvert<QString>())
            return false;

        QString newFilePath = value.toString();
        if (row.filePath != newFilePath) {
            row.filePath = newFilePath;
            emit dataChanged(index, index);
        }

        return true;
    }

    Core::Reflectogram &r = row.reflectogram;

    AbstractColumn::SetResults result = ColumnMap::instance()
            .column(columnId)
            ->setData(r, value);

    if (!result.testFlag(AbstractColumn::Accepted))
        return false;

    if (result.testFlag(AbstractColumn::Changed)) {
        emit dataChanged(index, index);

        bool sampleSpacingMeterChanged =
                columnId == ReflectogramColumn::SampleSpacing
                || columnId == ReflectogramColumn::IndexOfRefraction;

        if (sampleSpacingMeterChanged) {
            QModelIndex ssmIdx = this->index(
                index.row(),
                int (ReflectogramColumn::SampleSpacingMeter)
            );

            emit dataChanged(ssmIdx, ssmIdx);
        }
    }

    return true;
}

bool Reflectogram::insertRows(int row, int count, const QModelIndex &parent)
{
    if (parent.isValid())
        return false;

    if (row > int(m_data.size()) || row<0)
        return false;

    beginInsertRows(parent, row, row+count-1);

    int oldSize = m_data.size();
    m_data.resize(m_data.size()+count);
    auto beg = m_data.begin();
    auto it = beg+row;
    std::move_backward(it, beg+oldSize, it+count);

    endInsertRows();

    return true;
}

bool Reflectogram::removeRows(int row, int count, const QModelIndex &parent)
{
    if (parent.isValid())
        return false;

    int lastRow = row+count-1;

    if (row<0 || lastRow>=int(m_data.size()))
        return false;

    beginRemoveRows(parent, row, lastRow);

    auto it = m_data.begin()+row;
    m_data.erase(it, it+count);

    endRemoveRows();

    return true;
}

bool Reflectogram::readFile(int row)
{
    if (!rowInBound(row))
        return false;

    Row &r = m_data[row];

    QFile file(r.filePath);
    if (!file.open(QIODevice::ReadOnly))
        return false;

    FileInputBuffer buffer(file);
    bool result = r.reflectogram.read(buffer);

    //todo: implement signals from core, and reemit them
    //      remove explicit emiting after implement
    emit dataChanged(index(row, 0), index(row, ReflectogramColumnCount-1));

    return result;
}

bool Reflectogram::saveFile(int row)
{
    if (!rowInBound(row))
        return false;

    Row &r = m_data[row];
    QFile file(r.filePath);
    if (!file.open(QIODevice::WriteOnly))
        return false;

    Core::Reflectogram &rg = r.reflectogram;
    rg.calculateChecksum();

    for (auto it = rg.dataBegin(), end = rg.dataEnd(); it != end; ++it) {
        if (!file.putChar(*it))
            return false;
    }

    return true;
}

bool Reflectogram::rowInBound(int row) const
{
    return row >= 0 && row < int(m_data.size());
}

bool Reflectogram::columnInBound(int col) const
{
    return col >= 0 && col < int(ReflectogramColumnCount);
}

bool Reflectogram::inBound(const QModelIndex &index) const
{
    return rowInBound(index.row()) && columnInBound(index.column());
}

} // namespace Model
