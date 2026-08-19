#pragma once

#include <QObject>
#include "Core/Errors/RollScriptErrorOwner.h"

class QLockFile;


class SingleInstanceLock : public QObject, public RollScriptErrorOwner
{
    Q_OBJECT
public:
    explicit SingleInstanceLock(QObject* parent);
    virtual ~SingleInstanceLock() override;

    bool lock();

private:
    QLockFile* m_ptrLockFile = nullptr;
};
