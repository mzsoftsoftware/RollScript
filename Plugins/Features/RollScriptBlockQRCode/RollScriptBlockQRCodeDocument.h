#pragma once

#include "Core/Blocks/RollScriptBlockDocumentBase.h"


class RollScriptBlockQRCodeDocument : public RollScriptBlockDocumentBase
{
    Q_OBJECT

public:
    // Constructor / Destructor
    RollScriptBlockQRCodeDocument(const QString& qstrBlockPluginId, QObject* parent);
    ~RollScriptBlockQRCodeDocument() override;

    // JSON
    void clear() override;
    bool loadFromJson(const QJsonObject& jsonBlocks) override;
    bool saveToJson(QJsonObject& jsonBlocks) override;
};
