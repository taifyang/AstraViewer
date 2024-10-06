#include "myqopenglwidget.h"
#include <QtMath>

static const char *vertexShaderSource =
    "attribute highp vec3 posAttr;\n"
    "attribute lowp vec4 colAttr;\n"
    "varying lowp vec4 col;\n"
    "uniform highp mat4 matrix;\n"
    "void main() {\n"
    "  col=colAttr;\n"
    "  gl_Position=matrix * vec4(posAttr,1.0f);\n"
    "}\n";

static const char *fragmentShaderSource =   
    "varying lowp vec4 col;\n"
    "void main() {\n"
    "   gl_FragColor = col;\n"
    "}\n";

MyQOpenglWidget::MyQOpenglWidget(QWidget *parent)
    : QOpenGLWidget(parent)
    ,m_context(NULL)
    ,m_Program(NULL)
	,OpenGLCore(NULL)
    ,m_posAttr(0)    
    ,m_colAttr(0)
    ,m_norAttr(0)
    ,m_matrixUniform(0)
    ,m_VBO(0)
    ,m_VAO(0)
    ,m_VertexShader(NULL)
    ,m_FragmentShader(NULL)
    ,m_scale(1.0f)
{
    m_Timer = new QTimer;
    m_PointsVertex = QVector<VertexInfo>();
    ResetView();
    this->grabKeyboard();
}

MyQOpenglWidget::~MyQOpenglWidget()
{
    if(m_context)
    {
        delete m_context;
        m_context = NULL;
    }
    if(m_Program)
    {
        delete m_Program;
        m_Program = NULL;
    }
    m_PointsVertex.clear();
}

void MyQOpenglWidget::showPointCloud(const std::vector<PointXYZRGB> &cloud)
{
    initPointCloud(cloud);
    changePointCloud();
    ResetView();
    repaint();
}

void MyQOpenglWidget::calculateBoundingBox(const std::vector<PointXYZRGB> &cloud)
{
    float x_max=INT_MIN, y_max=INT_MIN, z_max=INT_MIN;
    float x_min=INT_MAX, y_min=INT_MAX, z_min=INT_MAX;
    for(size_t i = 0; i<cloud.size(); i++)
    {
        if(cloud[i].x>x_max)    x_max=cloud[i].x;
        if(cloud[i].x<x_min)    x_min=cloud[i].x;
        if(cloud[i].y>y_max)    y_max=cloud[i].y;
        if(cloud[i].y<y_min)    y_min=cloud[i].y;
        if(cloud[i].z>z_max)    z_max=cloud[i].z;
        if(cloud[i].z<z_max)    z_min=cloud[i].z;
    }
    float width = x_max - x_min;
    float height = y_max - y_min;
    float depth = z_max - z_min;
    QVector3D maxPoint(x_max, y_max, z_max);
    QVector3D minPoint(x_min, y_min, z_min);
    QVector3D centerPoint((x_max+x_min)/2, (y_max+y_min)/2, (z_max+z_min)/2);
    m_box.width = width;
    m_box.height = height;
    m_box.depth = depth;
    m_box.maxPoint = maxPoint;
    m_box.minPoint = minPoint;
    m_box.centerPoint = centerPoint;
}

void MyQOpenglWidget::initPointCloud(const std::vector<PointXYZRGB> &cloud)
{
    m_PointsVertex.clear();
    m_PointsVertex.resize((int)cloud.size());

    calculateBoundingBox(cloud);

    for(size_t i = 0; i<cloud.size(); i++)
    {
        //move cloud center to origin
        m_PointsVertex[i].pos[0] = cloud[i].x;
        m_PointsVertex[i].pos[1] = cloud[i].y;
        m_PointsVertex[i].pos[2] = cloud[i].z;
        gray2Pseudocolor(cloud[i], m_PointsVertex[i].color);
        m_PointsVertex[i].normal[0] = 0.0f;
        m_PointsVertex[i].normal[1] = 1.0f;
        m_PointsVertex[i].normal[2] = 0.0f;
    }
}

void MyQOpenglWidget::gray2Pseudocolor(const PointXYZRGB pos,float color[4])
{
    color[0] = pos.r *1.0f/255;
    color[1] = pos.g *1.0f/255;
    color[2] = pos.b *1.0f/255;
    color[3] = 1.0f;
}

