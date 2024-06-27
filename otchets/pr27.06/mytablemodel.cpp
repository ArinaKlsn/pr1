// mytablemodel.cpp
#include "mytablemodel.h"

MyTableModel::MyTableModel(QObject *parent)
    : QAbstractTableModel(parent) {
    m_data = {
        { "Item 1", 10 },
        { "Item 2", 20 },
        { "Item 3", 30 }
    };
}

int MyTableModel::rowCount(const QModelIndex &parent) const {
    return parent.isValid() ? 0 : m_data.size();
}

int MyTableModel::columnCount(const QModelIndex &parent) const {
    return parent.isValid() ? 0 : m_data[0].size();
}

QVariant MyTableModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid() || role != Qt::DisplayRole && role != Qt::EditRole)
        return QVariant();

    return m_data[index.row()][index.column()];
}

bool MyTableModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    if (index.isValid() && role == Qt::EditRole) {
        m_data[index.row()][index.column()] = value;
        emit dataChanged(index, index, {role});
        return true;
    }
    return false;
}

Qt::ItemFlags MyTableModel::flags(const QModelIndex &index) const {
    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

void MyTableModel::updateData(const std::vector<std::vector<QVariant>> &newData) {
    beginResetModel();
    m_data = newData;
    endResetModel();
}
