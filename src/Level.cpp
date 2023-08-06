#include "Level.hh"
#include <iostream>
#include <tuple>

extern int playerPosition;
extern bool playerOneMoved;
extern bool playerTwoMoved;
extern bool playerThreeMoved;


LevelManager::LevelManager() : currentLevel(0) {
    levelList = cursedLevelCreator();
    maxLevel = levelList.size();
}

void    LevelManager::finished(bool playedThrough) {
    //show score green or red (true | false)
    playerOneMoved = false;
    playerTwoMoved = false;
    playerThreeMoved = false;
}

void    LevelManager::callToAction() {
    for (auto & idx : levelList[currentLevel]) {
        if (std::get<0>(idx) == playerPosition) {
            bool ret = action(std::get<0>(idx), std::get<1>(idx), std::get<2>(idx), std::get<3>(idx));
            if (ret && std::get<1>(idx) == FIN) {
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

int LevelManager::getCurrentPlayer() {
  return currentPlayer;
}

void    LevelManager::setPlayer(int id) {
    currentPlayer = id;
}