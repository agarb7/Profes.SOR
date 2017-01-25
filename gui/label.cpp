#include "label.h"

QAbstractItemModel *Label::model() const
{
    return m_model;
}

void Label::setModel(QAbstractItemModel *model)
{
    m_model = model;
    updateText();
}

int Label::section() const
{
    return m_section;
}

void Label::setSection(int section)
{
    m_section = section;
    updateText();
}

void Label::updateText()
{
    if (!m_model || m_section == -1)
        return;

    QString text = m_model
            ->headerData(m_section, Qt::Horizontal)
            .toString();

    setText(text);
}
