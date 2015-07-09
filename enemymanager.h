#ifndef ENEMYMANAGER_H
#define ENEMYMANAGER_H

#include"model.h"
#include"goomba.h"

class Player;
class Goomba;

class EnemyManager
{
public:
  EnemyManager(Maze* maze,Player* player);
  ~EnemyManager();

  void renderEnemy();
  void reset();
  void clear();
  QVector<Goomba *> getGoombas();

  bool goombaCollidePlayer();
  void generateGoomba(GLfloat xStart, GLfloat yStart, GLfloat xEnd, GLfloat yEnd);
private:

  Model* goombaModel;
  GLuint goombaModelList;

  QVector<Goomba*> goombas;

  Maze* maze;
  Player* player;

};

#endif // ENEMYMANAGER_H
