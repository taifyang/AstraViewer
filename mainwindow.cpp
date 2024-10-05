/**
  *@file mainwindow.cpp
  *@brief 主窗口源文件
  */


#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

<<<<<<< Updated upstream
/**
 * @brief cloud 无色点云
 */
PointCloud::Ptr cloud(new PointCloud);

/**
 * @brief cloudRGB 彩色点云
 */
PointCloudRGB::Ptr cloudRGB(new PointCloudRGB);

/**
 * @brief bcq_colorMat colorMat阻塞队列
 */
BlockingConcurrentQueue<cv::Mat> bcq_colorMat;

/**
 * @brief bcq_depthMat depthMat阻塞队列
 */
BlockingConcurrentQueue<cv::Mat> bcq_depthMat;

/**
 * @brief bcq_cloud cloud阻塞队列
 */
BlockingConcurrentQueue<PointCloud::Ptr> bcq_cloud;

/**
 * @brief bcq_cloudRGB cloudRGB阻塞队列
 */
BlockingConcurrentQueue<PointCloudRGB::Ptr> bcq_cloudRGB;


Astra::Astra(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->action_save_colorMat, &QAction::triggered, [=]{this->save_color_image();});
    connect(ui->action_save_depthMat, &QAction::triggered, [=]{this->save_depth_image();});
    connect(ui->action_save_pointcloud, &QAction::triggered, [=]{this->save_point_cloud();});
    connect(ui->action_open_colorMat, &QAction::triggered, [=]{this->open_color_image();});
    connect(ui->action_open_depthMat, &QAction::triggered, [=]{this->open_depth_image();});
    connect(ui->action_open_pointcloud, &QAction::triggered, [=]{this->open_point_cloud();});
    connect(ui->action_close_all, &QAction::triggered, [=]{this->close_all();});
    connect(ui->action_exit, &QAction::triggered, [=]{this->close();});
    connect(ui->action_open_camera, &QAction::triggered, [=]{this->open_camera();});
    connect(ui->action_close_camera, &QAction::triggered, [=]{this->close_camera();});
    //connect(ui->action_set_camera, &QAction::triggered, [=]{this->set_camera();});
    connect(ui->action_help_guide, &QAction::triggered, [=]{this->help_guide();});
    connect(ui->action_help_about, &QAction::triggered, [=]{this->help_about();});

    openni::OpenNI::initialize();
}


Astra::~Astra()
=======
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
>>>>>>> Stashed changes
{
    delete ui;

    openni::OpenNI::shutdown();
}

<<<<<<< Updated upstream
void Astra::save_color_image()
=======
astra::DepthStream configure_depth(astra::StreamReader& reader)
>>>>>>> Stashed changes
{
    //选择路径
    QString fileName = QFileDialog::getSaveFileName(this,QString::fromLocal8Bit("保存彩色图")," ",tr(" (*.bmp *.jpg *.png)"));

<<<<<<< Updated upstream
    //文件名为空
    if (fileName.isEmpty())
    {
        QMessageBox *box = new QMessageBox(QMessageBox::Warning,QString::fromLocal8Bit("警告"),QString::fromLocal8Bit("文件名为空!"),QMessageBox::Ok);
        if(NULL!=box->button(QMessageBox::Ok))
        {
           box->button(QMessageBox::Ok)->setText(QString::fromLocal8Bit("确 定"));
=======
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
>>>>>>> Stashed changes
        }
        QTimer::singleShot(3000,box,SLOT(accept()));
        box->exec();
        return;
    }

    //彩色图像为空
    if (colorMat.empty())
    {
        QMessageBox *box = new QMessageBox(QMessageBox::Warning,QString::fromLocal8Bit("警告"),QString::fromLocal8Bit("彩色图保存错误!"),QMessageBox::Ok);
        if(NULL!=box->button(QMessageBox::Ok))
        {
<<<<<<< Updated upstream
           box->button(QMessageBox::Ok)->setText(QString::fromLocal8Bit("确 定"));
=======
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
>>>>>>> Stashed changes
        }
        QTimer::singleShot(3000,box,SLOT(accept()));
        box->exec();
        return;
    }

    std::string filename(fileName.toLocal8Bit().data()); //支持带中文路径的读取
    cv::imwrite(filename, colorMat); //将彩色图像写入磁盘
}


