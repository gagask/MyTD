#ifndef TILE_H
#define TILE_H

#include "gameobject.h"


class Tile : public GameObject
{
public:
    Tile(QString fileName, int id=0) : GameObject(fileName) , occupied(false) , active(false) , path_id(id){ (path_id==0) ? path = false : path = true; }
    bool isActive() const { return active; }
    bool isOccupied() const { return occupied; }
    bool isPath() const { return path; }
    int getPathID() const { return path_id; }

    void setActive(bool b) { active = b; }
    void setOccupied(bool b)  { occupied = b; }
private:
    bool path;
    bool occupied;
    bool active;
    int path_id;
};

#endif // TILE_H
