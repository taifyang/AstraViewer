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

#include <astra_core/astra_core.hpp>
#include <astra/astra.hpp>

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

    MultiFrameListener listener;

    QImage depth, color, ir;

    bool is_registered = false;
};


#endif // MAINWINDOW_H

