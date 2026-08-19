#pragma once

#include <QStyledItemDelegate>


class FeatureBlocksItemDelegate : public QStyledItemDelegate
{
public:
    FeatureBlocksItemDelegate(QObject* parent);

    QSize sizeHint(const QStyleOptionViewItem &, const QModelIndex &) const override;

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index ) const override;
};
