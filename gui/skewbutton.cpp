#include "skewbutton.h"

#include <QMetaProperty>

SkewButton::SkewButton(QWidget *parent) : QPushButton(parent)
{
    connect(this, &QPushButton::clicked, [this]() {
        if (!m_sourceEditor)
            return;

        QVariant value = m_sourceEditor
                ->metaObject()
                ->userProperty()
                .read(m_sourceEditor);

        if (!value.canConvert<double>())
            return;

        emit skewClicked(value.toDouble());
    });
}

const QWidget *SkewButton::sourceEditor() const
{
    return m_sourceEditor;
}

void SkewButton::setSourceEditor(const QWidget *editor)
{
    m_sourceEditor = editor;
}
