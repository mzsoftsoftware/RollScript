#include "FeatureBlocksItemDelegate.h"

#include <QPainter>


FeatureBlocksItemDelegate::FeatureBlocksItemDelegate(QObject* parent)
    : QStyledItemDelegate(parent)
{
}

QSize FeatureBlocksItemDelegate::sizeHint(const QStyleOptionViewItem &, const QModelIndex &) const
{
    return QSize(77, 77);
}

void FeatureBlocksItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    painter->save();

    if (option.state & QStyle::State_Selected)
        painter->fillRect(option.rect, option.palette.highlight());

    QIcon icon = qvariant_cast<QIcon>(index.data(Qt::DecorationRole));
    QString text = index.data(Qt::DisplayRole).toString();

    QRect iconRect(option.rect.left(),
                   option.rect.top() + 4,
                   option.rect.width(),
                   48);

    icon.paint(painter, iconRect, Qt::AlignCenter);

    QRect textRect(option.rect.left(),
                   option.rect.top() + 56,
                   option.rect.width(),
                   20);

    painter->drawText(textRect, Qt::AlignCenter, text);

    painter->restore();
}
