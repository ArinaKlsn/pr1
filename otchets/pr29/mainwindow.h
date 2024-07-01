#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QMenuBar>
#include <QMenu>
#include <QAction>

// Включение заголовочного файла, содержащего определение класса Ui::SDI
#include "ui_mainwindow.h"

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

    QString toBinary(const QString &text);
    QString fromBinary(const QString &binaryText);
};

#endif // MAINWINDOW_H
