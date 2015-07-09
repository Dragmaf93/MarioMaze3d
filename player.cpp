#include "player.h"
#include<cmath>
#include<QDebug>

Player::Player(Maze *maze, Goal *goal)
{
  angleRotation=1.5;
  delta_angleRotation=0.06;

  eyeX=START_X;
  eyeY=START_Y;
  eyeZ=START_Z;
//   eyeX=160.5;
//    eyeY=120.33;
//   eyeZ=250.0;

  forwardX=eyeX+cos(angleRotation)/3;
  forwardY=eyeY+sin(angleRotation)/3;
  forwardZ=2.0;

  numberLife=3;

  moveBack=false;
  moveForward=false;
  moveLeft=false;
  moveRight=false;
  width=height=depth=3.0;

  setPosition(eyeX,eyeY,eyeZ);

  this->maze = maze;
  this->goal = goal;

  fireballModel = new Model();
  fireballModel->loadModel("data/obj/fireball/object.obj");
  fireballModel->scaleModel(0.2);
  fireballModel->calcDim();
  fireballModelList = fireballModel->getGlList();

  fireball = new FireBall(fireballModelList,maze);
}

Player::~Player()
{
  delete fireballModel;
  delete fireball;
}
GLfloat Player::getEyeX()
{
   return eyeX;
}

GLfloat Player::getEyeY()
{
    return eyeY;
}

GLfloat Player::getEyeZ()
{
    return eyeZ;
}

GLfloat Player::getForwardX()
{
    return forwardX;
}

GLfloat Player::getForwardY()
{
    return forwardY;
}

GLfloat Player::getForwardZ()
{
    return forwardZ;
}

void Player::render()
{
    gluLookAt(eyeX,eyeY,eyeZ,forwardX,forwardY,forwardZ,0,0,1);
    fireball->render();
}

void Player::setEye (GLfloat x, GLfloat y, GLfloat z)
{
    eyeX=x;
    eyeY=y;
    eyeZ=z;
    setPosition(eyeX,eyeY,eyeZ);
}

void Player::setForward (GLfloat x, GLfloat y, GLfloat z)
{
    forwardX=x;
    forwardY=y;
    forwardZ=z;
}

void Player::update()
{
    if(moveRight){
        angleRotation-=delta_angleRotation;
        forwardX=eyeX+cos(angleRotation)/3;
        forwardY=eyeY+sin(angleRotation)/3;

    }
    if(moveLeft ){
        angleRotation+=delta_angleRotation;
        forwardX=eyeX+cos(angleRotation)/3;
        forwardY=eyeY+sin(angleRotation)/3;
    }
    if(moveForward && !collideWall( eyeX+cos(angleRotation)/3,eyeY+sin(angleRotation)/3)){
        eyeX+=cos(angleRotation)/3;
        eyeY+=sin(angleRotation)/3;
        forwardX=eyeX+cos(angleRotation)/3;
        forwardY=eyeY+sin(angleRotation)/3;
    }
    if(moveBack && !collideWall( eyeX-cos(angleRotation)/3,eyeY-sin(angleRotation)/3)){
        eyeX-=cos(angleRotation)/3;
        eyeY-=sin(angleRotation)/3;
        forwardX=eyeX+cos(angleRotation)/3;
        forwardY=eyeY+sin(angleRotation)/3;
    }
    setPosition(eyeX,eyeY,eyeZ);
}

void Player::reset(bool resetLife)
{
    angleRotation=0.50;
    delta_angleRotation=0.06;

    eyeX=START_X;
    eyeY=START_Y;
    eyeZ=START_Z;
    forwardX=eyeX+cos(angleRotation)/3;
    forwardY=eyeY+sin(angleRotation)/3;
    forwardZ=2.0;


    if(resetLife)
      numberLife=3;

    moveBack=false;
    moveForward=false;
    moveLeft=false;
    moveRight=false;
    width=height=depth=3.0;

    setPosition(eyeX,eyeY,eyeZ);
}

