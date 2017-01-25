#ifndef LABEL_H
#define LABEL_H

#include <QLabel>
#include <QAbstractItemModel>

class Label: public QLabel
{
    Q_OBJECT

public:
    using QLabel::QLabel;

    QAbstractItemModel *model() const;
    void setModel(QAbstractItemModel *model);

    int section() const;
    void setSection(int section);

private:
    void updateText();

    QAbstractItemModel *m_model=0;
    int m_section=-1;
};

#endif // LABEL_H
