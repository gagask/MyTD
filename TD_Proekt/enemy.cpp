#include "enemy.h"


Enemy::Enemy(Enemy_Type type, QPointF p) : GameObject(), currentWaypoint(0),
     dead(false), spawnDelay(2000), faceRight(false)
{
    if(type == Enemy_Type::NORMAL){
        leftAnimation = new Image(ENEMY::NORMAL_L);
        rightAnimation = new Image(ENEMY::NORMAL_R);
        health = 3;
        score = 10;
    }
    else if(type == Enemy_Type::BADASS){
        leftAnimation = new Image(ENEMY::BADASS_L);
        rightAnimation = new Image(ENEMY::BADASS_R);
        health = 10;
        score = 15;
    }
    else if(type == Enemy_Type::BAT){
        leftAnimation = new Image(ENEMY::BAT_L);
        rightAnimation = new Image(ENEMY::BAT_R);
        health = 15;
        score = 20;
    }

    setImage(*leftAnimation->getImage());
    setRect(*leftAnimation->getRect());

    getRect()->translate(p.toPoint().rx()-getRect()->width()/2, p.toPoint().ry()-getRect()->height()/2);
}

Enemy::~Enemy(){
    delete leftAnimation;
    delete rightAnimation;
}

void Enemy::move(QPointF w){
    int x=0, y=0;

    if(std::abs(w.rx() - getRect()->center().rx()) > 0.1 &&
       std::abs(w.ry() - getRect()->center().ry()) > 0.1){
        (w.rx() > getRect()->center().rx()) ? moveRight(x) : moveLeft(x);
        (w.ry() > getRect()->center().ry()) ? y=1 : y=-1;
    }
    else if(std::abs(w.rx() - getRect()->center().rx()) > 0.1)
        (w.rx() > getRect()->center().rx()) ? moveRight(x) : moveLeft(x);
    else if(std::abs(w.ry() - getRect()->center().ry()) > 0.1)
        (w.ry() > getRect()->center().ry()) ? y=1 : y=-1;

    getRect()->translate(x, y);
}

void Enemy::moveLeft(int& x){
    x=-1;
    faceRight = false;
    setImage(*leftAnimation->getImage());
}


void Enemy::moveRight(int& x){
    x=1;
    faceRight = true;
    setImage(*rightAnimation->getImage());
}


Image Enemy::getAnimation() const{
    if(faceRight)
        return *rightAnimation;
    else
        return *leftAnimation;
}
