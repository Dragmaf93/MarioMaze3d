#include "fireball.h"
#include<cmath>

FireBall::FireBall(GLuint modelList,
                   Maze* maze)
{
  this->modelList=modelList;
  this->readyToFire=true;
  this->readyToRender=false;
  this->maze=maze;
  setSize(1,1,1);
}

FireBall::~FireBall()
{

}

void FireBall::render()
{
  if(readyToRender){
    glPushMatrix();
    glTranslated(positionX,positionY,positionZ);
    glRotatef(90,1,0,0);
    glCallList(modelList);
    glPopMatrix();
  }
  if(!collideWall(positionX+cos(angle)/4,positionY+sin(angle)/4)){
    positionX+=cos(angle)/4;
    positionY+=sin(angle)/4;
    if(!increase)
      positionZ-=increaseZ;
    else
      positionZ+=increaseZ;
    if(positionZ<=0){
      increase=true;
      bounce++;
    }
    else if(positionZ>=maxHeight){
      increase=false;
      bounce++;
    }

    if(bounce==MAX_BOUNCE){
      readyToFire=true;
      readyToRender=false;
    }
  }
  else{
    readyToFire=true;
    readyToRender=false;
  }
}

void FireBall::set(GLfloat x, GLfloat y, GLfloat angle)
{
  this->positionX=x+cos(angle)/4;
  this->positionY=y+sin(angle)/4;

  this->angle=angle;
  this->positionZ=1.5;
  readyToFire=false;
  bounce=0;
  readyToRender=true;
}

void FireBall::setReady()
{
  readyToFire=true;
  readyToRender=false;
}

bool FireBall::ready()
{
  return readyToFire;
}

bool FireBall::collideWall(GLfloat x, GLfloat y)
{
  QVector<Wall*> walls = maze->getWalls();
  for (int i = 0; i < walls.size(); i++)
  {
    if ((x+RADIUS <= walls[i]->getPositionX() + walls[i]->getWidth() && x+RADIUS >= walls[i]->getPositionX())
      && (y+RADIUS <= walls[i]->getPositionY() + walls[i]->getHeight() && y+RADIUS >= walls[i]->getPositionY()) ||
    (x-RADIUS <= walls[i]->getPositionX() + walls[i]->getWidth() && x-RADIUS >= walls[i]->getPositionX())
      && (y-RADIUS <= walls[i]->getPositionY() + walls[i]->getHeight() && y-RADIUS >= walls[i]->getPositionY()))
      return true;
  }
  return false;
}


