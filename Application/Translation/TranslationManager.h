#pragma once

#include <QObject>
#include "Core/Errors/RollScriptErrorOwner.h"

#include <QTranslator>
#include <QLocale>


struct TranslationInfo
{
    QLocale qLocale;
    QString qstrLanguageName;
    QString qstrResourcePath;
};

class TranslationManager : public QObject, public RollScriptErrorOwner
{
    Q_OBJECT

public:
    explicit TranslationManager(QObject* parent);
    ~TranslationManager() override;

    // Getter
    QLocale currentLocale() const                   { return m_qLocaleCurrent; }
    QList<TranslationInfo> availableTranslations() const;

    // Operations
    bool init();

    bool loadLanguage(const QLocale& locale);
    bool loadPluginTranslation(const QString& qstrPluginFileName);

private:
    bool loadSystemLanguage();
    void scanTranslations();

private:
    QTranslator m_translator;
    QTranslator m_qtTranslator;

    QHash<QLocale, TranslationInfo> m_qhashTranslations;
    QHash<QString, QTranslator*> m_qhashPluginTranslators;

    QLocale m_qLocaleCurrent;
};
