#include "SingleInstanceLock.h"

#include <QDir>
#include <QCoreApplication>
#include <QLockFile>


SingleInstanceLock::SingleInstanceLock(QObject* parent)
    : QObject{parent}
{
    QString qstrLockFilePath = QDir::temp().absoluteFilePath(QStringLiteral("%1.lock").arg(QCoreApplication::applicationName()));

    m_ptrLockFile = new QLockFile(qstrLockFilePath);
}

SingleInstanceLock::~SingleInstanceLock()
{
    if(m_ptrLockFile)
    {
        m_ptrLockFile->unlock();
    }
}

bool SingleInstanceLock::lock()
{
    if(!m_ptrLockFile)
    {
        ROLLSCRIPT_ERROR(tr("LockFailed"), QStringLiteral("m_ptrLockFile is nullptr."));
        return false;
    }

    if(!m_ptrLockFile->tryLock())
    {
        ROLLSCRIPT_ERROR(tr("LockFailed.Running"), QStringLiteral("m_ptrLockFile->tryLock() failed."));
        return false;
    }

    return true;
}
