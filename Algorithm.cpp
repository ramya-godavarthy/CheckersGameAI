
#include <stdio.h>
#include "CheckerBoard.h"
#include "Algorithm.h"
//****** Functions for the Algorithms ******//

/*
Alpha-Beta-Search
Implemented From Text Book Chater 5 Adversarial searches
*/
/*---- Function:terminal()-----*
Purpose: If there are no moves then returns true else false
Return Type: bool */

bool Element::terminal() const
{

    if (childs.empty())
        return true;
    
    if(move >= depth)
        return true;
    
        return false;
}

void alpha_beta_search(Element state, char array2D[][8])
{
    state.v = max_value(state, -1000, 1000);
    for (int i = 0; i < state.childs.size(); i++)
    {
        if (state.childs[i].v == state.v)
        {
            for (int h = 0; h < 8; h++)
            {
                for (int w = 0; w < 8; w++)
                {
                    array2D[h][w] = state.childs[i].CheckerBoard[h][w];
                }
            }
            return;
        }
    }
}

int max_value(Element& state, int alpha, int beta)
{
    state.moves();
    if (state.terminal())
    {
        state.v = state.evaluate();
        return state.evaluate();
    }
    state.v = -100;
    for (int i = 0; i < state.childs.size(); i++)
    {
        state.v = max(state.v, min_value(state.childs[i], alpha, beta));
        if (state.v >= beta)
        {
            return state.v;
        }
        alpha = max(alpha, state.v);
    }
    return state.v;
}

int min_value(Element& state, int alpha, int beta)
{
    state.moves();
    if (state.terminal())
    {
        state.v = state.evaluate();
        return state.evaluate();
    }
    state.v = 50;
    for (int i = 0; i < state.childs.size(); i++)
    {
        state.v = min(state.v, max_value(state.childs[i], alpha, beta));
        if (state.v <= alpha)
        {
            return state.v;
        }
        beta = min(beta, state.v);
    }
    return state.v;
}


/*

MinMax AB Algorithm
Implemented from Rich and Knight Chapther 12

*/

bool DeepEnough(int d)
{
    if (depth == 2)
        return d >= 2;
    else
    return d >= 4;
}

//*************************************************************************
//minimaxAB: function for the implementation of rich and knight algorithm
//             gets the board position, current depth, player name, usethresh
//          passthresh as parameters and returns the bestvalue and the bestpath
//          for next move
//p:    current node being examined
//depth: level at which the node is examined
//player: name of the player at this level
//usethresh: lower bound value that a player may be assigned
//passthresh: upperbound value that a opponent may be assigned
//*************************************************************************
Element MinMaxAB(Element &e, int depth,char player,int useThresh,int passThresh)
{
    //vector<Element>path;
    int newValue = 0;

    //checks if the depth has been reached
    if(DeepEnough(depth)){

        e.moves();
        e.v = e.evaluate();
        if (opt == 1)
            if (e.player == PLAYER2)
                e.v *= -1;
        if (opt == 2)
            if (e.player == PLAYER1)
                e.v *= -1;
        return e;
    }

    e.moves();
    vector<Element> successors = e.childs;

    //checks if there is any move for the board position
    if (successors.empty()) {

        e.evaluate();
        if (opt == 1)
        {
            //PLAYER1 is Max
            //PLAYER2 is Min
            if (e.player == PLAYER2)
                e.v *= -1;
        }
        if (opt == 2)
        {
            //PLAYER2 is Max
            //PLAYER1 is Min
            if (e.player == PLAYER1)
                e.v *= -1;
        }

        return e;
    }

    //loop through sucessors
    for(auto & successor : successors){
        Element succ = successor;

        Element resultSucc;

        resultSucc = MinMaxAB(succ,succ.move,succ.player,-1*passThresh,-1*useThresh);
        newValue = -1*(resultSucc.v);

        //if newvalue is greater than cut off no further children will be explored
        if(newValue > passThresh){

            passThresh = newValue;
            if (depth  == 0)
                bestPath.push_back(succ);
        }
        //condition to cut off search
        if(passThresh >= useThresh){
            succ.v = passThresh;
            e = successor;
            return e;
        }

    }
    e.v = passThresh;
    return e;
}

//****** Functions for the Algorithms ******//
