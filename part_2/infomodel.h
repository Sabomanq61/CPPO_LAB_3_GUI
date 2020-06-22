#pragma once
#include <QAbstractTableModel>
#include "strategy.h"

class InfoModel : public QAbstractTableModel
{
Q_OBJECT

public:

    InfoModel(QObject* parent = nullptr, std::shared_ptr<ExplorerStrategy::FileList> pointer = nullptr)
        : QAbstractTableModel(parent), pointerData_(pointer)
    {}

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    void SetInfo(std::shared_ptr<ExplorerStrategy::FileList> pointer);

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
private:
    enum NameColumn
    {
        NAME = 0,
        SIZE,
        PERCENT
    };

    std::shared_ptr<ExplorerStrategy::FileList> pointerData_;
};

