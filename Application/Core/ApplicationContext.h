#pragma once

class TranslationManager;
class PluginManager;
class DeviceManager;


class ApplicationContext
{
public:
    ApplicationContext(TranslationManager* ptrTranslationManager,
                       PluginManager* ptrPluginManager,
                       DeviceManager* ptrDeviceManager);

    TranslationManager* translationManager() const  { return m_ptrTranslationManager; }
    PluginManager* pluginManager() const            { return m_ptrPluginManager; }
    DeviceManager* deviceManager() const            { return m_ptrDeviceManager; }

private:
    TranslationManager* m_ptrTranslationManager = nullptr;
    PluginManager* m_ptrPluginManager = nullptr;
    DeviceManager* m_ptrDeviceManager = nullptr;
};