#pragma once

#include <QObject>

class SingleInstanceLock;

class TranslationManager;
class PluginManager;

class PrinterManager;
class USBManager;


class ApplicationContext : public QObject
{
    Q_OBJECT

public:
    ApplicationContext(QObject* parent);

    TranslationManager* translationManager() const  { return m_ptrTranslationManager; }
    PluginManager* pluginManager() const            { return m_ptrPluginManager; }
    PrinterManager* printerManager() const            { return m_ptrPrinterManager; }

    bool init();

private:
    SingleInstanceLock* m_ptrSingleInstanceLock = nullptr;

    TranslationManager* m_ptrTranslationManager = nullptr;
    PluginManager* m_ptrPluginManager = nullptr;

    PrinterManager* m_ptrPrinterManager = nullptr;
    USBManager* m_ptrUSBManager = nullptr;
};