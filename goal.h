#ifndef GOAL_H
#define GOAL_H
#include"gameobject.h"
#include"model.h"

class Goal : public GameObject
{
public:
    Goal(GLfloat x, GLfloat y);
    ~Goal();
    void render();

private:
    Model* modelLoader;
    GLuint modelList;
    GLfloat angleRotation;

};

#endif // GOAL_H
