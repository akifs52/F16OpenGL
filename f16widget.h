#ifndef F16WIDGET_H
#define F16WIDGET_H

#include <QtOpenGLWidgets/QOpenGLWidget>

#include <QOpenGLFunctions>

#include <QTimer>
#include <QMouseEvent>

class F16Widget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    F16Widget(QWidget *parent = nullptr);
    ~F16Widget();

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

private:
    void drawF16();
    void drawWing();
    void drawTail();
    void drawBody();
    void drawCylinder(float baseRadius, float topRadius, float height, int slices);

    float rotationX = 0.0f;
    float rotationY = 0.0f;
    float angle = 0.0f;
    QPointF lastMousePos;
    QTimer timer;

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
};

#endif // F16WIDGET_H
