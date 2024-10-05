#include "mainwindow.h"
#include "ui_mainwindow.h"

QMutex g_mutex;
QWaitCondition g_waitcondition;
std::vector<PointXYZRGB> g_cloud;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    openglwidget = new MyQOpenglWidget(ui->openGLWidget);
    openglwidget->resize(ui->openGLWidget->width(),ui->openGLWidget->height());

    cloud_generate = new CloudGenerate;
    connect(cloud_generate, &CloudGenerate::send_cloud, this, &MainWindow::show_cloud);

    astra::initialize();
}

MainWindow::~MainWindow()
{
    delete ui;
    astra::terminate();
}

astra::DepthStream configure_depth(astra::StreamReader& reader)
{
    auto depthStream = reader.stream<astra::DepthStream>();
    astra::ImageStreamMode depthMode;
    depthMode.set_width(640);
    depthMode.set_height(480);
    depthMode.set_pixel_format(astra_pixel_formats::ASTRA_PIXEL_FORMAT_DEPTH_MM);
    depthMode.set_fps(30);
    depthStream.set_mode(depthMode);
    return depthStream;
}

astra::ColorStream configure_color(astra::StreamReader& reader)
{
    auto colorStream = reader.stream<astra::ColorStream>();
    astra::ImageStreamMode colorMode;
    colorMode.set_width(640);
    colorMode.set_height(480);
    colorMode.set_pixel_format(astra_pixel_formats::ASTRA_PIXEL_FORMAT_RGB888);
    colorMode.set_fps(30);
    colorStream.set_mode(colorMode);
    return colorStream;
}

astra::InfraredStream configure_ir(astra::StreamReader& reader)
{
    auto irStream = reader.stream<astra::InfraredStream>();
    astra::ImageStreamMode irMode;
    irMode.set_width(640);
    irMode.set_height(480);
    irMode.set_pixel_format(astra_pixel_formats::ASTRA_PIXEL_FORMAT_RGB888);
    irMode.set_fps(30);
    irStream.set_mode(irMode);
    return irStream;
}

void MainWindow::on_pushButton_open_rgbd_clicked()
{
    astra::StreamSet streamSet;
    astra::StreamReader reader = streamSet.create_reader();
    reader.stream<astra::PointStream>().start();

    auto depthStream = configure_depth(reader);
    auto colorStream = configure_color(reader);
    auto irStream = configure_ir(reader);
    depthStream.start();
    colorStream.start();

    listener.set_mode(MODE_RGB);
    reader.add_listener(listener);

    while(true)
    {
        astra_update();

        if(listener.get_mode() == MODE_RGB)
        {
            depth = QImage(listener.depthView_.buffer_, 640, 480, QImage::Format_Grayscale8);
            color = QImage(listener.colorView_.buffer_, 640, 480, QImage::Format_RGB888);

            QEventLoop loop;
            QTimer::singleShot(1, &loop, SLOT(quit()));
            loop.exec();
            g_waitcondition.wakeAll();

            ui->label_depth->clear();
            ui->label_rgb->clear();
            ui->label_ir->clear();
            ui->label_depth->setPixmap(QPixmap::fromImage(depth));
            ui->label_rgb->setPixmap(QPixmap::fromImage(color));
        }
        if(listener.get_mode() == MODE_IR)
        {
            colorStream.stop();
            configure_ir(reader);
            listener.set_mode(MODE_IR);
            irStream.start();

            ir = QImage(listener.colorView_.buffer_, 640, 480, QImage::Format_RGB888);

            QEventLoop loop;
            QTimer::singleShot(1, &loop, SLOT(quit()));
            loop.exec();

            ui->label_depth->clear();
            ui->label_rgb->clear();
            ui->label_ir->clear();
            ui->label_ir->setPixmap(QPixmap::fromImage(ir));
        }
        if(is_registered)
        {
            depthStream.enable_registration(true);
        }
    }
}

void MainWindow::on_pushButton_open_ir_clicked()
{
    listener.set_mode(MODE_IR);
}

void MainWindow::on_pushButton_d2c_clicked()
{
    is_registered = true;
}

void CloudGenerate::run()
{
    while(true)
    {
        g_mutex.lock();
        g_waitcondition.wait(&g_mutex);
        emit send_cloud();
        g_mutex.unlock();
    }
}

void MainWindow::on_pushButton_show_cloud_clicked()
{
    cloud_generate->start();
    is_registered = true;
}

void MainWindow::show_cloud()
{
    openglwidget->showPointCloud(g_cloud);
}

void MainWindow::on_pushButton_save_rgb_clicked()
{
    color.save(QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss") + "_color.png");
}

void MainWindow::on_pushButton_save_depth_clicked()
{
    depth.save(QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss") + "_depth.png");
}

void MainWindow::on_pushButton_save_ir_clicked()
{
    ir.save(QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss") + "_ir.png");
}

void MainWindow::on_pushButton_save_cloud_clicked()
{
    if(g_cloud.empty()) return;
    QFile file(QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss") + "_cloud.txt");
    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&file);
        for(size_t i=0; i<g_cloud.size(); i++)
        {
            out<<g_cloud[i].x<<" "<<g_cloud[i].y<<" "<<g_cloud[i].z<<" "
              <<g_cloud[i].r<<" "<<g_cloud[i].g<<" "<<g_cloud[i].b<<"\n";
        }
        file.close();
    }
}
