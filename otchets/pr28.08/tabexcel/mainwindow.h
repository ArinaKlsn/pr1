#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QMenu>
#include <QAction>
#include <QPushButton>
#include <QTableView>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void saveAsCSV();
    void loadFromCSV();
    void addRow();
    void addColumn();
    void removeRow();
    void removeColumn();

private:
    void createActions();
    void createMenus();

    Ui::MainWindow *ui;
    QStandardItemModel *model;
    QMenu *fileMenu;
    QAction *saveAsCSVAction;
    QAction *loadFromCSVAction;
    QToolBar *mainToolBar;
    QPushButton *addRowButton;
    QPushButton *addColumnButton;
    QPushButton *removeRowButton;
    QPushButton *removeColumnButton;
};

#endif // MAINWINDOW_H
