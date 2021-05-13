#include "game.h"
#include <QApplication>
#include <QPainter>
#include <QMouseEvent>

Game::Game(QWidget *parent) : QWidget(parent) , state(INGAME), curTowerOpt(0), curTowerType(FIRE)
{
    setWindowTitle("Tower Defence");
    setFixedSize(CONSTANTS::SCREEN_WIDTH, CONSTANTS::SCREEN_HEIGHT);
    loadInGame();
    newGame();
}

Game::~Game()
{
}

void Game::newGame(){
    //Delete any existing data
    clearGame();
    //load new wave data
    wave_value = 0;
    //Set up the wave
    newWave();
    score_value = 20;
    //start the timer used for spawning events
    paintTimer = startTimer(10);
}

void Game::newWave(){
    //New wave
    updateWave();
    //Clear enemy list
    for(auto& e : enemies)
        delete e;
    enemies.clear();

    //Clear spawnList
    spawnList.clear();

    //New spawnList
    spawnList = wave_generator.generateSpawnList(getWave(), navPath[0]);
    enemyCount = spawnList.size();

    //Start the timers
    spawnTimer = startTimer(2000);
    startTimers();
}

void Game::startTimers(){
    //Start the timer that will update the enemies positions
    QTimer::singleShot(30,this,SLOT(moveEvent()));
    //Start the timer that moves the damge number images
    QTimer::singleShot(150,this,SLOT(moveDecals()));
    //Start the timer that will check for enemies within the towers range
    QTimer::singleShot(30,this,SLOT(collisionEvent()));
}

void Game::clearGame(){
    //Reset the upgrade stats
    Tower::resetUpgrades();

    for(auto& e : enemies)
        delete e;
    enemies.clear();
    for(auto& t : towers)
        delete t;
    towers.clear();
    for(auto& t : map){
        t->setOccupied(false);
    }
    spawnList.clear();
}

void Game::timerEvent(QTimerEvent *event){
    //If the game is active then use the paintTimer to call repaint() on a loop
    if(state == INGAME){
        if(event->timerId() == spawnTimer)
            spawner();
    }
    repaint();
}

void Game::spawner(){
    //Stop the current timer
    killTimer(spawnTimer);

    //Then start spawning the new enemies
    if(!spawnList.empty()){
        //Spawn the next enemy
        enemies.push_back(spawnList.back());
        spawnTimer = startTimer(spawnList.back()->getSpawnDelay());
        spawnList.pop_back();
    }
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
    for(auto& e : enemies)
        if(!e->isDead())
            painter.drawImage(*e->getRect(), *e->getImage());

\
    //Draw the towers
    /*for(const auto t : towers)
        painter.drawImage(*t->getRect(), *t->getImage());
       */

    //Draw the tooltip
    /*if(tooltip != NULL)
        tooltip->paint(&painter);*/
}

void Game::cleanEnemyList(){
    for(size_t i = 0; i<enemies.size(); i++){
        if(enemies[i]->isDead()){
            //When deleting the enemy, award the player the appropriate points
            //updateScore(enemies[i]->getScore());
            delete enemies[i];
            enemies.erase(enemies.begin()+i);
        }
    }
}

void Game::moveEnemies(){
    for(auto& e : enemies){
        //If the enemy has reached the final waypoint then don't take any action
        if(e->getRect()->contains(navPath[CONSTANTS::PATH_TILE_COUNT - 1].toPoint())){
            //REACHED END
            state = MENU;
            break;
        }
        //If the enemy as reached its target waypoint then update its target waypoint
        if(e->getRect()->contains(navPath[e->getCurWaypoint()+1].toPoint()))
        {
            e->incrementCurWaypoint();
        }
        //Move the enemy towards its targeted waypoint
        e->move(navPath[e->getCurWaypoint()+1]);
    }
}

