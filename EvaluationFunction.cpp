#include <stdio.h>
#include <iostream>
#include "CheckerBoard.h"
//#include "Enum.h"

using namespace std;

//****** Functions for the EVALUATION FUNCTION ******//
/*---- Function:Evaluate()-----*
Purpose: Evaluates the options and returns the number for that particular player
Return Type: int - returns the value for that particular player. */


int Element::evaluate()
{
    if (opt == 1)
    {
        if (childs.empty())
        {
            if (player == PLAYER1)
                return -100;
            else
                return 100;
        }
    }
    else if (opt == 2)
    {
        if (childs.empty())
        {
            if (player == PLAYER1)
                return 100;
            else
                return -100;
        }
    }
    return EvalValue();
}

/*---- Function:EvalValue()-----*
Purpose: 3 Evaluation Functions are defined here. These are designed upon considering giving weightage to player's kings more than the pawns and also considered their defending neighbours.
Return Type: int - returns the value for that particular piece. */


int Element::EvalValue()
{
    int player1Count = 0, player2Count = 0;
    // EVALUATION FUNCTION 1
    // (Piece Difference) + 2*(KingPiece Difference) + 3*(Each Forward Move Difference + Each King Backward Move Difference) + 4*(Each Capture Difference + Each Capture in Backward By King)
    if ((opt == 1 && evalp1 == 1) || (opt == 2 && evalp2 == 1))
    {
        for(int i=0;i<8;i++)
        {
            for(int j=0;j<8;j++)
            {
                // Piece Count
                if(CheckerBoard[i][j] == PLAYER1)
                    player1Count++;
                else if(CheckerBoard[i][j] == PLAYER2)
                    player2Count++;
                //King Piece Count
                if(CheckerBoard[i][j] == PLAYER1_KING)
                    player1Count += 2;
                else if (CheckerBoard[i][j] == PLAYER2_KING)
                    player2Count += 2;

                //Possible Moves towards Opponents Direction for Player 1
                if(CheckerBoard[i][j] == PLAYER1 || CheckerBoard[i][j] == PLAYER1_KING)
                {
                    if((CheckerBoard[i+1][j-1] == EMPTY_SPACE //checks right diagonal
                       || CheckerBoard[i+1][j+1] == EMPTY_SPACE) // checks left diagonal
                       && i+1 < 8 && j-1 > -1 && j+1 < 8)
                        player1Count += 3;

                    // Possible Capture towards Opponents Direction
                    if((CheckerBoard[i+1][j-1] == PLAYER2 ||
                        CheckerBoard[i+1][j-1] == PLAYER2_KING) &&
                       CheckerBoard[i+2][j-2] == EMPTY_SPACE &&
                       i+2 < 8 && i+1 < 8 && j-1 > -1 && j-2 > -1)
                        player1Count += 4;
                    if((CheckerBoard[i+1][j+1]==PLAYER2 ||
                        CheckerBoard[i+1][j+1] == PLAYER2_KING) &&
                        CheckerBoard[i+2][j+2] == EMPTY_SPACE &&
                       i+2 < 8 && i+1 < 8 && j+1 < 8 && j+2 < 8)
                        player1Count += 4;
                }

                // Moves in backward direction by king
                if(CheckerBoard[i][j] == PLAYER1_KING)
                {
                    if((CheckerBoard[i-1][j-1] == EMPTY_SPACE //checks right diagonal
                       || CheckerBoard[i-1][j+1] == EMPTY_SPACE) // checks left diagonal
                       && i-1 > -1 && j-1 > -1 && j+1 < 8)
                        player1Count += 3;

                    // Capture in backward direction by king
                    if((CheckerBoard[i-1][j-1] == PLAYER2 ||
                        CheckerBoard[i-1][j-1] == PLAYER2_KING) &&
                       CheckerBoard[i-2][j-2] == EMPTY_SPACE &&
                       i-2 > -1 && i-1 > -1 && j-1 > -1 && j-2 > -1)
                        player1Count += 4;
                    if((CheckerBoard[i-1][j+1] == PLAYER2 ||
                        CheckerBoard[i-1][j+1] == PLAYER2_KING) &&
                        CheckerBoard[i-2][j+2] == EMPTY_SPACE &&
                       i-2 > -1 && i-1 > -1 && j+1 < 8 && j+2 < 8)
                        player1Count += 4;
                }

                //Possible Moves towards Opponents Direction for Player 2
                if(CheckerBoard[i][j] == PLAYER2 || CheckerBoard[i][j] == PLAYER2_KING)
                {
                    if((CheckerBoard[i-1][j-1] == EMPTY_SPACE //checks right diagonal
                       || CheckerBoard[i-1][j+1] == EMPTY_SPACE) // checks left diagonal
                       && i-1 > -1 && j-1 > -1 && j+1 < 8)
                        player2Count += 3;
                    // Possible Capture towards Opponents Direction
                    if((CheckerBoard[i-1][j-1] == PLAYER1 ||
                        CheckerBoard[i-1][j-1] == PLAYER1_KING) &&
                       CheckerBoard[i-2][j-2] == EMPTY_SPACE &&
                       i-2 > -1 && i-1 < -1 && j-1 > -1 && j-2 > -1)
                        player2Count += 4;
                    if((CheckerBoard[i-1][j+1] == PLAYER1 ||
                        CheckerBoard[i-1][j+1] == PLAYER1_KING) &&
                        CheckerBoard[i-2][j+2] == EMPTY_SPACE &&
                       i-2 > -1 && i-1 < -1 && j+1 < 8 && j+2 < 8)
                        player2Count += 4;
                }
                // Moves in backward direction by king
                if(CheckerBoard[i][j] == PLAYER2_KING)
                {
                    if((CheckerBoard[i+1][j-1] == EMPTY_SPACE //checks right diagonal
                       || CheckerBoard[i+1][j+1] == EMPTY_SPACE) // checks left diagonal
                       && i+1 < 8 && j-1 > -1 && j+1 < 8)
                        player2Count += 3;

                        // Capture in backward direction by king
                    if((CheckerBoard[i+1][j-1] == PLAYER1 ||
                        CheckerBoard[i+1][j-1] == PLAYER1_KING) &&
                       CheckerBoard[i+2][j-2] == EMPTY_SPACE &&
                       i+2 < 8 && i+1 < 8 && j-1 > -1 && j-2 > -1)
                        player2Count += 4;
                    if((CheckerBoard[i+1][j+1]==PLAYER1 ||
                        CheckerBoard[i+1][j+1] == PLAYER1_KING) &&
                        CheckerBoard[i+2][j+2] == EMPTY_SPACE &&
                       i+2 < 8 && i+1 < 8 && j+1 < 8 && j+2 < 8)
                        player2Count += 4;
                }
            }
        }
    }

    //Player 1 is positive and Player 2 is negative, taking count of all pieces with more weightage towards kings and adding it with player count difference , how close player is to become king and some randomness
    // EVALUATION FUNCTION 2
    else if ((opt == 1 && evalp1 == 2) || (opt == 2 && evalp2 == 2))
    {
        int a1 = 0, a2 = 0, b = 0, c = 0;
        for (int i = 0; i < 8; i++)
            for (int j = 0; j < 8; j++)
            {
                if (CheckerBoard[i][j] == PLAYER1)
                {
                    a1 += 2;
                    if (i == 0)
                        b += 9;
                    else b += i;
                    c += 1;
                }
                else if (CheckerBoard[i][j] == PLAYER2)
                {
                    a2 -= 2;
                    if (i == 7)
                        b -= 9;
                    else b -= (7 - i);
                    c -= 1;
                }
                else if (CheckerBoard[i][j] == PLAYER1_KING)
                {
                    a1 += 3;
                    c += 1;
                }
                else if (CheckerBoard[i][j] == PLAYER2_KING)
                {
                    a2 -= 3;
                    c -= 1;
                }
            }
        a1 *= 10000000;
        a2 *= 10000000;
        b *= 100000;
        c *= 1000;
        int e = rand() % 100;
        if (player == PLAYER2)
            e = -e;
        return a1 + a2 + b + c + e;
    }
    
    else if ((opt == 1 && evalp1 == 3) || (opt == 2 && evalp2 == 3))
    {
        //EVALUATION FUNCTION 3
        //Evaluation function 3 -  different weights are given to pieces based on their poisition
        //center position + edge position + my piece + myking
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                if(CheckerBoard[i][j] == PLAYER1)
                {
                    player1Count++;
                    //if piece in edge square
                    if( (i==3) && ((j==0) || (j==7)))
                        player1Count += 0.5;
                    //if piece in one of the four center squares
                    if (((i==3) && ((j == 2) || (j== 4))) || ((i==4) && ((j==3)||(j==5))))
                        player1Count += 0.75;

                }else if(CheckerBoard[i][j] == PLAYER2){

                    player2Count++;
                    //if piece in edge square
                    if( (i==4) && ((j==0) || (j==7)))
                       player2Count += 0.5;
                    //if piece is in one of the four center squares
                    if (((i==3) && ((j == 2) || (j== 4))) || ((i==4) && ((j==3)||(j==5))))
                       player2Count += 0.75;
                }
                if(CheckerBoard[i][j] == PLAYER1_KING){

                    player1Count += 2;
                    //if piece in edge square
                   if( (i==3) && ((j==0) || (j==7)))
                       player1Count += 0.5;
                    //if piece is in one of the four center squares
                    if (((i==3) && ((j == 2) || (j== 4))) || ((i==4) && ((j==3)||(j==5))))
                        player1Count += 0.75;

                }else if (CheckerBoard[i][j] == PLAYER2_KING){

                    player2Count += 2;
                    //if piece in edge square
                   if((i==4) && ((j==0) || (j==7)))
                      player2Count += 0.5;
                    //if piece in one of the four center squares
                    if (((i==3) && ((j == 2) || (j== 4))) || ((i==4) && ((j==3)||(j==5))))
                         player2Count += 0.75;
                }

            }
        }
    }
    if (opt == 1)
        return player1Count - player2Count;
    return player2Count - player1Count;
}


//****** Functions for the EVALUATION FUNCTION ******//

