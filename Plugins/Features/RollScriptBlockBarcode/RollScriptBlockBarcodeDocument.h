#pragma once

#include "Core/Blocks/RollScriptBlockDocumentBase.h"


class RollScriptBlockBarcodeDocument : public RollScriptBlockDocumentBase
{
    Q_OBJECT

public:
    // Constructor / Destructor
    RollScriptBlockBarcodeDocument(const QString& qstrBlockPluginId, QObject* parent);
    ~RollScriptBlockBarcodeDocument() override;

    // JSON
    void clear() override;
    bool loadFromJson(const QJsonObject& jsonBlocks) override;
    bool saveToJson(QJsonObject& jsonBlocks) override;
};
