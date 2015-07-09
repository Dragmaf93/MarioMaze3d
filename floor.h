#ifndef FLOOR_H
#define FLOOR_H
#include "gameobject.h"

class Floor:public GameObject
{
public:
    Floor(int size);
    ~Floor();
    void render();

    int getSize();
private:
    int size;
    GLuint textureId;
    GLfloat material[4] = {0,0.32,0.12,1};
};

#endif // FLOOR_H
