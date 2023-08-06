#pragma once

#include <vector>

enum instruction { JUMP, FIN, RESET };

void    action(int position, instruction action, int target);
void    resetLeds();

typedef std::vector< std::tuple<int, instruction, int> >  Level;

class LevelManager {
public:
    LevelManager();
    void    callToAction();
    Level   getLevel();
    void    finished(bool playedThrough);
private:
    int currentLevel;
    int maxLevel;
    std::vector<Level> levelList;
};