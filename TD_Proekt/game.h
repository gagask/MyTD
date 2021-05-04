#ifndef GAME_H
#define GAME_H

#include "tile.h"
#include "image.h"
#include "tower.h"
#include <QWidget>

enum State {MENU, INGAME, CLEARED, PAUSED, HELP};

class Game : public QWidget
{
    Q_OBJECT

public:
    Game(QWidget *parent = 0);
    ~Game();
public slots:

private:
    void loadInGame();
    void buildMap();
    void createNavigationPath();

    void paintEvent(QPaintEvent* event);

    State state;

    QPointF navPath[CONSTANTS::PATH_TILE_COUNT];

    std::vector<Tile*> map;
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
