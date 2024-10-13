#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include <QOpenGLWidget>
#include <QPainter>

class ImageWidget : public QOpenGLWidget
{
    Q_OBJECT

public:
    ImageWidget(QWidget *parent);

    ~ImageWidget();

    void setPixmap(QPixmap pixmap);

protected:
    void paintEvent(QPaintEvent *);

private:
    QPixmap m_pixmap;
};

#endif // IMAGEWIDGET_H
