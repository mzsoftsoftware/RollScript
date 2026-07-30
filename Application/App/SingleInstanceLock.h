#pragma once

#include <QObject>

class QLockFile;


class SingleInstanceLock : public QObject
{
    Q_OBJECT
public:
    explicit SingleInstanceLock(QObject *parent);
    virtual ~SingleInstanceLock() override;

    bool lock();

    QString lastError() const           { return m_qstrLastError; }

private:
    QString m_qstrLastError;

    QLockFile* m_ptrLockFile = nullptr;
};