void Game::raycast(){
    for(auto& t : towers){
        for(auto& e : enemies){
            //Draw a line between each tower and all of the enemies
            int distance = QLineF(t->getRect()->center(), e->getRect()->center()).length();
            //If the line's distance is less than the tower's range then that enemy can be attacked
            if(distance < t->getRange(t->getType()) && !t->isCoolDown()){
                //Cool down tower
                t->setCoolDown(true);
                QTimer::singleShot(t->getCoolDown(t->getType()),t,SLOT(toggleCoolDown()));
                //damage the enemy
                e->inflictDamage(t->getDamage(t->getType()));
                //Create the damage number obejct
                Image* damage = mergeChars(std::to_string(t->getDamage(t->getType())),1,RED);
                //reposition the damage number obejct
                damage->getRect()->moveTo(e->getRect()->center().x()+damageDisplayOffset(generator), e->getRect()->top());
                damageDisplays.push_back(damage);
                //start lifetime timer for the damage number decal
                QTimer::singleShot(1000,this,SLOT(removeDecal()));

                //If the enemy's health is depleted then indicate that it is dead
                if(e->getHealth() <= 0){
                    e->setDead(true);
                    enemyCount--;
                    cleanEnemyList();
                    //End wave
                    if(enemyCount == 0)
                        state = CLEARED;
                }
                break;
            }
        }
    }
}

void Game::appendChar(Image* character, double scale, Image* i){
    Image* copy = character->scaledCopy(scale);
    i->append(copy);
}

