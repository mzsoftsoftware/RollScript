#include "RollScriptBlockWidgetBase.h"

RollScriptBlockWidgetBase::RollScriptBlockWidgetBase(const QString &qstrPluginId, const QString &qstrTitle, QWidget *parent)
    : QGroupBox(parent)
    , m_qstrPluginId(qstrPluginId)
{
    setTitle(qstrTitle);
}