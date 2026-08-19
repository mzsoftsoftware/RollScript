#include "RollScriptBlock.h"


RollScriptBlock::RollScriptBlock(const QString& qstrTypeId, QObject* parent)
    : QObject(parent)
    , m_qstrTypeId(qstrTypeId)
{
}

RollScriptBlock::~RollScriptBlock()
{
}