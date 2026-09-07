#include "TranslationManager.h"

#include <QApplication>
#include <QDir>
#include <QLibraryInfo>


static const char* languageNameTranslation = QT_TRANSLATE_NOOP("TranslationManager", "Translation.LanguageName");

TranslationManager::TranslationManager(QObject* parent)
    : QObject{parent}
{
}
TranslationManager::~TranslationManager()
{
}

bool TranslationManager::init()
{
    scanTranslations();
    return loadSystemLanguage();
}

void TranslationManager::scanTranslations()
{
    QDir resourceDirectory(QStringLiteral(":/i18n"));
    const QStringList translationFiles = resourceDirectory.entryList(
        QStringList() << QStringLiteral("RollScript_*.qm"),
        QDir::Files,
        QDir::Name);

    for (const QString& fileName : translationFiles)
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
    }
}

bool TranslationManager::loadSystemLanguage()
{
    const QStringList uiLanguages = QLocale::system().uiLanguages();

    for (const QString& language : uiLanguages)
    {
        const QLocale locale(language);
        const QHash<QLocale, TranslationInfo>::const_iterator it = m_qhashTranslations.constFind(locale);
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

    const QHash<QLocale, TranslationInfo>::const_iterator it = m_qhashTranslations.constFind(fallbackLocale);
    if (it == m_qhashTranslations.constEnd())
    {
        qWarning()
        << "No suitable translation found";
        return false;
    }

    return loadLanguage(fallbackLocale);
}

bool TranslationManager::loadLanguage(const QLocale& locale)
{
    const QHash<QLocale, TranslationInfo>::const_iterator it = m_qhashTranslations.constFind(locale);
    if (it == m_qhashTranslations.constEnd())
    {
        qWarning()
        << "Translation not found:"
        << locale.name();
        return false;
    }

    // Plugin-Translator entfernen
    QHash<QString, QTranslator*>::iterator itPluginTranslator = m_qhashPluginTranslators.begin();
    while(itPluginTranslator != m_qhashPluginTranslators.end())
    {
        qApp->removeTranslator(itPluginTranslator.value());
        ++itPluginTranslator;
    }

    // Hauptübersetzungen entfernen
    qApp->removeTranslator(&m_qtTranslator);
    qApp->removeTranslator(&m_translator);

    QLocale::setDefault(locale);

    // RollScript-Übersetzung
    if (!m_translator.load(it->qstrResourcePath))
    {
        qWarning()
        << "Could not load translation:"
        << it->qstrResourcePath;
        return false;
    }
    qApp->installTranslator(&m_translator);

    // Qt-Übersetzung
    if(!m_qtTranslator.load(locale, QStringLiteral("qtbase"), QStringLiteral("_"), QLibraryInfo::path(QLibraryInfo::TranslationsPath)))
    {
        qWarning()
        << "Could not load translation:"
        << QLibraryInfo::path(QLibraryInfo::TranslationsPath);
        return false;
    }
    qApp->installTranslator(&m_qtTranslator);

    // Plugin-Übersetzungen
    itPluginTranslator = m_qhashPluginTranslators.begin();
    while(itPluginTranslator != m_qhashPluginTranslators.end())
    {
        QTranslator* ptrTranslator = itPluginTranslator.value();
        const QString qstrResourcePath = QStringLiteral(":/i18n/%1_%2.qm").arg(itPluginTranslator.key(), locale.name());
        if(!ptrTranslator->load(qstrResourcePath))
        {
            qWarning()
            << "Could not load plugin translation:"
            << qstrResourcePath;
        }
        else
        {
            qApp->installTranslator(ptrTranslator);
        }

        ++itPluginTranslator;
    }

    m_qLocaleCurrent = locale;

    return true;
}

QList<TranslationInfo> TranslationManager::availableTranslations() const
{
    return m_qhashTranslations.values();
}

bool TranslationManager::loadPluginTranslation( const QString& qstrPluginFileName)
{
    QFileInfo pluginFileInfo(qstrPluginFileName);
    QString qstrPluginName = pluginFileInfo.completeBaseName();

    // Unter Linux/Unix entfernt completeBaseName()
    // den Suffix .so, aber nicht den lib-Prefix.
    if(qstrPluginName.startsWith(QStringLiteral("lib")))
    {
        qstrPluginName = qstrPluginName.mid(3);
    }
    if(qstrPluginName.isEmpty())
    {
        qWarning() << "Could not determine plugin name from:" << qstrPluginFileName;
        return false;
    }
    if(m_qhashPluginTranslators.contains(qstrPluginName))
    {
        qWarning() << "Plugin translation already registered:" << qstrPluginName;
        return true;
    }

    QTranslator* ptrTranslator = new QTranslator(this);
    const QString qstrResourcePath = QStringLiteral(":/i18n/%1_%2.qm") .arg( qstrPluginName, m_qLocaleCurrent.name());
    if(!ptrTranslator->load(qstrResourcePath))
    {
        qWarning() << "Could not load plugin translation:" << qstrResourcePath;
        delete ptrTranslator;
        return false;
    }
    qApp->installTranslator(ptrTranslator);
    m_qhashPluginTranslators.insert( qstrPluginName, ptrTranslator);
    return true;
}
