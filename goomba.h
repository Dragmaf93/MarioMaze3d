#ifndef GOOMBA_H
#define GOOMBA_H
#include"gameobject.h"
#include"model.h"
#include"maze.h"
#include"player.h"
#define appross 1.5
#include"mediaplayermanager.h"
class Player;

class Goomba: public GameObject
{
public:
  Goomba(GLfloat xStart,GLfloat yStart,GLfloat xEnd,
         GLfloat yEnd, GLuint modelList,Player* player,Maze* maze);

  ~Goomba();
  void render();
  void move();
  void reset();
  void hit();
  bool canRemove();
  bool collideWall(GLfloat x,GLfloat y);

private:

  Player* player;
  GLuint modelList;
  Maze* maze;
  GLfloat xStart,yStart;
  GLfloat xEnd,yEnd;
  GLfloat angleRotation;
  GLfloat zDeath;
  int timeStopToSee;

  const  GLfloat MAX_Z_DEATH=-3;
  const  GLfloat SPEED=0.2;
  const  GLfloat RANGEM=15.0;
  const  GLfloat RANGEm=7.5;
  const  GLfloat MAX_DISTANCE_ROUTE=15.0;

  bool startToEnd;
  bool followPlayer;
  bool returnToRoute;
  bool hitByFireball;
  bool stopToSee;

  bool horizontalMove();
  bool isTherePlayer();
  bool farToRoute();
  void setAngleRotation(GLfloat x,GLfloat y);

};

#endif // GOOMBA_H
