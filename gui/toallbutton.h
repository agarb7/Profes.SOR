#ifndef TOALLBUTTON_H
#define TOALLBUTTON_H

#include <QToolButton>
#include <QAbstractItemModel>

class ToAllButton: public QToolButton
{
public:
    explicit ToAllButton(QWidget *parent = 0);    

    QAbstractItemModel *model() const;
    void setModel(QAbstractItemModel *model);

    int section() const;
    void setSection(int section);

    QWidget *editor() const;
    void setEditor(QWidget *editor);

private slots:
    void setEditorDataToAll();

private:
    QWidget *m_editor = 0;
    QAbstractItemModel *m_model=0;
    int m_section=-1;
};

#endif // TOALLBUTTON_H
