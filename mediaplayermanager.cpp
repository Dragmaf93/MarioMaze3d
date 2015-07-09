#include "mediaplayermanager.h"

QMediaPlayer* MediaPlayerManager::goombaWhat = new QMediaPlayer();

MediaPlayerManager::MediaPlayerManager()
{
    QDir dataDir ("data");

    overworldTheme = new QMediaPlayer();
    overworldTheme->setMedia(QUrl::fromLocalFile(dataDir.absolutePath()+"/music/overworld.ogg"));
    overworldTheme->setVolume(50*VOLUME);

    marioDie = new QMediaPlayer();
    marioDie->setMedia(QUrl::fromLocalFile(dataDir.absolutePath()+"/music/mariodie.wav"));

    gameOverList = new QMediaPlaylist();
    gameOverList->addMedia(QUrl::fromLocalFile(dataDir.absolutePath()+"/music/mariodie.wav"));
    gameOverList->addMedia(QUrl::fromLocalFile(dataDir.absolutePath()+"/music/gameover.wav"));

    gameOver = new QMediaPlayer();
    gameOver->setPlaylist(gameOverList);

    levelComplete = new QMediaPlayer();
    levelComplete->setMedia(QUrl::fromLocalFile(dataDir.absolutePath()+"/music/levelComplete.wav"));
    levelComplete->setVolume(60*VOLUME);

    fireball = new QMediaPlayer();
    fireball->setMedia(QUrl::fromLocalFile(dataDir.absolutePath()+"/music/fireball.wav"));
    fireball->setVolume(60*VOLUME);

    goombaDie = new QMediaPlayer();
    goombaDie->setMedia(QUrl::fromLocalFile(dataDir.absolutePath()+"/music/goomba-die.wav"));
    goombaDie->setVolume(60*VOLUME);

    goombaWhat->setMedia(QUrl::fromLocalFile(dataDir.absolutePath()+"/music/goomba-whatwhat.wav"));
    goombaWhat->setVolume(60*VOLUME);

}


MediaPlayerManager::~MediaPlayerManager()
{
    delete overworldTheme;
    delete gameOverList;
    delete pause;
    delete gameOver;
    delete levelComplete;
    delete marioDie;
    delete fireball;
    delete goombaDie;
}

void MediaPlayerManager::playGameOver()
{
  gameOverList->setCurrentIndex(0);
  gameOver->play();
}
void MediaPlayerManager::playGoombaWhat()
{
  goombaWhat->play();
}

void MediaPlayerManager::playPause()
{
  pause->play();
}

void MediaPlayerManager::playMarioDeath()
{
  marioDie->play();
}

void MediaPlayerManager::playLevelComplete()
{
  levelComplete->play();
}

void MediaPlayerManager::playFireball()
{
  fireball->play();
}

void MediaPlayerManager::playBackground()
{
    QObject::connect (overworldTheme, SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)), this, SLOT(loopBackgroundMusic(QMediaPlayer::MediaStatus))); //LOOP BACKGROUND MUSIC

    overworldTheme->play();
}
void MediaPlayerManager::stopBackground()
{
  overworldTheme->stop();
}

void MediaPlayerManager::playGoombaDie()
{
  goombaDie->play();
}

void MediaPlayerManager::loopBackgroundMusic(QMediaPlayer::MediaStatus status)
{
    if (status == QMediaPlayer::EndOfMedia)
            overworldTheme->play();
}
void MediaPlayerManager::reset(){
  gameOver->stop();
  gameOverList->setCurrentIndex(0);
  overworldTheme->stop();
  overworldTheme->play();

}
