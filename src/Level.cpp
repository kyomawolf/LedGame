#include "Level.hh"
#include <iostream>
#include <tuple>

extern int playerPosition;
extern bool playerOneMoved;
extern bool playerTwoMoved;
extern bool playerThreeMoved;

Level getLevelOne() {
    return {
        std::make_tuple(3, FIN, 0), 
        std::make_tuple(15, JUMP, 12)
    };
}

Level getLevelTwo() {
    return {
        std::make_tuple(6, FIN, 0), 
        std::make_tuple(15, JUMP, 12)
    };
}


Level getLevelThree() {
    return {
        std::make_tuple(9, FIN, 0), 
        std::make_tuple(15, JUMP, 12)
    };
}

LevelManager::LevelManager() : currentLevel(0) {
    levelList.push_back(getLevelOne());
    levelList.push_back(getLevelTwo());
    maxLevel = levelList.size();
}

void    LevelManager::finished(bool playedThrough) {
    //show score green or red (true | false)
}

void    LevelManager::callToAction() {
    for (auto & idx : levelList[currentLevel]) {
        if (std::get<0>(idx) == playerPosition) {
            action(std::get<0>(idx), std::get<1>(idx), std::get<2>(idx));
            if (std::get<1>(idx) == FIN) {
                currentLevel++;
                std::cout << "finished! Next Level: " << currentLevel << std::endl;
                playerOneMoved = false;
                playerTwoMoved = false;
                playerThreeMoved = false;
                break; //todo consider removing this; if the player can land on finished and be teleported away afterward... well see
            }
        }
    }
    if (currentLevel == maxLevel) {
        finished(true);
        currentLevel = 0;
        resetLeds();
    }
    else if (playerOneMoved && playerTwoMoved && playerThreeMoved) {
        finished(false);
        currentLevel = 0;
        resetLeds();
    }
}

Level LevelManager::getLevel() {
    return levelList[currentLevel];
}