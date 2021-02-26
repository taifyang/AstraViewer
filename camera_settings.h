/**
  *@file camera_settings.h
  *@brief 相机设置头文件
  */


#ifndef CAMERA_SETTINGS_H
#define CAMERA_SETTINGS_H

#include <QDialog>
#include <QString>


namespace Ui {
class Camera_Settings;
}


/**
 * @brief The Camera_Settings class
 */
class Camera_Settings : public QDialog
{
    Q_OBJECT

public:
    Camera_Settings(QWidget *parent = 0);

    ~Camera_Settings();

    /**
     * @brief color_index 彩色摄像头编号
     */
    static int color_index;

    /**
     * @brief color_resolution 彩色摄像头分辨率
     */
    static QString color_resolution;

    /**
     * @brief color_fps 彩色摄像头帧率
     */
    static QString color_fps;

    /**
     * @brief depth_resolution 深度摄像头分辨率
     */
    static QString depth_resolution;

    /**
     * @brief depth_fps 深度摄像头帧率
     */
    static QString depth_fps;

    /**
     * @brief flag_applied 相机设置应用标志
     */
    static bool flag_applied;

private slots:
    /**
     * @brief on_pushButton_apply_clicked 应用相机设置
     */
    void on_pushButton_apply_clicked();

private:
    Ui::Camera_Settings *ui;
};

#endif // CAMERA_SETTINGS_H
