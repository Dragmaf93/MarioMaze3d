#ifndef FIREBALL_H
#define FIREBALL_H
#include"gameobject.h"
#include"maze.h"

class FireBall: public GameObject
{
public:
  FireBall(GLuint modelList, Maze* maze);
  ~FireBall();
  void render();
  void set(GLfloat x, GLfloat y, GLfloat angle);
  void setReady();
  bool ready();
  bool collideWall(GLfloat x, GLfloat y);
private:

  Maze* maze;

  GLuint modelList;
  GLfloat angle;
  bool readyToFire;
  bool readyToRender;
  bool increase;
  int bounce;

  const GLfloat RADIUS=0.5;
  const GLfloat range= 7;
  const GLfloat maxHeight=2;
  const GLfloat increaseZ=0.1;
  const int MAX_BOUNCE=6;

};

#endif // FIREBALL_H
