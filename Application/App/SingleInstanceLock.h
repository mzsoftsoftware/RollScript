#pragma once

#include <QObject>
#include "Core/Errors/RollScriptErrorOwner.h"

class QLockFile;


class SingleInstanceLock : public QObject, public RollScriptErrorOwner
{
    Q_OBJECT
public:
    // Constructor / Destructor
    explicit SingleInstanceLock(QObject* parent);
    ~SingleInstanceLock() override;

    // Operations
    bool lock();

private:
    QLockFile* m_ptrLockFile = nullptr;
};
