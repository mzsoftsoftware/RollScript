#include "RollScriptBlockTextDocument.h"

#include <QJsonObject>
#include <QJsonArray>
#include "RollScriptBlockTextLineDocument.h"


RollScriptBlockTextDocument::RollScriptBlockTextDocument(const QString& qstrBlockPluginId, QObject* parent)
    : RollScriptBlockDocumentBase(qstrBlockPluginId, parent)
{
    setupBlockTextLines();
}
RollScriptBlockTextDocument::~RollScriptBlockTextDocument()
{
}

RollScriptBlockTextLineDocument* RollScriptBlockTextDocument::textLine(const unsigned int index) const
{
    Q_ASSERT(index<4);

    return m_qvecBlockTextLines[index];
}

void RollScriptBlockTextDocument::setupBlockTextLines()
{
    RollScriptBlockTextLineDocument* ptrBlockTextLine = nullptr;

    ptrBlockTextLine = new RollScriptBlockTextLineDocument(this);
    ptrBlockTextLine->setLineActive(true);
    connect(ptrBlockTextLine, &RollScriptBlockTextLineDocument::blockTextLineChanged, this, &RollScriptBlockTextDocument::blockChanged);
    m_qvecBlockTextLines.append(ptrBlockTextLine);

    ptrBlockTextLine = new RollScriptBlockTextLineDocument(this);
    connect(ptrBlockTextLine, &RollScriptBlockTextLineDocument::blockTextLineChanged, this, &RollScriptBlockTextDocument::blockChanged);
    m_qvecBlockTextLines.append(ptrBlockTextLine);

    ptrBlockTextLine = new RollScriptBlockTextLineDocument(this);
    connect(ptrBlockTextLine, &RollScriptBlockTextLineDocument::blockTextLineChanged, this, &RollScriptBlockTextDocument::blockChanged);
    m_qvecBlockTextLines.append(ptrBlockTextLine);

    ptrBlockTextLine = new RollScriptBlockTextLineDocument(this);
    connect(ptrBlockTextLine, &RollScriptBlockTextLineDocument::blockTextLineChanged, this, &RollScriptBlockTextDocument::blockChanged);
    m_qvecBlockTextLines.append(ptrBlockTextLine);
}

void RollScriptBlockTextDocument::clear()
{
    for(RollScriptBlockTextLineDocument* ptrBlockTextLine : m_qvecBlockTextLines)
    {
        ptrBlockTextLine->clear();
    }
    emit documentCleared();
}
bool RollScriptBlockTextDocument::loadFromJson(const QJsonObject& jsonBlockText)
{
    const int iVersion = jsonBlockText[QStringLiteral("version")].toInt();
    switch(iVersion)
    {
    case 1:
        return loadVersion_1(jsonBlockText);
        break;
    default:
        ROLLSCRIPT_ERROR(tr("DocumentBlockText.LoadFromFile.Json.Version.Error").arg(iVersion), QStringLiteral("version is unknown."));
        return false;
    }
}
bool RollScriptBlockTextDocument::loadVersion_1(const QJsonObject& jsonBlockText)
{
    QJsonArray linesArray = jsonBlockText[QStringLiteral("lines")].toArray();
    for(int index=0; index<linesArray.count(); index++)
    {
        if(!m_qvecBlockTextLines[index]->loadFromJson(linesArray[index].toObject()))
        {
            ROLLSCRIPT_ERROR_CAUSE(tr("DocumentBlockText.LoadFromFile.Json.Error"), QStringLiteral("m_vecBlockTextLines->loadFromJson failed."), m_qvecBlockTextLines[index]->takeError());
            return false;
        }
    }
    emit documentLoaded();

    return true;
}
bool RollScriptBlockTextDocument::saveToJson(QJsonObject& jsonBlockText)
{
    jsonBlockText[QStringLiteral("version")] = 1;
    QJsonArray linesArray;
    for(RollScriptBlockTextLineDocument* ptrBlockTextLine : m_qvecBlockTextLines)
    {
        QJsonObject line;
        if(!ptrBlockTextLine->saveToJson(line))
        {
            return false;
        }
        linesArray.append(line);
    }
    jsonBlockText[QStringLiteral("lines")] = linesArray;

    return true;
}
