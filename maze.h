#ifndef MAZE_H
#define MAZE_H
#include <fstream>
#include "wall.h"
#include "floor.h"
#include<QVector>
using namespace std;


class Maze : public GameObject
{
public:
    const static int SIZE=50;
    Maze();
    ~Maze();
    void render();
    QVector<Wall*> getWalls();
private:
    Floor* floor;
    QVector<Wall*> walls;
    void loadMaze();
    void addWalls();
    GLuint textureId;

};

#endif // MAZE_H
