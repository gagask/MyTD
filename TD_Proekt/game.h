#ifndef GAME_H
#define GAME_H

#include "tile.h"
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

    void paintEvent(QPaintEvent* event);

    State state;

    std::vector<Tile*> map;

};

#endif // GAME_H
