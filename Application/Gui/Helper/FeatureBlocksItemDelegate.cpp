#include "FeatureBlocksItemDelegate.h"

#include <QPainter>


FeatureBlocksItemDelegate::FeatureBlocksItemDelegate(QObject* parent)
    : QStyledItemDelegate(parent)
{
}

QSize FeatureBlocksItemDelegate::sizeHint(const QStyleOptionViewItem &, const QModelIndex &) const
{
    constexpr int iconSize = 48;
    constexpr int textHeight = 20;
    constexpr int topMargin = 4;
    constexpr int spacing = 4;

    return QSize(77, topMargin + iconSize + spacing + textHeight);
}

void FeatureBlocksItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    painter->save();

    if (option.state & QStyle::State_Selected)
        painter->fillRect(option.rect, option.palette.highlight());

    QIcon icon = qvariant_cast<QIcon>(index.data(Qt::DecorationRole));
    QString text = index.data(Qt::DisplayRole).toString();

    constexpr int iconSize = 48;
    constexpr int textHeight = 20;

    QRect iconRect(option.rect.left(), option.rect.top() + 4, option.rect.width(), iconSize);
    icon.paint(painter, iconRect, Qt::AlignCenter, QIcon::Normal, QIcon::On);

    QRect textRect(option.rect.left(), option.rect.top() + iconSize + 4, option.rect.width(), textHeight);
    painter->drawText(textRect, Qt::AlignCenter, text);

    painter->restore();
}
