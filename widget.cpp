#include "widget.h"
#include "ui_widget.h"

#include "fileinputbuffer.h"

#include "reflectogram/reflectogram.h"

#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QDateTime>

#include <algorithm>
#include <iterator>

#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    QString fileName = "D:/Projects/Reflektolom/data/amta/amta_1550_017.SOR";
    //QString fileName = QFileDialog::getOpenFileName(this);

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "can't open" << fileName;
        return;
    }

    Reflectogram r;
    FileInputBuffer buffer(file);
    if (!r.read(buffer)) {
        qDebug() << "not readed" << fileName;
        return;
    }

    QString out;
    QTextStream stream(&out);

    r.setSupplierName("Putinonix");
    r.setWavelength(10000);
    r.calculateChecksum();

    stream << r.supplierName().c_str() << "\n"
           << QDateTime::fromTime_t(r.dateTime()).toString() << "\n"
           << r.wavelength() << "\n"
           << r.fiberStartPosition() << "\n";

    auto pts = r.points();
    std::copy(pts.begin(), pts.end(), std::back_inserter(pts));
    r.setPoints(pts);

    ui->log->setPlainText(out);

    QFile outFile(fileName + ".0");
    if (!outFile.open(QIODevice::WriteOnly)) {
        qDebug() << "can't open out file";
        return;
    }

    for (auto it = r.dataBegin(), end = r.dataEnd(); it != end; ++it) {
        if (!outFile.putChar(*it)) {
            qDebug() << "can't put char";
            return;
        }
    }
}
