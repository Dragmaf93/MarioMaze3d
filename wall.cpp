#include "wall.h"
#include "QDebug"

Wall::Wall(GLfloat x,GLfloat y,GLfloat z,GLfloat dimension, bool horizontal)
{
    setPosition(x,y,z);

    if(horizontal)
        setSize(5.0,5*dimension,HEIGHT);
    else
        setSize(5*dimension,5.0,HEIGHT);

    this->horizontal=horizontal;
    this->dimension=dimension;

}

Wall::~Wall()
{

}

int Wall:: getDimension(){
    return dimension;
}

bool Wall:: getHorizontal(){
    return horizontal;
}

void Wall::setIdTexture(GLuint id)
{
    textureId=id;
}
const int SCALE_VALUE=10;
void Wall::scalePointWall(GLfloat* x1, GLfloat* y1, GLfloat* x2, GLfloat* y2)
{
    *x1=positionX/SCALE_VALUE;
    *y1=positionY/SCALE_VALUE;

    if(horizontal){
        *x2 = (positionX+dimension*5)/SCALE_VALUE;
        *y2 = positionY/SCALE_VALUE;
    }else{
        *x2 = positionX/SCALE_VALUE;
        *y2 = (positionY+dimension*5)/SCALE_VALUE;
    }
}

