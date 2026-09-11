#include "DialogAboutTableItemDelegate.h"

#include <QPainter>


DialogAboutTableItemDelegate::DialogAboutTableItemDelegate(QObject* parent)
 : QStyledItemDelegate(parent)
{
}

void DialogAboutTableItemDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    painter->save();

    const QStyleOptionViewItem opt = option;
    const QRect rect = opt.rect;

    if (index.column() == 0)
    {
        const QString title = index.data(Qt::DisplayRole).toString();
        const QString description = index.data(DescriptionRole).toString();
        const QIcon icon = index.data(Qt::DecorationRole).value<QIcon>();

        const int margin = 8;
        const int iconSize = 24;
        const int iconSpacing = 8;

        int textLeft = rect.left() + margin;
        if (!icon.isNull())
        {
            const QRect iconRect(textLeft, rect.top() + (rect.height() - iconSize) / 2, iconSize, iconSize);
            icon.paint(painter, iconRect, Qt::AlignCenter, QIcon::Normal);
            textLeft += iconSize + iconSpacing;
        }

        const QRect textRect(textLeft, rect.top() + margin, rect.right() - textLeft - margin, rect.height() - 2 * margin);
        QFont titleFont = painter->font();
        titleFont.setBold(true);

        painter->setFont(titleFont);
        painter->setPen(opt.palette.color(QPalette::Text));

        QFontMetrics titleMetrics(titleFont);
        const int titleHeight = titleMetrics.height();

        painter->drawText(QRect(textRect.left(), textRect.top(), textRect.width(), titleHeight),
                            Qt::AlignLeft | Qt::AlignVCenter, title);

        QFont descriptionFont = painter->font();
        descriptionFont.setBold(false);

        painter->setFont(descriptionFont);
        painter->setPen(opt.palette.color(QPalette::PlaceholderText));

        painter->drawText(QRect(textRect.left(), textRect.top() + titleHeight + 2, textRect.width(), textRect.height() - titleHeight - 2),
                            Qt::AlignLeft | Qt::AlignTop, description);
    }
    else if (index.column() == 1)
    {
        const QString value = index.data(Qt::DisplayRole).toString();

        painter->setFont(opt.font);
        painter->setPen(opt.palette.color(QPalette::Text));

        painter->drawText(rect.adjusted(8, 0, -8, 0), Qt::AlignRight | Qt::AlignVCenter, value);
    }

    painter->restore();
}

QSize DialogAboutTableItemDelegate::sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    Q_UNUSED(index);

    QFont titleFont = option.font;
    titleFont.setBold(true);

    QFont descriptionFont = option.font;
    descriptionFont.setBold(false);

    const QFontMetrics titleMetrics(titleFont);
    const QFontMetrics descriptionMetrics(descriptionFont);

    const int height = titleMetrics.height() + descriptionMetrics.height() + 10;

    if (index.column() == 1)
    {
        const QString value = index.data(Qt::DisplayRole).toString();
        const int width = option.fontMetrics.horizontalAdvance(value) + 16;
        return QSize(width, height);
    }

    return QSize(0, height);
}
