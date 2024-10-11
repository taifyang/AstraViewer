#ifndef UTILS_H
#define UTILS_H

#include <QImage>

#include <algorithm>

void convertYUV422ToRGB888(const uint8_t* yuv, uint8_t* rgb, int width, int height)
{
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x += 2)
        {
            int index = (y * width + x) * 2; // YUV422 数据索引
            int Y0 = yuv[index];         // 第一个 Y 值
            int U  = yuv[index + 1];     // U 值
            int Y1 = yuv[index + 2];     // 第二个 Y 值
            int V  = yuv[index + 3];     // V 值

            // 将 YUV 转换为 RGB
            int C0 = Y0 - 16; // 偏移
            int C1 = Y1 - 16; // 偏移
            int D = U - 128;  // 偏移
            int E = V - 128;  // 偏移

            // 计算 RGB 值
            int R0 = std::clamp((298 * C0 + 409 * E + 128) >> 8, 0, 255);
            int G0 = std::clamp((298 * C0 - 100 * D - 208 * E + 128) >> 8, 0, 255);
            int B0 = std::clamp((298 * C0 + 516 * D + 128) >> 8, 0, 255);

            int R1 = std::clamp((298 * C1 + 409 * E + 128) >> 8, 0, 255);
            int G1 = std::clamp((298 * C1 - 100 * D - 208 * E + 128) >> 8, 0, 255);
            int B1 = std::clamp((298 * C1 + 516 * D + 128) >> 8, 0, 255);

            // 将 RGB 值存储到输出数组中
            int rgbIndex0 = (y * width + width - x - 1) * 3; // 第一个像素
            int rgbIndex1 = (y * width + width - x - 2) * 3; // 第二个像素

            rgb[rgbIndex0 + 0] = static_cast<uint8_t>(R0); // R0
            rgb[rgbIndex0 + 1] = static_cast<uint8_t>(G0); // G0
            rgb[rgbIndex0 + 2] = static_cast<uint8_t>(B0); // B0

            rgb[rgbIndex1 + 0] = static_cast<uint8_t>(R1); // R1
            rgb[rgbIndex1 + 1] = static_cast<uint8_t>(G1); // G1
            rgb[rgbIndex1 + 2] = static_cast<uint8_t>(B1); // B1
        }
    }
}

QImage rgbToQImage(const uint8_t* data, int width, int height)
{
    QImage image(width, height, QImage::Format_RGB888);
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            int index = (y * width + x) * 3;
            image.setPixel(x, y, qRgb(data[index + 2], data[index + 1], data[index]));
        }
    }
    return image;
}

QImage Map16ToQImage(const uint16_t* data, int width, int height, float ratio)
{
    QImage image(width, height, QImage::Format_Grayscale8);
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            uint16_t Value = data[y * width + x];
            uint8_t grayValue = static_cast<uint8_t>(Value * ratio);
            image.setPixel(x, y, qRgb(grayValue, grayValue, grayValue));
        }
    }
    return image;
}

#endif // UTILS_H
