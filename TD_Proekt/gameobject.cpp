#include "gameobject.h"

GameObject::GameObject(){
    image = NULL;
    rect = NULL;
}
GameObject::GameObject(QString filePath, qreal scale)
{
    QImage* raw = new QImage(filePath);
    image = new QImage(raw->scaled(raw->width()/scale, raw->height()/scale, Qt::KeepAspectRatio));

    rect = new QRect(image->rect());
}

GameObject::~GameObject(){
    delete image;
    delete rect;
}
