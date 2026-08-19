#pragma once

#include "Core/Blocks/RollScriptBlock.h"


class RollScriptBlockText : public RollScriptBlock
{
    Q_OBJECT

public:
    explicit RollScriptBlockText(QObject* parent);
    virtual ~RollScriptBlockText() override = default;

    QString text() const
    {
        return m_qstrText;
    }

    void setText(const QString& qstrText)
    {
        m_qstrText = qstrText;
    }

private:
    QString m_qstrText;
};

