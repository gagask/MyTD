
#include "game.h"
#include <QApplication>
#include <QPainter>

Game::Game(QWidget *parent) : QWidget(parent) , state(INGAME)
{
    setWindowTitle("Tower Defence");
    setFixedSize(CONSTANTS::SCREEN_WIDTH, CONSTANTS::SCREEN_HEIGHT);
    loadInGame();
}

Game::~Game()
{
}

void Game::loadInGame(){
    buildMap();
}

void Game::buildMap(){
    for(const auto d : CONSTANTS::MAP)
        d==0 ?  map.push_back(new Tile(CONSTANTS::GRASS_TILE)) : map.push_back(new Tile(CONSTANTS::DIRT_TILE,d));
    int xPos = 50;
    int yPos = 50;
    int colCounter = 0;
    for(auto& t : map){
        t->getRect()->moveTo(xPos, yPos);
        if(++colCounter<CONSTANTS::TILE_COL)
            xPos += t->getRect()->width();
        else{
            xPos = 50;
            colCounter = 0;
            yPos += t->getRect()->height();
        }
    }
}
void Game::paintEvent(QPaintEvent*){
    QPainter painter(this);
    for(auto& t : map){
        painter.drawImage(*t->getRect(), *t->getImage());
    }
}
