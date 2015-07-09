#include "gamemanager.h"
#include<QDebug>
#include<QDir>

GameManager::GameManager(QGLFormat &format)
    : QGLWidget(format)
{

    ambientLight1[0] = 0.5;
    ambientLight1[1] = 0.5;
    ambientLight1[2] = 0.5;
    ambientLight1[3] = 1.0;

    ambientLight2[0] = 0.1;
    ambientLight2[1] = 0.1;
    ambientLight2[2] = 0.1;
    ambientLight2[3] = 1.0;

    diffuse[0] = 0.5;
    diffuse[1] = 0.5;
    diffuse[2] = 0.5;
    diffuse[3] = 1.0;

    lightPos[0] = 10;
    lightPos[1] = 10;
    lightPos[2] = 10;
    lightPos[3] = 1.0;

    forwardShowMap[0]=108.667;
    forwardShowMap[1]=116.33;
    forwardShowMap[2]=2.0;

    eyeShowMap[0]=109;
    eyeShowMap[1]=116;
    eyeShowMap[2]=300;


    timer_gameloop= new QTimer();
    connect(timer_gameloop,SIGNAL(timeout()),SLOT(updateGL()));
    timer_gameloop->start(25);

    initialTime = QTime::currentTime();
    initialTime.start();
    makeCurrent();

    victory=false;
    gameover=false;
    xDebug = yDebug=0;
    hView=false;
}

GameManager::~GameManager()
{
    delete player;
    delete maze;
    delete sky;
    delete goal;
    delete timer_gameloop;
    delete hudManager;
    delete mediaPlayerManager;
}

void GameManager::loadObject()
{
    mediaPlayerManager = new MediaPlayerManager();
    mediaPlayerManager->playBackground();
    maze = new Maze();
    goal = new Goal(115,150);
    sky = new Sky(200);
    player = new Player(maze,goal);
    hudManager = new HudManager(maze,player,width(),height());
    enemyManager = new EnemyManager(maze,player);
    addEnemy();
    player->setEnemyManager(enemyManager);

}
void GameManager::initializeGL()
{
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_LIGHTING);

    glLightfv(GL_LIGHT0,GL_AMBIENT,ambientLight2);
    glLightfv(GL_LIGHT0,GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0,GL_POSITION,lightPos);
    glEnable(GL_LIGHT0);

    glLightfv(GL_LIGHT1,GL_AMBIENT,ambientLight1);

    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glMateriali(GL_FRONT, GL_SHININESS,1);

    glEnable(GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void GameManager::resizeGL(int width, int height)
{
    glViewport (0, 0, width, height);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluPerspective(60.0, (float) width / (float) height, 1.0, 1024.0);
    glMatrixMode(GL_MODELVIEW);
    hudManager->resize(width,height);
    glLoadIdentity();

}
int distanceGoal =100;
void GameManager::paintGL()
{
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glPushMatrix();
    if(!victory && !gameover){

        if(hView){
        gluLookAt(eyeShowMap[0],eyeShowMap[1],eyeShowMap[2],forwardShowMap[0],forwardShowMap[1],forwardShowMap[2],0,1,0);
        }
        else player->render();
        maze->render();
        sky->render();
        goal->render();
        enemyManager->renderEnemy();

        if(player->hitGoomba())
          mediaPlayerManager->playGoombaDie();

    }else if(victory){
      hudManager->renderVictory();
    }else if(gameover){
      hudManager->renderLose();
    }
    glPopMatrix();

    if(!gameover && !victory){
        glEnable(GL_LIGHT1);
        hudManager->render();
        hudManager->renderTime(&timeString);
        glDisable(GL_LIGHT1);
    }
    glFlush();

}

void GameManager::keyPressEvent(QKeyEvent *event)
{
    if(event->key()== Qt::Key_Up){
        player->move("FORWARD");
    }
    if(event->key()== Qt::Key_Down){
        player->move("BACK");
    }
    if(event->key()== Qt::Key_Left){
        player->move("LEFT");
    }
    if(event->key()== Qt::Key_Right){
        player->move("RIGHT");
    }
    if(event->key() == Qt::Key_Space && player->readyToFire()){
      player->fire();
      mediaPlayerManager->playFireball();

    }
    if(event->key() == Qt::Key_R && (victory || gameover))
        this->reset();
    if(event->key() == Qt::Key_Escape && (victory || gameover))
       this->close();
    if(event->key() == Qt::Key_M)
      hView = !hView;
}

void GameManager::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key()== Qt::Key_Up){
        player->stopToMove("FORWARD");
    }
    if(event->key()== Qt::Key_Down){
        player->stopToMove("BACK");
    }
    if(event->key()== Qt::Key_Left){
        player->stopToMove("LEFT");
    }
    if(event->key()== Qt::Key_Right){
        player->stopToMove("RIGHT");
      }

}

