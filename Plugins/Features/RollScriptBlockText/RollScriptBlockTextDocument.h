#pragma once

#include "Core/Blocks/RollScriptBlockDocumentBase.h"

class RollScriptBlockTextLineDocument;


class RollScriptBlockTextDocument : public RollScriptBlockDocumentBase
{
    Q_OBJECT

public:
    // Constructor / Destructor
    RollScriptBlockTextDocument(const QString& qstrBlockPluginId, QObject* parent);
    ~RollScriptBlockTextDocument() override;

    // Getter
    unsigned int lineCount() const            { return m_qvecBlockTextLines.count(); }
    RollScriptBlockTextLineDocument* textLine(const unsigned int index) const;

    // JSON
    void clear() override;
    bool loadFromJson(const QJsonObject& jsonBlocks) override;
    bool saveToJson(QJsonObject& jsonBlocks) override;

signals:
    void documentCleared();
    void documentLoaded();

private:
    void setupBlockTextLines();
    bool loadVersion_1(const QJsonObject& jsonBlocks);

private:
    QVector<RollScriptBlockTextLineDocument*>  m_qvecBlockTextLines;
};
