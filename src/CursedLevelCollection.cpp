#include "Level.hh"
#include <tuple>

Level getLevelOne() {
    return {
        std::make_tuple(3, FIN, 0, 0)
    };
}

Level getLevelTwo() {
    return {
        std::make_tuple(6, FIN, 0, 0), 
        std::make_tuple(15, JUMP, 12, 0)
    };
}

Level getLevelThree() {
    return {
        std::make_tuple(15, FIN, 0, 0), 
        std::make_tuple(14, JUMP, 12, 0)
    };
}

std::vector<Level> cursedLevelCreator() {
    std::vector<Level> levelList;
    levelList.push_back(getLevelOne());
    levelList.push_back(getLevelTwo());
    levelList.push_back(getLevelThree());
    return levelList;
}