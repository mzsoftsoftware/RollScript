#pragma once

#include <QObject>

#include <QString>

#include "Core/Document/RollScriptDocumentSettings.h"


class RollScriptDocument : public QObject
{
    Q_OBJECT
public:
    explicit RollScriptDocument(QObject *parent = nullptr);

    // Getters
    QString lastError() const                       { return m_qstrLastError; }
    bool isModified() const                         { return m_bModified; }
    QString fileName() const                        { return m_qstrFileName; }

    RollScriptDocumentSettings* settings()          { return &m_settings; }

    // Setters

    // Document handling
    void clear();
    bool load(const QString& qstrFileName);
    bool loadVersion_1(const QJsonObject& jsonRoot);

    bool save();
    bool saveAs(const QString& qstrFileName);

    static QString fileExtension()  { return ".rollscript"; }

signals:
    void documentModifiedChanged(bool bModified);
    void documentFileNameChanged(const QString& qstrFileName);
    void documentCleared();
    void documentLoaded();
    void documentSaved();

    // TASK : void logMessage(const QString& qstrMessage);

private slots:


private:
    void setModified(bool bModified);
    bool loadFromFile(const QString& qstrFileName);
    bool saveToFile(const QString& qstrFileName);

private:
    QString                     m_qstrLastError;
    bool                        m_bModified = false;
    QString                     m_qstrFileName;

    RollScriptDocumentSettings  m_settings;

};
