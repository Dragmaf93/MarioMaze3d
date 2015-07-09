#include "maze.h"
#include<QDebug>

Maze::Maze()
{
    floor = new Floor(SIZE);
    addWalls();
    textureId=loadTexture("data/texture/wall2");
    for(int i =0; i < walls.size();i++)
        walls[i]->setIdTexture(textureId);

}

Maze::~Maze()
{
   delete floor;

    for(int i = 0 ; i < walls.size();i++){
       delete walls[i];
   }
   walls.clear();


}
QVector<Wall*> Maze:: getWalls(){
    return walls;
}

void Maze::render()
{
    floor->render();


      for(int i = 0 ; i < walls.size();i++){
            glPushMatrix();
            walls[i]->render();
            glPopMatrix();
        }  for(int i = 0 ; i < walls.size();i++){
        glPushMatrix();
        walls[i]->render();
        glPopMatrix();
    }
}

void Maze:: addWalls(){
    walls.append(new Wall(0.0,0.0,0.0,SIZE,false));
    walls.append(new Wall(0.0,0.0,0.0,SIZE,true));

    walls.append(new Wall(SIZE*Wall::WIDTH-5,0.0,0.0,SIZE,true));
    walls.append(new Wall(0.0,SIZE*Wall::WIDTH-5,0.0,SIZE,false));

    walls.append(new Wall(100,0.0,0.0,5,true));
    walls.append(new Wall(125+40,0.0,0.0,5,true));

    walls.append(new Wall(125+56,19,0.0,13,false));

    walls.append(new Wall(17,19,0.0,14,false));
    walls.append(new Wall(17,24,0.0,3,true));
    walls.append(new Wall(50,24,0.0,3,true));

    walls.append(new Wall(17,60,0.0,11,false));
    walls.append(new Wall(35,40,0.0,4,true));
    walls.append(new Wall(67,40,0.0,8,true));

    walls.append(new Wall(67,40,0.0,4,false));
    walls.append(new Wall(67,80,0.0,7,false));
    walls.append(new Wall(97,85,0.0,3,true));

    walls.append(new Wall(17,80,0.0,8,true));
    walls.append(new Wall(2,115,0.0,3,false));

    walls.append(new Wall(35,80,0.0,4,true));
    walls.append(new Wall(35,80,0.0,4,false));

    walls.append(new Wall(82,80,0.0,7,true));
    walls.append(new Wall(67,95,0.0,4,true));
    walls.append(new Wall(50,95,0.0,4,false));
    walls.append(new Wall(37,115,0.0,10,false));

    walls.append(new Wall(15,130,0.0,4,false));
    walls.append(new Wall(15,150,0.0,4,false));
    walls.append(new Wall(35,130,0.0,5,true));

    walls.append(new Wall(50,115,0.0,11,true));
    walls.append(new Wall(35,165,0.0,4,false));

    walls.append(new Wall(17,165,0.0,13,true));
    walls.append(new Wall(35,165,0.0,9,true));
    walls.append(new Wall(17,225,0.0,14,false));

    walls.append(new Wall(50,183,0.0,9,true));
    walls.append(new Wall(67,133,0.0,16,true));
    walls.append(new Wall(82,140,0.0,17,true));

    walls.append(new Wall(82,135,0.0,13,false));


    walls.append(new Wall(115,18,0.0,8,false));
    walls.append(new Wall(115,18,0.0,20,true));

    walls.append(new Wall(100,40,0.0,5,true));
    walls.append(new Wall(85,60,0.0,3,false));

    walls.append(new Wall(130,36,0.0,13,true));
    walls.append(new Wall(130,36,0.0,20,false));

    walls.append(new Wall(100,115,0.0,10,false));
    walls.append(new Wall(145,60,0.0,11,true));
    walls.append(new Wall(145,55,0.0,15,false));
    walls.append(new Wall(145,135,0.0,11,true));
    walls.append(new Wall(145,185,0.0,4,false));

    walls.append(new Wall(130,115,0.0,11,true));
    walls.append(new Wall(100,150,0.0,3,true));
    walls.append(new Wall(100,165,0.0,6,false));

    walls.append(new Wall(97,183,0.0,13,true));
    walls.append(new Wall(230,36,0.0,7,true));


    walls.append(new Wall(160,70,0.0,7,false));
    walls.append(new Wall(160,70,0.0,21,true));
    walls.append(new Wall(195,70,0.0,17,true));
    walls.append(new Wall(195,150,0.0,7,false));
    walls.append(new Wall(177.5,88,0.0,16,true));
    walls.append(new Wall(177.5,168,0.0,11,false));


    walls.append(new Wall(215,71,0.0,4,false));
    walls.append(new Wall(210,71,0.0,14,true));

    walls.append(new Wall(229,87,0.0,4,false));
    walls.append(new Wall(230,105,0.0,10,true));

    walls.append(new Wall(209,225,0.0,4,false));
    walls.append(new Wall(229,185,0.0,9,true));
    walls.append(new Wall(209,185,0.0,9,true));
    walls.append(new Wall(179,185,0.0,6,false));


    walls.append(new Wall(113,225,0.0,16,false));
    walls.append(new Wall(113,210,0.0,13,false));
    walls.append(new Wall(115,185,0.0,3,false));
    walls.append(new Wall(130,185,0.0,5,true));

//    walls.append(new Wall(177.5,200,0.0,3,true));
}
