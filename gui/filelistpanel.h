#ifndef FILELISTPANEL_H
#define FILELISTPANEL_H

#include <QWidget>

namespace Model {
class Reflectogram;
}

namespace Ui {
class FileListPanel;
}

class FileListPanel : public QWidget
{
    Q_OBJECT

public:
    explicit FileListPanel(QWidget *parent = 0);
    ~FileListPanel();

    Model::Reflectogram *model() const;
    void setModel(Model::Reflectogram *model);

signals:
    void activated(int index);

public slots:
    void addFiles();
    void saveAll();

private:
    Ui::FileListPanel *ui;
};

#endif // FILELISTPANEL_H
