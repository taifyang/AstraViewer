/**
  *@file cloud_generate.cpp
  *@brief 点云生成源文件
  */


#include "cloud_generate.h"



extern PointCloud::Ptr cloud;
extern PointCloudRGB::Ptr cloudRGB;

extern BlockingConcurrentQueue<cv::Mat> bcq_colorMat;
extern BlockingConcurrentQueue<cv::Mat> bcq_depthMat;
extern BlockingConcurrentQueue<PointCloud::Ptr> bcq_cloud;
extern BlockingConcurrentQueue<PointCloudRGB::Ptr> bcq_cloudRGB;


void Cloud_Generate::run()
{
    float camera_factor, camera_cx, camera_cy, camera_fx, camera_fy; //相机内参
    cv::Mat colorMat, depthMat;

    while(true)
    {
        if(bcq_depthMat.try_dequeue(depthMat))
        {
            if(Camera_Settings::depth_resolution == "640*480")
            {
                camera_factor = 1;
                camera_cx = 311.0;
                camera_cy = 244.0;
                camera_fx = 593.0;
                camera_fy = 588.0;
            }
            else if(Camera_Settings::depth_resolution == "320*240")
            {
                camera_factor = 1;
                camera_cx = 311.0*0.5;
                camera_cy = 244.0*0.5;
                camera_fx = 593.0*0.5;
                camera_fy = 588.0*0.5;
            }

            if(bcq_colorMat.try_dequeue(colorMat))
            {
                cloudRGB->clear(); //重置点云为空

                //遍历深度图
                for (int i = 0; i < depthMat.rows; ++i)
                {
                    uchar* depthData = depthMat.data + i*depthMat.step;
                    uchar* colorData = colorMat.data + i*colorMat.step;
                    for (int j = 0; j < depthMat.cols; ++j)
                    {
                        if (depthData == 0)
                            continue;

                        pcl::PointXYZRGB point;

                        //计算点的空间坐标
                        point.z = double(*(depthData++)) / camera_factor;
                        point.x = (j - camera_cx) * point.z / camera_fx;
                        point.y = -(i - camera_cy) * point.z / camera_fy;

                        //从彩色图像中获取该点的颜色
                        point.b = *(colorData++);
                        point.g = *(colorData++);
                        point.r = *(colorData++);

                        //把该点加入到点云中
                        cloudRGB->points.push_back(point);
                    }
                }
                bcq_cloudRGB.enqueue(cloudRGB);
            }
            else
            {
                cloud->clear(); //重置点云为空

                //遍历深度图
                for (int i = 0; i < depthMat.rows; ++i)
                {
                    uchar* depthData = depthMat.data + i*depthMat.step;
                    for (int j = 0; j < depthMat.cols; ++j)
                    {
                        if (depthData == 0)
                            continue;

                        pcl::PointXYZ point;

                        //计算点的空间坐标
                        point.z = double(*(depthData++)) / camera_factor;
                        point.x = (j - camera_cx) * point.z / camera_fx;
                        point.y = -(i - camera_cy) * point.z / camera_fy;

                        //把该点加入到点云中
                        cloud->points.push_back(point);
                    }
                }
                bcq_cloud.enqueue(cloud);
            }
        }
    }
}
