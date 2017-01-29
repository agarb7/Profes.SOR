#ifndef REFLECTOGRAMMODEL_H
#define REFLECTOGRAMMODEL_H

#include "core/reflectogram.h"

#include <QAbstractTableModel>
#include <QString>

#include <vector>

class ReflectogramModel : public QAbstractTableModel
{
public:
    enum Column {
        FilePathColumn,
        SupplierNameColumn,
        OtdrNameColumn,
        OtdrSerialNumberColumn,
        ModuleNameColumn,
        ModuleSerialNumberColumn,
        SoftwareVersionColumn,
        SupplierOtherColumn,
        DateTimeColumn,
        WavelengthColumn, // in nanometers
        PulseWidthColumn, // in nanoseconds
        SampleSpacingColumn, // in picoseconds
        IndexOfRefractionColumn,
        BackscatteringCoefficientColumn,
        FiberStartPositionColumn, // in nanoseconds
        PointsColumn,
        ColumnsCount
    };

    ReflectogramModel(QObject *parent = 0);

    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;

    virtual Qt::ItemFlags flags(const QModelIndex &index) const;

    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);

    virtual bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex());
    virtual bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex());

    int scalingFactor(int row) const;

    bool readFile(int row);
    bool saveFile(int row);

private:
    struct Row {
        QString filePath;
        Core::Reflectogram reflectogram;
    };

    template <Column Col>
    struct ColumnTraits
    {

        using NativeType = void;
        using ModelType = void;
    };

    bool rowInBound(int row) const;
    bool columnInBound(int col) const;
    bool inBound(const QModelIndex &index) const;

    std::vector<Row> m_data;
};

Q_DECLARE_METATYPE(Core::LeUInt16Vector)

#endif // REFLECTOGRAMMODEL_H
