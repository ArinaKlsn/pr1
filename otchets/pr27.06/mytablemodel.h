#ifndef MYTABLEMODEL_H
#define MYTABLEMODEL_H

#include <QAbstractTableModel>
#include <vector>

class MyTableModel : public QAbstractTableModel {
    Q_OBJECT

public:
    MyTableModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;

    void updateData(const std::vector<std::vector<QVariant>> &newData);

private:
    std::vector<std::vector<QVariant>> m_data;
};

#endif // MYTABLEMODEL_H
