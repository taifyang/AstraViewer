#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "image_utils.h"

const int frame_width = 640;
const int frame_height = 480;
const float camera_factor = 1000.0;
const float camera_cx = 311.0;
const float camera_cy = 244.0;
const float camera_fx = 593.0;
const float camera_fy = 588.0;
QMutex g_mutex_color, g_mutex_depth;
QWaitCondition g_wait_color, g_wait_depth;
uint8_t* g_color = new uint8_t[frame_width * frame_height * 3];
uint16_t* g_depth = new uint16_t[frame_width * frame_height];
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

    uvsSwapper.UvcInit();
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
    uvsSwapper.UVCStreamStart(640, 480, OB_PIXEL_FORMAT_YUV422, 30);
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
        uint8_t* p_color = g_color;
        uint16_t* p_depth = g_depth;
        for (int i = 0; i < frame_height; ++i)
        {
            for (int j = 0; j < frame_width; ++j)
            {
                if (p_depth == 0)
                    continue;

                PointXYZRGB point;
                point.z = double(*(p_depth++)) / camera_factor;
                point.x = (j - camera_cx) * point.z / camera_fx;
                point.y = (i - camera_cy) * point.z / camera_fy;
                point.b = *(p_color++);
                point.g = *(p_color++);
                point.r = *(p_color++);
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
    uint8_t* uvc = new uint8_t[frame_width * frame_height * 2];
    memset(uvc, 0, frame_width * frame_height * 2);
    uint32_t nSize = 0;
    uint32_t nImageType = 0;
    uvsSwapper.WaitUvcStream(uvc, nSize, nImageType, 1000);
    memset(g_color, 0, frame_width * frame_height * 3);
    convertYUV422ToRGB888(uvc, g_color, frame_width, frame_height);
    delete []  uvc;
    g_wait_color.wakeAll();
    image_color = rgbToQImage(g_color, frame_width, frame_height).rgbSwapped();
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
    std::copy((uint16_t*)depth, (uint16_t*)depth + frame_width * frame_height, g_depth);
    g_wait_depth.wakeAll();

    image_depth = Map16ToQImage((const uint16_t*)depth, frame_width, frame_height, 255.0 / max_depth);
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
    g_wait_depth.wakeAll();

    image_ir = Map16ToQImage((const uint16_t*)ir, frame_width, frame_height, 255.0 / max_ir);
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

