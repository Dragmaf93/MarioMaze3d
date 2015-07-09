#include "hudmanager.h"
#include<string>

HudManager::HudManager(Maze* maze, Player* player,int w,int h)
{
    this->maze=maze;
    this->player=player;
    width=w;
    height=h;

    textureClock = loadTexture("data/hud/timer");
    textureLife = loadTexture("data/hud/mario");
    textureFire = loadTexture("data/hud/flower");
    textureLose = loadTexture("data/hud/loser");
    textureBackground = loadTexture("data/hud/sfondo");
    marioHappy = loadTexture("data/hud/marioVictory");
    luigiHappy = loadTexture("data/hud/luigiVictory");
    toadHappy = loadTexture("data/hud/toad");
    texturemap = loadTexture("data/hud/map");
}

HudManager::~HudManager()
{
}

void HudManager::renderPos(int X, int Y)
{
  QString x,y;
  x.setNum(X);
  y.setNum(Y);
  FTGLPixmapFont textLife("/home/dragmaf/Sviluppo/build-GraficaProgetto-Desktop-Debug/data/font/SuperMario256.ttf");
  textLife.FaceSize(30);
  textLife.Render("X",-1,FTPoint(70, height/2, 0));
  textLife.Render(x.toStdString().c_str(),-1,FTPoint(120, height/2, 0));
  textLife.Render("Y",-1,FTPoint(70, height/2-40, 0));
  textLife.Render(y.toStdString().c_str(),-1,FTPoint(120, height/2-40, 0));



}

void HudManager::renderLife()
{
  QString life;
  life.setNum(player->getNumberLife());

  FTGLPixmapFont textLife("/home/dragmaf/Sviluppo/build-GraficaProgetto-Desktop-Debug/data/font/SuperMario256.ttf");
  textLife.FaceSize(30);
  orthoMode(true);
  glPushMatrix();
  textLife.Render("x",-1,FTPoint(100, height-55, 0));
  textLife.FaceSize(40);
  textLife.Render(life.toStdString().c_str(),-1,FTPoint(125, height-55, 0));
  glPopMatrix();
  orthoMode(false);
  drawImage(textureLife,20,height-87,80,80);
}

void HudManager::render()
{
  renderMap();
  renderLife();
  renderFire();
}

void HudManager::renderMap()
{

    GLfloat x=width-120, y = 10,width = 250, heig=250;

  orthoMode(true);
  glBindTexture(GL_TEXTURE_2D, texturemap);
  glEnable(GL_TEXTURE_2D);
  glPushMatrix();
  glColor4f(1.0, 1.0, 1.0, 1.0);
    glBegin(GL_QUADS);
    glTexCoord2d(0,0);
    glVertex2d(x/SCALE_VALUE,y/SCALE_VALUE);
    glTexCoord2d(1,0);
    glVertex2d((x+width)/SCALE_VALUE,y/SCALE_VALUE);
    glTexCoord2d(1,1);
    glVertex2d((x+width)/SCALE_VALUE,(y+heig)/SCALE_VALUE);
    glTexCoord2d(0,1);
    glVertex2d(x/SCALE_VALUE,(y+heig)/SCALE_VALUE);
    glEnd();

    GLfloat x1=player->getPositionX()+x,y1=y+player->getPositionY();
    glBegin(GL_QUADS);
           glColor3d(0,0,0);
           glVertex2d(x1/SCALE_VALUE,y1/SCALE_VALUE);
           glVertex2d(x1/SCALE_VALUE,(y1+3)/SCALE_VALUE);
           glVertex2d((x1+3)/SCALE_VALUE,(y1+3)/SCALE_VALUE);
           glVertex2d((x1+3)/SCALE_VALUE,y1/SCALE_VALUE);
    glEnd();
  glPopMatrix();

  orthoMode(false);

}


void HudManager::renderTime(QString* time)
{
  FTGLPixmapFont timer("/home/dragmaf/Sviluppo/build-GraficaProgetto-Desktop-Debug/data/font/SuperMario256.ttf");
  timer.FaceSize(40);
  orthoMode(true);
  glPushMatrix();
  timer.Render(time->toStdString().c_str(),-1,FTPoint(width-100, height-70, 0));
  glPopMatrix();
  orthoMode(false);
  drawImage(textureClock,width-185,height-93,80,80);

}