void GameManager::mousePressEvent(QMouseEvent *event)
{
  int x =event->pos().x()-459;
  int y=height()-event->pos().y()-109;
  xDebug=x*250/520;
  yDebug=y*250/520;
//  player->setEye(xDebug,yDebug,2);

}

void GameManager::reset()
{
  victory=false;
  gameover=false;
  initialTime.restart();

  player->reset(true);
  mediaPlayerManager->reset();
    addEnemy();
  enemyManager->reset();
}

void GameManager::updateTimer()
{
    int residualSec= MAX_SECOND - initialTime.elapsed()/1000;
    timeString.clear();
    timeString.setNum(residualSec);
}

void GameManager::updateGL()
{
    player->setLight(lightPos,spotDir);
    updateTimer();
    if(!victory && !gameover){
        player->update();
        if(enemyManager->goombaCollidePlayer()){
          player->die();
          if(player->getNumberLife()==0){
            gameover=true;
            mediaPlayerManager->stopBackground();
            mediaPlayerManager->playGameOver();
          }
          else{
            mediaPlayerManager->playMarioDeath();
            initialTime.restart();
            player->reset();
            mediaPlayerManager->reset();
            addEnemy();
            enemyManager->reset();
        }
       }
       if(player->collideGoal(player->getPositionX(),player->getPositionY())){
            victory=true;
            mediaPlayerManager->stopBackground();
            mediaPlayerManager->playLevelComplete();
      }
        if((initialTime.elapsed()/1000)>=MAX_SECOND){

          player->die();
          if(player->getNumberLife()==0){
            gameover=true;
            mediaPlayerManager->stopBackground();
            mediaPlayerManager->playGameOver();
          }
          else{
            mediaPlayerManager->playMarioDeath();
            initialTime.restart();
            player->reset();
            mediaPlayerManager->reset();
            addEnemy();
            enemyManager->reset();
          }
        }

    }

    QGLWidget::updateGL();

}

void GameManager::addEnemy()
{
  enemyManager->clear();
////  //vertical
  enemyManager->generateGoomba(10,10,10,50);
  enemyManager->generateGoomba(10,70,10,120);
  enemyManager->generateGoomba(10,200,10,250);
  enemyManager->generateGoomba(10,130,10,160);
  enemyManager->generateGoomba(27,160,27,200);
  enemyManager->generateGoomba(42,130,42,200);
  enemyManager->generateGoomba(45,180,45,250);
  enemyManager->generateGoomba(60,150,60,250);
  enemyManager->generateGoomba(75,150,75,250);
  enemyManager->generateGoomba(92,185,92,250);
  enemyManager->generateGoomba(93,10,93,50);
  enemyManager->generateGoomba(107,175,107,235);
  enemyManager->generateGoomba(110,40,110,100);
  enemyManager->generateGoomba(125,40,125,120);
  enemyManager->generateGoomba(140,50,140,120);
  enemyManager->generateGoomba(140,150,140,200);
  enemyManager->generateGoomba(155,60,155,120);
  enemyManager->generateGoomba(155,140,155,200);
  enemyManager->generateGoomba(173,80,173,170);
  enemyManager->generateGoomba(190,80,190,180);
  enemyManager->generateGoomba(207,60,207,180);
  enemyManager->generateGoomba(223,80,223,180);
  enemyManager->generateGoomba(240,140,240,180);
  enemyManager->generateGoomba(240,190,240,250);
  enemyManager->generateGoomba(240,40,240,80);



  //horizontal
  enemyManager->generateGoomba(60,125,150,125);
  enemyManager->generateGoomba(40,70,90,70);
  enemyManager->generateGoomba(26,236,76,236);
  enemyManager->generateGoomba(125,236,200,236);
  enemyManager->generateGoomba(125,219,190,219);
  enemyManager->generateGoomba(178,179,225,179);
  enemyManager->generateGoomba(26,105,60,105);
  enemyManager->generateGoomba(26,11,80,11);
  enemyManager->generateGoomba(145,195,220,195);
  enemyManager->generateGoomba(160,46,220,46);
  enemyManager->generateGoomba(138,30,160,30);
  enemyManager->generateGoomba(175,30,220,30);
  enemyManager->generateGoomba(110,11,160,11);
  enemyManager->generateGoomba(175,11,230,11);
}
const char* GameManager::intToString(int n)
{
//  qDebug() << n;
  stringstream convert;
  convert << n;
  string str = convert.str();
  return str.c_str();
}
