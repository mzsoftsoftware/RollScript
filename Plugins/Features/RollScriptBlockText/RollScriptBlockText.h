#pragma once

#include "Core/Blocks/RollScriptBlock.h"


class RollScriptBlockTextXXX : public RollScriptBlockXXX
{
    Q_OBJECT

public:
    explicit RollScriptBlockTextXXX(QObject* parent);
    virtual ~RollScriptBlockTextXXX() override = default;

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

