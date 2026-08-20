#pragma once

#include "Core/Blocks/RollScriptBlockDocumentBase.h"

class RollScriptBlockTextLineDocument;


class RollScriptBlockTextDocument : public RollScriptBlockDocumentBase
{
    Q_OBJECT

public:
    RollScriptBlockTextDocument(const QString& qstrBlockPluginId, QObject* parent);
    virtual ~RollScriptBlockTextDocument();

    RollScriptBlockTextLineDocument* textLine(const unsigned int index) const;

    // JSON
    void clear() override;
    bool loadFromJson(const QJsonObject& jsonBlocks) override;
    bool saveToJson(QJsonObject& jsonBlocks) const override;

signals:
    void documentCleared();
    void documentLoaded();

private:
    void setupBlockTextLines();

private:
    QVector<RollScriptBlockTextLineDocument*>  m_vecBlockTextLines;
};
