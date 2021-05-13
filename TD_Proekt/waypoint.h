#ifndef WAYPOINT_H
#define WAYPOINT_H

#include <QPointF>


class Waypoint
{
public:
    Waypoint(int x, int y) : pos(new QPointF(x, y)){}

    inline QPointF getPos() const{ return *pos; }
private:
    QPointF* pos;
};

#endif // WAYPOINT_H
