#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include <QPoint>
#include <QLine>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

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

private:
    Ui::MainWindow *ui;
    QList<QLine> lines;
    QPoint startPoint;
    QPoint currentPoint;  // Добавляем переменную currentPoint
    QLine tempLine;       // Добавляем переменную tempLine
    bool drawing;
};

#endif // MAINWINDOW_H

