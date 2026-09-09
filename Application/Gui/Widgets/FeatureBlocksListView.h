#pragma once

#include <QListView>


class FeatureBlocksListView : public QListView
{
    Q_OBJECT

public:
    explicit FeatureBlocksListView(QWidget* parent);
    ~FeatureBlocksListView() override;

protected:
    QSize viewportSizeHint() const override;
};