Image* Game::mergeChars(std::string word, double scale, Chars c){
    //Create an Image to append to
    Image* image = new Image();

    for(size_t i = 0; i < word.length(); i++){
        if(c == ACTIVE){
            switch(word[i]){
            case '0':
                appendChar(letterCharsAct[0], scale, image);
                break;
            case '1':
                appendChar(letterCharsAct[1], scale, image);
                break;
            case '2':
                appendChar(letterCharsAct[2], scale, image);
                break;
            case '3':
                appendChar(letterCharsAct[3], scale, image);
                break;
            case '4':
                appendChar(letterCharsAct[4], scale, image);
                break;
            case '5':
                appendChar(letterCharsAct[5], scale, image);
                break;
            case '6':
                appendChar(letterCharsAct[6], scale, image);
                break;
            case '7':
                appendChar(letterCharsAct[7], scale, image);
                break;
            case '8':
                appendChar(letterCharsAct[8], scale, image);
                break;
            case '9':
                appendChar(letterCharsAct[9], scale, image);
                break;
            case 'a':
                appendChar(letterCharsAct[10], scale, image);
                break;
            case 'b':
                appendChar(letterCharsAct[11], scale, image);
                break;
            case 'c':
                appendChar(letterCharsAct[12], scale, image);
                break;
            case 'd':
                appendChar(letterCharsAct[13], scale, image);
                break;
            case 'e':
                appendChar(letterCharsAct[14], scale, image);
                break;
            case 'f':
                appendChar(letterCharsAct[15], scale, image);
                break;
            case 'g':
                appendChar(letterCharsAct[16], scale, image);
                break;
            case 'h':
                appendChar(letterCharsAct[17], scale, image);
                break;
            case 'i':
                appendChar(letterCharsAct[18], scale, image);
                break;
            case 'j':
                appendChar(letterCharsAct[19], scale, image);
                break;
            case 'k':
                appendChar(letterCharsAct[20], scale, image);
                break;
            case 'l':
                appendChar(letterCharsAct[21], scale, image);
                break;
            case 'm':
                appendChar(letterCharsAct[22], scale, image);
                break;
            case 'n':
                appendChar(letterCharsAct[23], scale, image);
                break;
            case 'o':
                appendChar(letterCharsAct[24], scale, image);
                break;
            case 'p':
                appendChar(letterCharsAct[25], scale, image);
                break;
            case 'q':
                appendChar(letterCharsAct[26], scale, image);
                break;
            case 'r':
                appendChar(letterCharsAct[27], scale, image);
                break;
            case 's':
                appendChar(letterCharsAct[28], scale, image);
                break;
            case 't':
                appendChar(letterCharsAct[29], scale, image);
                break;
            case 'u':
                appendChar(letterCharsAct[30], scale, image);
                break;
            case 'v':
                appendChar(letterCharsAct[31], scale, image);
                break;
            case 'w':
                appendChar(letterCharsAct[32], scale, image);
                break;
            case 'x':
                appendChar(letterCharsAct[33], scale, image);
                break;
            case 'y':
                appendChar(letterCharsAct[34], scale, image);
                break;
            case 'z':
                appendChar(letterCharsAct[35], scale, image);
                break;
            case ' ':
                appendChar(specialChars[0], scale, image);
                break;
        }
        }
        else if(c == NORMAL){
            switch(word[i]){
                case '0':
                    appendChar(letterChars[0], scale, image);
                    break;
                case '1':
                    appendChar(letterChars[1], scale, image);
                    break;
                case '2':
                    appendChar(letterChars[2], scale, image);
                    break;
                case '3':
                    appendChar(letterChars[3], scale, image);
                    break;
                case '4':
                    appendChar(letterChars[4], scale, image);
                    break;
                case '5':
                    appendChar(letterChars[5], scale, image);
                    break;
                case '6':
                    appendChar(letterChars[6], scale, image);
                    break;
                case '7':
                    appendChar(letterChars[7], scale, image);
                    break;
                case '8':
                    appendChar(letterChars[8], scale, image);
                    break;
                case '9':
                    appendChar(letterChars[9], scale, image);
                    break;
                case 'a':
                    appendChar(letterChars[10], scale, image);
                    break;
                case 'b':
                    appendChar(letterChars[11], scale, image);
                    break;
                case 'c':
                    appendChar(letterChars[12], scale, image);
                    break;
                case 'd':
                    appendChar(letterChars[13], scale, image);
                    break;
                case 'e':
                    appendChar(letterChars[14], scale, image);
                    break;
                case 'f':
                    appendChar(letterChars[15], scale, image);
                    break;
                case 'g':
                    appendChar(letterChars[16], scale, image);
                    break;
                case 'h':
                    appendChar(letterChars[17], scale, image);
                    break;
                case 'i':
                    appendChar(letterChars[18], scale, image);
                    break;
                case 'j':
                    appendChar(letterChars[19], scale, image);
                    break;
                case 'k':
                    appendChar(letterChars[20], scale, image);
                    break;
                case 'l':
                    appendChar(letterChars[21], scale, image);
                    break;
                case 'm':
                    appendChar(letterChars[22], scale, image);
                    break;
                case 'n':
                    appendChar(letterChars[23], scale, image);
                    break;
                case 'o':
                    appendChar(letterChars[24], scale, image);
                    break;
                case 'p':
                    appendChar(letterChars[25], scale, image);
                    break;
                case 'q':
                    appendChar(letterChars[26], scale, image);
                    break;
                case 'r':
                    appendChar(letterChars[27], scale, image);
                    break;
                case 's':
                    appendChar(letterChars[28], scale, image);
                    break;
                case 't':
                    appendChar(letterChars[29], scale, image);
                    break;
                case 'u':
                    appendChar(letterChars[30], scale, image);
                    break;
                case 'v':
                    appendChar(letterChars[31], scale, image);
                    break;
                case 'w':
                    appendChar(letterChars[32], scale, image);
                    break;
                case 'x':
                    appendChar(letterChars[33], scale, image);
                    break;
                case 'y':
                    appendChar(letterChars[34], scale, image);
                    break;
                case 'z':
                    appendChar(letterChars[35], scale, image);
                    break;
                case ' ':
                    appendChar(specialChars[0], scale, image);
                    break;
            }
        }
        else if(c == RED){
            switch(word[i]){
                case '0':
                    appendChar(letterCharsRed[0], scale, image);
                    break;
                case '1':
                    appendChar(letterCharsRed[1], scale, image);
                    break;
                case '2':
                    appendChar(letterCharsRed[2], scale, image);
                    break;
                case '3':
                    appendChar(letterCharsRed[3], scale, image);
                    break;
                case '4':
                    appendChar(letterCharsRed[4], scale, image);
                    break;
                case '5':
                    appendChar(letterCharsRed[5], scale, image);
                    break;
                case '6':
                    appendChar(letterCharsRed[6], scale, image);
                    break;
                case '7':
                    appendChar(letterCharsRed[7], scale, image);
                    break;
                case '8':
                    appendChar(letterCharsRed[8], scale, image);
                    break;
                case '9':
                    appendChar(letterCharsRed[9], scale, image);
                    break;
            }
        }
    }

    return image;
}

