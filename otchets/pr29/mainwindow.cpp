#include "mainwindow.h"
// Не нужно повторно включать ui_mainwindow.h здесь, так как он уже включен в mainwindow.h
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
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
    fileMenu = menuBar()->addMenu(tr("FileVibor"));
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
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, tr("Error"), tr("Cannot save file: ") + file.errorString());
        return;
    }

    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << toBinary(text);
    file.close();
}

void MainWindow::loadFromBinary()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Load from Binary"), "", tr("Binary Files (*.bin)"));
    if (fileName.isEmpty()) {
        return;
    }

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, tr("Error"), tr("Cannot open file: ") + file.errorString());
        return;
    }

    QTextStream in(&file);
    QString binaryText = in.readAll();
    ui->textEdit->setPlainText(fromBinary(binaryText));
    file.close();
}

QString MainWindow::toBinary(const QString &text)
{
    QString binaryText;
    for (QChar ch : text) {
        QString binaryChar = QString::number(ch.unicode(), 2).rightJustified(16, '0');
        binaryText.append(binaryChar);
    }
    return binaryText;
}

QString MainWindow::fromBinary(const QString &binaryText)
{
    QString text;
    for (int i = 0; i < binaryText.length(); i += 16) {
        QString binaryChar = binaryText.mid(i, 16);
        QChar ch(binaryChar.toUShort(nullptr, 2));
        text.append(ch);
    }
    return text;
}
