#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mytablemodel.h"
#include<QPushButton>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionSave_triggered();
    void on_actionLoad_triggered();
    void onPinkButtonClicked();

private:
    Ui::MainWindow *ui;
    MyTableModel *model;
    QPushButton *pinkButton;
};

#endif // MAINWINDOW_H
