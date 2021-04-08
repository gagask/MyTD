#ifndef TILE_H
#define TILE_H

#include "gameobject.h"

class Tile : public GameObject
{
public:
    Tile(QString fileName, int id=0) : GameObject(fileName) , occupied(false) , active(false) , path_id(id){ (path_id==0) ? path = false : path = true; }
private:
    //Properties
    bool path;
    bool occupied;
    bool active;
    int path_id;
};

#endif // TILE_H
