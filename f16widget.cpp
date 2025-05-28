#include "f16widget.h"

#include <GL/gl.h>

#include <QtMath>

F16Widget::F16Widget(QWidget *parent)
    : QOpenGLWidget(parent)
{
    connect(&timer, &QTimer::timeout, this, [this]() {
        angle += 0.3f;
        if (angle >= 360.0f) angle = 0.0f;
        update();
    });
    timer.start(16);
}

F16Widget::~F16Widget() {
    // gerekirse kaynak temizliği
}

void F16Widget::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0.05f, 0.05f, 0.1f, 1.0f);
    glEnable(GL_DEPTH_TEST);
}

void F16Widget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    float aspect = float(w) / float(h ? h : 1);
    float fovY = 60.0f;
    float zNear = 1.0f;
    float zFar = 100.0f;
    float fH = tan(fovY / 360.0f * 3.14159f) * zNear;
    float fW = fH * aspect;
    glFrustum(-fW, fW, -fH, fH, zNear, zFar);

    glMatrixMode(GL_MODELVIEW);
}

void F16Widget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Kamera konumu (0, 5, 15), hedef (0, 0, 0), yukarı vektör (0, 1, 0)
    float eyeX = 0, eyeY = 5, eyeZ = 15;
    float centerX = 0, centerY = 0, centerZ = 0;
    float upX = 0, upY = 1, upZ = 0;

    // Kamera yönünü hesapla (basit lookAt)
    float dirX = centerX - eyeX;
    float dirY = centerY - eyeY;
    float dirZ = centerZ - eyeZ;
    gluLookAt(eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ); // aşağıda tanımlayacağız

    glRotatef(rotationX, 1.0f, 0.0f, 0.0f);
    glRotatef(rotationY, 0.0f, 1.0f, 0.0f);


    glColor3f(0.7f, 0.7f, 0.75f);
    glBegin(GL_TRIANGLES);

    // Burun
    glVertex3f(0.0f, 0.0f, 3.5f);
    glVertex3f(-1.0f, 0.0f, 1.0f);
    glVertex3f(1.0f, 0.0f, 1.0f);

    // Gövde
    glVertex3f(-1.0f, 0.0f, 1.0f);
    glVertex3f(1.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, -2.0f);

    // Motorlar
    glVertex3f(-0.5f, 0.0f, -2.0f);
    glVertex3f(-1.5f, 0.0f, -3.0f);
    glVertex3f(0.0f, 0.0f, -2.0f);

    glVertex3f(0.5f, 0.0f, -2.0f);
    glVertex3f(0.0f, 0.0f, -2.0f);
    glVertex3f(1.5f, 0.0f, -3.0f);

    // Kanatlar
    glVertex3f(-1.0f, 0.0f, 0.5f);
    glVertex3f(-4.0f, 0.0f, -1.0f);
    glVertex3f(-1.0f, 0.0f, -1.0f);

    glVertex3f(1.0f, 0.0f, 0.5f);
    glVertex3f(1.0f, 0.0f, -1.0f);
    glVertex3f(4.0f, 0.0f, -1.0f);

    glEnd();

    // Dikey Stabilizatörler
    glColor3f(0.6f, 0.6f, 0.7f);
    glBegin(GL_QUADS);

    glVertex3f(-0.5f, 0.0f, -2.0f);
    glVertex3f(-0.3f, 1.0f, -2.5f);
    glVertex3f(-0.2f, 1.0f, -2.5f);
    glVertex3f(0.0f, 0.0f, -2.0f);

    glVertex3f(0.5f, 0.0f, -2.0f);
    glVertex3f(0.3f, 1.0f, -2.5f);
    glVertex3f(0.2f, 1.0f, -2.5f);
    glVertex3f(0.0f, 0.0f, -2.0f);

    glEnd();
}

void F16Widget::mousePressEvent(QMouseEvent *event)
{
    lastMousePos = event->pos();
}

// Mouse kontrolü


void F16Widget::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - lastMousePos.x();
    int dy = event->y() - lastMousePos.y();

    if (event->buttons() & Qt::LeftButton) {
        rotationX += dy * 0.5f;
        rotationY += dx * 0.5f;
        update();
    }

    lastMousePos = event->pos();

}

void gluLookAt(float eyeX, float eyeY, float eyeZ,
               float centerX, float centerY, float centerZ,
               float upX, float upY, float upZ)
{
    float forward[3], side[3], up[3];
    float m[16];

    forward[0] = centerX - eyeX;
    forward[1] = centerY - eyeY;
    forward[2] = centerZ - eyeZ;

    float fLen = sqrt(forward[0]*forward[0] + forward[1]*forward[1] + forward[2]*forward[2]);
    forward[0] /= fLen; forward[1] /= fLen; forward[2] /= fLen;

    up[0] = upX; up[1] = upY; up[2] = upZ;

    // side = forward x up
    side[0] = forward[1]*up[2] - forward[2]*up[1];
    side[1] = forward[2]*up[0] - forward[0]*up[2];
    side[2] = forward[0]*up[1] - forward[1]*up[0];

    // yeniden ortogonalize et
    float sLen = sqrt(side[0]*side[0] + side[1]*side[1] + side[2]*side[2]);
    side[0] /= sLen; side[1] /= sLen; side[2] /= sLen;

    // up = side x forward
    up[0] = side[1]*forward[2] - side[2]*forward[1];
    up[1] = side[2]*forward[0] - side[0]*forward[2];
    up[2] = side[0]*forward[1] - side[1]*forward[0];

    memset(m, 0, sizeof(m));
    m[0] = side[0];
    m[4] = side[1];
    m[8] = side[2];

    m[1] = up[0];
    m[5] = up[1];
    m[9] = up[2];

    m[2]  = -forward[0];
    m[6]  = -forward[1];
    m[10] = -forward[2];
    m[15] = 1.0f;

    glMultMatrixf(m);
    glTranslatef(-eyeX, -eyeY, -eyeZ);
}
