#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    model(new MyTableModel(this))

{
    ui->setupUi(this);
    ui->tableView->setModel(model);

    // Проверяем наличие действий в ui
    if (ui->actionSave) {
        connect(ui->actionSave, &QAction::triggered, this, &MainWindow::on_actionSave_triggered);
    } else {
        qDebug() << "actionSave not found in ui";
    }

    if (ui->actionLoad) {
        connect(ui->actionLoad, &QAction::triggered, this, &MainWindow::on_actionLoad_triggered);
    } else {
        qDebug() << "actionLoad not found in ui";
    }


pinkButton = new QPushButton("Save", this);
pinkButton->setGeometry(100, 300, 100, 30); // Измените геометрию кнопки по необходимости
pinkButton->setStyleSheet("QPushButton { background-color: pink; }");

connect(pinkButton, &QPushButton::clicked, this, &MainWindow::onPinkButtonClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionSave_triggered() {
    QString filePath = "D:/taba/data.txt";
    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        for (int row = 0; row < model->rowCount(); ++row) {
            for (int col = 0; col < model->columnCount(); ++col) {
                out << model->data(model->index(row, col)).toString() << "\t";
            }
            out << "\n";
        }
        file.close();
    } else {
        qDebug() << "Could not open file for writing.";
    }
}

void MainWindow::on_actionLoad_triggered() {
    QString filePath = "D:/taba/data.txt";
    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        std::vector<std::vector<QVariant>> newData;
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList fields = line.split("\t", Qt::SkipEmptyParts);
            std::vector<QVariant> row;
            for (const QString &field : fields) {
                row.push_back(field);
            }
            newData.push_back(row);
        }
        model->updateData(newData);
        file.close();
    } else {
        qDebug() << "Could not open file for reading.";
    }
}
void MainWindow::onPinkButtonClicked()
{
    QString filePath = "D:/taba/data.txt";

    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Could not open file for writing:" << file.errorString();
        return;
    }
    QTextStream out(&file);

    // Запись данных из модели в файл
    for (int row = 0; row < model->rowCount(); ++row) {
        for (int col = 0; col < model->columnCount(); ++col) {
            QModelIndex index = model->index(row, col);
            QVariant data = model->data(index);
            out << data.toString();
            if (col < model->columnCount() - 1)
                out << ", ";
        }
        out << "\n";
    }

    file.close();
}
