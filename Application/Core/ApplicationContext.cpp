#include "ApplicationContext.h"

ApplicationContext::ApplicationContext(TranslationManager* ptrTranslationManager,
                   PluginManager* ptrPluginManager,
                   PrinterManager* ptrPrinterManager)
    : m_ptrTranslationManager(ptrTranslationManager)
    , m_ptrPluginManager(ptrPluginManager)
    , m_ptrPrinterManager(ptrPrinterManager)
{

}
