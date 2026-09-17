#pragma once

#include "Core/Plugins/IPluginInfo.h"

#include <QString>
#include <QIcon>


class PluginInfo : public virtual IPluginInfo
{
public:
    explicit PluginInfo(const char* pszContext,
                        const QString& qstrPluginId,
                        const QString& qstrPluginVersion,
                        const char* pszPluginNameKey,
                        const char* pszPluginDescriptionKey,
                        const QIcon& iconPlugin);
    ~PluginInfo() override;

    // Getter
    const QString& pluginId() const override        { return m_qstrPluginId; }
    const QString& pluginVersion() const override   { return m_qstrPluginVersion; }
    QString pluginName() const override             { return translate(m_pszPluginNameKey); }
    QString pluginDescription() const override      { return translate(m_pszPluginDescriptionKey); }
    const QIcon& pluginIcon() const override        { return m_iconPlugin; }

protected:
    QString translate(const char* pszKey) const;

private:
    const char* m_pszContext;
    QString m_qstrPluginId;
    QString m_qstrPluginVersion;
    const char* m_pszPluginNameKey;
    const char* m_pszPluginDescriptionKey;
    QIcon m_iconPlugin;
};