void Astra::save_depth_image()
{
    //选择路径
    QString fileName = QFileDialog::getSaveFileName(this,QString::fromLocal8Bit("保存深度图")," ",tr(" (*.bmp *.jpg *.png)"));

    //文件名为空
    if (fileName.isEmpty())
    {
        QMessageBox *box = new QMessageBox(QMessageBox::Warning,QString::fromLocal8Bit("警告"),QString::fromLocal8Bit("文件名为空!"),QMessageBox::Ok);
        if(NULL!=box->button(QMessageBox::Ok))
        {
           box->button(QMessageBox::Ok)->setText(QString::fromLocal8Bit("确 定"));
        }
        QTimer::singleShot(3000,box,SLOT(accept()));
        box->exec();
        return;
    }

    //深度图为空
    if (depthMat.empty())
    {
        QMessageBox *box = new QMessageBox(QMessageBox::Warning,QString::fromLocal8Bit("警告"),QString::fromLocal8Bit("深度图保存错误!"),QMessageBox::Ok);
        if(NULL!=box->button(QMessageBox::Ok))
        {
           box->button(QMessageBox::Ok)->setText(QString::fromLocal8Bit("确 定"));
        }
        QTimer::singleShot(3000,box,SLOT(accept()));
        box->exec();
        return;
    }

    std::string filename(fileName.toLocal8Bit().data()); //支持带中文路径的读取
    cv::imwrite(filename, depthMat); //将深度图像写入磁盘
}


void Astra::save_point_cloud()
{
    //选择路径
    QString fileName = QFileDialog::getSaveFileName(this,QString::fromLocal8Bit("保存点云")," ",tr(" (*.pcd)"));

    //文件名为空
    if (fileName.isEmpty())
    {
        QMessageBox *box = new QMessageBox(QMessageBox::Warning,QString::fromLocal8Bit("警告"),QString::fromLocal8Bit("文件名为空!"),QMessageBox::Ok);
        if(NULL!=box->button(QMessageBox::Ok))
        {
           box->button(QMessageBox::Ok)->setText(QString::fromLocal8Bit("确 定"));
        }
        QTimer::singleShot(3000,box,SLOT(accept()));
        box->exec();
        return;
    }

    //点云数据为空
    if (cloudRGB->size()==0 && cloud->size()==0)
    {
        QMessageBox *box = new QMessageBox(QMessageBox::Warning,QString::fromLocal8Bit("警告"),QString::fromLocal8Bit("点云保存错误!"),QMessageBox::Ok);
        if(NULL!=box->button(QMessageBox::Ok))
        {
           box->button(QMessageBox::Ok)->setText(QString::fromLocal8Bit("确 定"));
        }
        QTimer::singleShot(3000,box,SLOT(accept()));
        box->exec();
        return;
    }

    std::string filename(fileName.toLocal8Bit().data()); //支持带中文路径的读取
    if(flag_cloud)
        pcl::io::savePCDFileBinary(filename,*cloud); //将无色点云写入磁盘
    else
        pcl::io::savePCDFileBinary(filename,*cloudRGB); //将彩色点云写入磁盘
}


void Astra::open_color_image()
{
    ui->stackedWidget->setCurrentIndex(0);

    //选择路径
    QString fileName  = QFileDialog::getOpenFileName(this,QString::fromLocal8Bit("打开彩色图"),"home",tr("(*.bmp *.jpg *.png )"));
    //文件名为空
    if (fileName.isEmpty())
    {
        QMessageBox *box = new QMessageBox(QMessageBox::Warning,QString::fromLocal8Bit("警告"),QString::fromLocal8Bit("文件名为空!"),QMessageBox::Ok);
        if(NULL!=box->button(QMessageBox::Ok))
        {
           box->button(QMessageBox::Ok)->setText(QString::fromLocal8Bit("确 定"));
        }
        QTimer::singleShot(3000,box,SLOT(accept()));
        box->exec();
        return;
    }

    std::string filename(fileName.toLocal8Bit().data()); //支持带中文路径的读取
    cv::Mat colorMat = cv::imread(filename,-1); //-1表示读取原始数据
    //彩色图像为空或通道数不为3
    if(colorMat.empty() || colorMat.channels()!=3)
    {
        QMessageBox *box = new QMessageBox(QMessageBox::Warning,QString::fromLocal8Bit("警告"),QString::fromLocal8Bit("彩色图打开错误!"),QMessageBox::Ok);
        if(NULL!=box->button(QMessageBox::Ok))
        {
           box->button(QMessageBox::Ok)->setText(QString::fromLocal8Bit("确 定"));
        }
        QTimer::singleShot(3000,box,SLOT(accept()));
        box->exec();
        return;
    }

    //缩放图像使其适应窗口大小
    cv::resize(colorMat,colorMat,cv::Size(ui->label_color_1->width(),ui->label_color_1->height()));
    //cv::Mat转QImage
    QImage image_color = QImage((const uchar*)colorMat.data,colorMat.cols,colorMat.rows,QImage::Format_RGB888).rgbSwapped();

    //更新ui
    ui->label_color_1->clear();
    ui->label_color_1->setPixmap(QPixmap::fromImage(image_color));
}


