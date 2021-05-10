#ifndef IMAGE_H
#define IMAGE_H

#include "gameobject.h"


class Image : public GameObject
{
public:
    //Constructors
    Image(QString filePath) : GameObject(filePath) , fpath(filePath) {}
    Image(QString filePath, qreal scale) : GameObject(filePath, scale) {}
    Image(const Image& i);
    Image(){ setRect(QRect(0,0,0,11));}

    //Function to rescale the image
    Image* scaledCopy(double scale);

    //function to append another image to the current image
    void append(Image* i);
private:
    //The file path of the image
    QString fpath;
};

#endif // IMAGE_H
