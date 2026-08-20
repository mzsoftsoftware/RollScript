#include "RollScriptBlockTextLineDocument.h"

RollScriptBlockTextLineDocument::RollScriptBlockTextLineDocument(QObject* parent)
    : QObject(parent)
{
}

void RollScriptBlockTextLineDocument::setLineActive(const bool bActive)
{
    m_bActive = bActive;
    emit blockTextLineChanged();
}
void RollScriptBlockTextLineDocument::setLineText(const QString& qstrLineText)
{
    m_qstrText = qstrLineText;
    emit blockTextLineChanged();
}
void RollScriptBlockTextLineDocument::setLineFont(const QFont& font)
{
    m_font = font;
    emit blockTextLineChanged();
}
void RollScriptBlockTextLineDocument::setLineAlignment(const Qt::Alignment& alignment)
{
    m_alignment = alignment;
    emit blockTextLineChanged();
}
