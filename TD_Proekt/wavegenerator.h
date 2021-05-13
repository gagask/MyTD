#ifndef WAVEGENERATOR_H
#define WAVEGENERATOR_H

#include<vector>
#include "enemy.h"
#include<chrono>
#include<random>

#define DEFAULT std::default_random_engine
#define SEED (unsigned int)std::chrono::system_clock::now().time_since_epoch().count()


class WaveGenerator
{
public:
    WaveGenerator() : generator(SEED) {}

    std::vector<Enemy*> generateSpawnList(int wave, QPointF spawnLocation);
private:
    DEFAULT generator;
    std::vector<Enemy*> spawnList;

    void clearSpawnList();
};

#endif // WAVEGENERATOR_H
