#ifndef SKY_H
#define SKY_H
#include"gameobject.h"

class Sky : public GameObject
{
public:
    Sky(GLfloat size);
    ~Sky();
    void render();
private:
    GLuint textureId;
    GLUquadric* quad;
    GLfloat material[4] = {0.6,0.79,1.0,1};


};

#endif // SKY_H
