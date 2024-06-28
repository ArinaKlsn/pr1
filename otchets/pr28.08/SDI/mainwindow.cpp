#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QDataStream>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SDI)
{
    ui->setupUi(this);

    createActions();
    createMenus();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createActions()
{
    saveAsTextAction = new QAction(tr("Save as Text"), this);
    connect(saveAsTextAction, &QAction::triggered, this, &MainWindow::saveAsText);

    loadFromTextAction = new QAction(tr("Load from Text"), this);
    connect(loadFromTextAction, &QAction::triggered, this, &MainWindow::loadFromText);

    saveAsBinaryAction = new QAction(tr("Save as Binary"), this);
    connect(saveAsBinaryAction, &QAction::triggered, this, &MainWindow::saveAsBinary);

    loadFromBinaryAction = new QAction(tr("Load from Binary"), this);
    connect(loadFromBinaryAction, &QAction::triggered, this, &MainWindow::loadFromBinary);
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("File"));
    fileMenu->addAction(saveAsTextAction);
    fileMenu->addAction(loadFromTextAction);
    fileMenu->addAction(saveAsBinaryAction);
    fileMenu->addAction(loadFromBinaryAction);
}

void MainWindow::saveAsText()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save as Text"), "", tr("Text Files (*.txt)"));
    if (fileName.isEmpty()) {
        return;
    }

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, tr("Error"), tr("Cannot save file: ") + file.errorString());
        return;
    }

    QTextStream out(&file);
    out << ui->textEdit->toPlainText();
    file.close();
}

void MainWindow::loadFromText()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Load from Text"), "", tr("Text Files (*.txt)"));
    if (fileName.isEmpty()) {
        return;
    }

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, tr("Error"), tr("Cannot open file: ") + file.errorString());
        return;
    }

    QTextStream in(&file);
    ui->textEdit->setPlainText(in.readAll());
    file.close();
}

void MainWindow::saveAsBinary()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save as Binary"), "", tr("Binary Files (*.bin)"));
    if (fileName.isEmpty()) {
        return;
    }

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::warning(this, tr("Error"), tr("Cannot save file: ") + file.errorString());
        return;
    }

    QDataStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.close();
}

void MainWindow::loadFromBinary()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Load from Binary"), "", tr("Binary Files (*.bin)"));
    if (fileName.isEmpty()) {
        return;
    }

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, tr("Error"), tr("Cannot open file: ") + file.errorString());
        return;
    }

    QDataStream in(&file);
    QString text;
    in >> text;
    ui->textEdit->setPlainText(text);
    file.close();
}
