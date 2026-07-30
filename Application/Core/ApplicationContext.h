#pragma once

class TranslationManager;
class PluginManager;
class PrinterManager;


class ApplicationContext
{
public:
    ApplicationContext(TranslationManager* ptrTranslationManager,
                       PluginManager* ptrPluginManager,
                       PrinterManager* ptrPrinterManager);

    TranslationManager* translationManager() const  { return m_ptrTranslationManager; }
    PluginManager* pluginManager() const            { return m_ptrPluginManager; }
    PrinterManager* printerManager() const            { return m_ptrPrinterManager; }

private:
    TranslationManager* m_ptrTranslationManager = nullptr;
    PluginManager* m_ptrPluginManager = nullptr;
    PrinterManager* m_ptrPrinterManager = nullptr;
};