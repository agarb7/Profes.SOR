#ifndef FILELISTPANEL_H
#define FILELISTPANEL_H

#include <QWidget>

class ReflectogramModel;

namespace Ui {
class FileListPanel;
}

class FileListPanel : public QWidget
{
    Q_OBJECT

public:
    explicit FileListPanel(QWidget *parent = 0);
    ~FileListPanel();

    ReflectogramModel *model() const;
    void setModel(ReflectogramModel *model);

signals:
    void activated(int index);

public slots:
    void addFiles();
    void saveAll();

private:
    Ui::FileListPanel *ui;
};

#endif // FILELISTPANEL_H
