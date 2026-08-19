#include "RollScriptError.h"

#include <QDebug>


RollScriptError::RollScriptError(const QString& qstrUserMessage,
                                 const QString& qstrTechnicalMessage,
                                 const QString& qstrFile,
                                 const QString& qstrFunction,
                                 int iLine)
    : m_qstrUserMessage(qstrUserMessage)
    , m_qstrTechnicalMessage(qstrTechnicalMessage)
    , m_qstrFile(qstrFile)
    , m_qstrFunction(qstrFunction)
    , m_iLine(iLine)
{
}

RollScriptError::~RollScriptError()
{
    delete m_ptrCause;
    m_ptrCause = nullptr;
}

QString RollScriptError::messageUser() const
{
    return m_qstrUserMessage;
}

QString RollScriptError::messageDebug(int iIndentLevel) const
{
    const QString qstrIndent(iIndentLevel * 4, QChar(u' '));
    QString qstrResult;

    qstrResult += qstrIndent;
    qstrResult += m_qstrUserMessage;
    qstrResult += QStringLiteral("\n\n");

    qstrResult += qstrIndent;
    qstrResult += QStringLiteral("Technical message:\n");

    qstrResult += qstrIndent;
    qstrResult += m_qstrTechnicalMessage;
    qstrResult += QStringLiteral("\n\n");

    qstrResult += qstrIndent;
    qstrResult += QStringLiteral("Location:\n");

    qstrResult += qstrIndent;
    qstrResult += m_qstrFunction;
    qstrResult += QStringLiteral("\n");

    qstrResult += qstrIndent;
    qstrResult += m_qstrFile;
    qstrResult += QStringLiteral(" : ");
    qstrResult += QString::number(m_iLine);


    if(m_ptrCause)
    {
        qstrResult += QStringLiteral("\n\n");

        qstrResult += qstrIndent;
        qstrResult += QStringLiteral("Caused by:\n");
        qstrResult += m_ptrCause->messageDebug(iIndentLevel + 1);
    }

    return qstrResult;
}

void RollScriptError::setCause(RollScriptError* ptrCause)
{
    if(m_ptrCause == ptrCause)
        return;

    delete m_ptrCause;

    m_ptrCause = ptrCause;
}

RollScriptError* RollScriptError::cause() const
{
    return m_ptrCause;
}
