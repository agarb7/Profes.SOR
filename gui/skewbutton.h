#ifndef SKEWBUTTON_H
#define SKEWBUTTON_H

#include <QPushButton>

class SkewButton : public QPushButton
{
    Q_OBJECT
public:
    explicit SkewButton(QWidget *parent = 0);

    const QWidget *sourceEditor() const;
    void setSourceEditor(const QWidget *editor);

signals:
    void skewClicked(double skew);

private:
    const QWidget *m_sourceEditor = 0;
};

#endif // SKEWBUTTON_H
