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
    explicit TranslationManager(QObject* parent = nullptr);

    bool init();

    QList<TranslationInfo> availableTranslations() const;
    bool loadLanguage(const QLocale &locale);

    // Getter
    QLocale currentLocale() const                   { return m_qLocaleCurrent; }

private:
    bool loadSystemLanguage();
    void scanTranslations();

private:
    QTranslator m_translator;
    QTranslator m_qtTranslator;
    QHash<QLocale, TranslationInfo> m_qhashTranslations;
    QLocale m_qLocaleCurrent;
};
