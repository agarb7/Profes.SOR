#include "toallbutton.h"

#include <QMetaProperty>

ToAllButton::ToAllButton(QWidget *parent) :
    QToolButton(parent)
{
    setText(tr("all"));

    connect(this, &QToolButton::clicked,
            this, &ToAllButton::setEditorDataToAll);
}


QAbstractItemModel *ToAllButton::model() const
{
    return m_model;
}

void ToAllButton::setModel(QAbstractItemModel *model)
{
    m_model = model;
}

int ToAllButton::section() const
{
    return m_section;
}

void ToAllButton::setSection(int section)
{
    m_section = section;
}

QWidget *ToAllButton::editor() const
{
    return m_editor;
}

void ToAllButton::setEditor(QWidget *editor)
{
    m_editor = editor;
}

void ToAllButton::setEditorDataToAll()
{
    if (!m_editor || !m_model || m_section == -1)
        return;

    QVariant data = m_editor
            ->metaObject()
            ->userProperty()
            .read(m_editor);

    for (int row = 0, count = m_model->rowCount(); row<count; ++row) {
        QModelIndex index = m_model->index(row, m_section);
        m_model->setData(index, data);
    }
}
