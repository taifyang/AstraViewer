/**
  *@file mainwindow.h
  *@brief 主窗口头文件
  */


#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <QVTKWidget.h>
#include <QMessageBox>
#include <QAbstractButton>
#include <QTimer>
#include <QThread>
#include <QString>
#include <QFileDialog>

#include <iostream>
#include <opencv2/opencv.hpp>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/visualization/cloud_viewer.h>
#include <OpenNI.h>
#include <vtkAutoInit.h>
#include <vtkRenderWindow.h>

#include "blockingconcurrentqueue.h"
#include "camera_settings.h"
#include "cloud_generate.h"


VTK_MODULE_INIT(vtkRenderingOpenGL2)
VTK_MODULE_INIT(vtkInteractionStyle)


typedef pcl::PointCloud<pcl::PointXYZ> PointCloud;
typedef pcl::PointCloud<pcl::PointXYZRGB> PointCloudRGB;


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
using namespace moodycamel;
QT_END_NAMESPACE


/**
 * @brief The Astra class
 */
class Astra : public QMainWindow
{
    Q_OBJECT

public:
    explicit Astra(QWidget *parent = 0);

    ~Astra();

    Ui::MainWindow *ui;

private slots:
    /**
     * @brief save_color_image 保存彩色图
     */
    void save_color_image();

    /**
     * @brief save_depth_image 保存深度图
     */
    void save_depth_image();

    /**
     * @brief save_point_cloud 保存点云
     */
    void save_point_cloud();

    /**
     * @brief open_color_image 打开彩色图
     */
    void open_color_image();

    /**
     * @brief open_depth_image 打开深度图
     */
    void open_depth_image();

    /**
     * @brief open_point_cloud 打开点云
     */
    void open_point_cloud();


    /**
     * @brief close_all 关闭所有文件
     */
    void close_all();

    /**
     * @brief open_camera 打开相机
     */
    void open_camera();

    /**
     * @brief close_camera 关闭相机
     */
    void close_camera();

    //void set_camera();

    /**
     * @brief show_color_image 显示彩色图
     */
    void show_color_image();

    /**
     * @brief show_depth_image 显示深度图
     */
    void show_depth_image();

    /**
     * @brief show_point_cloud 显示点云
     */
    void show_point_cloud();

    /**
     * @brief help_guide 使用说明
     */
    void help_guide();

    /**
     * @brief help_about 关于AstraGUI
     */
    void help_about();

private:
    /**
     * @brief camera_settings 相机设置界面类指针
     */
    Camera_Settings *camera_settings;

    /**
     * @brief capture 彩色摄像头
     */
    cv::VideoCapture capture;

    /**
     * @brief device 深度摄像头
     */
    openni::Device device;

    /**
     * @brief depthStream 深度流
     */
    openni::VideoStream depthStream;

    /**
     * @brief depthMode 深度模式
     */
    openni::VideoMode depthMode;

    /**
     * @brief viewer pclviewer窗口
     */
    boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer;

    /**
     * @brief timerColor 彩色图像显示定时器
     */
    QTimer *timerColor;

    /**
     * @brief timerDepth 深度图像显示定时器
     */
    QTimer *timerDepth;

    /**
     * @brief timerCloud 点云显示定时器
     */
    QTimer *timerCloud;

    /**
     * @brief colorMat 彩色图像
     */
    cv::Mat colorMat;

    /**
     * @brief depthMat 深度图像
     */
    cv::Mat depthMat;

    /**
     * @brief flag_depth 深度图采集标志
     */
    bool flag_depth = false;

    /**
     * @brief flag_cloud 点云生成标志
     */
    bool flag_cloud =false;
};


#endif // MAINWINDOW_H
