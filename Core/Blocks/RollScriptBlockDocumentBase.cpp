#include "RollScriptBlockDocumentBase.h"


RollScriptBlockDocumentBase::RollScriptBlockDocumentBase(const QString& qstrBlockPluginId, QObject* parent)
    : QObject(parent)
    , m_qstrBlockPluginId(qstrBlockPluginId)
{
}