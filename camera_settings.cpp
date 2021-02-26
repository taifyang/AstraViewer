/**
  *@file camera_settings.cpp
  *@brief 相机设置源文件
  */


#include "camera_settings.h"
#include "mainwindow.h"
#include "ui_camera_settings.h"
#include "ui_mainwindow.h"
#include <QDebug>


int Camera_Settings::color_index = 0;
QString Camera_Settings::color_resolution = "640*480";
QString Camera_Settings::color_fps= "30fps";
QString Camera_Settings::depth_resolution = "640*480";
QString Camera_Settings::depth_fps = "30fps";
bool Camera_Settings::flag_applied = false;


Camera_Settings::Camera_Settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Camera_Settings)
{
    ui->setupUi(this);
}


Camera_Settings::~Camera_Settings()
{
    delete ui;
}


void Camera_Settings::on_pushButton_apply_clicked()
{
    Astra *ptr = (Astra*)parentWidget(); //指向父窗口的指针

    color_index = ui->comboBox_color_index->currentIndex();

    color_resolution = ui->comboBox_color_resolution->currentText();
    depth_resolution = ui->comboBox_depth_resolution->currentText();

    if(color_resolution=="640*480" && depth_resolution=="640*480")
    {
        ptr->ui->stackedWidget->setCurrentIndex(0);
    }
    else if(color_resolution=="320*240" && depth_resolution=="320*240")
    {
        ptr->ui->stackedWidget->setCurrentIndex(1);
    }
    else if(color_resolution == "1280*720")
    {
        ptr->ui->stackedWidget->setCurrentIndex(2);
    }
    else
    {
        QMessageBox *box = new QMessageBox(QMessageBox::Warning,QString::fromLocal8Bit("警告"),QString::fromLocal8Bit("分辨率设置错误!"),QMessageBox::Ok);
        if(NULL!=box->button(QMessageBox::Ok))
        {
           box->button(QMessageBox::Ok)->setText(QString::fromLocal8Bit("确 定"));
        }
        QTimer::singleShot(3000,box,SLOT(accept()));
        box->exec();
        return;
    }

    color_fps = ui->comboBox_color_fps->currentText();
    depth_fps = ui->comboBox_depth_fps->currentText();

    if(color_resolution != "1280*720" && color_fps != depth_fps)
    {
        QMessageBox *box = new QMessageBox(QMessageBox::Warning,QString::fromLocal8Bit("警告"),QString::fromLocal8Bit("帧率设置错误!"),QMessageBox::Ok);
        if(NULL!=box->button(QMessageBox::Ok))
        {
           box->button(QMessageBox::Ok)->setText(QString::fromLocal8Bit("确 定"));
        }
        QTimer::singleShot(3000,box,SLOT(accept()));
        box->exec();
        return;
    }

    flag_applied = true;
    this->close(); //点击应用后相机设置窗口关闭
}



