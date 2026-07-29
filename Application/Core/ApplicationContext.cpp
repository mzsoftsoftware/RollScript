#include "ApplicationContext.h"

ApplicationContext::ApplicationContext(TranslationManager* ptrTranslationManager,
                   PluginManager* ptrPluginManager,
                   DeviceManager* ptrDeviceManager)
    : m_ptrTranslationManager(ptrTranslationManager)
    , m_ptrPluginManager(ptrPluginManager)
    , m_ptrDeviceManager(ptrDeviceManager)
{

}
