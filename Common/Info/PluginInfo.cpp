#include "PluginInfo.h"

#include <QCoreApplication>


PluginInfo::PluginInfo(const char* pszContext,
                       const QString& qstrPluginId,
                       const QString& qstrPluginVersion,
                       const char* pszPluginDisplayNameKey)
    : m_pszContext(pszContext)
    , m_qstrPluginId(qstrPluginId)
    , m_qstrPluginVersion(qstrPluginVersion)
    , m_pszPluginDisplayNameKey(pszPluginDisplayNameKey)
{
}

QString PluginInfo::translate(const char* pszKey) const
{
    return QCoreApplication::translate(m_pszContext, pszKey);
}
