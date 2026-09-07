#include "RollScriptBlockWidgetBase.h"


RollScriptBlockWidgetBase::RollScriptBlockWidgetBase(const QString& qstrBlockPluginId, QWidget* parent)
    : QGroupBox(parent)
    , m_qstrBlockPluginId(qstrBlockPluginId)
{
}
RollScriptBlockWidgetBase::~RollScriptBlockWidgetBase()
{
}

//void RollScriptBlockWidgetBase::setTitle(const QString& qstrTitle)
//{
//    setTitle(qstrTitle);
//}
