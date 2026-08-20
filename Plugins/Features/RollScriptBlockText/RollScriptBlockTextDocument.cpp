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

    return m_vecBlockTextLines[index];
}

void RollScriptBlockTextDocument::setupBlockTextLines()
{
    RollScriptBlockTextLineDocument* ptrBlockTextLine = nullptr;

    ptrBlockTextLine = new RollScriptBlockTextLineDocument(this);
    ptrBlockTextLine->setLineActive(true);
    connect(ptrBlockTextLine, &RollScriptBlockTextLineDocument::blockTextLineChanged, this, &RollScriptBlockTextDocument::blockChanged);
    m_vecBlockTextLines.append(ptrBlockTextLine);

    ptrBlockTextLine = new RollScriptBlockTextLineDocument(this);
    connect(ptrBlockTextLine, &RollScriptBlockTextLineDocument::blockTextLineChanged, this, &RollScriptBlockTextDocument::blockChanged);
    m_vecBlockTextLines.append(ptrBlockTextLine);

    ptrBlockTextLine = new RollScriptBlockTextLineDocument(this);
    connect(ptrBlockTextLine, &RollScriptBlockTextLineDocument::blockTextLineChanged, this, &RollScriptBlockTextDocument::blockChanged);
    m_vecBlockTextLines.append(ptrBlockTextLine);

    ptrBlockTextLine = new RollScriptBlockTextLineDocument(this);
    connect(ptrBlockTextLine, &RollScriptBlockTextLineDocument::blockTextLineChanged, this, &RollScriptBlockTextDocument::blockChanged);
    m_vecBlockTextLines.append(ptrBlockTextLine);
}

void RollScriptBlockTextDocument::clear()
{
    for(RollScriptBlockTextLineDocument* ptrBlockTextLine : m_vecBlockTextLines)
    {
        ptrBlockTextLine->clear();
    }
}
bool RollScriptBlockTextDocument::loadFromJson(const QJsonObject& jsonBlocks)
{
    QJsonArray linesArray = jsonBlocks[QStringLiteral("lines")].toArray();
    for(int index=0; index<linesArray.count(); index++)
    {
        if(!m_vecBlockTextLines[index]->loadFromJson(linesArray[index].toObject()))
        {
            return false;
        }
    }

    return true;
}
bool RollScriptBlockTextDocument::saveToJson(QJsonObject& jsonBlocks) const
{
    QJsonArray linesArray;
    for(RollScriptBlockTextLineDocument* ptrBlockTextLine : m_vecBlockTextLines)
    {
        QJsonObject line;
        if(!ptrBlockTextLine->saveToJson(line))
        {
            return false;
        }
        linesArray.append(line);
    }
    jsonBlocks[QStringLiteral("lines")] = linesArray;

    return true;
}
