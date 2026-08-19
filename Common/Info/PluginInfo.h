#pragma once

#include "Core/Plugins/IPluginInfo.h"

#include <QString>


class PluginInfo : public virtual IPluginInfo
{
public:
    PluginInfo(const char* pszContext,
               const QString& qstrPluginId,
               const QString& qstrPluginVersion,
               const char* pszPluginDisplayNameKey);
    ~PluginInfo() override = default;

    const QString& pluginId() const override        { return m_qstrPluginId; }
    const QString& pluginVersion() const override   { return m_qstrPluginVersion; }
    QString pluginDisplayName() const override      { return translate(m_pszPluginDisplayNameKey); }

protected:
    QString translate(const char* pszKey) const;

private:
    const char* m_pszContext;
    QString m_qstrPluginId;
    QString m_qstrPluginVersion;
    const char* m_pszPluginDisplayNameKey;
};