void Astra::open_depth_image()
{
    ui->stackedWidget->setCurrentIndex(0);

    //选择路径
    QString fileName  = QFileDialog::getOpenFileName(this,QString::fromLocal8Bit("打开深度图"),"home",tr("(*.bmp *.jpg *.png )"));
    //文件名为空
    if (fileName.isEmpty())
    {
        QMessageBox *box = new QMessageBox(QMessageBox::Warning,QString::fromLocal8Bit("警告"),QString::fromLocal8Bit("文件名为空!"),QMessageBox::Ok);
        if(NULL!=box->button(QMessageBox::Ok))
        {
           box->button(QMessageBox::Ok)->setText(QString::fromLocal8Bit("确 定"));
        }
        QTimer::singleShot(3000,box,SLOT(accept()));
        box->exec();
        return;
    }

    std::string filename(fileName.toLocal8Bit().data()); //支持带中文路径的读取
    cv::Mat depthMat = cv::imread(filename,-1); //-1表示读取原始数据
     //深度图像为空或通道数不为1
    if(depthMat.empty() || depthMat.channels()!=1)
    {
        QMessageBox *box = new QMessageBox(QMessageBox::Warning,QString::fromLocal8Bit("警告"),QString::fromLocal8Bit("深度图打开错误!"),QMessageBox::Ok);
        if(NULL!=box->button(QMessageBox::Ok))
        {
           box->button(QMessageBox::Ok)->setText(QString::fromLocal8Bit("确 定"));
        }
        QTimer::singleShot(3000,box,SLOT(accept()));
        box->exec();
        return;
    }

    //缩放图像使其适应窗口大小
    cv::resize(depthMat,depthMat,cv::Size(ui->label_depth_1->width(),ui->label_depth_1->height()));
    //cv::Mat转QImage
    QImage image_depth = QImage((const uchar*)depthMat.data,depthMat.cols,depthMat.rows,QImage::Format_Grayscale8).rgbSwapped();

    //更新ui
    ui->label_depth_1->clear();
    ui->label_depth_1->setPixmap(QPixmap::fromImage(image_depth));

}


void Astra::open_point_cloud()
{
    ui->stackedWidget->setCurrentIndex(0);
    //选择路径
    QString fileName  = QFileDialog::getOpenFileName(this,QString::fromLocal8Bit("打开点云"),"home",tr("(*.pcd)"));
    //文件名为空
    if (fileName.isEmpty())
    {
        QMessageBox *box = new QMessageBox(QMessageBox::Warning,QString::fromLocal8Bit("警告"),QString::fromLocal8Bit("文件名为空!"),QMessageBox::Ok);
        if(NULL!=box->button(QMessageBox::Ok))
        {
           box->button(QMessageBox::Ok)->setText(QString::fromLocal8Bit("确 定"));
        }
        QTimer::singleShot(3000,box,SLOT(accept()));
        box->exec();
        return;
    }

    std::string filename(fileName.toLocal8Bit().data()); //支持带中文路径的读取

    PointCloud::Ptr cloud(new PointCloud);
    PointCloudRGB::Ptr cloudRGB(new PointCloudRGB);

    //点云加载失败
    if(pcl::io::loadPCDFile(filename,*cloudRGB)==-1)
    {
        QMessageBox *box = new QMessageBox(QMessageBox::Warning,QString::fromLocal8Bit("警告"),QString::fromLocal8Bit("点云打开错误!"),QMessageBox::Ok);
        if(NULL!=box->button(QMessageBox::Ok))
        {
           box->button(QMessageBox::Ok)->setText(QString::fromLocal8Bit("确 定"));
        }
        QTimer::singleShot(3000,box,SLOT(accept()));
        box->exec();
        return;
    }

    //判断点云是否带有rgb信息
    if(cloudRGB->points[0].r)
    {
        viewer.reset(new pcl::visualization::PCLVisualizer("viewer", false));
        viewer->addPointCloud(cloudRGB);
        ui->qvtkWidget_1->SetRenderWindow(viewer->getRenderWindow());
        ui->qvtkWidget_1->update();
    }
    else
    {
        pcl::io::loadPCDFile(filename,*cloud);
        viewer.reset(new pcl::visualization::PCLVisualizer("viewer", false));
        viewer->addPointCloud(cloud);
        ui->qvtkWidget_1->SetRenderWindow(viewer->getRenderWindow());
        ui->qvtkWidget_1->update();
    }
}

