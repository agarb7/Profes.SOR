#include "toallbutton.h"

#include "model/reflectogram_.h"

#include <QMetaProperty>

ToAllButton::ToAllButton(QWidget *parent) :
    QToolButton(parent)
{
    setText(tr("all"));

    connect(this, &QToolButton::clicked,
            this, &ToAllButton::onClickSlot);
}

Model::Reflectogram *ToAllButton::model() const
{
    return m_model;
}

void ToAllButton::setModel(Model::Reflectogram *model)
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

/*!
 * \brief ToAllButton::isSectionValid
 * \param section
 * \return true if model and section is valid, otherwise false
 */
bool ToAllButton::sectionIsValid() const
{
    return m_model
            && m_section >= 0
            && m_section < m_model->columnCount();
}

QVariant ToAllButton::editorData() const
{
    return m_editor
            ->metaObject()
            ->userProperty()
            .read(m_editor);
}

void ToAllButton::onClick()
{
    if (!m_editor || !sectionIsValid())
        return;

    QVariant data = editorData();
    for (int row = 0, count = m_model->rowCount(); row<count; ++row) {
        QModelIndex index = m_model->index(row, m_section);
        m_model->setData(index, data);
    }
}

void ToAllButton::onClickSlot()
{
    onClick();
}
