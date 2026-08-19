#include "PrinterMedia.h"


PrinterMedia::PrinterMedia(const QString& qstrId, const QString& qstrDisplayName, QObject* parent)
    : QObject{parent}
    , m_qstrId(qstrId)
    , m_qstrDisplayName(qstrDisplayName)
{
}
PrinterMedia::~PrinterMedia()
{
}
