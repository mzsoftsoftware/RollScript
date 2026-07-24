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

    QList<TranslationInfo> availableTranslations() const;
    bool loadSystemLanguage();
    bool loadLanguage(const QLocale &locale);

    QLocale currentLocale() const                   { return m_qLocaleCurrent; }

private:
    void scanTranslations();

private:
    QTranslator m_translator;
    QHash<QLocale, TranslationInfo> m_qhashTranslations;
    QLocale m_qLocaleCurrent;
};
