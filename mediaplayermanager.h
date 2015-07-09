#ifndef MEDIAPLAYERMANAGER_H
#define MEDIAPLAYERMANAGER_H
#include<QMediaPlayer>
#include<QMediaPlaylist>
#include<QObject>
#include<QDir>

class MediaPlayerManager: public QObject
{
    Q_OBJECT
public:
    explicit MediaPlayerManager();
    ~MediaPlayerManager();

    void playBackground();
    void playGameOver();
    void playPause();
    void playMarioDeath();
    void playLevelComplete();
    void playFireball();
    void stopBackground();
    void playGoombaDie();
    void static playGoombaWhat();
    void reset();
private:
    QMediaPlayer* overworldTheme;
    QMediaPlaylist* gameOverList;
    QMediaPlayer* gameOver;
    QMediaPlayer* pause;
    QMediaPlayer* levelComplete;
    QMediaPlayer* fireball;
    QMediaPlayer* goombaDie;
    QMediaPlayer* marioDie;
    static QMediaPlayer* goombaWhat;

    double const VOLUME=0.2;

private slots:
    void loopBackgroundMusic(QMediaPlayer::MediaStatus status);

};

#endif // MEDIAPLAYERMANAGER_H
