#include "goomba.h"

Goomba::Goomba(GLfloat xStart, GLfloat yStart, GLfloat xEnd, GLfloat yEnd,
               GLuint modelList,Player* player,Maze* maze)
{

  this->xStart=xStart;
  this->yStart=yStart;
  this->xEnd=xEnd;
  this->yEnd=yEnd;
  this->modelList=modelList;
  this->player=player;
  this->maze = maze;
  positionX=xStart;
  positionY=yStart;
  positionZ=zDeath=0;
  timeStopToSee=0;
  setSize(1.5,1.5,1.5);
  hitByFireball=false;

  startToEnd=true;
  followPlayer=false;
  returnToRoute=false;
  stopToSee=false;

  if(horizontalMove())
    angleRotation=180;
  else
    angleRotation=90;

}

Goomba::~Goomba()
{

}

void Goomba::render()
{
  glPushMatrix();
  if(!hitByFireball && !stopToSee){
    glTranslated(positionX,positionY,positionZ);
    glRotatef(90,1,0,0);
    glRotatef(angleRotation,0,1,0);
    move();
    glCallList(modelList);
  }else if(hitByFireball){
      zDeath-=0.3;
      glTranslated(positionX,positionY,zDeath);
      glRotatef(90,1,0,0);
      glRotatef(angleRotation,0,1,0);
      move();
      glCallList(modelList);
  }else if(stopToSee){

      glTranslated(positionX,positionY,positionZ);
      glRotatef(90,1,0,0);
      glRotatef(angleRotation,0,1,0);
      move();
      glCallList(modelList);
      timeStopToSee++;
      if(timeStopToSee>20){
        timeStopToSee=0;
        stopToSee=false;
      }
  }
  glPopMatrix();
}

bool Goomba::farToRoute(){
  if(horizontalMove()){
    if(positionX<xStart+MAX_DISTANCE_ROUTE && positionX>xStart-MAX_DISTANCE_ROUTE)
      return false;
  }else{
    if(positionY<yStart+MAX_DISTANCE_ROUTE && positionY>yStart-MAX_DISTANCE_ROUTE)
      return false;
  }
  return true;
}

void Goomba::setAngleRotation(GLfloat x2, GLfloat y2)
{

  if(positionX>x2 && positionY<y2)
    angleRotation=225;
  else if(positionX>x2 && positionY>y2)
    angleRotation=315;
  else if(positionX<x2 && positionY>y2)
    angleRotation=45;
  else if(positionX<x2 && positionY<y2)
    angleRotation=135;

  GLfloat radiant = atan2(y2,x2)-atan2(positionY,positionX);
  angleRotation=((int)(angleRotation+(radiant*180/3.141592653589793))) % 360;
  qDebug() <<angleRotation;
}

void Goomba:: move()
{
  if(isTherePlayer()){
    if(!stopToSee && !followPlayer){
      MediaPlayerManager::playGoombaWhat();
      stopToSee=true;
    }
      followPlayer=true;
  }else{
      if(followPlayer){
          returnToRoute=true;
      }
    followPlayer=false;
  }

  if(farToRoute()){
   followPlayer=false;
   returnToRoute=true;
  }

  if(followPlayer && !returnToRoute && !hitByFireball &&!stopToSee){
      if(!collideWall( positionX+((player->getPositionX()-positionX)/30),positionY+(player->getPositionY()-positionY)/30))
       {
          setAngleRotation(player->getPositionX(),player->getPositionY());
          positionX+=(player->getPositionX()-positionX)/30;
          positionY+=(player->getPositionY()-positionY)/30;
       }
  }else if(returnToRoute && !hitByFireball &&!stopToSee){
      if(horizontalMove()){
        if(positionX<xStart){
            angleRotation=90;
           positionX+=SPEED;
          if(positionX>xStart)
            positionX=xStart;
        }else{
          positionX-=SPEED;
          angleRotation=270;
          if(positionX<xStart)
            positionX=xStart;
        }
        if(positionX==xStart)
          returnToRoute=false;
      }else{
          if(positionY<yStart){
            positionY+=SPEED;
            angleRotation=180;
            if(positionY>yStart)
              positionY=yStart;
          }else{
            positionY-=SPEED;
            angleRotation=0;
            if(positionY<yStart)
              positionY=yStart;
          }
          if(positionY==yStart)
            returnToRoute=false;
      }
  }else if(!hitByFireball && !stopToSee){
    if(horizontalMove()){
      if(startToEnd){
       if(!collideWall( positionX,positionY+SPEED)){
         positionY+=SPEED;
         angleRotation=180;
       }else{
         startToEnd=false;
         angleRotation=0;
        }
      }
      else{
          if(!collideWall( positionX,positionY-SPEED)){
              positionY-=SPEED;
              angleRotation=0;
          }else{
            startToEnd=true;
            angleRotation=180;

          }
      }
     if(positionY<=yStart && (positionX<=xStart+1 || positionX>=xStart-1)){
       startToEnd=true;
       angleRotation=180;
     }else if(positionY>=yEnd && (positionX<=xStart+1 || positionX>=xStart-1)){
       startToEnd=false;
       angleRotation=0;
     }

    }else{
     if(startToEnd){
        if(!collideWall( positionX+SPEED,positionY)){
          positionX+=SPEED;
          angleRotation=90;

        }else{
          startToEnd=false;
          angleRotation=270;
        }
     }else{
      if(!collideWall( positionX-SPEED,positionY)){
        positionX-=SPEED;
        angleRotation=270;
        }else{
          startToEnd=true;
          angleRotation=90;
        }
      }
      if(positionX<=xStart && (positionY<=yStart+1 || positionY>=yStart-1)){
        startToEnd=true;
        angleRotation=90;
      }else if(positionX>=xEnd && (positionY<=yStart+1 || positionY>=yStart-1)){
        startToEnd=false;
        angleRotation=270;
      }
  }
  }
}

