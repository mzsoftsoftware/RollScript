#pragma once

#include <QObject>
#include "Core/Errors/RollScriptErrorOwner.h"

#include <QFont>


class RollScriptBlockTextLineDocument : public QObject, public RollScriptErrorOwner
{
    Q_OBJECT

public:
    RollScriptBlockTextLineDocument(QObject* parent);

    // Getter
    const bool lineActive() const               { return m_bActive; }
    const QString& lineText() const             { return m_qstrText; }
    const QFont& lineFont() const               { return m_font; }
    const Qt::Alignment lineAlignment() const   { return m_alignment; }

    // Setter
    void setLineActive(const bool bActive);
    void setLineText(const QString& qstrLineText);
    void setLineFont(const QFont& font);
    void setLineAlignment(const Qt::Alignment& alignment);

    // JSON
    void clear();
    bool loadFromJson(const QJsonObject& jsonBlockTextLine);
    bool saveToJson(QJsonObject& jsonBlockTextLine);

private:
    bool loadVersion_1(const QJsonObject& jsonBlockTextLine);

signals:
    void documentCleared();
    void documentLoaded();
    void blockTextLineChanged();

private:
    bool            m_bActive = false;
    QString         m_qstrText;
    QFont           m_font;
    Qt::Alignment   m_alignment;
};
