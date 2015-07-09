#include "floor.h"
#include "wall.h"
Floor::Floor(int size)
{
    this->size= size;
    setSize(size,size,size);

    textureId = loadTexture("data/texture/floor4");
}

Floor::~Floor()
{

}
int Floor::getSize(){
    return size;
}

void Floor::render()
{
    glBindTexture(GL_TEXTURE_2D, textureId);
    glEnable(GL_TEXTURE_2D);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,material);

    glPushMatrix();

    glTranslated(getPositionX(),getPositionY(),getPositionZ());
    glColor4f(1,1,1,1);

    for (int i= 0; i < size; i++)
    {
      for (int k = 0; k < size; k++)
      {
        glBegin(GL_QUADS);
         glNormal3f(0.0f, 0.0f, 1.0f);
        glTexCoord2d(0,0);
        glVertex2d( Wall::WIDTH*i, Wall::WIDTH*k);

        glTexCoord2d(1,0);
        glVertex2d( Wall::WIDTH*i+5, Wall::WIDTH*k);

        glTexCoord2d(1,1);
        glVertex2d( Wall::WIDTH*i+5, Wall::WIDTH*k+5);

        glTexCoord2d(0, 1);
        glVertex2d( Wall::WIDTH*i, Wall::WIDTH*k+5);
        glEnd();
      }
    }
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

}
