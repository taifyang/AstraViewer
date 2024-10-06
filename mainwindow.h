#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QDebug>
#include <QDateTime>
#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include <QFile>
#include <QTextStream>

#include <OpenNI.h>
#include <UVC_Swapper.h>
#include <UVCSwapper.h>
#include <OBTypes.h>
#include <ObCommon.h>


#include "myqopenglwidget.h"

extern std::vector<PointXYZRGB> g_points;

class PointsGenerate : public QThread
{
  Q_OBJECT

private:
    void run();

signals:
    void send_points();
};


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
    void on_pushButton_show_color_clicked();

    void on_pushButton_show_depth_clicked();

    void on_pushButton_show_ir_clicked();

    void on_pushButton_show_points_clicked();

    void show_color();

    void show_depth();

    void show_ir();

    void show_points();

    void on_pushButton_save_color_clicked();

    void on_pushButton_save_depth_clicked();

    void on_pushButton_save_ir_clicked();

    void on_pushButton_save_points_clicked();

private:
    Ui::MainWindow *ui;

    MyQOpenglWidget* openglwidget;

    PointsGenerate* points_generate;

    UVC_Swapper uvsSwapper;

    //cv::VideoCapture capture;

    openni::Device device;

    openni::VideoStream stream_color, stream_depth, stream_ir;

    QImage image_color, image_depth, image_ir;

    QTimer *timer_color, *timer_depth, *timer_ir;
};


#endif // MAINWINDOW_H

