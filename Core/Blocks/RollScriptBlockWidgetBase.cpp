#include "RollScriptBlockWidgetBase.h"


RollScriptBlockWidgetBase::RollScriptBlockWidgetBase(const QString& qstrBlockPluginId, const QString& qstrTitle, QWidget* parent)
    : QGroupBox(parent)
    , m_qstrBlockPluginId(qstrBlockPluginId)
{
    setTitle(qstrTitle);
}
RollScriptBlockWidgetBase::~RollScriptBlockWidgetBase()
{
}
