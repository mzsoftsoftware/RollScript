#pragma once

#include "RollScriptError.h"
#include "RollScriptErrorMacros.h"


class RollScriptErrorOwner
{
public:
    explicit RollScriptErrorOwner();
    virtual ~RollScriptErrorOwner();

    /*
     * Returns the current error and transfers ownership.
     * Caller is responsible for deleting the returned pointer.
     */
    RollScriptError* takeError();
    bool hasError() const;

protected:
    void setErrorInternal(const QString& qstrUserMessage,
                          const QString& qstrTechnicalMessage,
                          const char* pszFile,
                          const char* pszFunction,
                          int iLine,
                          RollScriptError* ptrCause = nullptr);
    void setErrorInternal(RollScriptError* ptrCause = nullptr);

private:
    RollScriptError* m_ptrError = nullptr;
};
