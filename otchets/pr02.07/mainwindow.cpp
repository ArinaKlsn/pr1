#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qshape.h"
#include <QMouseEvent>
#include <QPainter>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QColorDialog>
#include <QBrush>
#include <QToolBar>
#include <QAction>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , drawing(false)
    , currentColor(Qt::black)
    , currentShape(Line)
    , fillShapes(false)
{
    ui->setupUi(this);

    QAction *actionSave = new QAction(tr("&Save"), this);
    QAction *actionLoad = new QAction(tr("&Load"), this);
    QAction *actionSetColor = new QAction(tr("&Set Color"), this);
    QAction *actionSetBrush = new QAction(tr("&Set Brush"), this);
    QAction *actionUndo = new QAction(tr("&Undo"), this);

    connect(actionSave, &QAction::triggered, this, &MainWindow::saveToFile);
    connect(actionLoad, &QAction::triggered, this, &MainWindow::loadFromFile);
    connect(actionSetColor, &QAction::triggered, this, &MainWindow::setColor);
    connect(actionSetBrush, &QAction::triggered, this, &MainWindow::setBrush);
    connect(actionUndo, &QAction::triggered, this, &MainWindow::undo);

    QMenuBar *menuBar = new QMenuBar(this);
    QMenu *fileMenu = menuBar->addMenu(tr("&File"));
    fileMenu->addAction(actionSave);
    fileMenu->addAction(actionLoad);
    fileMenu->addAction(actionSetColor);
    fileMenu->addAction(actionSetBrush);
    fileMenu->addAction(actionUndo);

    setMenuBar(menuBar);

    createToolBar();
}

