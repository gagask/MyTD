#include "wavegenerator.h"
#include <random>
#include <chrono>
#include <cmath>

void WaveGenerator::clearSpawnList(){
    spawnList.clear();
}

std::vector<Enemy*> WaveGenerator::generateSpawnList(int wave, QPointF spawnLocation){
    clearSpawnList();

    int spawnTokens = std::ceil(wave * 0.2) * 10;

    std::uniform_int_distribution<int> unif(0,2);

    do{
        int token = unif(generator);
        switch( token ){
            case 0:
                if(spawnTokens >= 1){
                    spawnList.push_back(new Enemy(Enemy_Type::NORMAL, spawnLocation));
                    spawnTokens -= 1;
                }
                break;
            case 1:
                if(spawnTokens >= 3){
                    spawnList.push_back(new Enemy(Enemy_Type::BADASS, spawnLocation));
                    spawnTokens -= 3;
                }
                break;
            case 2:
                if(spawnTokens >= 3){
                    spawnList.push_back(new Enemy(Enemy_Type::BAT, spawnLocation));
                    spawnTokens -= 3;
                }
                break;
        }
    }while(spawnTokens > 0);
    return spawnList;
}
