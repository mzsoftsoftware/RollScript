#pragma once

#include "IPluginInfo.h"

#include <QIcon>


class IPrinterPluginInfo : public virtual IPluginInfo
{
public:
    ~IPrinterPluginInfo() override = default;

    virtual const QIcon& printerIcon() const = 0;
};
