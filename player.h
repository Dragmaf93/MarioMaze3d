#ifndef PLAYER_H
#define PLAYER_H
#define appross 1.5

#include"fireball.h"
#include"goal.h"
#include"enemymanager.h"

class Fireball;
class EnemyManager;
class Player : public GameObject
{
public:
    Player(Maze* maze,Goal* goal);
    ~Player();

    void move(QString direction);
    void stopToMove(QString direction);
    bool collideWall(GLfloat x,GLfloat y);
    bool collideGoal(GLfloat x, GLfloat y);
    bool hitGoomba();
    void fire();
    bool readyToFire();
    void setLight(GLfloat* pos,GLfloat *dir);
    void setEnemyManager(EnemyManager* enemyManager);
    int getNumberLife(){return numberLife;}
    GLfloat getAngleRotation(){return angleRotation;}

    void die();
    GLfloat getEyeX();
    GLfloat getEyeY();
    GLfloat getEyeZ();
    GLfloat getForwardX();
    GLfloat getForwardY();
    GLfloat getForwardZ();

    virtual void render();
    void renderShowMap();
    void update();
    void reset(bool resetLife=false);
    void setEye (GLfloat x, GLfloat y, GLfloat z);
    void setForward (GLfloat x, GLfloat y, GLfloat z);

private:
    Maze* maze;
    Goal* goal;
    EnemyManager* enemyManager;

    int numberLife;

    bool moveForward;
    bool moveBack;
    bool moveLeft;
    bool moveRight;

    GLfloat eyeX;
    GLfloat eyeY;
    GLfloat eyeZ;
    GLfloat forwardX;
    GLfloat forwardY;
    GLfloat forwardZ;

    GLfloat angleRotation;
    GLfloat delta_angleRotation;

    const GLfloat START_X=94.5;
    const GLfloat START_Y=89.3;
    const GLfloat START_Z=2.0;

    FireBall* fireball;
    Model* fireballModel;
    GLuint fireballModelList;
};

#endif // PLAYER_H