void MyQOpenglWidget::changePointCloud()
{
    if(m_PointsVertex.size()<=0)
    {
        return ;
    }
    OpenGLCore->glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(VertexInfo)*(int)m_PointsVertex.size(), m_PointsVertex.data(), GL_DYNAMIC_DRAW);

    glEnableVertexAttribArray(m_posAttr);
    glVertexAttribPointer(m_posAttr, 3, GL_FLOAT, GL_FALSE, sizeof(VertexInfo), (void*)(offsetof(VertexInfo, pos)));
    glEnableVertexAttribArray(m_colAttr);
    glVertexAttribPointer(m_colAttr, 4, GL_FLOAT, GL_FALSE, sizeof(VertexInfo), (void*)(offsetof(VertexInfo,color)));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    OpenGLCore->glBindVertexArray(0);
}

void MyQOpenglWidget::ResetView()
{
    m_lineMove = QVector3D();
    m_rotate = QQuaternion(); 
    m_rotate *= QQuaternion::fromAxisAndAngle(QVector3D(0,0,1),180);
	m_rotationAxis = QVector3D();
    m_scale = 1.0f;
}

void MyQOpenglWidget::setBackgroundColor(QVector3D color)
{
    m_backgroundColor= QVector4D(color, 1.0f);
}

void MyQOpenglWidget::resizeGL(int w, int h)
{
    const qreal retinaScale = devicePixelRatio();
    glViewport(0, 0, w * retinaScale, h * retinaScale);
    repaint();
}

void MyQOpenglWidget::initializeGL()
{
    bool binit = true;
	binit &= InitShader();
	if (!binit)
	{
		return;
	}
    OpenGLCore = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_3_3_Core>();
    initializeOpenGLFunctions();
    glEnable(GL_DEPTH_TEST);
	OpenGLCore->glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);

    //init need import a point data
    initCloud();
    changePointCloud();

    QObject::connect(m_Timer, SIGNAL(timeout()), this, SLOT(onTimerOut()));
    m_Timer->start(50);
}

bool MyQOpenglWidget::InitShader()
{
    m_Program = new QOpenGLShaderProgram(this);
    bool success = true;
    success &= m_Program->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
    success &= m_Program->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);
    success &= m_Program->link();
    GetShaderUniformPara();
    return success;
}

void MyQOpenglWidget::GetShaderUniformPara()
{
    m_posAttr = m_Program->attributeLocation("posAttr");
    m_colAttr = m_Program->attributeLocation("colAttr");  
    m_matrixUniform = m_Program->uniformLocation("matrix");
}

void MyQOpenglWidget::paintGL()
{
    m_Program->bind();
    glClearColor(m_backgroundColor.x(), m_backgroundColor.y(), m_backgroundColor.z(), m_backgroundColor.w());
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BITS);

    OpenGLCore->glBindVertexArray(m_VAO);
    setMatrixUniform();
    glDrawArrays(GL_POINTS, 0,(GLsizei ) m_PointsVertex.size());    
    OpenGLCore->glPointSize(2.0f);

    OpenGLCore->glBindVertexArray(0);
    m_Program->release();
}

void MyQOpenglWidget::setMatrixUniform()
{
    QMatrix4x4 matrix = QMatrix4x4();
    QMatrix4x4 matrixPerspect= QMatrix4x4();;
    QMatrix4x4 matrixView= QMatrix4x4();;
    QMatrix4x4 matrixModel= QMatrix4x4();;

    QVector3D minPos = (m_box.minPoint - m_box.centerPoint);
    QVector3D maxPos = (m_box.maxPoint - m_box.centerPoint);
    float maxAxis =qAbs(qMax(qMax(m_box.width,m_box.height),m_box.depth)) ;

    matrixPerspect.ortho(2*minPos[0], 2*maxPos[0], 2*minPos[1], 2*maxPos[1], -2*maxAxis, 2*maxAxis);

    matrixView.lookAt(QVector3D(0, 0, 1.0),QVector3D(0.0,0.0,-1),QVector3D(0.0,1.0,0.0));
    matrixView.translate(m_lineMove.x(),m_lineMove.y(),m_lineMove.z());

    matrixModel.rotate(m_rotate);
    matrixModel.scale(m_scale);

    matrix = matrixPerspect*matrixView*matrixModel;

    m_Program->setUniformValue(m_matrixUniform, matrix);
}

void MyQOpenglWidget::initCloud()
{
    m_PointsVertex.clear();
    VertexInfo point;
    point.pos[0] = 0.0f ;
    point.pos[1] = 0.0f ;
    point.pos[2] = 0.0f ;
    point.color[0] = m_backgroundColor.x();
    point.color[1] = m_backgroundColor.y();
    point.color[2] = m_backgroundColor.z();
    point.color[3] = m_backgroundColor.w();
    point.normal[0] = 0.0f;
    point.normal[1] = 1.0f;
    point.normal[2] = 0.0f;
    m_PointsVertex.push_back(point);
}

void MyQOpenglWidget::onTimerOut()
{
    if(this->isVisible())
    {
        repaint();
    }
}

