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
<<<<<<< Updated upstream
#include <QThread>
#include <QString>
#include <QFileDialog>
=======
#include <QDebug>
#include <QDateTime>
#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include <QFile>
#include <QTextStream>
>>>>>>> Stashed changes

#include <iostream>
#include <opencv2/opencv.hpp>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/visualization/cloud_viewer.h>
#include <OpenNI.h>
#include <vtkAutoInit.h>
#include <vtkRenderWindow.h>

<<<<<<< Updated upstream
#include "blockingconcurrentqueue.h"
#include "camera_settings.h"
#include "cloud_generate.h"


VTK_MODULE_INIT(vtkRenderingOpenGL2)
VTK_MODULE_INIT(vtkInteractionStyle)


typedef pcl::PointCloud<pcl::PointXYZ> PointCloud;
typedef pcl::PointCloud<pcl::PointXYZRGB> PointCloudRGB;
=======
#include "MyQOpenglWidget.h"

extern std::vector<PointXYZRGB> g_cloud;

enum Mode
{
    MODE_RGB,
    MODE_IR,
};

class MultiFrameListener : public astra::FrameListener
{
public:
    struct StreamView
    {
        uint8_t* buffer_;
        int width_{0};
        int height_{0};
    };

    void init_view(int width, int height, StreamView& view)
    {
        if (view.buffer_ == nullptr || width != view.width_ || height != view.height_)
        {
            view.width_ = width;
            view.height_ = height;
            const int byteLength = width * height * 3;
            view.buffer_ = new uint8_t[byteLength];
            std::fill(&view.buffer_[0], &view.buffer_[0] + view.width_ * view.height_ * 3, 0);
        }
    }

    void update_depth(astra::Frame& frame)
    {
        const astra::PointFrame pointFrame = frame.get<astra::PointFrame>();
        if (!pointFrame.is_valid())
        {
            return;
        }

        const int depthWidth = pointFrame.width();
        const int depthHeight = pointFrame.height();

        init_view(depthWidth, depthHeight, depthView_);
        qDebug() << "depth";

        const astra::Vector3f* pointData = pointFrame.data();
        uint8_t* buffer = &depthView_.buffer_[0];
        float min_value = INT_MAX, max_value = INT_MIN;
        for (int i = 0; i < depthWidth * depthHeight; i++)
        {
            if(pointData[i].z > max_value)    max_value = pointData[i].z;
            if(pointData[i].z < min_value)    min_value = pointData[i].z;
        }

        g_cloud.clear();
        g_cloud.resize(depthWidth * depthHeight);
        for (int i = 0; i < depthWidth * depthHeight; i++)
        {
            g_cloud[i] = PointXYZRGB(pointData[i].x, pointData[i].y, pointData[i].z);
            buffer[i] = 255 * (pointData[i].z - min_value) / (max_value - min_value);
        }
    }

    void update_rgb(astra::Frame& frame)
    {
        const astra::ColorFrame colorFrame = frame.get<astra::ColorFrame>();
        if (!colorFrame.is_valid())
        {
            return;
        }

        const int colorWidth = colorFrame.width();
        const int colorHeight = colorFrame.height();

        init_view(colorWidth, colorHeight, colorView_);
        qDebug() << "rgb";

        const astra::RgbPixel* rgb = colorFrame.data();
        uint8_t* buffer = &colorView_.buffer_[0];
        for(int i = 0; i < colorWidth * colorHeight; i++)
        {
            buffer[i * 3 + 0] = rgb[i].r;
            buffer[i * 3 + 1] = rgb[i].g;
            buffer[i * 3 + 2] = rgb[i].b;
            g_cloud[i].r = rgb[i].r;
            g_cloud[i].g = rgb[i].g;
            g_cloud[i].b = rgb[i].b;
        }
    }

    void update_ir(astra::Frame& frame)
    {
        const astra::InfraredFrameRgb irFrame = frame.get<astra::InfraredFrameRgb>();
        if (!irFrame.is_valid())
        {
            return;
        }

        int irWidth = irFrame.width();
        int irHeight = irFrame.height();

        init_view(irWidth, irHeight, colorView_);
        qDebug() << "ir";

        const astra::RgbPixel* irRGB = irFrame.data();
        uint8_t* buffer = &colorView_.buffer_[0];
        for (int i = 0; i < irWidth * irHeight; i++)
        {
            buffer[i * 3 + 0] = irRGB[i].r;
            buffer[i * 3 + 1] = irRGB[i].g;
            buffer[i * 3 + 2] = irRGB[i].b;
        }
    }

    virtual void on_frame_ready(astra::StreamReader& reader, astra::Frame& frame) override
    {
        update_depth(frame);
        if(Mode_ == MODE_RGB)
            update_rgb(frame);
        if(Mode_ == MODE_IR)
            update_ir(frame);
    }

    Mode get_mode() const { return Mode_; }
    void set_mode(Mode mode) { Mode_ = mode; }

public:
    StreamView depthView_;
    StreamView colorView_;
    Mode Mode_;
};

class CloudGenerate : public QThread
{
  Q_OBJECT

private:
    void run();

signals:
    void send_cloud();
};
>>>>>>> Stashed changes


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

<<<<<<< Updated upstream
    Ui::MainWindow *ui;

private slots:
    /**
     * @brief save_color_image 保存彩色图
     */
    void save_color_image();
=======
private slots:
    void on_pushButton_open_rgbd_clicked();

    void on_pushButton_open_ir_clicked();

    void on_pushButton_d2c_clicked();

    void on_pushButton_show_cloud_clicked();

    void show_cloud();

    void on_pushButton_save_rgb_clicked();

    void on_pushButton_save_depth_clicked();

    void on_pushButton_save_ir_clicked();

    void on_pushButton_save_cloud_clicked();

private:
    Ui::MainWindow *ui;

    MyQOpenglWidget* openglwidget;

    CloudGenerate* cloud_generate;

    astra::StreamReader reader;
>>>>>>> Stashed changes

    /**
     * @brief save_depth_image 保存深度图
     */
    void save_depth_image();

<<<<<<< Updated upstream
    /**
     * @brief save_point_cloud 保存点云
     */
    void save_point_cloud();
=======
    QImage depth, color, ir;
>>>>>>> Stashed changes

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

<<<<<<< Updated upstream
=======

#endif // MAINWINDOW_H
>>>>>>> Stashed changes

#endif // MAINWINDOW_H
