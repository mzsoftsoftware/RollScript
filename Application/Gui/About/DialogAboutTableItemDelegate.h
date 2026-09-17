#pragma once

#include <QStyledItemDelegate>


class DialogAboutTableItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    enum ItemDataRole
    {
        DescriptionRole = Qt::UserRole,
        ValueRole
    };

    explicit DialogAboutTableItemDelegate(QObject* parent);

protected:
    void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
    QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const override;
};
