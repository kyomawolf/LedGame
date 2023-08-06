#pragma once

#include <vector>

enum instruction { JUMP, FIN, RESET };

bool    action(int position, instruction action, int target, int playerColor);
void    resetLeds();

/* tuple for one action:
    first int: position of instruction
    second instruction: what is going to happen
    third int: where to 
    fourth int: who can trigger this instruction
*/
typedef std::vector< std::tuple<int, instruction, int, int> >  Level;
std::vector<Level> cursedLevelCreator();

class LevelManager {
public:
    LevelManager();
    void    callToAction();
    Level   getLevel();
    void    finished(bool playedThrough);
    int     getCurrentPlayer();
    void    setPlayer(int id);
private:
    int currentLevel;
    int maxLevel;
    std::vector<Level> levelList;
    int currentPlayer;
};