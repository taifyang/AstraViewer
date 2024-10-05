/**
  *@file mainwindow.cpp
  *@brief ������Դ�ļ�
  */


#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

<<<<<<< Updated upstream
/**
 * @brief cloud ��ɫ����
 */
PointCloud::Ptr cloud(new PointCloud);

/**
 * @brief cloudRGB ��ɫ����
 */
PointCloudRGB::Ptr cloudRGB(new PointCloudRGB);

/**
 * @brief bcq_colorMat colorMat��������
 */
BlockingConcurrentQueue<cv::Mat> bcq_colorMat;

/**
 * @brief bcq_depthMat depthMat��������
 */
BlockingConcurrentQueue<cv::Mat> bcq_depthMat;

/**
 * @brief bcq_cloud cloud��������
 */
BlockingConcurrentQueue<PointCloud::Ptr> bcq_cloud;

/**
 * @brief bcq_cloudRGB cloudRGB��������
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
    //ѡ��·��
    QString fileName = QFileDialog::getSaveFileName(this,QString::fromLocal8Bit("�����ɫͼ")," ",tr(" (*.bmp *.jpg *.png)"));

<<<<<<< Updated upstream
    //�ļ���Ϊ��
    if (fileName.isEmpty())
    {
        QMessageBox *box = new QMessageBox(QMessageBox::Warning,QString::fromLocal8Bit("����"),QString::fromLocal8Bit("�ļ���Ϊ��!"),QMessageBox::Ok);
        if(NULL!=box->button(QMessageBox::Ok))
        {
           box->button(QMessageBox::Ok)->setText(QString::fromLocal8Bit("ȷ ��"));
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

    //��ɫͼ��Ϊ��
    if (colorMat.empty())
    {
        QMessageBox *box = new QMessageBox(QMessageBox::Warning,QString::fromLocal8Bit("����"),QString::fromLocal8Bit("��ɫͼ�������!"),QMessageBox::Ok);
        if(NULL!=box->button(QMessageBox::Ok))
        {
<<<<<<< Updated upstream
           box->button(QMessageBox::Ok)->setText(QString::fromLocal8Bit("ȷ ��"));
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

    std::string filename(fileName.toLocal8Bit().data()); //֧�ִ�����·���Ķ�ȡ
    cv::imwrite(filename, colorMat); //����ɫͼ��д�����
}


void Astra::save_depth_image()
{
    //ѡ��·��
    QString fileName = QFileDialog::getSaveFileName(this,QString::fromLocal8Bit("�������ͼ")," ",tr(" (*.bmp *.jpg *.png)"));

    //�ļ���Ϊ��
    if (fileName.isEmpty())
    {
        QMessageBox *box = new QMessageBox(QMessageBox::Warning,QString::fromLocal8Bit("����"),QString::fromLocal8Bit("�ļ���Ϊ��!"),QMessageBox::Ok);
        if(NULL!=box->button(QMessageBox::Ok))
        {
           box->button(QMessageBox::Ok)->setText(QString::fromLocal8Bit("ȷ ��"));
        }
        QTimer::singleShot(3000,box,SLOT(accept()));
        box->exec();
        return;
    }

    //���ͼΪ��
    if (depthMat.empty())
    {
        QMessageBox *box = new QMessageBox(QMessageBox::Warning,QString::fromLocal8Bit("����"),QString::fromLocal8Bit("���ͼ�������!"),QMessageBox::Ok);
        if(NULL!=box->button(QMessageBox::Ok))
        {
           box->button(QMessageBox::Ok)->setText(QString::fromLocal8Bit("ȷ ��"));
        }
        QTimer::singleShot(3000,box,SLOT(accept()));
        box->exec();
        return;
    }

    std::string filename(fileName.toLocal8Bit().data()); //֧�ִ�����·���Ķ�ȡ
    cv::imwrite(filename, depthMat); //�����ͼ��д�����
}


void Astra::save_point_cloud()
{
    //ѡ��·��
    QString fileName = QFileDialog::getSaveFileName(this,QString::fromLocal8Bit("�������")," ",tr(" (*.pcd)"));

    //�ļ���Ϊ��
    if (fileName.isEmpty())
    {
        QMessageBox *box = new QMessageBox(QMessageBox::Warning,QString::fromLocal8Bit("����"),QString::fromLocal8Bit("�ļ���Ϊ��!"),QMessageBox::Ok);
        if(NULL!=box->button(QMessageBox::Ok))
        {
           box->button(QMessageBox::Ok)->setText(QString::fromLocal8Bit("ȷ ��"));
        }
        QTimer::singleShot(3000,box,SLOT(accept()));
        box->exec();
        return;
    }

    //��������Ϊ��
    if (cloudRGB->size()==0 && cloud->size()==0)
    {
        QMessageBox *box = new QMessageBox(QMessageBox::Warning,QString::fromLocal8Bit("����"),QString::fromLocal8Bit("���Ʊ������!"),QMessageBox::Ok);
        if(NULL!=box->button(QMessageBox::Ok))
        {
           box->button(QMessageBox::Ok)->setText(QString::fromLocal8Bit("ȷ ��"));
        }
        QTimer::singleShot(3000,box,SLOT(accept()));
        box->exec();
        return;
    }

    std::string filename(fileName.toLocal8Bit().data()); //֧�ִ�����·���Ķ�ȡ
    if(flag_cloud)
        pcl::io::savePCDFileBinary(filename,*cloud); //����ɫ����д�����
    else
        pcl::io::savePCDFileBinary(filename,*cloudRGB); //����ɫ����д�����
}


void Astra::open_color_image()
{
    ui->stackedWidget->setCurrentIndex(0);

    //ѡ��·��
    QString fileName  = QFileDialog::getOpenFileName(this,QString::fromLocal8Bit("�򿪲�ɫͼ"),"home",tr("(*.bmp *.jpg *.png )"));
    //�ļ���Ϊ��
    if (fileName.isEmpty())
    {
        QMessageBox *box = new QMessageBox(QMessageBox::Warning,QString::fromLocal8Bit("����"),QString::fromLocal8Bit("�ļ���Ϊ��!"),QMessageBox::Ok);
        if(NULL!=box->button(QMessageBox::Ok))
        {
           box->button(QMessageBox::Ok)->setText(QString::fromLocal8Bit("ȷ ��"));
        }
        QTimer::singleShot(3000,box,SLOT(accept()));
        box->exec();
        return;
    }

    std::string filename(fileName.toLocal8Bit().data()); //֧�ִ�����·���Ķ�ȡ
    cv::Mat colorMat = cv::imread(filename,-1); //-1��ʾ��ȡԭʼ����
    //��ɫͼ��Ϊ�ջ�ͨ������Ϊ3
    if(colorMat.empty() || colorMat.channels()!=3)
    {
        QMessageBox *box = new QMessageBox(QMessageBox::Warning,QString::fromLocal8Bit("����"),QString::fromLocal8Bit("��ɫͼ�򿪴���!"),QMessageBox::Ok);
        if(NULL!=box->button(QMessageBox::Ok))
        {
           box->button(QMessageBox::Ok)->setText(QString::fromLocal8Bit("ȷ ��"));
        }
        QTimer::singleShot(3000,box,SLOT(accept()));
        box->exec();
        return;
    }

    //����ͼ��ʹ����Ӧ���ڴ�С
    cv::resize(colorMat,colorMat,cv::Size(ui->label_color_1->width(),ui->label_color_1->height()));
    //cv::MatתQImage
    QImage image_color = QImage((const uchar*)colorMat.data,colorMat.cols,colorMat.rows,QImage::Format_RGB888).rgbSwapped();

    //����ui
    ui->label_color_1->clear();
    ui->label_color_1->setPixmap(QPixmap::fromImage(image_color));
}


void Astra::open_depth_image()
{
    ui->stackedWidget->setCurrentIndex(0);

    //ѡ��·��
    QString fileName  = QFileDialog::getOpenFileName(this,QString::fromLocal8Bit("�����ͼ"),"home",tr("(*.bmp *.jpg *.png )"));
    //�ļ���Ϊ��
    if (fileName.isEmpty())
    {
        QMessageBox *box = new QMessageBox(QMessageBox::Warning,QString::fromLocal8Bit("����"),QString::fromLocal8Bit("�ļ���Ϊ��!"),QMessageBox::Ok);
        if(NULL!=box->button(QMessageBox::Ok))
        {
           box->button(QMessageBox::Ok)->setText(QString::fromLocal8Bit("ȷ ��"));
        }
        QTimer::singleShot(3000,box,SLOT(accept()));
        box->exec();
        return;
    }

    std::string filename(fileName.toLocal8Bit().data()); //֧�ִ�����·���Ķ�ȡ
    cv::Mat depthMat = cv::imread(filename,-1); //-1��ʾ��ȡԭʼ����
     //���ͼ��Ϊ�ջ�ͨ������Ϊ1
    if(depthMat.empty() || depthMat.channels()!=1)
    {
        QMessageBox *box = new QMessageBox(QMessageBox::Warning,QString::fromLocal8Bit("����"),QString::fromLocal8Bit("���ͼ�򿪴���!"),QMessageBox::Ok);
        if(NULL!=box->button(QMessageBox::Ok))
        {
           box->button(QMessageBox::Ok)->setText(QString::fromLocal8Bit("ȷ ��"));
        }
        QTimer::singleShot(3000,box,SLOT(accept()));
        box->exec();
        return;
    }

    //����ͼ��ʹ����Ӧ���ڴ�С
    cv::resize(depthMat,depthMat,cv::Size(ui->label_depth_1->width(),ui->label_depth_1->height()));
    //cv::MatתQImage
    QImage image_depth = QImage((const uchar*)depthMat.data,depthMat.cols,depthMat.rows,QImage::Format_Grayscale8).rgbSwapped();

    //����ui
    ui->label_depth_1->clear();
    ui->label_depth_1->setPixmap(QPixmap::fromImage(image_depth));

}


void Astra::open_point_cloud()
{
    ui->stackedWidget->setCurrentIndex(0);
    //ѡ��·��
    QString fileName  = QFileDialog::getOpenFileName(this,QString::fromLocal8Bit("�򿪵���"),"home",tr("(*.pcd)"));
    //�ļ���Ϊ��
    if (fileName.isEmpty())
    {
        QMessageBox *box = new QMessageBox(QMessageBox::Warning,QString::fromLocal8Bit("����"),QString::fromLocal8Bit("�ļ���Ϊ��!"),QMessageBox::Ok);
        if(NULL!=box->button(QMessageBox::Ok))
        {
           box->button(QMessageBox::Ok)->setText(QString::fromLocal8Bit("ȷ ��"));
        }
        QTimer::singleShot(3000,box,SLOT(accept()));
        box->exec();
        return;
    }

    std::string filename(fileName.toLocal8Bit().data()); //֧�ִ�����·���Ķ�ȡ

    PointCloud::Ptr cloud(new PointCloud);
    PointCloudRGB::Ptr cloudRGB(new PointCloudRGB);

    //���Ƽ���ʧ��
    if(pcl::io::loadPCDFile(filename,*cloudRGB)==-1)
    {
        QMessageBox *box = new QMessageBox(QMessageBox::Warning,QString::fromLocal8Bit("����"),QString::fromLocal8Bit("���ƴ򿪴���!"),QMessageBox::Ok);
        if(NULL!=box->button(QMessageBox::Ok))
        {
           box->button(QMessageBox::Ok)->setText(QString::fromLocal8Bit("ȷ ��"));
        }
        QTimer::singleShot(3000,box,SLOT(accept()));
        box->exec();
        return;
    }

    //�жϵ����Ƿ����rgb��Ϣ
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
    //�����ɫͼ����ʾ
    ui->label_color_1->clear();
    ui->label_color_2->clear();
    ui->label_color_3->clear();
    //������ͼ����ʾ
    ui->label_depth_1->clear();
    ui->label_depth_2->clear();
    //�Ƴ�viewer�еĵ���
    viewer->removeAllPointClouds();
    //���������ʾ
    ui->qvtkWidget_1->update();
    ui->qvtkWidget_2->update();
}


void Astra::open_camera()
{  
    //����������ý���
    Camera_Settings camera_settings(this);
    camera_settings.setWindowTitle(QString::fromLocal8Bit("�������"));
    camera_settings.exec();

    //���û�е��������ý����е�Ӧ�ð�ť��ʲô������
    if(!Camera_Settings::flag_applied)
    {
        return;
    }

    //��ɫ����ͷ���������ͷ�ѱ���
    if(capture.isOpened() || flag_depth)
    {
        close_camera(); //�ȵ��ùر�����ĺ���
        QMessageBox *box = new QMessageBox(QMessageBox::Warning,QString::fromLocal8Bit("����"),QString::fromLocal8Bit("����ͷ�򿪳���!"),QMessageBox::Ok);
        if(NULL!=box->button(QMessageBox::Ok))
        {
           box->button(QMessageBox::Ok)->setText(QString::fromLocal8Bit("ȷ ��"));
        }
        QTimer::singleShot(3000,box,SLOT(accept()));
        box->exec();
        return;
    }

    //�����ɫͼ�ֱ��ʲ�Ϊ1280*720�����������ͷ
    if(Camera_Settings::color_resolution != "1280*720")
    {
        if (device.open(openni::ANY_DEVICE) != openni::STATUS_OK)
        {
            QMessageBox *box = new QMessageBox(QMessageBox::Warning,QString::fromLocal8Bit("����"),QString::fromLocal8Bit("�������ͷ�򿪳���!"),QMessageBox::Ok);
            if(NULL!=box->button(QMessageBox::Ok))
            {
               box->button(QMessageBox::Ok)->setText(QString::fromLocal8Bit("ȷ ��"));
            }
            QTimer::singleShot(3000,box,SLOT(accept()));
            box->exec();
            goto color;
        }

        //���������
        depthStream.create(device, openni::SENSOR_DEPTH);

        //�����������ģʽ
        std::string depth_resolution = Camera_Settings::depth_resolution.toStdString();
        int DEPTH_COLS = std::stoi(depth_resolution.substr(0,depth_resolution.size()-4));
        int DEPTH_ROWS = std::stoi(depth_resolution.substr(depth_resolution.size()-3));

        std::string depth_fps = Camera_Settings::depth_fps.toStdString();
        int DEPTH_FPS = std::stoi(depth_fps.substr(0,depth_fps.size()-3));

        depthMode.setResolution(DEPTH_COLS, DEPTH_ROWS);
        depthMode.setPixelFormat(openni::PIXEL_FORMAT_DEPTH_1_MM);
        depthMode.setFps(DEPTH_FPS);
        depthStream.setVideoMode(depthMode);

        //�������
        depthStream.start();

        //�������ͼ��ɼ���־λ
        flag_depth = true;

        //�������������ͼ����ʾ��ʱ��
        timerDepth = new QTimer(this);
        timerDepth-> setTimerType(Qt::PreciseTimer);
        connect(timerDepth, SIGNAL(timeout()), this, SLOT(show_depth_image()));
        timerDepth->start(100);
    }

    //�򿪲�ɫ����ͷ
color:
    //��ɫ����ͷ��ʧ��
    if(capture.open(Camera_Settings::color_index) != true)
    {
        QMessageBox *box = new QMessageBox(QMessageBox::Warning,QString::fromLocal8Bit("����"),QString::fromLocal8Bit("��ɫ����򿪳���!"),QMessageBox::Ok);
        if(NULL!=box->button(QMessageBox::Ok))
        {
           box->button(QMessageBox::Ok)->setText(QString::fromLocal8Bit("ȷ ��"));
        }
        QTimer::singleShot(3000,box,SLOT(accept()));
        box->exec();
        return;
    }

    //����rgb����ģʽ
    std::string color_resolution = Camera_Settings::color_resolution.toStdString();
    int COLOR_COLS = std::stoi(color_resolution.substr(0,color_resolution.size()-4));
    int COLOR_ROWS = std::stoi(color_resolution.substr(color_resolution.size()-3));

    std::string color_fps = Camera_Settings::color_fps.toStdString();
    int COLOR_FPS = std::stoi(color_fps.substr(0,color_fps.size()-3));

    capture.set(cv::CAP_PROP_FRAME_WIDTH, COLOR_COLS);//���
    capture.set(cv::CAP_PROP_FRAME_HEIGHT, COLOR_ROWS);//�߶�
    capture.set(cv::CAP_PROP_FPS, COLOR_FPS);//֡�� ֡/��

    //������������ɫͼ����ʾ��ʱ��
    timerColor = new QTimer(this);
    timerColor-> setTimerType(Qt::PreciseTimer);
    connect(timerColor, SIGNAL(timeout()), this, SLOT(show_color_image()));
    timerColor->start(100);

    //����������������ʾ��ʱ��
    if(flag_depth)
    {
        timerCloud = new QTimer(this);
        timerCloud-> setTimerType(Qt::PreciseTimer);
        connect(timerCloud, SIGNAL(timeout()), this, SLOT(show_point_cloud()));
        timerCloud->start(100);
    }

    //�������������߳�
    Cloud_Generate *task = new Cloud_Generate;
    task->start();
}


void Astra::close_camera()
{
    //������δ������ֱ�ӷ���
    if(!capture.isOpened())
    {
        return;
    }

    //�رղ�ɫͼ����ʾ��ʱ��
    timerColor->stop();
    //�رղ�ɫ����ͷ
    capture.release();
    //�����ɫͼ����ʾ
    ui->label_color_1->clear();
    ui->label_color_2->clear();
    ui->label_color_3->clear();

    if(Camera_Settings::color_resolution != "1280*720" && flag_depth)
    {
        //�ر����ͼ����ʾ��ʱ��
        timerDepth->stop();
        //�رյ�����ʾ��ʱ��
        timerCloud->stop();
        //�ر������
        depthStream.stop();
        depthStream.destroy();
        //�ر��������ͷ
        device.close();
        //������ͼ����ʾ
        ui->label_depth_1->clear();
        ui->label_depth_2->clear();
        //�������
        cloud->clear();
        cloudRGB->clear();
        //�Ƴ�viewer�еĵ���
        viewer->removeAllPointClouds();
        //���������ʾ
        ui->qvtkWidget_1->update();
        ui->qvtkWidget_2->update();
        //�������ͼ��ɼ���־
        flag_depth = false;
    }

    //�����������Ӧ�ñ�־λ
    Camera_Settings::flag_applied = false;
}


//void Astra::set_camera()
//{
////    camera_settings = new Camera_Settings(this);
////    camera_settings->setWindowTitle(QString::fromLocal8Bit("�������"));
////    camera_settings->show();
//    Camera_Settings camera_settings(this);
//    camera_settings.setWindowTitle(QString::fromLocal8Bit("�������"));
//    camera_settings.exec();
//}


void Astra::show_color_image()
{
    capture >> colorMat;

    //��ɫͼ��ɼ�Ϊ��
    if(colorMat.empty())
    {
        timerColor->stop();
        QMessageBox *box = new QMessageBox(QMessageBox::Warning,QString::fromLocal8Bit("����"),QString::fromLocal8Bit("��ɫͼ�ɼ�����!"),QMessageBox::Ok);
        if(NULL!=box->button(QMessageBox::Ok))
        {
           box->button(QMessageBox::Ok)->setText(QString::fromLocal8Bit("ȷ ��"));
        }
        QTimer::singleShot(3000,box,SLOT(accept()));
        box->exec();
        return;
    }

    //��ɫͼ�����ͼ�ʾ����ϵ������Ҫ��תһ��
    cv::flip(colorMat, colorMat, 1);
    //cv::MatתQImage
    QImage image_color = QImage((const uchar*)colorMat.data, colorMat.cols, colorMat.rows, QImage::Format_RGB888).rgbSwapped();

    //���ݲ�ͬ�ֱ�����ʾ��ͬ��С�Ĳ�ɫͼ��
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

    cv::waitKey(10); //��ֹ����ס
}


void Astra::show_depth_image()
{
    openni::VideoFrameRef depth_frame;
    int iMaxDepth = depthStream.getMaxPixelValue();
    openni::VideoStream* pstream = &depthStream;

    int changedStreamDummy;

    openni::Status ops = openni::OpenNI::waitForAnyStream(&pstream, 1, &changedStreamDummy, 50); //�ȴ�һ֡
    ops = depthStream.readFrame(&depth_frame);

    if (ops != openni::STATUS_OK)
    {
        timerDepth->stop();
        return;
    }

    //��ȡ���֡����
    auto depth = depth_frame.getData();
    auto depthWidth = depth_frame.getWidth();
    auto depthHeight = depth_frame.getHeight();

    //������Ⱦ���֡����
    cv::Mat rawMat(depthHeight, depthWidth, CV_16UC1, (void*)depth);
    rawMat.convertTo(depthMat, CV_8UC1, 255.0 / iMaxDepth);

    //���ͼ�ɼ�Ϊ��
    if(depthMat.empty())
    {
        timerDepth->stop();
        QMessageBox *box = new QMessageBox(QMessageBox::Warning,QString::fromLocal8Bit("����"),QString::fromLocal8Bit("���ͼ�ɼ�����!"),QMessageBox::Ok);
        if(NULL!=box->button(QMessageBox::Ok))
        {
           box->button(QMessageBox::Ok)->setText(QString::fromLocal8Bit("ȷ ��"));
        }
        QTimer::singleShot(3000,box,SLOT(accept()));
        box->exec();
        return;
    }

    //cv::MatתQImage
    QImage image_depth = QImage((const uchar*)depthMat.data, depthMat.cols,depthMat.rows, QImage::Format_Grayscale8).rgbSwapped();

    //���ݲ�ͬ�ֱ�����ʾ��ͬ��С�����ͼ��
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

    cv::waitKey(10); //��ֹ����ס
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

    //���ݲ�ͬ�ֱ�����ʾ����
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
    QMessageBox *box = new QMessageBox(QMessageBox::Information, QString::fromLocal8Bit("ʹ��˵��"),
                                       QString::fromLocal8Bit(" ������ṩ��Astra��������ͼ��\n ��ɫͼ�Լ�������ʾ�ͱ��湦�ܡ�\n\n"
                                                              " ���ڿ������ڶ̺ͱ����������ޣ�\n �������ܻ���δ���ƣ������½⡣"),
                                       QMessageBox::Ok);
    if(NULL!=box->button(QMessageBox::Ok))
    {
       box->button(QMessageBox::Ok)->setText(QString::fromLocal8Bit("ȷ ��"));
    }
    box->setStyleSheet("QLabel{min-width: 240px;min-height: 180px;}");
    box->exec();
}


void Astra::help_about()
{
    QMessageBox::about(NULL, QString::fromLocal8Bit("����AstraGUI"), "by taify");
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
