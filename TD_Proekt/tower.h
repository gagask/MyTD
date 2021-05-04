#ifndef TOWER_H
#define TOWER_H

#include "gameobject.h"
#include <QPointF>
#include "image.h"
#include "enemy.h"

//Tower media file paths
namespace TOWER{
    const QString TOWER_FIRE = ":/fire.png";
    const QString TOWER_ICE = ":/ice.png";
    const QString TOWER_EARTH = ":/rock.png";
}

//Tower types
enum Type{FIRE,ICE,EARTH};

/*
    @class Tower
    @brief class for all tower functions and data
*/
class Tower : public GameObject
{
    Q_OBJECT
public:
    //Constructor
    Tower(QString fileName, QRect tile);

    //Getters
    inline int getTimer() const { return timerID; }
    inline bool isCoolDown() const { return coolDown; }
    inline Type getType() const { return type; }

    //Setters
    inline void setTimer(int id) { timerID = id; }
    inline void setCoolDown(bool c) { coolDown = c; }

    //Static getters for Tower types
    static int getCost(Type t);
    static int getDamageCost(Type t);
    static int getRangeCost(Type t);
    static int getCoolDownCost(Type t);
    static int getDamage(Type t);
    static int getRange(Type t);
    static int getCoolDown(Type t);
    static void upgradeDamage(Type t);
    static void upgradeRange(Type t);
    static void upgradeCoolDown(Type t);

    //Function to reset the Tower type data
    static void resetUpgrades();
public slots:
    void toggleCoolDown(){setCoolDown(false);}
private:
    //Attacking stats
    Type type;
    int timerID;
    bool coolDown;

    //Class to hold tower type data
    class TowerStats{
    public:
        TowerStats():d_count(0), r_count(0), s_count(0){}
        int d_count, r_count, s_count;
    };

    //The tower type data variables
    static TowerStats fire;
    static TowerStats ice;
    static TowerStats earth;

    //The counts of each tower type
    static int fireCount;
    static int iceCount;
    static int earthCount;
};

#endif // TOWER_H
