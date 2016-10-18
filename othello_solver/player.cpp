#include "player.h"
#include <stdio.h>


/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish 
 * within 30 seconds.
 *
 * 
 */
Player::Player(Side side) {
    // Will be set to true in test_minimax.cpp.
    testingMinimax = false; 
    ourSide = side;
    other = (side == BLACK) ? WHITE : BLACK;

    gameBoard = Board();
}

/*
 * Destructor for the player.
 */
Player::~Player() {
}

/*
 * Compute the next move given the opponent's last move. Your AI is
 * expected to keep track of the board on its own. If this is the first move,
 * or if the opponent passed on the last move, then opponentsMove will be NULL.
 *
 * msLeft represents the time your AI has left for the total game, in
 * milliseconds. doMove() must take no longer than msLeft, or your AI will
 * be disqualified! An msLeft value of -1 indicates no time limit.
 *
 * The move returned must be legal; if there are no valid moves for your side,
 * return NULL.
 */

Move *Player::doMove(Move *opponentsMove, int msLeft) {

  	if(opponentsMove!=NULL)
  	{
  		gameBoard.doMove(opponentsMove, other);
  	}

	Move *move;

	if(testingMinimax)
		move = minimax();
	else
		//move = randomChoice();
		move = heuristic();

	if(move != NULL)
	{
		gameBoard.doMove(move, ourSide);
	}

    return move; 
}

/*
 * Compute the next move randomly by choosing the first valid move.
 *
 * The move returned must be legal; if there are no valid moves for your side,
 * return NULL.
 */

Move *Player::randomChoice() {

	if(gameBoard.hasMoves(ourSide))
	{
		for(int i = 0; i < 8; i ++)
		{
			for(int j = 0; j < 8; j ++)
			{
				Move *move = new Move(i, j);
				if(gameBoard.checkMove(move, ourSide) == true)
				{
					gameBoard.doMove(move, ourSide);
					return move;
				}
			}
		}
	}

	return NULL;
}

/* 
 * Compute the next move by heuristically choosing next move.
 * This will compute the scores for each move (with particular
 * weightage) and choose the move that causes the best score.
 *
 * The move returned must be legal; if there are no valid moves for your side,
 * return NULL;
 */

Move *Player::heuristic() { 

    if(gameBoard.hasMoves(ourSide))
    {
    	int score = -1000;
    	int x = 0;
    	int y = 0;

    	for(int i = 0; i < 8; i ++)
    	{
    		for(int j = 0; j < 8; j ++)
    		{
    			Move *tempMove = new Move(i, j);

    			if (gameBoard.checkMove(tempMove, ourSide))
    			{
    				Board *copyBoard = gameBoard.copy();
    				copyBoard->doMove(tempMove, ourSide);
    				int tempScore = copyBoard->count(ourSide) - copyBoard->count(other);


					if(i == 0 || i == 7){
						if(j == 0 || j == 7)
							tempScore += 120; 
						else if(j == 1 || j == 6)
							tempScore += -30; 
						else if(j == 2 || j == 5)
							tempScore += 20;
						else if(j == 3 || j == 4)
							tempScore += 5;
					}
					else if(i == 1 || i == 6){
						if(j == 0 || j == 7)
							tempScore += -30;
						else if(j == 1 || j == 6)
							tempScore += -40; 
						else if(j == 2 || j == 3 || j == 4 || j == 5)
							tempScore += -5;
					}
					else if(i == 2 || i == 5){
						if(j == 0 || j == 7)
							tempScore += 20;
						else if(j == 1 || j == 6)
							tempScore += -5;
						else if(j == 2 || j == 5)
							tempScore += 15; 
						else if(j == 3 || j == 4)
							tempScore += 3; 
					}
					else if(i == 3 || i == 4){
						if(j == 0 || j == 7)
							tempScore += 5;
						else if(j == 1 || j == 6)
							tempScore += -5;
						else if(j == 2 || j == 3 || j == 4 || j == 5)
							tempScore += 3;
					}

    				fprintf(stderr, "Considering move (%d, %d): Score is %d\n", x, y, tempScore);

    				if(tempScore > score)
    				{
    					score = tempScore;
    					x = i;
    					y = j;
    				}

    				delete copyBoard;
    			}
    			delete tempMove;
    		}
    	}
    	Move *nextMove = new Move(x, y);
    	gameBoard.doMove(nextMove, ourSide);
    	fprintf(stderr, "Chosen move (%d, %d)\n", x, y);
    	return nextMove;
    }
    return NULL;
}
    
/* 
 * Computes the next move using the minimax method. It will iterate through
 * the list of next possible moves and then iterate through the opponents
 * possible moves given each one of our sides possible moves. It will then find
 * the maximum of the minimum scores in order to figure out which move is the best.
 *
 * The move returned must be legal; if there are no valid moves for your side,
 * return NULL;
 */

Move *Player::minimax() {

	if(gameBoard.hasMoves(ourSide))
	{	 
		int maxScore = -1000;
		Move *nextMove = new Move(0,0);
		vector<Move*> ourMoves = gameBoard.listMoves(ourSide);
		vector<Move*>::iterator i;

		for(i = ourMoves.begin(); i < ourMoves.end(); i++)
		{
			int index1 = distance(ourMoves.begin(), i);
			Board *copyBoard1 = gameBoard.copy();
			copyBoard1->doMove(ourMoves[index1], ourSide);
			vector<Move*> oppMoves = copyBoard1->listMoves(other);
			int minOppScore = 1000;

			vector<Move*>::iterator j;

			for(j = oppMoves.begin(); j < oppMoves.end(); j++)
			{
				int index2 = distance(oppMoves.begin(), j);
				Board *copyBoard2 = copyBoard1->copy();
				copyBoard2->doMove(oppMoves[index2], other);
				int tempScore = (copyBoard2->countWhite() - copyBoard2->countBlack()) * (ourSide == BLACK ? -1 : 1);

				if(tempScore < minOppScore)
				{
					minOppScore = tempScore;
				}
			}

			if(minOppScore > maxScore)
			{
				maxScore = minOppScore;
				nextMove = ourMoves[index1];
			}
		}

		return nextMove;
	}
	return NULL;
}


