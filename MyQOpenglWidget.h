#ifndef MYQOPENGLWIDGET_H
#define MYQOPENGLWIDGET_H

#include <QtGui/QOpenGLFunctions>
#include <QtWidgets/QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <QPainter>
#include <QOpenGLContext>
#include <QOpenGLPaintDevice>
#include <QOpenGLShaderProgram>
#include <QOpenGLShader>
#include <QTime>
#include <QTimer>
#include <QVector3D>
#include <QMouseEvent>
#include <QKeyEvent>


QT_BEGIN_NAMESPACE
class QPainter;
class QOpenGLContext;
class QOpenGLPaintDevice;
class QOpenGLShaderProgram;
class QOpenGLShader;
QT_END_NAMESPACE

struct PointXYZRGB
{
    float x;
    float y;
    float z;
    int r;
    int g;
    int b;
    PointXYZRGB() : x(0), y(0), z(0), r(255), g(255), b(255) {}
    PointXYZRGB(float x, float y, float z) : x(x), y(y), z(z), r(255), g(255), b(255) {}
    PointXYZRGB(float x, float y, float z, int r, int g, int b) : x(x), y(y), z(z), r(r), g(g), b(b) {}
};

struct BoundingBox
{
    float width;
    float height;
    float depth;
    QVector3D maxPoint;
    QVector3D minPoint;
    QVector3D centerPoint;
};

class MyQOpenglWidget: public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit MyQOpenglWidget(QWidget *parent = 0);
    ~MyQOpenglWidget();
    void showPointCloud(const std::vector<PointXYZRGB>& cloud);
    virtual void resizeGL(int w, int h);
    void setBackgroundColor(QVector3D color);

protected:
    virtual void initializeGL(void);
    virtual void paintGL(void);

    struct VertexInfo
    {
        float pos[3];
        float normal[3];
        float color[4];
    };
private slots:
    void onTimerOut(void);
    virtual void mousePressEvent(QMouseEvent * e);
    virtual void mouseMoveEvent(QMouseEvent * e);
    virtual void mouseReleaseEvent(QMouseEvent * e);
    virtual void wheelEvent(QWheelEvent * e);
    virtual void keyPressEvent(QKeyEvent *e);
    virtual void leaveEvent(QEvent *);
    virtual void enterEvent(QEvent *);

private:
    QTimer *m_Timer;
    QOpenGLContext *m_context;					
    QOpenGLShaderProgram *m_Program;			
    QOpenGLFunctions_3_3_Core *OpenGLCore;
    QOpenGLShader *m_VertexShader;
    QOpenGLShader *m_FragmentShader;

	// shader spara
    GLuint m_posAttr;                           
    GLuint m_colAttr;                          
    GLuint m_norAttr;                           
    GLuint m_matrixUniform;						
	GLuint m_VBO;
    GLuint m_VAO;
    QVector4D m_backgroundColor;

	//store points
	QVector<VertexInfo> m_PointsVertex;				
    BoundingBox m_box;
   
    QVector3D m_lineMove;
    QQuaternion m_rotate;
	QVector3D m_rotationAxis;
    float m_scale;

    QVector2D m_lastPoint;

    GLuint createGPUProgram(QString nVertexShaderFile, QString nFragmentShaderFile);
    void GetShaderUniformPara();
    bool InitShader();                    

    void LineMove(QVector2D posOrgin, QVector2D posEnd);
    void Rotate(QVector2D posOrgin, QVector2D posEnd);
    void modelZoomInOrOut(bool ZoomInOrOut);
    QVector3D pixelPosToViewPos(const QVector2D& p);
    void calRotation(QVector2D posOrgin, QVector2D posEnd);
    void calculateBoundingBox(const std::vector<PointXYZRGB>& cloud);
    void initPointCloud(const std::vector<PointXYZRGB>& cloud);
    void gray2Pseudocolor(const PointXYZRGB pos, float color[4]);
    void changePointCloud();
    void setMatrixUniform();
    void ResetView();
    void initCloud();
};

#endif // MYQOPENGLWIDGET_H
