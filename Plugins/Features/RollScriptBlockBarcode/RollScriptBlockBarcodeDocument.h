#pragma once

#include "Core/Blocks/RollScriptBlockDocumentBase.h"


class RollScriptBlockBarcodeDocument : public RollScriptBlockDocumentBase
{
    Q_OBJECT

public:
    // Constructor / Destructor
    RollScriptBlockBarcodeDocument(const QString& qstrBlockPluginId, QObject* parent);
    ~RollScriptBlockBarcodeDocument() override;

    // Getter
    const QString& text() const             { return m_qstrText; }

    // Setter
    void setText(const QString& qstrText);

    // JSON
    void clear() override;
    bool loadFromJson(const QJsonObject& jsonBlocks) override;
    bool saveToJson(QJsonObject& jsonBlocks) override;

signals:
    void documentCleared();
    void documentLoaded();

private:
    bool loadVersion_1(const QJsonObject& jsonBlocks);

private:
    QString         m_qstrText;
};