void Game::mouseMoveEvent(QMouseEvent *event){
    switch(state){
        case MENU:
            //If hovering over start change start's image and make sure the others are passive
            if(start_button->getRect()->contains(event->pos())){
                start_button->setActive(true);
                help_button->setActive(false);
                quit_button->setActive(false);
            }
            //If hovering over help change help's image and make sure the others are passive
            else if(help_button->getRect()->contains(event->pos())){
                help_button->setActive(true);
                start_button->setActive(false);
                quit_button->setActive(false);
            }
            //If hovering over quit change quit's image and make sure the others are passive
            else if(quit_button->getRect()->contains(event->pos())){
                quit_button->setActive(true);
                start_button->setActive(false);
                help_button->setActive(false);
            }
            //Otherwise make sure that all the buttons are displaying passive images
            else{
                start_button->setActive(false);
                help_button->setActive(false);
                quit_button->setActive(false);
            }
            break;
        case PAUSED:
            //If hovering over resume change resume's image and make sure main menu is passive
            if(pauseButtons[0]->getRect()->contains(event->pos())){
                pauseButtons[0]->setActive(true);
                pauseButtons[1]->setActive(false);
            }
            //If hovering over main menu change main menu's image and make sure resume is passive
            else if(pauseButtons[1]->getRect()->contains(event->pos())){
                pauseButtons[0]->setActive(false);
                pauseButtons[1]->setActive(true);
            }
            //Otherwise set resume and main menu to the passive image
            else{
                pauseButtons[0]->setActive(false);
                pauseButtons[1]->setActive(false);
            }
            break;
        case HELP:
            //If hovering over left arrow change left arrow's image and make sure the others are passive
            if(arrows[0]->getRect()->contains(event->pos())){
                arrows[0]->setActive(true);
                arrows[1]->setActive(false);
                arrows[2]->setActive(false);
            }
            //If hovering over right arrow change right arrow's image and make sure the others are passive
            else if(arrows[1]->getRect()->contains(event->pos())){
                arrows[0]->setActive(false);
                arrows[1]->setActive(true);
                arrows[2]->setActive(false);
            }
            //If hovering over back change back's image and make sure the others are passive
            else if(arrows[2]->getRect()->contains(event->pos())){
                arrows[0]->setActive(false);
                arrows[1]->setActive(false);
                arrows[2]->setActive(true);
            }
            //Otherwise set all three to passive
            else{
                arrows[0]->setActive(false);
                arrows[1]->setActive(false);
                arrows[2]->setActive(false);
            }
            break;
        case CLEARED:
            //If hovering over continue's image make it active
            if(continue_button->getRect()->contains(event->pos()))
                continue_button->setActive(true);
            //Otherwise make it passive
            else
                continue_button->setActive(false);
            break;
        case INGAME:
            //Start by clearing the tooltip
            delete tooltip;
            tooltip = NULL;

            //Then draw the correct tooltip based on the event->pos()

            //TowerOption # 1
            if(towerOptions[0]->getRect()->contains(event->pos())){
                tooltip = new ToolTip(mergeChars("cost", 1, NORMAL),
                                      mergeChars(std::to_string(Tower::getCost(FIRE)), 1, ACTIVE));
                tooltip->moveTo(event->pos());
            }

            //TowerOption # 2
            else if(towerOptions[1]->getRect()->contains(event->pos())){
                tooltip = new ToolTip(mergeChars("cost", 1, NORMAL),
                                      mergeChars(std::to_string(Tower::getCost(ICE)), 1, ACTIVE));
                tooltip->moveTo(event->pos());
            }

            //TowerOption # 3
            else if(towerOptions[2]->getRect()->contains(event->pos())){
                tooltip = new ToolTip(mergeChars("cost", 1, NORMAL),
                                      mergeChars(std::to_string(Tower::getCost(EARTH)), 1, ACTIVE));
                tooltip->moveTo(event->pos());
            }

            //Upgrade #1
            if(upgrade_icon[0]->getRect()->contains(event->pos())){
                tooltip = new ToolTip(mergeChars("cost", 1, NORMAL),
                                      mergeChars(std::to_string(Tower::getDamageCost(curTowerType)), 1, ACTIVE),
                                      mergeChars("str", 1, NORMAL),
                                      mergeChars(std::to_string(Tower::getDamage(curTowerType)), 1, ACTIVE));
                tooltip->moveTo(event->pos());
            }
            //Upgrade #2
            else if(upgrade_icon[1]->getRect()->contains(event->pos())){
                tooltip = new ToolTip(mergeChars("cost", 1, NORMAL),
                                      mergeChars(std::to_string(Tower::getRangeCost(curTowerType)), 1, ACTIVE),
                                      mergeChars("range", 1, NORMAL),
                                      mergeChars(std::to_string(Tower::getRange(curTowerType)), 1, ACTIVE));
                tooltip->moveTo(event->pos());
            }
            //Upgrade #3
            else if(upgrade_icon[2]->getRect()->contains(event->pos())){
               tooltip = new ToolTip(mergeChars("cost", 1, NORMAL),
                                      mergeChars(std::to_string(Tower::getCoolDownCost(curTowerType)), 1, ACTIVE),
                                      mergeChars("rate", 1, NORMAL),
                                      mergeChars(std::to_string(Tower::getCoolDown(curTowerType)), 1, ACTIVE));
                tooltip->moveTo(event->pos());
            }
            break;
    }
    repaint();
}


