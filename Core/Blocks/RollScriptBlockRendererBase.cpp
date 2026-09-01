#include "RollScriptBlockRendererBase.h"


RollScriptBlockRendererBase::RollScriptBlockRendererBase(const QString& qstrBlockPluginId, QObject* parent)
    : QObject(parent)
    , m_qstrBlockPluginId(qstrBlockPluginId)
{
}