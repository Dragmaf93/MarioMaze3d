#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include<QGLWidget>
#include<QtOpenGL>
#include<QKeyEvent>
#include<QMediaPlayer>
#include<QTimer>
#include <GL/gl.h>
#include <GL/glu.h>
#include"player.h"
#include"maze.h"
#include"sky.h"
#include"goal.h"
#include"wall.h"
#include"hudmanager.h"
#include"mediaplayermanager.h"
#include"enemymanager.h"

using namespace std;

class GameManager : public QGLWidget
{
    Q_OBJECT
public:
    explicit GameManager(QGLFormat &format);
    ~GameManager();

    void loadObject();

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width,int height);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void reset();
    void updateTimer();
    void updateGL();
    void addEnemy();
    const char *intToString(int n);
private:

    Player* player;
    Maze* maze;
    Sky* sky;
    Goal* goal;

    EnemyManager* enemyManager;
    HudManager* hudManager;
    MediaPlayerManager* mediaPlayerManager;

    QMediaPlayer* overworldTheme;
    QTimer* timer_gameloop;
    QTime initialTime;
    const int MAX_SECOND=300;
    QString timeString;

    bool hView;
    int contAfterDeath;
    bool victory;
    bool gameover;

    int xDebug,yDebug;

    GLfloat eyeShowMap[3];
    GLfloat forwardShowMap[3];
    GLdouble viewVolume;
    GLfloat ambientLight1[4];
    GLfloat ambientLight2[4];

    GLfloat diffuse[4];
    GLfloat specref[4];
    GLfloat lightPos[4];
    GLfloat  spotDir[3];
signals:


};

#endif // GAMEMANAGER_H