/*
    mousePressEvent
    @brief This function handles all mouse clicks on Button objects.
    It checks the position of the click agains the Buttons' QRects.
*/
void Game::mousePressEvent(QMouseEvent *event){
    switch(state){
        case MENU:
            //Pressing the start button will start the game
            if(start_button->getRect()->contains(event->pos())){
                //Start game
                state = INGAME;
                //set up a new game
                newGame();
            }
            //Pressing the help button will activate the Help state
            else if(help_button->getRect()->contains(event->pos())){
                //Open Help Window
                state = HELP;
            }
            //Pressing the quit button will end the application
            else if(quit_button->getRect()->contains(event->pos())){
                qApp->quit();
            }
            break;
        case PAUSED:
            //Pressing resume will continue the current game
            if(pauseButtons[0]->getRect()->contains(event->pos())){
                //Resume game
                state = INGAME;
                startTimers();

            }
            //Pressing Main Menu will return the user to the main menu
            else if(pauseButtons[1]->getRect()->contains(event->pos())){
                //Return to main menu
                killTimer(paintTimer);
                state = MENU;
            }
            break;
        case HELP:
            //Pressing the left arrow will update the helpIndex so that it shows the image on the left
            if(arrows[0]->getRect()->contains(event->pos())){
                if(helpIndex == 0)
                    helpIndex = helpImages.size()-1;
                else
                    helpIndex--;
            }
            //Pressing the right arrow will update the helpIndex so that it shows the image on the right
            else if(arrows[1]->getRect()->contains(event->pos())){
                if(helpIndex == helpImages.size()-1)
                    helpIndex = 0;
                else
                    helpIndex++;
            }
            //Pressing back will return the user to the main menu
            else if(arrows[2]->getRect()->contains(event->pos())){
                //Reset the helpIndex so that it will reopen at the first image
                helpIndex = 0;
                //Return to main menu
                state = MENU;
            }
            repaint();
            break;
    case INGAME:
        //Check if the event occurred on a non-path tile that is empty. If so then highlight that tile
        for(auto& t : map)
            (!t->isPath() && !t->isOccupied() && t->getRect()->contains(event->pos())) ? selectTile(t) : t->setActive(false);

        //Check if the click event occured on one of the tower builder options and if so update the selected tower type
        for(size_t i=0; i<towerOptions.size(); i++){
            if(towerOptions[i]->getRect()->contains(event->pos())){
                curTowerOpt = i;
                //Also update the tower type variable
                switch(curTowerOpt){
                    case 0:
                        curTowerType = FIRE;
                        break;
                    case 1:
                        curTowerType = ICE;
                        break;
                    case 2:
                        curTowerType = EARTH;
                        break;
                }
            }
        }

        //Update the correspond tooltip and tower stat based on click event pos

        //Upgrade #1
        if(getScore() > Tower::getDamageCost(curTowerType) && upgrade_icon[0]->getRect()->contains(event->pos())){
            updateScore(-Tower::getDamageCost(curTowerType));
            Tower::upgradeDamage(curTowerType);
            tooltip = new ToolTip(mergeChars("cost", 1, NORMAL),
                                  mergeChars(std::to_string(Tower::getDamageCost(curTowerType)), 1, ACTIVE),
                                  mergeChars("str", 1, NORMAL),
                                  mergeChars(std::to_string(Tower::getDamage(curTowerType)), 1, ACTIVE));
            tooltip->moveTo(event->pos());
        }
        //Upgrade #2
        else if(getScore() > Tower::getRangeCost(curTowerType) && upgrade_icon[1]->getRect()->contains(event->pos())){
            updateScore(-Tower::getRangeCost(curTowerType));
            Tower::upgradeRange(curTowerType);
            tooltip = new ToolTip(mergeChars("cost", 1, NORMAL),
                                  mergeChars(std::to_string(Tower::getRangeCost(curTowerType)), 1, ACTIVE),
                                  mergeChars("range", 1, NORMAL),
                                  mergeChars(std::to_string(Tower::getRange(curTowerType)), 1, ACTIVE));
            tooltip->moveTo(event->pos());
        }
        //Upgrade #3
        else if(getScore() > Tower::getCoolDownCost(curTowerType) && upgrade_icon[2]->getRect()->contains(event->pos())){
            updateScore(-Tower::getCoolDownCost(curTowerType));
            Tower::upgradeCoolDown(curTowerType);
            tooltip = new ToolTip(mergeChars("cost", 1, NORMAL),
                                  mergeChars(std::to_string(Tower::getCoolDownCost(curTowerType)), 1, ACTIVE),
                                  mergeChars("rate", 1, NORMAL),
                                  mergeChars(std::to_string(Tower::getCoolDown(curTowerType)), 1, ACTIVE));
            tooltip->moveTo(event->pos());
        }

        break;
    case CLEARED:
        //Pressing continue will start the next wave
        if(continue_button->getRect()->contains(event->pos())){
            newWave(); //start next wave
            state = INGAME;
        }
        break;
    }
}
Game::ToolTip::ToolTip(Image* s, Image* s_u, Image* c, Image* c_a) : upgrade(true)
{
    cost = c;
    cost_amount = c_a;
    stat = s;
    stat_upgrade = s_u;
    background = new Image(TOOLTIP::BASE);
}


