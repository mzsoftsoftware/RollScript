#include "ApplicationContext.h"

#include <QLockFile>
#include <QDir>
#include <QMessageBox>

#include "App/SingleInstanceLock.h"

#include "Core/Translation/TranslationManager.h"
#include "Core/Plugins/PluginManager.h"

#include "Core/Printers/PrinterManager.h"
#include "Core/USB/USBManager.h"


ApplicationContext::ApplicationContext(QObject* parent)
    : QObject{parent}
{
}

bool ApplicationContext::init()
{
    m_ptrSingleInstanceLock = new SingleInstanceLock(this);
    if(!m_ptrSingleInstanceLock->lock())
    {
        QMessageBox::critical(nullptr, tr("Startup.Title"), m_ptrSingleInstanceLock->lastError());
        return false;
    }

    m_ptrTranslationManager = new TranslationManager(this);
    if(!m_ptrTranslationManager->init())
    {
        QMessageBox::critical(nullptr, tr("Startup.Title"), m_ptrTranslationManager->lastError());
        return false;
    }

    m_ptrPluginManager = new PluginManager(this);
    if(!m_ptrPluginManager->init())
    {
        QMessageBox::critical(nullptr, tr("Startup.Title"), m_ptrPluginManager->lastError());
        return false;
    }

    m_ptrUSBManager = new USBManager(this);
    if(!m_ptrUSBManager->init())
    {
        QMessageBox::critical(nullptr, tr("Startup.Title"), m_ptrUSBManager->lastError());
        return false;
    }
    m_ptrPrinterManager = new PrinterManager(m_ptrPluginManager, m_ptrUSBManager, this);

    return true;
}
