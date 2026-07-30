#pragma once

#include <QObject>
#include <QTranslator>
#include <QLocale>


struct TranslationInfo
{
    QLocale qLocale;
    QString qstrLanguageName;
    QString qstrResourcePath;
};

class TranslationManager : public QObject
{
    Q_OBJECT

public:
    explicit TranslationManager(QObject *parent = nullptr);

    bool init();

    QList<TranslationInfo> availableTranslations() const;
    bool loadLanguage(const QLocale &locale);

    // Getter
    QString lastError() const                       { return m_qstrLastError; }
    QLocale currentLocale() const                   { return m_qLocaleCurrent; }

private:
    bool loadSystemLanguage();
    void scanTranslations();

private:
    QString m_qstrLastError;

    QTranslator m_translator;
    QTranslator m_qtTranslator;
    QHash<QLocale, TranslationInfo> m_qhashTranslations;
    QLocale m_qLocaleCurrent;
};
