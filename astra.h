#ifndef ASTRA_H
#define ASTRA_H

#include <QDebug>

#include <astra_core/astra_core.hpp>
#include <astra/astra.hpp>



enum ColorMode
{
    MODE_COLOR,
    MODE_IR,
};


class MultiFrameListener : public astra::FrameListener
{
public:
    struct StreamView
    {
        uint8_t* buffer_;
        int width_{0};
        int height_{0};
    };

    void init_view(int width, int height, StreamView& view)
    {
        if (view.buffer_ == nullptr || width != view.width_ || height != view.height_)
        {
            view.width_ = width;
            view.height_ = height;
            const int byteLength = width * height * 3;
            view.buffer_ = new uint8_t[byteLength];
            std::fill(&view.buffer_[0], &view.buffer_[0] + view.width_ * view.height_ * 3, 0);
        }
    }

    void update_depth(astra::Frame& frame)
    {
        const astra::PointFrame pointFrame = frame.get<astra::PointFrame>();
        if (!pointFrame.is_valid())
        {
            return;
        }

        const int depthWidth = pointFrame.width();
        const int depthHeight = pointFrame.height();

        init_view(depthWidth, depthHeight, depthView_);
        qDebug() << "depth";

        const astra::Vector3f* pointData = pointFrame.data();
        uint8_t* buffer = &depthView_.buffer_[0];
        float min_value = INT_MAX, max_value = INT_MIN;
        for (int i = 0; i < depthWidth * depthHeight; i++)
        {
            if(pointData[i].z > max_value)    max_value = pointData[i].z;
            if(pointData[i].z < min_value)    min_value = pointData[i].z;
        }
        for (int i = 0; i < depthWidth * depthHeight; i++)
        {
            buffer[i] = 255 * (pointData[i].z - min_value) / (max_value - min_value);
        }
    }

    void update_color(astra::Frame& frame)
    {
        const astra::ColorFrame colorFrame = frame.get<astra::ColorFrame>();
        if (!colorFrame.is_valid())
        {
            return;
        }

        const int colorWidth = colorFrame.width();
        const int colorHeight = colorFrame.height();

        init_view(colorWidth, colorHeight, colorView_);
        qDebug() << "rgb";

        const astra::RgbPixel* color = colorFrame.data();
        uint8_t* buffer = &colorView_.buffer_[0];
        for(int i = 0; i < colorWidth * colorHeight; i++)
        {
            buffer[i * 3 + 0] = color[i].b;
            buffer[i * 3 + 1] = color[i].g;
            buffer[i * 3 + 2] = color[i].r;
        }

        //  color_image = cv::Mat(cv::Size(colorWidth, colorHeight), CV_8UC3);
        //  std::copy(buffer, buffer + 3 * colorWidth * colorHeight, color_image.data);
    }

    void update_ir(astra::Frame& frame)
    {
        const astra::InfraredFrameRgb irFrame = frame.get<astra::InfraredFrameRgb>();
        if (!irFrame.is_valid())
        {
            return;
        }

        int irWidth = irFrame.width();
        int irHeight = irFrame.height();

        init_view(irWidth, irHeight, colorView_);
        qDebug() << "ir";

        const astra::RgbPixel* irRGB = irFrame.data();
        uint8_t* buffer = &colorView_.buffer_[0];
        for (int i = 0; i < irWidth * irHeight; i++)
        {
            buffer[i * 3 + 0] = irRGB[i].r;
            buffer[i * 3 + 1] = irRGB[i].g;
            buffer[i * 3 + 2] = irRGB[i].b;
        }
    }

    virtual void on_frame_ready(astra::StreamReader& reader, astra::Frame& frame) override
    {
        update_depth(frame);
        if(colorMode_ == MODE_COLOR)
            update_color(frame);
        if(colorMode_ == MODE_IR)
            update_ir(frame);
    }

    ColorMode get_mode() const { return colorMode_; }
    void set_mode(ColorMode mode) { colorMode_ = mode; }

public:
    StreamView depthView_;
    StreamView colorView_;
    ColorMode colorMode_;
};


#endif // ASTRA_H
