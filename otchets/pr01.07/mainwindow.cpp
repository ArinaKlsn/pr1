#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMouseEvent>
#include <QPainter>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , drawing(false)
{
    ui->setupUi(this);

    // Создание действий для меню
    QAction *actionSave = new QAction(tr("&Save"), this);
    QAction *actionLoad = new QAction(tr("&Load"), this);

    // Подключение сигналов к слотам
    connect(actionSave, &QAction::triggered, this, &MainWindow::saveToFile);
    connect(actionLoad, &QAction::triggered, this, &MainWindow::loadFromFile);

    // Создание меню
    QMenuBar *menuBar = new QMenuBar(this);
    QMenu *fileMenu = menuBar->addMenu(tr("&File"));
    fileMenu->addAction(actionSave);
    fileMenu->addAction(actionLoad);

    setMenuBar(menuBar);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        startPoint = event->pos();
        currentPoint = startPoint;  // Инициализация currentPoint
        drawing = true;
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (drawing) {
        currentPoint = event->pos();
        tempLine = QLine(startPoint, currentPoint);
        update();
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && drawing) {
        lines.append(QLine(startPoint, event->pos()));
        drawing = false;
        update();
    }
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    for (const QLine &line : lines) {
        painter.drawLine(line);
    }
    if (drawing) {
        painter.drawLine(tempLine);  // Рисуем временную линию
    }
}

void MainWindow::saveToFile()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), "", tr("Text Files (*.txt);;All Files (*)"));
    if (fileName.isEmpty()) {
        return;
    }

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly)) {
        return;
    }

    QTextStream out(&file);
    for (const QLine &line : lines) {
        out << line.x1() << " " << line.y1() << " " << line.x2() << " " << line.y2() << "\n";
    }
    file.close();
}

void MainWindow::loadFromFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Text Files (*.txt);;All Files (*)"));
    if (fileName.isEmpty()) {
        return;
    }

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        return;
    }

    QTextStream in(&file);
    lines.clear();
    while (!in.atEnd()) {
        int x1, y1, x2, y2;
        in >> x1 >> y1 >> x2 >> y2;
        lines.append(QLine(x1, y1, x2, y2));
    }
    file.close();
    update();
}
