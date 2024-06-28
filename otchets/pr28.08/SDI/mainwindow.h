#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QMenuBar>
#include <QMenu>
#include <QAction>

QT_BEGIN_NAMESPACE
namespace Ui { class SDI; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void saveAsText();
    void loadFromText();
    void saveAsBinary();
    void loadFromBinary();

private:
    void createActions();
    void createMenus();

    Ui::SDI *ui;
    QMenu *fileMenu;
    QAction *saveAsTextAction;
    QAction *loadFromTextAction;
    QAction *saveAsBinaryAction;
    QAction *loadFromBinaryAction;
};

#endif // MAINWINDOW_H
