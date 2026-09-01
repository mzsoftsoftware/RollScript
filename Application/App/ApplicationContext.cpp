#include "ApplicationContext.h"

#include <QLockFile>
#include <QDir>
#include <QMessageBox>

#include "App/SingleInstanceLock.h"

#include "Translation/TranslationManager.h"
#include "Plugins/PluginManager.h"

#include "Printers/PrinterManager.h"
#include "Core/USB/USBManager.h"

#include "Features/FeatureBlockManager.h"

#include "Rendering/RollScriptRenderer.h"

#include "Core/Errors/RollScriptError.h"


ApplicationContext::ApplicationContext(QObject* parent)
    : QObject{parent}
{
}

bool ApplicationContext::init()
{
    m_ptrSingleInstanceLock = new SingleInstanceLock(this);
    if(!m_ptrSingleInstanceLock->lock())
    {
        RollScriptError *ptrError = m_ptrSingleInstanceLock->takeError();
        if(ptrError)
        {
            // TASK : Use correct tr !!!
            QMessageBox::critical(nullptr, tr("Startup.Title"), ptrError->messageUser());
            qDebug() << ptrError->messageDebug();
            delete ptrError;
        }
        else
            Q_ASSERT_X(false, "ApplicationContext::init", "No RollScriptError found");

        return false;
    }

    m_ptrTranslationManager = new TranslationManager(this);
    if(!m_ptrTranslationManager->init())
    {
        RollScriptError *ptrError = m_ptrTranslationManager->takeError();
        if(ptrError)
        {
            // TASK : Use correct tr !!!
            QMessageBox::critical(nullptr, tr("Startup.Title"), ptrError->messageUser());
            qDebug() << ptrError->messageDebug();
            delete ptrError;
        }
        else
            Q_ASSERT_X(false, "ApplicationContext::init", "No RollScriptError found");

        return false;
    }

    m_ptrPluginManager = new PluginManager(this);
    if(!m_ptrPluginManager->init())
    {
        RollScriptError *ptrError = m_ptrPluginManager->takeError();
        if(ptrError)
        {
            // TASK : Use correct tr !!!
            QMessageBox::critical(nullptr, tr("Startup.Title"), ptrError->messageUser());
            qDebug() << ptrError->messageDebug();
            delete ptrError;
        }
        else
            Q_ASSERT_X(false, "ApplicationContext::init", "No RollScriptError found");

        return false;
    }

    m_ptrFeatureBlockManager = new FeatureBlockManager(m_ptrPluginManager, this);
    if(!m_ptrFeatureBlockManager->init())
    {
        RollScriptError *ptrError = m_ptrFeatureBlockManager->takeError();
        if(ptrError)
        {
            // TASK : Use correct tr !!!
            QMessageBox::critical(nullptr, tr("Startup.Title"), ptrError->messageUser());
            qDebug() << ptrError->messageDebug();
            delete ptrError;
        }
        else
            Q_ASSERT_X(false, "ApplicationContext::init", "No RollScriptError found");

        return false;
    }

    m_ptrUSBManager = new USBManager(this);
    if(!m_ptrUSBManager->init())
    {
        RollScriptError *ptrError = m_ptrUSBManager->takeError();
        if(ptrError)
        {
            // TASK : Use correct tr !!!
            QMessageBox::critical(nullptr, tr("Startup.Title"), ptrError->messageUser());
            qDebug() << ptrError->messageDebug();
            delete ptrError;
        }
        else
            Q_ASSERT_X(false, "ApplicationContext::init", "No RollScriptError found");

        return false;
    }

    m_ptrPrinterManager = new PrinterManager(m_ptrPluginManager, m_ptrUSBManager, this);
    if(!m_ptrPrinterManager->init())
    {
        RollScriptError *ptrError = m_ptrPrinterManager->takeError();
        if(ptrError)
        {
            // TASK : Use correct tr !!!
            QMessageBox::critical(nullptr, tr("Startup.Title"), ptrError->messageUser());
            qDebug() << ptrError->messageDebug();
            delete ptrError;
        }
        else
            Q_ASSERT_X(false, "ApplicationContext::init", "No RollScriptError found");

        return false;
    }

    m_ptrRollScriptRenderer = new RollScriptRenderer(m_ptrPrinterManager, m_ptrFeatureBlockManager, this);
    if(!m_ptrRollScriptRenderer->init())
    {
        RollScriptError *ptrError = m_ptrRollScriptRenderer->takeError();
        if(ptrError)
        {
            // TASK : Use correct tr !!!
            QMessageBox::critical(nullptr, tr("Startup.Title"), ptrError->messageUser());
            qDebug() << ptrError->messageDebug();
            delete ptrError;
        }
        else
            Q_ASSERT_X(false, "ApplicationContext::init", "No RollScriptError found");

        return false;
    }


    return true;
}
