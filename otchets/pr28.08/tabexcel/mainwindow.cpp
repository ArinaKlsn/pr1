#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QStandardItemModel>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QToolBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , model(new QStandardItemModel(this))
{
    ui->setupUi(this);

    ui->tableView->setModel(model);

    // Создаем начальную таблицу 5x5
    model->setRowCount(5);
    model->setColumnCount(5);

    createActions();
    createMenus();

    // Создаем ToolBar и добавляем кнопки
    mainToolBar = addToolBar("Main Toolbar");
    addRowButton = new QPushButton("Add Row", this);
    addColumnButton = new QPushButton("Add Column", this);
    removeRowButton = new QPushButton("Remove Row", this);
    removeColumnButton = new QPushButton("Remove Column", this);

    connect(addRowButton, &QPushButton::clicked, this, &MainWindow::addRow);
    connect(addColumnButton, &QPushButton::clicked, this, &MainWindow::addColumn);
    connect(removeRowButton, &QPushButton::clicked, this, &MainWindow::removeRow);
    connect(removeColumnButton, &QPushButton::clicked, this, &MainWindow::removeColumn);

    mainToolBar->addWidget(addRowButton);
    mainToolBar->addWidget(addColumnButton);
    mainToolBar->addWidget(removeRowButton);
    mainToolBar->addWidget(removeColumnButton);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createActions()
{
    saveAsCSVAction = new QAction(tr("Save as CSV"), this);
    connect(saveAsCSVAction, &QAction::triggered, this, &MainWindow::saveAsCSV);

    loadFromCSVAction = new QAction(tr("Load from CSV"), this);
    connect(loadFromCSVAction, &QAction::triggered, this, &MainWindow::loadFromCSV);
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("File"));
    fileMenu->addAction(saveAsCSVAction);
    fileMenu->addAction(loadFromCSVAction);
}

void MainWindow::saveAsCSV()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save as CSV"), "", tr("CSV Files (*.csv)"));
    if (fileName.isEmpty()) {
        return;
    }

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, tr("Error"), tr("Could not open file for writing"));
        return;
    }

    QTextStream out(&file);
    for (int row = 0; row < model->rowCount(); ++row) {
        for (int col = 0; col < model->columnCount(); ++col) {
            QStandardItem *item = model->item(row, col);
            out << (item ? item->text() : "") << (col == model->columnCount() - 1 ? "\n" : ",");
        }
    }

    file.close();
}

void MainWindow::loadFromCSV()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Load from CSV"), "", tr("CSV Files (*.csv)"));
    if (fileName.isEmpty()) {
        return;
    }

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, tr("Error"), tr("Could not open file for reading"));
        return;
    }

    model->clear();
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList values = line.split(',');
        QList<QStandardItem *> items;
        for (const QString &value : values) {
            items.append(new QStandardItem(value));
        }
        model->appendRow(items);
    }

    file.close();
}

void MainWindow::addRow()
{
    model->insertRow(model->rowCount());
}

void MainWindow::addColumn()
{
    model->insertColumn(model->columnCount());
}

void MainWindow::removeRow()
{
    model->removeRow(model->rowCount() - 1);
}

void MainWindow::removeColumn()
{
    model->removeColumn(model->columnCount() - 1);
}
