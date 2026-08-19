#pragma once

#include <QObject>
#include "Core/Errors/RollScriptErrorOwner.h"

#include <QString>

class RollScriptDocumentSettings;
class RollScriptDocumentBlocks;


class RollScriptDocument : public QObject, public RollScriptErrorOwner
{
    Q_OBJECT
public:
    explicit RollScriptDocument(QObject* parent = nullptr);

    // Getters
    bool isModified() const                   { return m_bModified; }
    QString fileName() const                  { return m_qstrFileName; }

    RollScriptDocumentSettings* settings()          { return m_ptrSettings; }
    RollScriptDocumentBlocks* blocks()              { return m_ptrBlocks; }

    // Setters

    // Document handling
    void clear();
    bool load(const QString& qstrFileName);
    bool loadVersion_1(const QJsonObject& jsonRoot);

    bool save();
    bool saveAs(const QString& qstrFileName);

    static QString fileExtension()  { return QStringLiteral(".rollscript"); }

signals:
    void documentModifiedChanged(bool bModified);
    void documentFileNameChanged(const QString& qstrFileName);
    void documentCleared();
    void documentLoaded();
    void documentSaved();

private slots:
    void slotSettingsChanged();
    void slotBlocksChanged();

private:
    void setModified(bool bModified);
    bool loadFromFile(const QString& qstrFileName);
    bool saveToFile(const QString& qstrFileName);

private:
    bool                        m_bModified = false;
    QString                     m_qstrFileName;

    RollScriptDocumentSettings* m_ptrSettings;
    RollScriptDocumentBlocks* m_ptrBlocks;
};
