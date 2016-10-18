#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include "common.h"
#include "board.h"
using namespace std;

class Player {

public:
    Player(Side side);
    ~Player();
    
    Move *doMove(Move *opponentsMove, int msLeft);
    Move *randomChoice();
    Move *heuristic();
    Move *minimax();

    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;
	Board gameBoard;


private:
	Side ourSide;
	Side other;

};

#endif
