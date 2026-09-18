#pragma once

#include "Core/Blocks/RollScriptBlockDocumentBase.h"


class RollScriptBlockImageDocument : public RollScriptBlockDocumentBase
{
    Q_OBJECT

public:
    // Constructor / Destructor
    RollScriptBlockImageDocument(const QString& qstrBlockPluginId, QObject* parent);
    ~RollScriptBlockImageDocument() override;

    // Getter
    const QString& fileName() const             { return m_qstrFileName; }

    // Setter
    void setFileName(const QString& qstrFileName);

    // JSON
    void clear() override;
    bool loadFromJson(const QJsonObject& jsonBlockImage) override;
    bool saveToJson(QJsonObject& jsonBlockImage) override;

signals:
    void documentCleared();
    void documentLoaded();

private:
    bool loadVersion_1(const QJsonObject& jsonBlockImage);

private:
    QString     m_qstrFileName;
};
