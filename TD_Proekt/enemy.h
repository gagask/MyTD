#ifndef ENEMY_H
#define ENEMY_H

#include "gameobject.h"
#include "image.h"


//Types of enemies
enum class Enemy_Type{NORMAL, BADASS, BAT};

//Enemy Media Locations
namespace ENEMY {
    const QString NORMAL_L = ":/white ghost left.png";
    const QString NORMAL_R = ":/white ghost right.png";
    const QString BADASS_L = ":/red ghost left.png";
    const QString BADASS_R = ":/red ghost right.png";
    const QString BAT_L = ":/bat_l.png";
    const QString BAT_R = ":/bat_r.png";
}

class Enemy : public GameObject
{
public:
    Enemy(Enemy_Type type, QPointF p);
    ~Enemy();

    //Function to move the enemy towards the next waypoint
    void move(QPointF w);

    //Getter for the currentWaypoint
    inline int getCurWaypoint() const { return currentWaypoint; }

    //Function to increment the currentWaypoint
    inline void incrementCurWaypoint() { currentWaypoint++; }

    //Function to damage the enemy
    inline void inflictDamage(int d) { health -= d; }

    //Function to check if the enemy is dead
    inline bool isDead() const { return dead; }

    //Health getter
    inline int getHealth() const { return health; }

    //Bool dead getter
    inline void setDead(bool b) { dead = b; }

    //Score getter
    inline int getScore() const { return score; }

    //SpawnDelay getter
    inline int getSpawnDelay() const { return spawnDelay; }

    //Animation getter
    Image getAnimation() const;
private:
    //index of current or last waypoint that it has touched to use for navigating the waypoints
    int currentWaypoint;

    //All of the enemy's stats
    int health;
    bool dead;
    int score;
    int spawnDelay;

    //Animation variables
    bool faceRight;
    Image* rightAnimation;
    Image* leftAnimation;

    //animation functions
    void moveLeft(int& x);
    void moveRight(int& x);
};

#endif // ENEMY_H
