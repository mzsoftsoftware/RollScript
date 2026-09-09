#include "FeatureBlocksListView.h"

#include <QScrollBar>
#include <QStyleOptionViewItem>


FeatureBlocksListView::FeatureBlocksListView(QWidget* parent)
    : QListView(parent)
{
}

FeatureBlocksListView::~FeatureBlocksListView()
{
}

QSize FeatureBlocksListView::viewportSizeHint() const
{
    QSize size = QListView::viewportSizeHint();

    QStyleOptionViewItem option;
    option.initFrom(this);

    const int itemHeight =
        itemDelegate()->sizeHint(
                          option,
                          QModelIndex()
                          ).height();

    size.setHeight(itemHeight);

    if (horizontalScrollBar()->isVisible())
    {
        size.rheight() += horizontalScrollBar()->sizeHint().height();
    }

    return size;
}