<<<<<<< Updated upstream

void Astra::close_all()
{
    //清除彩色图像显示
    ui->label_color_1->clear();
    ui->label_color_2->clear();
    ui->label_color_3->clear();
    //清除深度图像显示
    ui->label_depth_1->clear();
    ui->label_depth_2->clear();
    //移除viewer中的点云
    viewer->removeAllPointClouds();
    //清除点云显示
    ui->qvtkWidget_1->update();
    ui->qvtkWidget_2->update();
}


void Astra::open_camera()
{  
    //弹出相机设置界面
    Camera_Settings camera_settings(this);
    camera_settings.setWindowTitle(QString::fromLocal8Bit("相机设置"));
    camera_settings.exec();

    //如果没有点击相机设置界面中的应用按钮则什么都不做
    if(!Camera_Settings::flag_applied)
    {
        return;
    }

    //彩色摄像头或深度摄像头已被打开
    if(capture.isOpened() || flag_depth)
    {
        close_camera(); //先调用关闭相机的函数
        QMessageBox *box = new QMessageBox(QMessageBox::Warning,QString::fromLocal8Bit("警告"),QString::fromLocal8Bit("摄像头打开出错!"),QMessageBox::Ok);
        if(NULL!=box->button(QMessageBox::Ok))
        {
           box->button(QMessageBox::Ok)->setText(QString::fromLocal8Bit("确 定"));
        }
        QTimer::singleShot(3000,box,SLOT(accept()));
        box->exec();
        return;
    }

    //如果彩色图分辨率不为1280*720则开启深度摄像头
    if(Camera_Settings::color_resolution != "1280*720")
    {
        if (device.open(openni::ANY_DEVICE) != openni::STATUS_OK)
        {
            QMessageBox *box = new QMessageBox(QMessageBox::Warning,QString::fromLocal8Bit("警告"),QString::fromLocal8Bit("深度摄像头打开出错!"),QMessageBox::Ok);
            if(NULL!=box->button(QMessageBox::Ok))
            {
               box->button(QMessageBox::Ok)->setText(QString::fromLocal8Bit("确 定"));
            }
            QTimer::singleShot(3000,box,SLOT(accept()));
            box->exec();
            goto color;
        }

        //创建深度流
        depthStream.create(device, openni::SENSOR_DEPTH);

        //配置深度流的模式
        std::string depth_resolution = Camera_Settings::depth_resolution.toStdString();
        int DEPTH_COLS = std::stoi(depth_resolution.substr(0,depth_resolution.size()-4));
        int DEPTH_ROWS = std::stoi(depth_resolution.substr(depth_resolution.size()-3));

        std::string depth_fps = Camera_Settings::depth_fps.toStdString();
        int DEPTH_FPS = std::stoi(depth_fps.substr(0,depth_fps.size()-3));

        depthMode.setResolution(DEPTH_COLS, DEPTH_ROWS);
        depthMode.setPixelFormat(openni::PIXEL_FORMAT_DEPTH_1_MM);
        depthMode.setFps(DEPTH_FPS);
        depthStream.setVideoMode(depthMode);

        //打开深度流
        depthStream.start();

        //设置深度图像采集标志位
        flag_depth = true;

        //创建并开启深度图像显示定时器
        timerDepth = new QTimer(this);
        timerDepth-> setTimerType(Qt::PreciseTimer);
        connect(timerDepth, SIGNAL(timeout()), this, SLOT(show_depth_image()));
        timerDepth->start(100);
    }

    //打开彩色摄像头
color:
    //彩色摄像头打开失败
    if(capture.open(Camera_Settings::color_index) != true)
    {
        QMessageBox *box = new QMessageBox(QMessageBox::Warning,QString::fromLocal8Bit("警告"),QString::fromLocal8Bit("彩色摄像打开出错!"),QMessageBox::Ok);
        if(NULL!=box->button(QMessageBox::Ok))
        {
           box->button(QMessageBox::Ok)->setText(QString::fromLocal8Bit("确 定"));
        }
        QTimer::singleShot(3000,box,SLOT(accept()));
        box->exec();
        return;
    }

    //配置rgb流的模式
    std::string color_resolution = Camera_Settings::color_resolution.toStdString();
    int COLOR_COLS = std::stoi(color_resolution.substr(0,color_resolution.size()-4));
    int COLOR_ROWS = std::stoi(color_resolution.substr(color_resolution.size()-3));

    std::string color_fps = Camera_Settings::color_fps.toStdString();
    int COLOR_FPS = std::stoi(color_fps.substr(0,color_fps.size()-3));

    capture.set(cv::CAP_PROP_FRAME_WIDTH, COLOR_COLS);//宽度
    capture.set(cv::CAP_PROP_FRAME_HEIGHT, COLOR_ROWS);//高度
    capture.set(cv::CAP_PROP_FPS, COLOR_FPS);//帧率 帧/秒

    //创建并开启彩色图像显示定时器
    timerColor = new QTimer(this);
    timerColor-> setTimerType(Qt::PreciseTimer);
    connect(timerColor, SIGNAL(timeout()), this, SLOT(show_color_image()));
    timerColor->start(100);

    //创建并开启点云显示定时器
    if(flag_depth)
    {
        timerCloud = new QTimer(this);
        timerCloud-> setTimerType(Qt::PreciseTimer);
        connect(timerCloud, SIGNAL(timeout()), this, SLOT(show_point_cloud()));
        timerCloud->start(100);
    }

    //启动点云生成线程
    Cloud_Generate *task = new Cloud_Generate;
    task->start();
}


