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

    return ColumnsCount;
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

    const Row &row = m_data[index.row()];
    const Core::Reflectogram &r = row.reflectogram;

    switch (index.column()) {
    case FilePathColumn:
        return row.filePath;
    case SupplierNameColumn:
        return QString::fromStdString(r.supplierName());
    case OtdrNameColumn:
        return QString::fromStdString(r.otdrName());
    case OtdrSerialNumberColumn:
        return QString::fromStdString(r.otdrSerialNumber());
    case ModuleNameColumn:
        return QString::fromStdString(r.moduleName());
    case ModuleSerialNumberColumn:
        return QString::fromStdString(r.moduleSerialNumber());
    case SoftwareVersionColumn:
        return QString::fromStdString(r.softwareVersion());
    case SupplierOtherColumn:
        return QString::fromStdString(r.supplierOther());
    case DateTimeColumn:
        return QDateTime::fromTime_t(r.dateTime());
    case WavelengthColumn:
        return double(r.wavelength())/10;
    case PulseWidthColumn:
        return int(r.pulseWidth());
    case SampleSpacingColumn:
        return double(r.sampleSpacing())/100;
    case IndexOfRefractionColumn:
        return double(r.indexOfRefraction())/100000;
    case BackscatteringCoefficientColumn:
        return int(r.backscatteringCoefficient());
    case FiberStartPositionColumn:
        return double(r.fiberStartPosition())/10;
    case PointsColumn:
        return QVariant::fromValue(r.points());
//    case ColumnsCount:
    }

    return QVariant();
}

QVariant ReflectogramModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation != Qt::Horizontal || role != Qt::DisplayRole)
        return QAbstractTableModel::headerData(section, orientation, role);

    if (!columnInBound(section))
        return QVariant();

    switch (section) {
    case FilePathColumn:
        return tr("File path");
    case SupplierNameColumn:
        return tr("Supplier name");
    case OtdrNameColumn:
        return tr("Otdr name");
    case OtdrSerialNumberColumn:
        return tr("Otdr s/n");
    case ModuleNameColumn:
        return tr("Module name");
    case ModuleSerialNumberColumn:
        return tr("Module s/n");
    case SoftwareVersionColumn:
        return tr("Software version");
    case SupplierOtherColumn:
        return tr("Supplier other");
    case DateTimeColumn:
        return tr("Date/time");
    case WavelengthColumn:
        return tr("Wavelength");
    case PulseWidthColumn:
        return tr("Pulse width");
    case SampleSpacingColumn:
        return tr("Sample spacing");
    case IndexOfRefractionColumn:
        return tr("Index of refraction");
    case BackscatteringCoefficientColumn:
        return tr("Backscattering coef.");
    case FiberStartPositionColumn:
        return tr("Fiber start position");
    case PointsColumn:
        return tr("Trace");
//    case ColumnsCount:
    }

    return QVariant();
}

