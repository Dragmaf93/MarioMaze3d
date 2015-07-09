#include "sky.h"

Sky::Sky(GLfloat size)
{
    setPosition(0, 0,250);
    setSize (size, size, size);

    this->quad = gluNewQuadric();
    gluQuadricTexture(this->quad, GLU_TRUE);

    this->textureId = loadTexture("data/texture/sky4");
}

Sky::~Sky()
{

}

void Sky::render()
{
    glBindTexture(GL_TEXTURE_2D, textureId);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,material);

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(getPositionX(),getPositionY(),getPositionZ());
    glColor4f(1.0, 1.0, 1.0, 1.0);
    gluSphere(quad, width*3, 10, 10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}