void MainWindow::createToolBar()
{
    QToolBar *toolBar = new QToolBar(this);
    addToolBar(Qt::TopToolBarArea, toolBar);

    QAction *lineAction = new QAction(tr("Line"), this);
    QAction *rectAction = new QAction(tr("Rectangle"), this);
    QAction *ellipseAction = new QAction(tr("Ellipse"), this);
    QAction *triangleAction = new QAction(tr("Triangle"), this);
    QAction *polygonAction = new QAction(tr("Polygon"), this);

    connect(lineAction, &QAction::triggered, [this]() { setShape(Line); });
    connect(rectAction, &QAction::triggered, [this]() { setShape(Rectangle); });
    connect(ellipseAction, &QAction::triggered, [this]() { setShape(Ellipse); });
    connect(triangleAction, &QAction::triggered, [this]() { setShape(Triangle); });
    connect(polygonAction, &QAction::triggered, [this]() { setShape(Polygon); });

    toolBar->addAction(lineAction);
    toolBar->addAction(rectAction);
    toolBar->addAction(ellipseAction);
    toolBar->addAction(triangleAction);
    toolBar->addAction(polygonAction);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        startPoint = event->pos();
        currentPoint = startPoint;
        drawing = true;
        if (currentShape == Polygon) {
            if (tempShape.polygon.isEmpty()) {
                tempShape = QShape(QPolygon() << event->pos(), currentColor, fillShapes, currentBrush);
            } else {
                tempShape.polygon << event->pos();
            }
        }
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (drawing) {
        currentPoint = event->pos();
        switch (currentShape) {
        case Line:
            tempShape = QShape(QLine(startPoint, currentPoint), currentColor, currentBrush);
            break;
        case Rectangle:
            tempShape = QShape(QRect(startPoint, currentPoint), currentColor, false, fillShapes, currentBrush);
            break;
        case Ellipse:
            tempShape = QShape(QRect(startPoint, currentPoint), currentColor, true, fillShapes, currentBrush);
            break;
        case Triangle:
            if (tempShape.polygon.count() == 2) {
                tempShape.polygon[1] = currentPoint;
            } else {
                tempShape.polygon << currentPoint;
            }
            tempShape = QShape(tempShape.polygon, currentColor, fillShapes, currentBrush);
            break;
        case Polygon:
            break;
        }
        update();
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && drawing) {
        switch (currentShape) {
        case Line:
            shapes.append(QShape(QLine(startPoint, event->pos()), currentColor, currentBrush));
            break;
        case Rectangle:
            shapes.append(QShape(QRect(startPoint, event->pos()), currentColor, false, fillShapes, currentBrush));
            break;
        case Ellipse:
            shapes.append(QShape(QRect(startPoint, event->pos()), currentColor, true, fillShapes, currentBrush));
            break;
        case Triangle:
            if (tempShape.polygon.count() == 3) {
                tempShape.isFilled = fillShapes;
                shapes.append(tempShape);
                tempShape.polygon.clear();
            }
            break;
        case Polygon:
            tempShape.isFilled = fillShapes;
            shapes.append(tempShape);
            tempShape.polygon.clear();
            break;
        }
        drawing = false;
        undoStack.clear();
        update();
    } else if (event->button() == Qt::RightButton && currentShape == Polygon) {
        shapes.append(tempShape);
        tempShape.polygon.clear();
        drawing = false;
        undoStack.clear();
        update();
    }
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    for (const QShape &shape : shapes) {
        painter.setPen(QPen(shape.color));
        painter.setBrush(shape.brush);
        if (shape.isEllipse) {
            painter.drawEllipse(shape.rect);
        } else if (shape.line.isNull()) {
            if (shape.isPolygon) {
                if (shape.isFilled) {
                    painter.drawPolygon(shape.polygon);
                } else {
                    painter.drawPolyline(shape.polygon);
                }
            } else {
                if (shape.isFilled) {
                    painter.drawRect(shape.rect);
                } else {
                    painter.drawRect(shape.rect);
                }
            }
        } else {
            painter.drawLine(shape.line);
        }
    }
    if (drawing) {
        painter.setPen(QPen(tempShape.color));
        painter.setBrush(tempShape.brush);
        if (tempShape.isEllipse) {
            painter.drawEllipse(tempShape.rect);
        } else if (tempShape.line.isNull()) {
            if (tempShape.isPolygon) {
                if (tempShape.isFilled) {
                    painter.drawPolygon(tempShape.polygon);
                } else {
                    painter.drawPolyline(tempShape.polygon);
                }
            } else {
                if (tempShape.isFilled) {
                    painter.drawRect(tempShape.rect);
                } else {
                    painter.drawRect(tempShape.rect);
                }
            }
        } else {
            painter.drawLine(tempShape.line);
        }
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
    for (const QShape &shape : shapes) {
        out << shape.color.name() << " ";
        out << shape.brush.color().name() << " ";
        if (shape.isEllipse) {
            out << "Ellipse " << shape.rect.x() << " " << shape.rect.y() << " " << shape.rect.width() << " " << shape.rect.height() << " " << shape.isFilled << "\n";
        } else if (shape.line.isNull()) {
            if (shape.isPolygon) {
                out << "Polygon ";
                for (const QPoint &point : shape.polygon) {
                    out << point.x() << " " << point.y() << " ";
                }
                out << shape.isFilled << "\n";
            } else {
                out << "Rect " << shape.rect.x() << " " << shape.rect.y() << " " << shape.rect.width() << " " << shape.rect.height() << " " << shape.isFilled << "\n";
            }
        } else {
            out << "Line " << shape.line.x1() << " " << shape.line.y1() << " " << shape.line.x2() << " " << shape.line.y2() << "\n";
        }
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
    shapes.clear();
    while (!in.atEnd()) {
        QString colorName, brushColorName, shapeType;
        in >> colorName >> brushColorName >> shapeType;
        QColor color(colorName);
        QColor brushColor(brushColorName);
        QBrush brush(brushColor);

        if (shapeType == "Ellipse") {
            int x, y, w, h, isFilled;
            in >> x >> y >> w >> h >> isFilled;
            shapes.append(QShape(QRect(x, y, w, h), color, true, isFilled, brush));
        } else if (shapeType == "Rect") {
            int x, y, w, h, isFilled;
            in >> x >> y >> w >> h >> isFilled;
            shapes.append(QShape(QRect(x, y, w, h), color, false, isFilled, brush));
        } else if (shapeType == "Polygon") {
            QPolygon polygon;
            int isFilled;
            in >> isFilled;
            int x, y;
            while (!in.atEnd() && in.status() == QTextStream::Ok) {
                in >> x >> y;
                polygon << QPoint(x, y);
            }
            shapes.append(QShape(polygon, color, isFilled, brush));
        } else if (shapeType == "Line") {
            int x1, y1, x2, y2;
            in >> x1 >> y1 >> x2 >> y2;
            shapes.append(QShape(QLine(x1, y1, x2, y2), color, brush));
        }
    }
    file.close();
    update();
}

void MainWindow::setColor()
{
    QColor color = QColorDialog::getColor(currentColor, this, tr("Select Color"));
    if (color.isValid()) {
        currentColor = color;
    }
}

void MainWindow::setBrush()
{
    QColor brushColor = QColorDialog::getColor(currentBrush.color(), this, tr("Select Brush Color"));
    if (brushColor.isValid()) {
        currentBrush.setColor(brushColor);
    }
}

void MainWindow::undo()
{
    if (!shapes.isEmpty()) {
        undoStack.append(shapes.takeLast());
        update();
    }
}

void MainWindow::setShape(ShapeType shape)
{
    currentShape = shape;
}

