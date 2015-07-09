#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QGLWidget>
#include <QString>
#include<QDebug>
#include <QOffscreenSurface>
#include <GL/gl.h>
#include <GL/glu.h>
#include<cmath>
#define approx 15

class GameObject : public  QOffscreenSurface
{
    Q_OBJECT
public:
    GameObject();
    virtual GLfloat getPositionX();
    virtual GLfloat getPositionY();
    virtual GLfloat getPositionZ();
    virtual GLfloat getHeight();
    virtual GLfloat getWidth();
    virtual GLfloat getDepth();
    virtual void setSize (GLfloat width, GLfloat height, GLfloat depth);
    virtual void setPosition (GLfloat x, GLfloat y, GLfloat z);
    virtual void render() = 0;
protected:
    GLuint loadTexture(QString imgPath);
    GLfloat positionX;
    GLfloat positionY;
    GLfloat positionZ;
    GLfloat width;
    GLfloat height;
    GLfloat depth;
};

#endif // GAMEOBJECT_H
