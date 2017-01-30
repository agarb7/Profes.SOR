#include "reflectogrammodel.h"

#include "fileinputbuffer.h"

#include <QFile>
#include <QDateTime>
#include <QVector>

#include <algorithm>

ReflectogramModel::ReflectogramModel(QObject *parent) :
    QAbstractTableModel(parent)
{    
}

int ReflectogramModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return m_data.size();
}

int ReflectogramModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return ReflectogramModelColumnCount;
}

Qt::ItemFlags ReflectogramModel::flags(const QModelIndex &index) const
{
    if (!inBound(index))
        return 0;

    return Qt::ItemIsEnabled|Qt::ItemIsEditable|Qt::ItemIsSelectable;
}

QVariant ReflectogramModel::data(const QModelIndex &index, int role) const
{
    if (!inBound(index) || (role != Qt::DisplayRole && role != Qt::EditRole))
        return QVariant();

    auto columnId = static_cast<ReflectogramModelColumn>(index.column());

    const Row &row = m_data[index.row()];

    if (columnId == ReflectogramModelColumn::FilePath)
        return row.filePath;

    const Core::Reflectogram &r = row.reflectogram;

    return ColumnMap::instance().column(columnId)->data(r);
}

QVariant ReflectogramModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation != Qt::Horizontal || role != Qt::DisplayRole)
        return QAbstractTableModel::headerData(section, orientation, role);

    if (!columnInBound(section))
        return QVariant();

    auto columnId = static_cast<ReflectogramModelColumn>(section);
    if (columnId == ReflectogramModelColumn::FilePath)
        return tr("File path");

    return ColumnMap::instance().column(columnId)->headerData();
}

bool ReflectogramModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!inBound(index) || role != Qt::EditRole)
        return false;    

    auto columnId = static_cast<ReflectogramModelColumn>(index.column());

    Row &row = m_data[index.row()];

    if (columnId == ReflectogramModelColumn::FilePath) {
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
                columnId == ReflectogramModelColumn::SampleSpacing
                || columnId == ReflectogramModelColumn::IndexOfRefraction;

        if (sampleSpacingMeterChanged) {
            QModelIndex ssmIdx = this->index(
                index.row(),
                int (ReflectogramModelColumn::SampleSpacingMeter)
            );

            emit dataChanged(ssmIdx, ssmIdx);
        }
    }

    return true;
}

bool ReflectogramModel::insertRows(int row, int count, const QModelIndex &parent)
{
    if (parent.isValid())
        return false;

    if (row<0 || row > int(m_data.size()))
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

bool ReflectogramModel::removeRows(int row, int count, const QModelIndex &parent)
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

bool ReflectogramModel::readFile(int row)
{
    if (!rowInBound(row))
        return false;

    Row &r = m_data[row];

    QFile file(r.filePath);
    if (!file.open(QIODevice::ReadOnly))
        return false;

    FileInputBuffer buffer(file);
    return r.reflectogram.read(buffer);
}

bool ReflectogramModel::saveFile(int row)
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

bool ReflectogramModel::rowInBound(int row) const
{
    return row >= 0 && row < int(m_data.size());
}

bool ReflectogramModel::columnInBound(int col) const
{
    return col >= 0 && col < int(ReflectogramModelColumnCount);
}

bool ReflectogramModel::inBound(const QModelIndex &index) const
{
    return rowInBound(index.row()) && columnInBound(index.column());
}
