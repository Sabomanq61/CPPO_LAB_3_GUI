#include "infomodel.h"

const int numberColumn = 3;

int InfoModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    if(pointerData_)
        return pointerData_->size();
    return 0;
}

int InfoModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return numberColumn;
}

void InfoModel::SetInfo(std::shared_ptr<ExplorerStrategy::FileList> pointer)
{
    pointerData_ = pointer;
}

QVariant InfoModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Vertical)
        return section;

    switch (section)
    {
    case NAME:  return trUtf8("Название");

    case SIZE:  return trUtf8("Размер");

    case PERCENT:  return trUtf8("В процентах");
    }
    return QVariant();
}

QVariant InfoModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid() || pointerData_->size() <= index.row() || (role != Qt::DisplayRole && role != Qt::EditRole) || !pointerData_)
        return QVariant();

    if(index.column() == 0)
        return pointerData_->operator[](index.row()).name_;
    else if(index.column() == 1)
        return pointerData_->operator[](index.row()).size_;
    else
        return pointerData_->operator[](index.row()).percent_;

}