bool ReflectogramModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!inBound(index) || role != Qt::EditRole)
        return false;    

    Row &row = m_data[index.row()];
    Core::Reflectogram &r = row.reflectogram;

    switch (index.column()) {
    case FilePathColumn: {
        if (!value.canConvert<QString>())
            return false;

        QString newFilePath = value.toString();
        if (row.filePath != newFilePath) {
            row.filePath = newFilePath;
            emit dataChanged(index, index);
        }

        return true;
    }
    case SupplierNameColumn: {
        if (r.empty() || !value.canConvert<QString>())
            return false;

        Core::String newSupplierName = value.toString().toStdString(); //todo isolate String from std::string by templ spec convert<QString>(String);
        if (r.supplierName() != newSupplierName) {
            r.setSupplierName(newSupplierName);
            emit dataChanged(index, index);
        }

        return true;
    }
    case OtdrNameColumn: {
        if (r.empty() || !value.canConvert<QString>())
            return false;

        Core::String newOtdrName = value.toString().toStdString();
        if (r.otdrName() != newOtdrName) {
            r.setOtdrName(newOtdrName);
            emit dataChanged(index, index);
        }

        return true;
    }
    case OtdrSerialNumberColumn: {
        if (r.empty() || !value.canConvert<QString>())
            return false;

        Core::String newOtdrSerialNumber = value.toString().toStdString();
        if (r.otdrSerialNumber() != newOtdrSerialNumber) {
            r.setOtdrSerialNumber(newOtdrSerialNumber);
            emit dataChanged(index, index);
        }

        return true;
    }
    case ModuleNameColumn: {
        if (r.empty() || !value.canConvert<QString>())
            return false;

        Core::String newModuleName = value.toString().toStdString();
        if (r.moduleName() != newModuleName) {
            r.setModuleName(newModuleName);
            emit dataChanged(index, index);
        }

        return true;
    }
    case ModuleSerialNumberColumn: {
        if (r.empty() || !value.canConvert<QString>())
            return false;

        Core::String newModuleSerialNumber = value.toString().toStdString();
        if (r.moduleSerialNumber() != newModuleSerialNumber) {
            r.setModuleSerialNumber(newModuleSerialNumber);
            emit dataChanged(index, index);
        }

        return true;
    }
    case SoftwareVersionColumn: {
        if (r.empty() || !value.canConvert<QString>())
            return false;

        Core::String newSoftwareVersion = value.toString().toStdString();
        if (r.softwareVersion() != newSoftwareVersion) {
            r.setSoftwareVersion(newSoftwareVersion);
            emit dataChanged(index, index);
        }

        return true;
    }
    case SupplierOtherColumn: {
        if (r.empty() || !value.canConvert<QString>())
            return false;

        Core::String newSupplierOther = value.toString().toStdString();
        if (r.supplierOther() != newSupplierOther) {
            r.setSupplierOther(newSupplierOther);
            emit dataChanged(index, index);
        }

        return true;
    }
    case DateTimeColumn: {
        if (r.empty() || !value.canConvert<QDateTime>())
            return false;

        Core::LeUInt32 newDateTime = value.toDateTime().toTime_t();
        if (r.dateTime() != newDateTime) {
            r.setDateTime(newDateTime);
            emit dataChanged(index, index);
        }

        return true;
    }
    case WavelengthColumn: {
        if (r.empty() || !value.canConvert<double>())
            return false;

        Core::LeUInt16 newWavelength = value.toDouble()*10;
        if (r.wavelength() != newWavelength) {
            r.setWavelength(newWavelength);
            emit dataChanged(index, index);
        }

        return true;
    }
    case PulseWidthColumn: {
        if (r.empty() || !value.canConvert<int>())
            return false;

        Core::LeUInt16 newPulseWidth = value.toInt();
        if (r.pulseWidth() != newPulseWidth) {
            r.setPulseWidth(newPulseWidth);
            emit dataChanged(index, index);
        }

        return true;
    }
    case SampleSpacingColumn: {
        if (r.empty() || !value.canConvert<double>())
            return false;

        Core::LeUInt32 newSampleSpacing = value.toDouble()*100;
        if (r.sampleSpacing() != newSampleSpacing) {
            r.setSampleSpacing(newSampleSpacing);
            emit dataChanged(index, index);
        }

        return true;
    }
    case IndexOfRefractionColumn: {
        if (r.empty() || !value.canConvert<double>())
            return false;

        Core::LeUInt32 newIndexOfRefraction = value.toDouble()*100000;
        if (r.indexOfRefraction() != newIndexOfRefraction) {
            r.setIndexOfRefraction(newIndexOfRefraction);
            emit dataChanged(index, index);
        }

        return true;
    }
    case BackscatteringCoefficientColumn: {
        if (r.empty() || !value.canConvert<int>())
            return false;

        Core::LeUInt16 newBackscatteringCoefficient = value.toInt();
        if (r.backscatteringCoefficient() != newBackscatteringCoefficient) {
            r.setBackscatteringCoefficient(newBackscatteringCoefficient);
            emit dataChanged(index, index);
        }

        return true;
    }
    case FiberStartPositionColumn: {
        if (r.empty() || !value.canConvert<double>())
            return false;

        Core::LeInt32 newFiberStartPosition = value.toDouble()*10;
        if (r.fiberStartPosition() != newFiberStartPosition) {
            r.setFiberStartPosition(newFiberStartPosition);
            emit dataChanged(index, index);
        }

        return true;
    }
    case PointsColumn: {
        if (r.empty() || !value.canConvert<Core::LeUInt16Vector>())
            return false;

        Core::LeUInt16Vector newPoints = value.value<Core::LeUInt16Vector>();
        if (r.points() != newPoints) {
            r.setPoints(newPoints);
            emit dataChanged(index, index);
        }

        return true;
    }
//    case ColumnsCount:
    }

    return false;
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

int ReflectogramModel::scalingFactor(int row) const
{
    if (!rowInBound(row))
        return 0;

    return m_data[row]
            .reflectogram
            .scalingFactor();
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
    return col >= 0 && col < ColumnsCount;
}

bool ReflectogramModel::inBound(const QModelIndex &index) const
{
    return rowInBound(index.row()) && columnInBound(index.column());
}