Game::ToolTip::ToolTip(Image* c, Image* c_a) : upgrade(false)
{
    stat = c;
    stat_upgrade = c_a;
    background = new Image(TOOLTIP::BASE);
}

Game::ToolTip::~ToolTip(){
    delete background;
    delete stat;
    delete stat_upgrade;
    if(upgrade){
        delete cost;
        delete cost_amount;
    }
}


void Game::ToolTip::moveTo(QPointF position){
    int x = position.x();
    int y = position.y();
    resizeBackground();
    background->getRect()->moveTo(x-background->getRect()->width(), y);
    stat->getRect()->moveTo(background->getRect()->x()+2, background->getRect()->y()+2);
    stat_upgrade->getRect()->moveTo(stat->getRect()->right()+3, stat->getRect()->y());
    if(upgrade){
        cost->getRect()->moveTo(stat_upgrade->getRect()->right()+5, stat_upgrade->getRect()->y());
        cost_amount->getRect()->moveTo(cost->getRect()->right()+3, cost->getRect()->y());
    }
}


void Game::ToolTip::paint(QPainter *p){
    p->drawImage(*background->getRect(), *background->getImage());
    p->drawImage(*stat->getRect(), *stat->getImage());
    p->drawImage(*stat_upgrade->getRect(), *stat_upgrade->getImage());
    if(upgrade){
        p->drawImage(*cost->getRect(), *cost->getImage());
        p->drawImage(*cost_amount->getRect(), *cost_amount->getImage());
    }
}

void Game::ToolTip::resizeBackground(){
    int width = 2 + stat->getRect()->width() + 3 + stat_upgrade->getRect()->width();
    upgrade ? width += 5 + cost->getRect()->width() + 3 + cost_amount->getRect()->width() : width += 0;
    int height = stat->getRect()->height() + 4;
    background->setImage(background->getImage()->scaled(width, height, Qt::IgnoreAspectRatio));
    background->setRect(background->getImage()->rect());
}
void Game::selectTile(Tile* t){
    //If the tile isn't already selected then select it by highlighting it
    if(!t->isActive()){
        t->setActive(true);
        tileHighlight->getRect()->moveTo(t->getRect()->topLeft());
    }
    //Otherwise if it is already selected build the selected tower type on the tile
    else{
        t->setActive(false);
        switch(curTowerOpt){
            case 0:
                if(getScore() >= Tower::getCost(curTowerType)){
                    updateScore(-Tower::getCost(curTowerType));
                    towers.push_back(new Tower(CONSTANTS::TOWER_FIRE, *t->getRect()));
                    t->setOccupied(true);
                }
                break;
            case 1:
                if(getScore() >= Tower::getCost(curTowerType)){
                    updateScore(-Tower::getCost(curTowerType));
                    towers.push_back(new Tower(CONSTANTS::TOWER_ICE, *t->getRect()));
                    t->setOccupied(true);
                }
                break;
            case 2:
                if(getScore() >= Tower::getCost(curTowerType)){
                    updateScore(-Tower::getCost(curTowerType));
                    towers.push_back(new Tower(CONSTANTS::TOWER_EARTH, *t->getRect()));
                    t->setOccupied(true);
                }
                break;
        }
    }
}
