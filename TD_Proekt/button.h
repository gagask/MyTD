#ifndef BUTTON_H
#define BUTTON_H

#include "image.h"


class Button : public Image
{
public:
    //Constructor
    Button(QString filePath, QString h_filePath, qreal scale);
    Button(Image* passive, Image* active);
    ~Button();

    inline void setActive(bool a){ active = a; }
    inline bool isActive() const { return active; }
    inline QImage getActiveImage() const { return *activeImage; }
private:

    QImage* activeImage;
    bool active;
};

#endif // BUTTON_H