void MyQOpenglWidget::mousePressEvent(QMouseEvent *e)
{
	if (e->buttons()&Qt::LeftButton || e->buttons()&Qt::MidButton)
	{
		setMouseTracking(true);
		m_lastPoint = QVector2D(e->localPos());
	}   
}

void MyQOpenglWidget::mouseMoveEvent(QMouseEvent *e)
{	
    if (e->buttons()&Qt::LeftButton)
    {
        Rotate(QVector2D(m_lastPoint), QVector2D(e->localPos()));
    }
    if (e->buttons()&Qt::MidButton)
    {
        LineMove(m_lastPoint, QVector2D(e->localPos()));
    }
    m_lastPoint = QVector2D(e->localPos());
}

void MyQOpenglWidget::mouseReleaseEvent(QMouseEvent *e)
{
    setMouseTracking(false);
}

void MyQOpenglWidget::wheelEvent(QWheelEvent *e)
{   
    if(e->delta() > 0){
        modelZoomInOrOut(true);
    }else{
        modelZoomInOrOut(false);
    }
}

void MyQOpenglWidget::keyPressEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_R)
    {
        ResetView();
        //return;
    }
    QWidget::keyPressEvent(e);
}

void MyQOpenglWidget::leaveEvent(QEvent *)
{
    releaseKeyboard();
}

void MyQOpenglWidget::enterEvent(QEvent *)
{
    grabKeyboard();
}

GLuint MyQOpenglWidget::createGPUProgram(QString nVertexShaderFile, QString nFragmentShaderFile)
{
    m_VertexShader = new QOpenGLShader(QOpenGLShader::Vertex);
    bool isOK = m_VertexShader->compileSourceFile(nVertexShaderFile);
    if (!isOK)
    {
        delete m_VertexShader;
        m_VertexShader = nullptr;
        qDebug() << "compile vertex shader fail" ;
        return 0;
    }

    m_FragmentShader = new QOpenGLShader(QOpenGLShader::Fragment);
    if (!m_FragmentShader->compileSourceFile(nFragmentShaderFile))
    {
        delete m_VertexShader;
        delete m_FragmentShader;
        m_FragmentShader = nullptr;
        qDebug() << "compile fragment shader fail";
        return 0;
    }
    m_Program = new QOpenGLShaderProgram(this);
    m_Program->addShader(m_VertexShader);
    m_Program->addShader(m_FragmentShader);
    m_Program->link();
    GetShaderUniformPara();
    return m_Program->programId();
}

void MyQOpenglWidget::LineMove(QVector2D posOrgin, QVector2D posEnd)
{
    float ratio = 1.0f;
    float xoffset = posEnd.x() - posOrgin.x();
    float yoffset = posEnd.y() - posOrgin.y();

    m_lineMove.setX(m_lineMove.x()+xoffset*ratio);
    m_lineMove.setY(m_lineMove.y()-yoffset*ratio);
}

void MyQOpenglWidget::Rotate(QVector2D posOrgin, QVector2D posEnd)
{
	QVector2D diff = posEnd - posOrgin;
	qreal acc = diff.length() / 100.0;
	if (acc<0.01f)
	{
		return;
	}
    calRotation(posOrgin,posEnd);
}

void MyQOpenglWidget::modelZoomInOrOut(bool ZoomInOrOut)
{
    if(ZoomInOrOut)//zoom in
    {
        m_scale*=1.1f;
    }else{
        m_scale*=0.9f;
        if(m_scale<0.5f)
            m_scale = 0.5f;
    }
}

void MyQOpenglWidget::calRotation(QVector2D posOrgin, QVector2D posEnd)
{
    QVector3D orginViewPos = pixelPosToViewPos(posOrgin);
    QVector3D endViewPos = pixelPosToViewPos(posEnd);
    float RotateAngle;
    RotateAngle = qRadiansToDegrees(std::acos(QVector3D::dotProduct(orginViewPos,endViewPos)));
    QVector3D axis;
    axis=QVector3D::crossProduct(orginViewPos, endViewPos);
    axis.normalize();
    m_rotate=  QQuaternion::fromAxisAndAngle(axis, RotateAngle)*m_rotate;
}

QVector3D MyQOpenglWidget::pixelPosToViewPos(const QVector2D &p)
{
    QVector3D viewPos(2.0 * float(p.x()) / width() - 1.0,  1.0 - 2.0 * float(p.y()) / height(), 0);
    float sqrZ = 1 - QVector3D::dotProduct(viewPos, viewPos);
    if(sqrZ>0)
        viewPos.setZ(std::sqrt(sqrZ));
    else
        viewPos.normalize();
    return viewPos;
}

