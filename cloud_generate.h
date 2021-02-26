/**
  *@file cloud_generate.h
  *@brief 点云生成头文件
  */


#ifndef CLOUD_GENERATE_H
#define CLOUD_GENERATE_H


#include "mainwindow.h"


/**
 * @brief The Cloud_Generate class
 */
class Cloud_Generate : public QThread
{
private:
    /**
     * @brief run 重写QThread的run方法
     */
    void run();
};


#endif // CLOUD_GENERATE_H