void Goomba::reset()
{
  positionX=xStart;
  positionY=yStart;
  positionZ=zDeath=0;

  startToEnd=true;
  followPlayer=false;
  hitByFireball=false;
  if(horizontalMove())
    angleRotation=180;
  else
    angleRotation=90;
}

void Goomba::hit()
{
  hitByFireball=true;
}

bool Goomba::collideWall(GLfloat x,GLfloat y)
{

  QVector<Wall*> walls = maze->getWalls();
  for (int i = 0; i < walls.size(); i++)
  {
    if ((x+appross <= walls[i]->getPositionX() + walls[i]->getWidth()+3 && x+appross >= walls[i]->getPositionX())
      && (y+appross <= walls[i]->getPositionY() + walls[i]->getHeight()+3 && y+appross >= walls[i]->getPositionY()) ||
    (x-appross <= walls[i]->getPositionX() + walls[i]->getWidth() && x-appross >= walls[i]->getPositionX())
      && (y-appross <= walls[i]->getPositionY() + walls[i]->getHeight() && y-appross >= walls[i]->getPositionY()))
      return true;
  }
  return false;
}

bool Goomba::horizontalMove()
{
  if(xStart==xEnd && yStart!=yEnd) return true;
  else if(xStart!=xEnd && yStart==yEnd) return false;
  else
    qDebug() << "ERRORE ALLOCAZIONE GOOMBA";
}

bool Goomba::isTherePlayer()
{
  if(horizontalMove()){
    if(startToEnd){
        if(positionY< player->getPositionY() && positionY+RANGEM>=player->getPositionY()
           && ((positionX< player->getPositionX() && positionX+RANGEm>=player->getPositionX())
               || (positionX> player->getPositionX() && positionX-RANGEm<=player->getPositionX())))
              return true;

    }
    else{
        if(positionY>player->getPositionY() && positionY-RANGEM<=player->getPositionY()
           && ((positionX< player->getPositionX() && positionX+RANGEm>=player->getPositionX())
               || (positionX> player->getPositionX() && positionX-RANGEm<=player->getPositionX())))
             return true;
   }
    }
   else
          if(startToEnd){
              if(positionX< player->getPositionX() && positionX+RANGEM>=player->getPositionX()
                 && ((positionY< player->getPositionY() && positionY+RANGEm>=player->getPositionY())
                     || (positionY> player->getPositionY() && positionY-RANGEm<=player->getPositionY())))
                    return true;
          }
          else{
              if(positionX>player->getPositionX() && positionX-RANGEM<=player->getPositionX()
                 && ((positionY< player->getPositionY() && positionY+RANGEm>=player->getPositionY())
                     || (positionY> player->getPositionY() && positionY-RANGEm<=player->getPositionY())))
                      return true;}
  return false;

}

bool Goomba::canRemove()
{
  if(zDeath<=MAX_Z_DEATH) return true;
  return false;
}

