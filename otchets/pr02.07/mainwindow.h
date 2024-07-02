#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include <QColor>
#include <QBrush>
#include <QStack>
#include "qshape.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

enum ShapeType {
    Line,
    Rectangle,
    Ellipse,
    Triangle,
    Polygon
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private slots:
    void saveToFile();
    void loadFromFile();
    void setShape(ShapeType shape);
    void setColor();
    void setBrush();
    void undo();

private:
    Ui::MainWindow *ui;
    QList<QShape> shapes;
    QShape tempShape;
    QStack<QShape> undoStack;
    bool drawing;
    QPoint startPoint, currentPoint;
    QColor currentColor;
    QBrush currentBrush;
    bool fillShapes;
    ShapeType currentShape;

    void createToolBar();
};

#endif // MAINWINDOW_H
