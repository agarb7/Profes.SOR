#include "filelistpanel.h"
#include "ui_filelistpanel.h"

#include "model/reflectogram_.h"

#include <QFileDialog>
#include <QMessageBox>

FileListPanel::FileListPanel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FileListPanel)
{
    ui->setupUi(this);

    ui->listView->setModelColumn(int(Model::ReflectogramColumn::FilePath));
    connect(ui->listView, &QListView::activated, [this](const QModelIndex &index) {
        emit activated(index.row());
    });

    connect(ui->addFileBtn, &QPushButton::clicked,
            this, &FileListPanel::addFiles);

    connect(ui->saveAllBtn, &QPushButton::clicked,
            this, &FileListPanel::saveAll);
}

FileListPanel::~FileListPanel()
{
    delete ui;
}

Model::Reflectogram *FileListPanel::model() const
{
    return static_cast<Model::Reflectogram*>(ui->listView->model());
}

void FileListPanel::setModel(Model::Reflectogram *model)
{
    ui->listView->setModel(model);
}

void FileListPanel::addFiles()
{
    Model::Reflectogram *model = this->model();
    if (!model)
        return;

    QStringList files
            = QFileDialog::getOpenFileNames(this,
                                            QString(),
                                            QString(),
                                            tr("Traces (*.*)"));

    bool result = true;
    for (QString file: files) {
        int row = model->rowCount();
        model->insertRow(row);
        QModelIndex index = model->index(row, int(Model::ReflectogramColumn::FilePath));
        model->setData(index, file);
        if (!model->readFile(row)) {
            model->removeRow(row);
            result = false;
        }
    }

    if (!result) {
        QMessageBox::warning(this,
                             QString(),
                             tr("Not all (or nothing) files readed"));
    }
}

void FileListPanel::saveAll()
{
    Model::Reflectogram *model = this->model();
    if (!model)
        return;

    bool result = true;
    for (int row = 0, count = model->rowCount(); row<count; ++row) {
        if (!model->saveFile(row))
            result = false;
    }

    if (result) {
        QMessageBox::information(this,
                                 QString(),
                                 tr("Files saved"));
    }
    else {
        QMessageBox::critical(this,
                              QString(),
                              tr("Not all (or nothing) files saved"));
    }
}

