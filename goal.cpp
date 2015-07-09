#include "goal.h"

Goal::Goal(GLfloat x, GLfloat y)
{
    positionX=x;
    positionY=y;
    positionZ=3;
    angleRotation=0.0;

    modelLoader= new Model();
    modelLoader->loadModel("/home/dragmaf/Sviluppo/build-GraficaProgetto-Desktop-Debug/data/obj/luma/mesh/Luma.obj");
    modelLoader->scaleModel(0.2);
    width=height=depth=5;
    modelLoader->calcDim();
    modelList = modelLoader->getGlList();
}

Goal::~Goal()
{
  delete modelLoader;
}

void Goal:: render(){
    glPushMatrix();
    glTranslatef(positionX,positionY,positionZ);
    glRotatef(angleRotation,0,0,1);
    glCallList(modelList);
    glPopMatrix();
    angleRotation+=3;
}