void HudManager::orthoMode(bool b)
{
    if(b){
            glMatrixMode(GL_PROJECTION);
            glPushMatrix();
            glLoadIdentity();

            gluOrtho2D(0, width, 0, height);
            glMatrixMode(GL_MODELVIEW);
            glPushMatrix();
            glLoadIdentity();
            glDisable(GL_DEPTH_TEST);
        }
        else
        {
            glMatrixMode(GL_PROJECTION);
            glPopMatrix();
            glMatrixMode(GL_MODELVIEW);
            glPopMatrix();
            glEnable(GL_DEPTH_TEST);
    }
}

void HudManager::resize(int w, int h)
{
    width=w;
    height=h;
}

void HudManager::renderFire()
{
  drawImage(textureFire,20,20,100,100,!player->readyToFire());
}

void HudManager::renderVictory()
{
  glEnable(GL_LIGHT1);
  drawImage(textureBackground,0,0,width,height);
  drawImage(marioHappy,100,100,300,600);
  drawImage(luigiHappy,width-350,100,300,600);
  drawImage(toadHappy,width/2-75,200,150,300);
  FTGLPixmapFont win("/home/dragmaf/Sviluppo/build-GraficaProgetto-Desktop-Debug/data/font/SuperMario256.ttf");
  win.FaceSize(72);
  win.Render("HAI VINTO",-1,FTPoint(width/2-200, height-190, 0));
  win.FaceSize(30);
  win.Render("Premi R per ricominciare a giocare.",-1,FTPoint(width/2-300, height/2-200, 0));
  win.Render("Premi ESC per chiudere.",-1,FTPoint(width/2-300, height/2-250, 0));
  glDisable(GL_LIGHT1);


}

void HudManager::renderLose()
{
  glEnable(GL_LIGHT1);

  FTGLPixmapFont lose("/home/dragmaf/Sviluppo/build-GraficaProgetto-Desktop-Debug/data/font/SuperMario256.ttf");
  lose.FaceSize(72);
  lose.Render("HAI PERSO",-1,FTPoint(width/2-200, height-190, 0));
  lose.FaceSize(30);
  lose.Render("Premi R per ricominciare a giocare.",-1,FTPoint(width/2-300, height/2-200, 0));
  lose.Render("Premi ESC per chiudere.",-1,FTPoint(width/2-300, height/2-250, 0));

  drawImage(textureLose,width/2-300,height/2-150,600,300);
  glDisable(GL_LIGHT1);

}

void HudManager::drawImage(GLuint texture, GLfloat x, GLfloat y, GLfloat width, GLfloat heig,bool dark)
{
  orthoMode(true);
  glBindTexture(GL_TEXTURE_2D, texture);
  glEnable(GL_TEXTURE_2D);
  glPushMatrix();
  glColor4f(1.0, 1.0, 1.0, 1.0);
  if(dark)   glColor4f(0.5, 0.5, 0.5, 1.0);
  glTranslatef(x,y,0);
    glBegin(GL_QUADS);
    glTexCoord2d(0,0);
    glVertex2d(0,0);
    glTexCoord2d(1,0);
    glVertex2d(width,0);
    glTexCoord2d(1,1);
    glVertex2d(width,heig);
    glTexCoord2d(0,1);
    glVertex2d(0,heig);
    glEnd();
  glPopMatrix();
  orthoMode(false);
}


//    orthoMode(true);
//    QVector<Wall*> walls = maze->getWalls();
//    int x=width-125,y=10;
//    for(int i =0; i <walls.size();i++){
//        Wall* wall = walls[i];
//        GLfloat x1=wall->getPositionY(),y1=wall->getPositionX();
//        glBegin(GL_QUADS);
//            glColor3d(0,0,1);
//            glVertex2d((x1+x)/SCALE_VALUE,(y1+y)/SCALE_VALUE);
//            glVertex2d((x1+x)/SCALE_VALUE,(y+y1+wall->getWidth())/SCALE_VALUE);
//            glVertex2d((x1+wall->getHeight()+x)/SCALE_VALUE,(y+y1+wall->getWidth())/SCALE_VALUE);
//            glVertex2d((x+x1+wall->getHeight())/SCALE_VALUE,(y1+y)/SCALE_VALUE);
//        glEnd();
//    }

//    GLfloat x1=player->getPositionY()+x,y1=y+player->getPositionX();

//    glBegin(GL_QUADS);
//        glColor3d(0,0,0);
//        glVertex2d(x1/SCALE_VALUE,y1/SCALE_VALUE);
//        glVertex2d(x1/SCALE_VALUE,(y1+5)/SCALE_VALUE);
//        glVertex2d((x1+5)/SCALE_VALUE,(y1+5)/SCALE_VALUE);
//        glVertex2d((x1+5)/SCALE_VALUE,y1/SCALE_VALUE);
//    glEnd();
//    orthoMode(false);
