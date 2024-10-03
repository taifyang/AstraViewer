#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QDebug>

#include <astra_core/astra_core.hpp>
#include <astra/astra.hpp>

#include "astra.h"


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
    void on_pushButton_open_rgbd_clicked();

    void on_pushButton_open_d2c_clicked();

    void on_pushButton_open_ir_clicked();

private:
    Ui::MainWindow *ui;

    astra::StreamReader reader;

    MultiFrameListener listener;

    bool is_color = true;

    bool is_registered = false;
};

#endif // MAINWINDOW_H

