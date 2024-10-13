#include "imagewidget.h"

ImageWidget::ImageWidget(QWidget *parent)
    : QOpenGLWidget(parent)
{
}

ImageWidget::~ImageWidget()
{
}

void ImageWidget::setPixmap(QPixmap pixmap)
{
    m_pixmap = pixmap;
    this->update();
}

void ImageWidget::paintEvent(QPaintEvent *)
{
    QPainter painter;
    painter.begin(this);
    painter.drawPixmap(0, 0, m_pixmap.width(), m_pixmap.height(), m_pixmap);
}