void Astra::close_camera()
{
    //如果相机未开启则直接返回
    if(!capture.isOpened())
    {
        return;
    }

    //关闭彩色图像显示定时器
    timerColor->stop();
    //关闭彩色摄像头
    capture.release();
    //清除彩色图像显示
    ui->label_color_1->clear();
    ui->label_color_2->clear();
    ui->label_color_3->clear();

    if(Camera_Settings::color_resolution != "1280*720" && flag_depth)
    {
        //关闭深度图像显示定时器
        timerDepth->stop();
        //关闭点云显示定时器
        timerCloud->stop();
        //关闭深度流
        depthStream.stop();
        depthStream.destroy();
        //关闭深度摄像头
        device.close();
        //清除深度图像显示
        ui->label_depth_1->clear();
        ui->label_depth_2->clear();
        //清除点云
        cloud->clear();
        cloudRGB->clear();
        //移除viewer中的点云
        viewer->removeAllPointClouds();
        //清除点云显示
        ui->qvtkWidget_1->update();
        ui->qvtkWidget_2->update();
        //设置深度图像采集标志
        flag_depth = false;
    }

    //设置相机设置应用标志位
    Camera_Settings::flag_applied = false;
}


//void Astra::set_camera()
//{
////    camera_settings = new Camera_Settings(this);
////    camera_settings->setWindowTitle(QString::fromLocal8Bit("相机设置"));
////    camera_settings->show();
//    Camera_Settings camera_settings(this);
//    camera_settings.setWindowTitle(QString::fromLocal8Bit("相机设置"));
//    camera_settings.exec();
//}


void Astra::show_color_image()
{
    capture >> colorMat;

    //彩色图像采集为空
    if(colorMat.empty())
    {
        timerColor->stop();
        QMessageBox *box = new QMessageBox(QMessageBox::Warning,QString::fromLocal8Bit("警告"),QString::fromLocal8Bit("彩色图采集错误!"),QMessageBox::Ok);
        if(NULL!=box->button(QMessageBox::Ok))
        {
           box->button(QMessageBox::Ok)->setText(QString::fromLocal8Bit("确 定"));
        }
        QTimer::singleShot(3000,box,SLOT(accept()));
        box->exec();
        return;
    }

    //彩色图和深度图呈镜像关系，所以要翻转一下
    cv::flip(colorMat, colorMat, 1);
    //cv::Mat转QImage
    QImage image_color = QImage((const uchar*)colorMat.data, colorMat.cols, colorMat.rows, QImage::Format_RGB888).rgbSwapped();

    //依据不同分辨率显示不同大小的彩色图像
    if(Camera_Settings::color_resolution == "640*480")
    {
        ui->label_color_1->clear();
        ui->label_color_1->setPixmap(QPixmap::fromImage(image_color));
    }
    else if(Camera_Settings::color_resolution == "320*240")
    {
        ui->label_color_2->clear();
        ui->label_color_2->setPixmap(QPixmap::fromImage(image_color));
    }
    else if(Camera_Settings::color_resolution == "1280*720")
    {
        ui->label_color_3->clear();
        ui->label_color_3->setPixmap(QPixmap::fromImage(image_color));
    }

    bcq_colorMat.enqueue(colorMat);

    cv::waitKey(10); //防止程序卡住
}


