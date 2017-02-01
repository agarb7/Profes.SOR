#ifndef REFLECTOGRAM__H
#define REFLECTOGRAM__H

#include "columnmap.h"

#include "core/reflectogram.h"

#include <QAbstractTableModel>
#include <QString>

#include <vector>

namespace Model {

class Reflectogram : public QAbstractTableModel
{
    Q_OBJECT

public:
    Reflectogram(QObject *parent = 0);

    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;

    virtual Qt::ItemFlags flags(const QModelIndex &index) const;

    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);

    virtual bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex());
    virtual bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex());

    bool readFile(int row);
    bool saveFile(int row);

private:
    struct Row {
        QString filePath;
        Core::Reflectogram reflectogram;
    };

    bool rowInBound(int row) const;
    bool columnInBound(int col) const;
    bool inBound(const QModelIndex &index) const;

    std::vector<Row> m_data;    
};

} // namespace Model

#endif // REFLECTOGRAM__H
