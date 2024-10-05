#include "mainwindow.h"
#include "ui_mainwindow.h"

const float camera_factor = 1.0;
const float camera_cx = 311.0;
const float camera_cy = 244.0;
const float camera_fx = 593.0;
const float camera_fy = 588.0;
QMutex g_mutex_color, g_mutex_depth;
QWaitCondition g_wait_color, g_wait_depth;
cv::Mat g_color, g_depth, g_ir;
std::vector<PointXYZRGB> g_points;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    openglwidget = new MyQOpenglWidget(ui->openGLWidget);
    openglwidget->resize(ui->openGLWidget->width(),ui->openGLWidget->height());

    points_generate = new PointsGenerate;
    connect(points_generate, &PointsGenerate::send_points, this, &MainWindow::show_points);

    openni::OpenNI::initialize();

    timer_color = new QTimer(this);
    timer_color-> setTimerType(Qt::PreciseTimer);
    connect(timer_color, SIGNAL(timeout()), this, SLOT(show_color()));

    timer_depth = new QTimer(this);
    timer_depth-> setTimerType(Qt::PreciseTimer);
    connect(timer_depth, SIGNAL(timeout()), this, SLOT(show_depth()));

    timer_ir = new QTimer(this);
    timer_ir-> setTimerType(Qt::PreciseTimer);
    connect(timer_ir, SIGNAL(timeout()), this, SLOT(show_ir()));
}

MainWindow::~MainWindow()
{
    delete ui;
    openni::OpenNI::shutdown();
}

void MainWindow::on_pushButton_show_color_clicked()
{
    capture.open(0);
    timer_color->start(100);
}

void MainWindow::on_pushButton_show_depth_clicked()
{
    device.open(openni::ANY_DEVICE);
    device.setImageRegistrationMode(openni::IMAGE_REGISTRATION_DEPTH_TO_COLOR);
    stream_depth.create(device, openni::SENSOR_DEPTH);
    stream_depth.start();
    timer_depth->start(100);
}

void MainWindow::on_pushButton_show_ir_clicked()
{
    device.open(openni::ANY_DEVICE);
    stream_ir.create(device, openni::SENSOR_IR);
    stream_ir.start();
    timer_ir->start(100);
}


void PointsGenerate::run()
{
    while(true)
    {
        g_mutex_color.lock();
        g_mutex_depth.lock();
        g_wait_color.wait(&g_mutex_color);
        g_wait_depth.wait(&g_mutex_depth);

        g_points.clear();
        for (int i = 0; i < g_depth.rows; ++i)
        {
            uchar* depthData = g_depth.data + i*g_depth.step;
            uchar* colorData = g_color.data + i*g_color.step;
            for (int j = 0; j < g_depth.cols; ++j)
            {
                if (depthData == 0)
                    continue;

                PointXYZRGB point;
                point.z = double(*(depthData++)) / camera_factor;
                point.x = (j - camera_cx) * point.z / camera_fx;
                point.y = -(i - camera_cy) * point.z / camera_fy;
                point.b = *(colorData++);
                point.g = *(colorData++);
                point.r = *(colorData++);
                g_points.push_back(point);
            }
        }

        emit send_points();
        g_mutex_color.unlock();
        g_mutex_depth.unlock();
    }
}

void MainWindow::on_pushButton_show_points_clicked()
{
    points_generate->start();
}

void MainWindow::show_color()
{
    capture >> g_color;
    cv::flip(g_color, g_color, 1);
    g_wait_color.wakeAll();

    image_color = QImage((const uchar*)g_color.data, g_color.cols, g_color.rows, QImage::Format_RGB888).rgbSwapped();
    ui->label_color->clear();
    ui->label_color->setPixmap(QPixmap::fromImage(image_color));
}

void MainWindow::show_depth()
{
    openni::VideoFrameRef depth_frame;
    int max_depth = stream_depth.getMaxPixelValue();
    openni::VideoStream* pstream = &stream_depth;

    int changedStreamDummy;
    openni::Status ops = openni::OpenNI::waitForAnyStream(&pstream, 1, &changedStreamDummy, 1000);
    ops = stream_depth.readFrame(&depth_frame);

    if (ops != openni::STATUS_OK)
    {
        timer_depth->stop();
        return;
    }

    auto depth = depth_frame.getData();
    auto width = depth_frame.getWidth();
    auto height = depth_frame.getHeight();

    cv::Mat rawMat(height, width, CV_16UC1, (void*)depth);
    rawMat.convertTo(g_depth, CV_8UC1, 255.0 / max_depth);
    g_wait_depth.wakeAll();

    image_depth = QImage((const uchar*)g_depth.data, g_depth.cols, g_depth.rows, QImage::Format_Grayscale8);
    ui->label_depth->clear();
    ui->label_depth->setPixmap(QPixmap::fromImage(image_depth));
}

void MainWindow::show_ir()
{
    openni::VideoFrameRef ir_frame;
    int max_ir = stream_ir.getMaxPixelValue();
    openni::VideoStream* pstream = &stream_ir;

    int changedStreamDummy;
    openni::Status ops = openni::OpenNI::waitForAnyStream(&pstream, 1, &changedStreamDummy, 1000);
    ops = stream_ir.readFrame(&ir_frame);

    if (ops != openni::STATUS_OK)
    {
        timer_ir->stop();
        return;
    }

    auto ir = ir_frame.getData();
    auto width = ir_frame.getWidth();
    auto height = ir_frame.getHeight();

    cv::Mat rawMat(height, width, CV_16UC1, (void*)ir);
    rawMat.convertTo(g_ir, CV_8UC1, 255.0 / max_ir);
    g_wait_depth.wakeAll();

    image_ir = QImage((const uchar*)g_ir.data, g_ir.cols, g_ir.rows, QImage::Format_Grayscale8);
    ui->label_ir->clear();
    ui->label_ir->setPixmap(QPixmap::fromImage(image_ir));
}

void MainWindow::show_points()
{
    openglwidget->showPointCloud(g_points);
}

void MainWindow::on_pushButton_save_color_clicked()
{
    image_color.save(QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss") + "_color.png");
}

void MainWindow::on_pushButton_save_depth_clicked()
{
    image_depth.save(QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss") + "_depth.png");
}

void MainWindow::on_pushButton_save_ir_clicked()
{
    image_ir.save(QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss") + "_ir.png");
}

void MainWindow::on_pushButton_save_points_clicked()
{
    if(g_points.empty()) return;
    QFile file(QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss") + "_points.txt");
    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&file);
        for(size_t i=0; i<g_points.size(); i++)
        {
            out<<g_points[i].x<<" "<<g_points[i].y<<" "<<g_points[i].z<<" "
              <<g_points[i].r<<" "<<g_points[i].g<<" "<<g_points[i].b<<"\n";
        }
        file.close();
    }
}

