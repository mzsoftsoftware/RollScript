#pragma once

#include <QString>


class RollScriptError
{
public:
    // Constructor / Destructor
    explicit RollScriptError(const QString& qstrUserMessage,
                             const QString& qstrTechnicalMessage,
                             const QString& qstrFile,
                             const QString& qstrFunction,
                             const int iLine);
    virtual ~RollScriptError();

    // Operations
    QString messageUser() const;
    QString messageDebug(int iIndentLevel = 0) const;

    void setCause(RollScriptError* ptrCause);
    RollScriptError* cause() const;

private:
    QString m_qstrUserMessage;
    QString m_qstrTechnicalMessage;

    QString m_qstrFile;
    QString m_qstrFunction;
    int m_iLine = 0;

    RollScriptError* m_ptrCause = nullptr;
};
