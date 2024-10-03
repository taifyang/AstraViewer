#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
    is_color = true;

    astra::StreamSet streamSet;
    astra::StreamReader reader = streamSet.create_reader();
    reader.stream<astra::PointStream>().start();

    auto depthStream = configure_depth(reader);
    auto colorStream = configure_color(reader);
    auto irStream = configure_ir(reader);
    depthStream.start();
    colorStream.start();

    listener.set_mode(MODE_COLOR);
    reader.add_listener(listener);

    while(true)
    {
        astra_update();

        if(listener.get_mode() == MODE_COLOR)
        {
            QImage depth = QImage(listener.depthView_.buffer_, 640, 480, QImage::Format_Grayscale8);
            QImage color = QImage(listener.colorView_.buffer_, 640, 480, QImage::Format_RGB888);

            QEventLoop loop_depth;
            QTimer::singleShot(1, &loop_depth, SLOT(quit()));
            loop_depth.exec();

            ui->label_depth->clear();
            ui->label_color->clear();
            ui->label_depth->setPixmap(QPixmap::fromImage(depth));
            ui->label_color->setPixmap(QPixmap::fromImage(color));
        }
        if(listener.get_mode() == MODE_IR)
        {
            colorStream.stop();
            configure_ir(reader);
            listener.set_mode(MODE_IR);
            irStream.start();

            QImage depth = QImage(listener.depthView_.buffer_, 640, 480, QImage::Format_Grayscale8);
            QImage ir = QImage(listener.colorView_.buffer_, 640, 480, QImage::Format_RGB888);

            QEventLoop loop_depth;
            QTimer::singleShot(1, &loop_depth, SLOT(quit()));
            loop_depth.exec();

            ui->label_depth->clear();
            ui->label_color->clear();
            ui->label_depth->setPixmap(QPixmap::fromImage(depth));
            ui->label_color->setPixmap(QPixmap::fromImage(ir));
        }
        if(is_registered)
        {
            depthStream.enable_registration(true);
        }
    }
}


void MainWindow::on_pushButton_open_d2c_clicked()
{
    is_registered = true;
    //depthStream.enable_registration(true);
}

void MainWindow::on_pushButton_open_ir_clicked()
{
    listener.set_mode(MODE_IR);

}
