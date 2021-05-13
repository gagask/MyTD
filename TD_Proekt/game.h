#ifndef GAME_H
#define GAME_H
#include "button.h"
#include "tile.h"
#include "image.h"
#include "tower.h"
#include "wavegenerator.h"
#include <QWidget>
#include <deque>
#include <QTimer>

namespace TOOLTIP{
    const QString BASE = ":/tooltip_base.png";
}
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
    void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
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

    void paintChar(std::string,double,QPainter&,int,int,bool);
    void printChar(Image* character, double scale, QPainter& p, int& x, int& y);

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
    Button* start_button;
    Button* help_button;
    Button* quit_button;
    Button* continue_button;
    std::vector<Image*> letterChars;
    std::vector<Image*> letterCharsAct;
    std::vector<Image*> letterCharsRed;
    std::vector<Image*> specialChars;

    std::vector<Image*> towerOptions;
    int curTowerOpt;
    Type curTowerType;
    Image* title_line1;
    Image* title_line2;
    Image* wave_title;
    Image* score_title;
    Image* towerOptHighlight;
    Image* tileHighlight;
    std::vector<Image*> fire_upgrade;
    std::vector<Image*> upgrade_icon;
    std::vector<Image*> ice_upgrade;
    std::vector<Image*> earth_upgrade;
    std::vector<Button*> pauseButtons;
    std::vector<Button*> arrows;
    std::vector<Image*> helpImages;
    int helpIndex;
    void selectTile(Tile*);
     class ToolTip;
     ToolTip* tooltip;

     class ToolTip{
     public:
         ToolTip(Image* s, Image* s_u, Image*, Image* c_a);
         ToolTip(Image* c, Image* c_a);
         ~ToolTip();

         void moveTo(QPointF position);
         void paint(QPainter* p);
     private:
         bool upgrade;
         Image* cost;
         Image* cost_amount;
         Image* background;
         Image* stat;
         Image* stat_upgrade;

         void resizeBackground();
     };
};

#endif // GAME_H
