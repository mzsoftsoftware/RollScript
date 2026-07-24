#include "TranslationManager.h"

#include <QApplication>
#include <QDir>

static const char *languageNameTranslation =
    QT_TRANSLATE_NOOP(
        "TranslationManager",
        "Translation.LanguageName"
        );

TranslationManager::TranslationManager(QObject *parent)
    : QObject{parent}
{
    scanTranslations();
}

void TranslationManager::scanTranslations()
{
    QDir resourceDirectory(":/i18n");
    const QStringList translationFiles = resourceDirectory.entryList(
        QStringList() << QStringLiteral("RollScript_*.qm"),
        QDir::Files,
        QDir::Name);

    for (const QString &fileName : translationFiles)
    {
        const QString fullPath = resourceDirectory.filePath(fileName);
        const QString baseName = QFileInfo(fileName).completeBaseName();
        const QString localeName = baseName.mid(QStringLiteral("RollScript_").length());

        const QLocale locale(localeName);
        if (locale == QLocale::c())
        {
            qWarning()
            << "Invalid translation locale:"
            << localeName;
            continue;
        }

        QTranslator translator;
        if (!translator.load(fullPath))
        {
            qWarning()
            << "Could not load translation:"
            << fullPath;
            continue;
        }

        const QString languageName = translator.translate(
                "TranslationManager",
                languageNameTranslation
                );
        if (languageName.isEmpty())
        {
            qWarning()
            << "Translation has no language name:"
            << fullPath;
            continue;
        }

        TranslationInfo info;
        info.qLocale = locale;
        info.qstrLanguageName = languageName;
        info.qstrResourcePath = fullPath;

        m_qhashTranslations.insert(locale, info);

        qDebug()
            << "Found translation:"
            << locale.name()
            << languageName
            << fullPath;
    }
}

bool TranslationManager::loadSystemLanguage()
{
    const QStringList uiLanguages = QLocale::system().uiLanguages();

    for (const QString &language : uiLanguages)
    {
        const QLocale locale(language);
        const auto it = m_qhashTranslations.constFind(locale);
        if (it == m_qhashTranslations.constEnd())
        {
            continue;
        }

        return loadLanguage(locale);
    }

    // Fallback auf Englisch
    const QLocale fallbackLocale(
        QLocale::English,
        QLocale::UnitedStates
        );

    const auto it = m_qhashTranslations.constFind(fallbackLocale);
    if (it == m_qhashTranslations.constEnd())
    {
        qWarning()
        << "No suitable translation found";
        return false;
    }

    return loadLanguage(fallbackLocale);
}

bool TranslationManager::loadLanguage(const QLocale &locale)
{
    const auto it = m_qhashTranslations.constFind(locale);
    if (it == m_qhashTranslations.constEnd())
    {
        qWarning()
        << "Translation not found:"
        << locale.name();
        return false;
    }

    qApp->removeTranslator(&m_translator);
    if (!m_translator.load(it->qstrResourcePath))
    {
        qWarning()
        << "Could not load translation:"
        << it->qstrResourcePath;
        return false;
    }

    qApp->installTranslator(&m_translator);
    m_qLocaleCurrent = locale;

    return true;
}

QList<TranslationInfo> TranslationManager::availableTranslations() const
{
    return m_qhashTranslations.values();
}
