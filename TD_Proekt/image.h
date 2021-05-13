#ifndef IMAGE_H
#define IMAGE_H

#include "gameobject.h"
#include <iostream>


class Image : public GameObject
{
public:
    Image(QString filePath) : GameObject(filePath) , fpath(filePath) {}
    Image(QString filePath, qreal scale) : GameObject(filePath, scale) {}
    Image(const Image& i);
    Image(){ setRect(QRect(0,0,0,11));}

    Image* scaledCopy(double scale);

    void append(Image* i);
private:
    QString fpath;
};

#endif // IMAGE_H