void Player::move(QString direction)
{

    if(direction == "LEFT"){
        this->moveLeft=true;
    }
    if(direction == "RIGHT"){
        this->moveRight=true;
    }
    if(direction == "FORWARD"){
        this->moveForward=true;
    }
    if(direction == "BACK"){
        this->moveBack=true;
    }
}

void Player::stopToMove(QString direction)
{
    if(direction == "LEFT"){
        this->moveLeft=false;
    }
    if(direction == "RIGHT"){
        this->moveRight=false;
    }
    if(direction == "FORWARD"){
        this->moveForward=false;
    }
    if(direction == "BACK"){
        this->moveBack=false;
    }
}

bool Player::collideWall(GLfloat x,GLfloat y)
{
    QVector<Wall*> walls = maze->getWalls();

    for (int i = 0; i < walls.size(); i++)
    {
      if (((x+appross <= walls[i]->getPositionX() + walls[i]->getWidth()+3 && x+appross >= walls[i]->getPositionX())
        && (y+appross <= walls[i]->getPositionY() + walls[i]->getHeight()+3 && y+appross >= walls[i]->getPositionY())) ||
      (x-appross <= walls[i]->getPositionX() + walls[i]->getWidth() && x-appross >= walls[i]->getPositionX())
        && (y-appross <= walls[i]->getPositionY() + walls[i]->getHeight() && y-appross >= walls[i]->getPositionY()))
        return true;
    }
    return false;
}

bool Player::collideGoal(GLfloat x, GLfloat y)
{
    if ((x+appross <= goal->getPositionX() + goal->getWidth() && x+appross >= goal->getPositionX())
      && (y+appross <= goal->getPositionY() + goal->getHeight() && y+appross >= goal->getPositionY()) ||
    (x-appross <= goal->getPositionX() + goal->getWidth() && x-appross >= goal->getPositionX())
      && (y-appross <= goal->getPositionY() + goal->getHeight() && y-appross >= goal->getPositionY()))
        return true;
    return false;
}

bool Player::hitGoomba()
{
  QVector<Goomba* > goombas = enemyManager->getGoombas();
  GLfloat x = fireball->getPositionX();
  GLfloat y = fireball->getPositionY();
  GLfloat appros=1.0;
  for (int i = 0; i < goombas.size(); i++)
  {
    if ((x < goombas[i]->getPositionX() && x+appros >= goombas[i]->getPositionX() && y < goombas[i]->getPositionY() && y+appros >=goombas[i]->getPositionY()) ||
        (x < goombas[i]->getPositionX() && x+appros >= goombas[i]->getPositionX() && y > goombas[i]->getPositionY() && y-appros <=goombas[i]->getPositionY()) ||
        (x > goombas[i]->getPositionX() && x-appros <= goombas[i]->getPositionX() && y < goombas[i]->getPositionY() && y+appros >=goombas[i]->getPositionY()) ||
        (x > goombas[i]->getPositionX() && x-appros <= goombas[i]->getPositionX() && y > goombas[i]->getPositionY() && y-appros <=goombas[i]->getPositionY()))
        {
        fireball->setReady();
        goombas[i]->hit();
        return true;
      }
  }
  return false;
}

void Player::fire()
{
  if(fireball->ready())
    fireball->set(positionX,positionY,angleRotation);
}

bool Player::readyToFire()
{
  return fireball->ready();
}

void Player::setLight(GLfloat* pos, GLfloat* dir)
{
  pos[0]=eyeX;
  pos[1]=eyeX;
  pos[2]=eyeX;

  dir[0]=forwardX;
  dir[1]=forwardY;
  dir[2]=forwardZ;
}

void Player::setEnemyManager(EnemyManager *enemyManager)
{
  this->enemyManager=enemyManager;
}

void Player::die()
{
  numberLife--;
}
