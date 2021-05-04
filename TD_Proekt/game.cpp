
#include "game.h"
#include <QApplication>
#include <QPainter>

Game::Game(QWidget *parent) : QWidget(parent) , state(INGAME), curTowerOpt(0), curTowerType(FIRE)
{
    setWindowTitle("Tower Defence");
    setFixedSize(CONSTANTS::SCREEN_WIDTH, CONSTANTS::SCREEN_HEIGHT);
    loadInGame();
}

Game::~Game()
{
}

void Game::loadInGame(){
    towerOptions.push_back(new Image(CONSTANTS::TOWER_FIRE));
    towerOptions.push_back(new Image(CONSTANTS::TOWER_ICE));
    towerOptions.push_back(new Image(CONSTANTS::TOWER_EARTH));
    towerOptHighlight = new Image(CONSTANTS::TOWEROPT_H);

    //Upgrade Menu
    for(int i = 0; i<3; i++){
        fire_upgrade.push_back(new Image(CONSTANTS::UPGRADE_FIRE_BASE));
        ice_upgrade.push_back(new Image(CONSTANTS::UPGRADE_ICE_BASE));
        earth_upgrade.push_back(new Image(CONSTANTS::UPGRADE_EARTH_BASE));
    }
    upgrade_icon.push_back(new Image(CONSTANTS::UPGRADE_STRENGTH));
    upgrade_icon.push_back(new Image(CONSTANTS::UPGRADE_RANGE));
    upgrade_icon.push_back(new Image(CONSTANTS::UPGRADE_RATE));


    towerOptions[0]->getRect()->moveTo(width()-towerOptions[0]->getRect()->width()-5, 50);
    towerOptions[1]->getRect()->moveTo(width()-towerOptions[1]->getRect()->width()-5, 50 + towerOptions[0]->getRect()->height());
    towerOptions[2]->getRect()->moveTo(width()-towerOptions[2]->getRect()->width()-5, 50 + towerOptions[0]->getRect()->height() + towerOptions[1]->getRect()->height());

    //Upgrade Menu
    int x = width()-towerOptions[0]->getRect()->width()-5;
    int y = 75 + towerOptions[0]->getRect()->height() + towerOptions[1]->getRect()->height() + towerOptions[2]->getRect()->height();
    for(size_t i = 0, s = fire_upgrade.size(); i < s; i++){
        fire_upgrade[i]->getRect()->moveTo(x+(fire_upgrade[i]->getRect()->width())/4, y);
        ice_upgrade[i]->getRect()->moveTo(x+(fire_upgrade[i]->getRect()->width())/4, y);
        earth_upgrade[i]->getRect()->moveTo(x+(fire_upgrade[i]->getRect()->width())/4, y);
        upgrade_icon[i]->getRect()->moveTo(x+(fire_upgrade[i]->getRect()->width())/4, y);
        y += fire_upgrade[i]->getRect()->height()+2;
    }

    //Build the map and create the waypoint system
    buildMap();
    createNavigationPath();
}

void Game::createNavigationPath(){
    for(auto& t : map){
        if(t->isPath())
            navPath[t->getPathID()-1] = t->getRect()->center();
    }
}

void Game::buildMap(){
    for(const auto d : CONSTANTS::MAP)
        d==0 ?  map.push_back(new Tile(CONSTANTS::GRASS_TILE)) : map.push_back(new Tile(CONSTANTS::DIRT_TILE,d));
    int xPos = 50;
    int yPos = 50;
    int colCounter = 0;
    for(auto& t : map){
        t->getRect()->moveTo(xPos, yPos);
        if(++colCounter < CONSTANTS::TILE_COL)
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
    //Draw the score and wave Images

    //Tower Builder Menu
    for(const auto o : towerOptions)
        painter.drawImage(*o->getRect(), *o->getImage());
    painter.drawImage(*towerOptions[curTowerOpt]->getRect(), *towerOptHighlight->getImage());

    //Upgrade menu
    switch(curTowerOpt){
        case 0:
            for(auto& u : fire_upgrade)
                painter.drawImage(*u->getRect(), *u->getImage());
            break;
        case 1:
            for(auto& u : ice_upgrade)
                painter.drawImage(*u->getRect(), *u->getImage());
            break;
        case 2:
            for(auto& u : earth_upgrade)
                painter.drawImage(*u->getRect(), *u->getImage());
            break;
    }

    //Draw the upgrade menu icons
    for(auto& i : upgrade_icon)
        painter.drawImage(*i->getRect(), *i->getImage());

    //Draw the map tiles
    for(auto& t : map){
        painter.drawImage(*t->getRect(), *t->getImage());
        if(t->isActive())
            painter.drawImage(*tileHighlight->getRect(), *tileHighlight->getImage());
    }

    //Draw each of the enemies
    /*for(auto& e : enemies)
        if(!e->isDead())
            painter.drawImage(*e->getRect(), *e->getImage());
            */
\
    //Draw the towers
    /*for(const auto t : towers)
        painter.drawImage(*t->getRect(), *t->getImage());
        */

    //Draw the tooltip
    /*if(tooltip != NULL)
        tooltip->paint(&painter);*/
}
