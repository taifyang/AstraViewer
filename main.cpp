/**
  *@file main.cpp
  *@brief 主函数源文件
  */


#include "mainwindow.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Astra *w = new Astra;
    w->show();

    return a.exec();
}
