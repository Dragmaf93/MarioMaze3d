#include <QApplication>
#include<QDesktopWidget>
#include<QDebug>
#include"gamemanager.h"
#include<QGLFormat>
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QGLFormat glFormat;
    glFormat.setVersion( 3, 2 );
    glFormat.setProfile( QGLFormat::CoreProfile ); // Requires >=Qt-4.8.0
    glFormat.setSampleBuffers( true );
    GameManager game(glFormat);
    game.loadObject();
    game.setWindowTitle("Maze3D");

    game.showMaximized();
    return app.exec();
}
