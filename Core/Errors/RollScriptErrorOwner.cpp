#include "RollScriptErrorOwner.h"

#include <QDebug>
#include "RollScriptError.h"

RollScriptErrorOwner::RollScriptErrorOwner()
{
}

RollScriptErrorOwner::~RollScriptErrorOwner()
{
    /*
     * An unhandled error is a programming error.
     * During development we want to see it immediately.
     */
    if(m_ptrError)
    {
        qCritical().noquote()
        << "Unhandled RollScriptError:\n"
                << m_ptrError->messageDebug();

        Q_ASSERT_X(
            false,
            "RollScriptErrorOwner::~RollScriptErrorOwner",
            "Unhandled RollScriptError detected."
            );

        delete m_ptrError;
        m_ptrError = nullptr;
    }
}

RollScriptError* RollScriptErrorOwner::takeError()
{
    RollScriptError* ptrResult = m_ptrError;
    m_ptrError = nullptr;
    return ptrResult;
}

void RollScriptErrorOwner::setErrorInternal(const QString& qstrUserMessage,
                                            const QString& qstrTechnicalMessage,
                                            const char* pszFile,
                                            const char* pszFunction,
                                            const int iLine,
                                            RollScriptError* ptrCause)
{
    RollScriptError* ptrError = new RollScriptError(qstrUserMessage,
                                     qstrTechnicalMessage,
                                     QString::fromUtf8(pszFile),
                                     QString::fromUtf8(pszFunction),
                                     iLine);
    /*
     * Only one active error is allowed.
     */
    if(m_ptrError)
    {
        qCritical().noquote() << "Previous RollScriptError was not handled:\n" << m_ptrError->messageDebug();
        qCritical().noquote() << "New RollScriptError:\n" << ptrError->messageDebug();
        Q_ASSERT_X(false, "RollScriptErrorOwner::setError", "Previous RollScriptError was not taken.");
    }

    if(ptrCause)
    {
        ptrError->setCause(ptrCause);
    }

    m_ptrError = ptrError;
}
void RollScriptErrorOwner::setErrorInternal(RollScriptError* ptrError)
{
    /*
     * Only one active error is allowed.
     */
    if(m_ptrError)
    {
        qCritical().noquote() << "Previous RollScriptError was not handled:\n" << m_ptrError->messageDebug();
        qCritical().noquote() << "New RollScriptError:\n" << ptrError->messageDebug();
        Q_ASSERT_X(false, "RollScriptErrorOwner::setError", "Previous RollScriptError was not taken.");
    }

    m_ptrError = ptrError;
}

bool RollScriptErrorOwner::hasError() const
{
    return m_ptrError != nullptr;
}