void Wall::render()
{
    glBindTexture(GL_TEXTURE_2D, textureId);
    glEnable(GL_TEXTURE_2D);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,material);

    glPushMatrix();
    glTranslatef(positionX,positionY,positionZ);


    glColor4f(1.0, 1.0, 1.0, 1.0);
    for (int i=0; i<dimension; i++)
    {
      if (!horizontal)
      {
        if (i > 0)
        glTranslated(5.0, 0.0, 0.0);
      //lato sud
        glBegin(GL_QUADS);
         glNormal3f(0.0f, -1.0f, 0.0f);
      glTexCoord2d (0, 0);
      glVertex3d(0.0, 0.0, 0.0);
      glTexCoord2d (1, 0);
      glVertex3d(5.0, 0.0, 0.0);
      glTexCoord2d (1, 1);
      glVertex3d(5.0, 0.0, HEIGHT);
      glTexCoord2d (0, 1);
      glVertex3d(0.0, 0.0, HEIGHT);

      glColor4f(0.59, 0.46, 0.32, 1.0);

//      glNormal3f(0.0f, 1.0f, 0.0f);
//      glTexCoord2d (0, 0);
      glVertex3d(0.0, 0.0, HEIGHT);
//      glTexCoord2d (1, 0);
      glVertex3d(5.0, 0.0, HEIGHT);
//      glTexCoord2d (1, 1);
      glVertex3d(5.0, 5.0, HEIGHT);
//      glTexCoord2d (0, 1);
      glVertex3d(0.0, 5.0, HEIGHT);

      //lato nord
      glColor4f(1.0, 1.0, 1.0, 1.0);
      glNormal3f(0.0f, 1.0f, 0.0f);
      glTexCoord2d (0, 0);
      glVertex3d(0.0, 5.0, 0.0);
      glTexCoord2d (1, 0);
      glVertex3d(5.0, 5.0, 0.0);
      glTexCoord2d (1, 1);
      glVertex3d(5.0, 5.0, HEIGHT);
      glTexCoord2d (0, 1);
      glVertex3d(0.0, 5.0, HEIGHT);
      glColor4f(0.59, 0.46, 0.32, 1.0);

//      glNormal3f(0.0f, 0.0f, 1.0f);
//      glTexCoord2d (0, 0);
      glVertex3d(0.0, 0.0, 0.0);
//      glTexCoord2d (1, 0);
      glVertex3d(5.0, 0.0, 0.0);
//      glTexCoord2d (1, 1);
      glVertex3d(5.0, 5.0, 0.0);
//      glTexCoord2d (0, 1);
      glVertex3d(0.0, 5.0, 0.0);

      //lato ovest
      glColor4f(1.0, 1.0, 1.0, 1.0);
      glNormal3f(-1.0f, 0.0f, 0.0f);
      glTexCoord2d (0, 0);
      glVertex3d(0.0, 0.0, 0.0);
      glTexCoord2d (0, 1);
      glVertex3d(0.0, 0.0, HEIGHT);
      glTexCoord2d (1, 1);
      glVertex3d(0.0, 5.0, HEIGHT);
      glTexCoord2d (1, 0);
      glVertex3d(0.0, 5.0, 0.0);
//lato est
      glNormal3f(1.0f, 0.0f, 0.0f);
      glTexCoord2d (0, 0);
      glVertex3d(5.0, 0.0, 0.0);
      glTexCoord2d (0, 1);
      glVertex3d(5.0, 0.0, HEIGHT);
      glTexCoord2d (1, 1);
      glVertex3d(5.0, 5.0, HEIGHT);
      glTexCoord2d (1, 0);
      glVertex3d(5.0, 5.0, 0.0);
        glEnd();
      }
      if (horizontal)
      {

        if (i > 0)
      glTranslated(0.0, 5.0, 0.0);

        glBegin(GL_QUADS);
//lato ovest
        glNormal3f(-1.0f, 0.0f, 0.0f);
      glTexCoord2d (0, 0);
      glVertex3d(0.0, 0.0, 0.0);
      glTexCoord2d (1, 0);
      glVertex3d(0.0, 5.0, 0.0);
      glTexCoord2d (1, 1);
      glVertex3d(0.0, 5.0, HEIGHT);
      glTexCoord2d (0, 1);
      glVertex3d(0.0, 0.0, HEIGHT);

      glColor4f(0.59, 0.46, 0.32, 1.0);
//      glNormal3f(0.0f, 1.0f, 0.0f);
//      glTexCoord2d (0, 0);
      glVertex3d(0.0, 0.0, HEIGHT);
//      glTexCoord2d (1, 0);
      glVertex3d(0.0, 5.0, HEIGHT);
//      glTexCoord2d (1, 1);
      glVertex3d(5.0, 5.0, HEIGHT);
//      glTexCoord2d (0, 1);
      glVertex3d(5.0, 0.0, HEIGHT);
      glColor4f(1.0, 1.0, 1.0, 1.0);

      //lato est
      glNormal3f(1.0f, 0.0f, 0.0f);
      glTexCoord2d (0, 0);
      glVertex3d(5.0, 0.0, 0.0);
      glTexCoord2d (1, 0);
      glVertex3d(5.0, 5.0, 0.0);
      glTexCoord2d (1, 1);
      glVertex3d(5.0, 5.0, HEIGHT);
      glTexCoord2d (0, 1);
      glVertex3d(5.0, 0.0, HEIGHT);

      glColor4f(0.59, 0.46, 0.32, 1.0);
//    glNormal3f(0.0f, 0.0f, 1.0f);
//     glTexCoord2d (0, 0);
      glVertex3d(0.0, 0.0, 0.0);
//      glTexCoord2d (1, 0);
      glVertex3d(0.0, 5.0, 0.0);
//      glTexCoord2d (1, 1);
      glVertex3d(5.0, 5.0, 0.0);
//      glTexCoord2d (0, 1);
      glVertex3d(5.0, 0.0, 0.0);

      //lato sud
      glColor4f(1.0, 1.0, 1.0, 1.0);
      glNormal3f(0.0f, -1.0f, 0.0f);
      glTexCoord2d (0, 0);
      glVertex3d(0.0, 0.0, 0.0);
      glTexCoord2d (0, 1);
      glVertex3d(0.0, 0.0, HEIGHT);
      glTexCoord2d (1, 1);
      glVertex3d(5.0, 0.0, HEIGHT);
      glTexCoord2d (1, 0);
      glVertex3d(5.0, 0.0, 0.0);
//lato nord
      glNormal3f(0.0f, 1.0f, 0.0f);
      glTexCoord2d (0, 0);
      glVertex3d(0.0, 5.0, 0.0);
      glTexCoord2d (0, 1);
      glVertex3d(0.0, 5.0, HEIGHT);
      glTexCoord2d (1, 1);
      glVertex3d(5.0, 5.0, HEIGHT);
      glTexCoord2d (1, 0);
      glVertex3d(5.0, 5.0, 0.0);
        glEnd();
      }

    }

    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

