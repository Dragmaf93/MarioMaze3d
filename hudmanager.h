#ifndef HUDMANAGER_H
#define HUDMANAGER_H

#include"player.h"
#include"maze.h"
#include"wall.h"
#include<FTGL/ftgl.h>
#include<sstream>

class HudManager : public GameObject
{
public:
    HudManager(Maze* maze,Player* player,int width,int heig);
    ~HudManager();

    void renderPos(int x, int y);
    void renderLife();
    void render();
    void renderMap();
    void renderTime(QString* time);
    void orthoMode(bool);
    void resize(int w,int h);
    void renderFire();
    void renderVictory();
    void renderLose();

private:

    Maze* maze;
    Player* player;
    GLuint textureClock;
    GLuint textureLife;
    GLuint textureFire;
    GLuint texturemap;
    GLuint textureLose;

    GLuint textureBackground;
    GLuint luigiHappy;
    GLuint marioHappy;
    GLuint toadHappy;

    GLuint mapList;

    int width;
    int height;

    const double SCALE_VALUE=1.1;

    void drawImage(GLuint texture,GLfloat x,GLfloat y,GLfloat width,GLfloat heig,bool dark = false);



};

#endif // HUDMANAGER_H
