#ifndef WALL_H
#define WALL_H
#include"gameobject.h"

class Wall: public GameObject
{
public:
    Wall(GLfloat x,GLfloat y,GLfloat z,GLfloat dimension,bool horizontal);
    ~Wall();

    void render();


    int getDimension();
    bool getHorizontal();
    void setIdTexture(GLuint id);
    void scalePointWall(GLfloat* x1,GLfloat* y1,GLfloat* x2,GLfloat* y2);
    const static int HEIGHT = 7.0;
    const static int WIDTH = 5.0;
private:
    int dimension;
    bool horizontal;
    GLuint textureId;
    GLfloat material[4] = {0.58,0.29,0.0,1};



};

#endif // WALL_H
