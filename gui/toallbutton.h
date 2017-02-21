#ifndef TOALLBUTTON_H
#define TOALLBUTTON_H

#include <QToolButton>

namespace Model {
    class Reflectogram;
}

class ToAllButton: public QToolButton
{
    Q_OBJECT

public:
    explicit ToAllButton(QWidget *parent = 0);    

    Model::Reflectogram *model() const;
    void setModel(Model::Reflectogram *model);

    int section() const;
    void setSection(int section);

    QWidget *editor() const;
    void setEditor(QWidget *editor);

protected:
    bool sectionIsValid() const;
    QVariant editorData() const;
    virtual void onClick();

private slots:
    void onClickSlot();

private:
    QWidget *m_editor = 0;
    Model::Reflectogram *m_model=0;
    int m_section=-1;
};

#endif // TOALLBUTTON_H
