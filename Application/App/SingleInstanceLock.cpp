#include "SingleInstanceLock.h"

#include <QDir>
#include <QCoreApplication>
#include <QLockFile>


SingleInstanceLock::SingleInstanceLock(QObject *parent)
    : QObject{parent}
{
    QString qstrLockFilePath = QDir::temp().absoluteFilePath(QString("%1.lock").arg(QCoreApplication::applicationName()));

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
        // TASK : Use correct tr !!!
        m_qstrLastError = tr("Lock file is not initialized.");
        return false;
    }

    if(!m_ptrLockFile->tryLock())
    {
        // TASK : Use correct tr !!!
        m_qstrLastError = tr("The application is already running.");
        return false;
    }

    return true;
}
