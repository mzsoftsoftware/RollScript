#pragma once

#include <QStyledItemDelegate>


class FeatureBlocksItemDelegate : public QStyledItemDelegate
{
public:
    // Constructor / Destructor
    explicit FeatureBlocksItemDelegate(QObject* parent);
    ~FeatureBlocksItemDelegate() override;

    // Operations
    QSize sizeHint(const QStyleOptionViewItem&, const QModelIndex&) const override;
    void paint(QPainter* ptrPainter, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
};
