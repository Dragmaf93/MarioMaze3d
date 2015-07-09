#include "enemymanager.h"

EnemyManager::EnemyManager(Maze *maze, Player *player)
{
  this->maze=maze;
  this->player= player;

  goombaModel = new Model();
  goombaModel->loadModel("data/obj/goomba/goomba.obj");
  goombaModel->scaleModel(0.2);
  goombaModel->calcDim();
  goombaModelList = goombaModel->getGlList();

}

EnemyManager::~EnemyManager()
{
  delete goombaModel;
}

void EnemyManager::renderEnemy()
{
  for(int i = 0; i < goombas.size(); i++){
    goombas[i]->render();
    if(goombas[i]->canRemove())
      goombas.remove(i);
  }
}

void EnemyManager::reset()
{

  for(int i = 0; i < goombas.size(); i++)
    goombas[i]->reset();
}

void EnemyManager::clear()
{
  goombas.clear();
}

QVector<Goomba *> EnemyManager::getGoombas()
{
  return goombas;
}

bool EnemyManager::goombaCollidePlayer()
{
  int x = player->getPositionX();
  int y = player->getPositionY();
  float appros = 2.4;
  for(int i = 0; i<goombas.size();i++)
    if ((x < goombas[i]->getPositionX() && x+appros >= goombas[i]->getPositionX() && y < goombas[i]->getPositionY() && y+appros >=goombas[i]->getPositionY()) ||
        (x < goombas[i]->getPositionX() && x+appros >= goombas[i]->getPositionX() && y > goombas[i]->getPositionY() && y-appros <=goombas[i]->getPositionY()) ||
        (x > goombas[i]->getPositionX() && x-appros <= goombas[i]->getPositionX() && y < goombas[i]->getPositionY() && y+appros >=goombas[i]->getPositionY()) ||
        (x > goombas[i]->getPositionX() && x-appros<= goombas[i]->getPositionX() && y > goombas[i]->getPositionY() && y-appros <=goombas[i]->getPositionY()))
           return true;
  return false;
}

void EnemyManager::generateGoomba(GLfloat xStart, GLfloat yStart,
                                    GLfloat xEnd, GLfloat yEnd)
{
    Goomba* goomba = new Goomba(xStart, yStart, xEnd, yEnd,
                                goombaModelList, player,maze);
    goombas.append(goomba);
}


