#include "PrinterPluginRegistry.h"

#include "Common/Core/Plugins/IPrinterPlugin.h"


bool PrinterPluginRegistry::registerPlugin(IPrinterPlugin* ptrPrinterPlugin)
{
    if(!ptrPrinterPlugin)
        return false;

    if(m_registryPlugins.contains(ptrPrinterPlugin))
        return false;

    m_registryPlugins.append(ptrPrinterPlugin);

    return true;
}