void Astra::show_depth_image()
{
    openni::VideoFrameRef depth_frame;
    int iMaxDepth = depthStream.getMaxPixelValue();
    openni::VideoStream* pstream = &depthStream;

    int changedStreamDummy;

    openni::Status ops = openni::OpenNI::waitForAnyStream(&pstream, 1, &changedStreamDummy, 50); //等待一帧
    ops = depthStream.readFrame(&depth_frame);

    if (ops != openni::STATUS_OK)
    {
        timerDepth->stop();
        return;
    }

    //获取深度帧数据
    auto depth = depth_frame.getData();
    auto depthWidth = depth_frame.getWidth();
    auto depthHeight = depth_frame.getHeight();

    //处理并渲染深度帧数据
    cv::Mat rawMat(depthHeight, depthWidth, CV_16UC1, (void*)depth);
    rawMat.convertTo(depthMat, CV_8UC1, 255.0 / iMaxDepth);

    //深度图采集为空
    if(depthMat.empty())
    {
        timerDepth->stop();
        QMessageBox *box = new QMessageBox(QMessageBox::Warning,QString::fromLocal8Bit("警告"),QString::fromLocal8Bit("深度图采集错误!"),QMessageBox::Ok);
        if(NULL!=box->button(QMessageBox::Ok))
        {
           box->button(QMessageBox::Ok)->setText(QString::fromLocal8Bit("确 定"));
        }
        QTimer::singleShot(3000,box,SLOT(accept()));
        box->exec();
        return;
    }

    //cv::Mat转QImage
    QImage image_depth = QImage((const uchar*)depthMat.data, depthMat.cols,depthMat.rows, QImage::Format_Grayscale8).rgbSwapped();

    //依据不同分辨率显示不同大小的深度图像
    if(Camera_Settings::depth_resolution == "640*480")
    {
        ui->label_depth_1->clear();
        ui->label_depth_1->setPixmap(QPixmap::fromImage(image_depth));
    }
    else if(Camera_Settings::depth_resolution == "320*240")
    {
        ui->label_depth_2->clear();
        ui->label_depth_2->setPixmap(QPixmap::fromImage(image_depth));
    }

    bcq_depthMat.enqueue(depthMat);

    cv::waitKey(10); //防止程序卡住
}


void Astra::show_point_cloud()
{
    if(bcq_cloudRGB.try_dequeue(cloudRGB))
    {
        viewer.reset(new pcl::visualization::PCLVisualizer("viewer", false));
        viewer->addPointCloud(cloudRGB);
        flag_cloud = false;

    }
    else if(bcq_cloud.try_dequeue(cloud))
    {
        viewer.reset(new pcl::visualization::PCLVisualizer("viewer", false));
        viewer->addPointCloud(cloud);
        flag_cloud = true;
    }

    //依据不同分辨率显示点云
    if(Camera_Settings::depth_resolution == "640*480")
    {
        ui->qvtkWidget_1->SetRenderWindow(viewer->getRenderWindow());
        ui->qvtkWidget_1->update();
    }
    else if(Camera_Settings::depth_resolution == "320*240")
    {
        ui->qvtkWidget_2->SetRenderWindow(viewer->getRenderWindow());
        ui->qvtkWidget_2->update();
    }
}


void Astra::help_guide()
{
    QMessageBox *box = new QMessageBox(QMessageBox::Information, QString::fromLocal8Bit("使用说明"),
                                       QString::fromLocal8Bit(" 本软件提供了Astra相机的深度图，\n 彩色图以及点云显示和保存功能。\n\n"
                                                              " 由于开发周期短和本人能力有限，\n 其他功能还尚未完善，敬请谅解。"),
                                       QMessageBox::Ok);
    if(NULL!=box->button(QMessageBox::Ok))
    {
       box->button(QMessageBox::Ok)->setText(QString::fromLocal8Bit("确 定"));
    }
    box->setStyleSheet("QLabel{min-width: 240px;min-height: 180px;}");
    box->exec();
}


void Astra::help_about()
{
    QMessageBox::about(NULL, QString::fromLocal8Bit("关于AstraGUI"), "by taify");
=======
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
>>>>>>> Stashed changes
}
