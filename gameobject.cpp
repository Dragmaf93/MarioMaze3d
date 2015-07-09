#include "gameobject.h"
#include<QDebug>

GameObject::GameObject()
{

}

GLfloat GameObject::getPositionX(){
    return this->positionX;
}

GLfloat GameObject::getPositionY(){
    return this->positionY;
}

GLfloat GameObject::getPositionZ(){
    return this->positionZ;
}
GLfloat GameObject::getHeight(){
    return this->height;
}

GLfloat GameObject::getWidth(){
    return this->width;
}

GLfloat GameObject::getDepth(){
    return this->depth;
}

void GameObject::setSize (GLfloat width, GLfloat height, GLfloat depth){
    this->width=width;
    this->height=height;
    this->depth=depth;
}

void GameObject::setPosition (GLfloat x, GLfloat y, GLfloat z){
    this->positionX=x;
    this->positionY=y;
    this->positionZ=z;
}

GLuint GameObject::loadTexture(QString imgPath)
{
    QImage im;
    im.load(imgPath);

    QImage image = QGLWidget::convertToGLFormat (im);
    if (image.isNull())
        qDebug() << "Impossibile caricare la texture " << imgPath << endl;
    GLuint textureId=0;
    glGenTextures(1,&textureId);
    glBindTexture(GL_TEXTURE_2D,textureId);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,
                 image.width(), image.height(),0,GL_RGBA,GL_UNSIGNED_BYTE,image.bits());
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
      glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
//    glBindTexture( GL_TEXTURE_2D, 0 );
//    qDebug() <<imgPath << image.depth()<< textureId;

    return textureId;
}
