#ifndef GAME_H
#define GAME_H

#include "tile.h"
#include "image.h"
#include "tower.h"
#include "wavegenerator.h"
#include <QWidget>
#include <deque>
#include <QTimer>

enum State {MENU, INGAME, CLEARED, PAUSED, HELP};

enum Chars {NORMAL, ACTIVE, RED};

class Game : public QWidget
{
    Q_OBJECT

public:
    Game(QWidget *parent = 0);
    ~Game();
public slots:
    void moveDecals(){for(auto& d : damageDisplays)d->getRect()->translate(0,-1); if(state==INGAME)QTimer::singleShot(150,this,SLOT(moveDecals()));}
    void removeDecal(){Image* front = damageDisplays.front(); damageDisplays.pop_front(); delete front;}
    void moveEvent(){cleanEnemyList(); moveEnemies(); if(state==INGAME)QTimer::singleShot(30,this,SLOT(moveEvent()));}
    void collisionEvent(){raycast(); if(state == INGAME)QTimer::singleShot(30,this,SLOT(collisionEvent()));}

private:
    void loadInGame();
    void buildMap();
    void createNavigationPath();

    void paintEvent(QPaintEvent* event);
    void timerEvent(QTimerEvent* event);

    void newGame();
    void clearGame();
    void raycast();
    void moveEnemies();
    void cleanEnemyList();
    void spawner();
    void newWave();
    void startTimers();

    inline int getWave() const { return wave_value; }
    inline int getScore() const { return score_value; }

    inline void updateWave(){ wave_value++; }
    inline void updateScore(int v) { score_value += v; }


    void appendChar(Image* character, double scale, Image* i);
    Image* mergeChars(std::string,double,Chars);

    int wave_value;
    int score_value;
    State state;

    QPointF navPath[CONSTANTS::PATH_TILE_COUNT];

    int paintTimer;
    int spawnTimer;

    int enemyCount;

    WaveGenerator wave_generator;

    DEFAULT generator;
    std::uniform_int_distribution<int> damageDisplayOffset;
    std::deque<Image*> damageDisplays;

    std::vector<Enemy*> enemies;
    std::vector<Enemy*> spawnList;
    std::vector<Tile*> map;
    std::vector<Tower*> towers;

    std::vector<Image*> letterChars;
    std::vector<Image*> letterCharsAct;
    std::vector<Image*> letterCharsRed;
    std::vector<Image*> specialChars;

    std::vector<Image*> towerOptions;
    int curTowerOpt;
    Type curTowerType;
    Image* towerOptHighlight;
    Image* tileHighlight;
    std::vector<Image*> fire_upgrade;
    std::vector<Image*> upgrade_icon;
    std::vector<Image*> ice_upgrade;
    std::vector<Image*> earth_upgrade;
};

#endif // GAME_H
