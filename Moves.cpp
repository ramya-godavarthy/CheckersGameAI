
#include <stdio.h>
#include <iostream>
#include "CheckerBoard.h"

using namespace std;

/*---- Function:action()-----*
Purpose: Move one place ahead by setting to newboard and setting to the player
Input: newboard[][]
Return Type: void */

void Element::action(char newboard[][8])
{
    Element child1;
    child1.setBoard(newboard);
    char newplayer = (player == PLAYER1) ? PLAYER2 : PLAYER1;
    child1.setPlayer(newplayer);
    child1.move = move + 1;
    childs.push_back(child1);
    TotalElements++;
}

/*---- Function:moves()-----*
Purpose: Defining each moves a piece can take. Leftdiagnoal check,right diagnoal check and check if its king
         and then performs the action.
Return Type: void */

void Element::moves()
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (CheckerBoard[i][j] != EMPTY_SPACE)
            {
                if (player == PLAYER1 && CheckerBoard[i][j] == PLAYER1)//Computer normal player
                {
                    char newboard[8][8];
                    copy(&CheckerBoard[0][0], &CheckerBoard[0][0] + 8 * 8, &newboard[0][0]);

                    //Left diagnoal check
                    if (Leftcheck(CheckerBoard, i, j, player))
                    {
                        // then can move left
                        if (checkKing(i + 1, player))
                            newboard[i + 1][j - 1] = PLAYER1_KING;
                        else
                            newboard[i + 1][j - 1] = PLAYER1;
                        newboard[i][j] = EMPTY_SPACE;
                        //Perform an Action
                        action(newboard);
                        copy(&CheckerBoard[0][0], &CheckerBoard[0][0] + 8 * 8, &newboard[0][0]);
                    }
                    //Right diagnoal check
                    if (Rightcheck(CheckerBoard, i, j, player))
                    {
                        //then can move right
                        if (checkKing(i + 1, player))
                            newboard[i + 1][j + 1] = PLAYER1_KING;
                        else
                            newboard[i + 1][j + 1] = PLAYER1;
                        newboard[i][j] = EMPTY_SPACE;
                        //Perform Action
                        action(newboard);
                        copy(&CheckerBoard[0][0], &CheckerBoard[0][0] + 8 * 8, &newboard[0][0]);
                    }
                    //Check jumps
                    jump(CheckerBoard, i, j, player);
                }
                else if (player == PLAYER2 && CheckerBoard[i][j] == PLAYER2) //user normal player
                {
                    char newboard[8][8];
                    copy(&CheckerBoard[0][0], &CheckerBoard[0][0] + 8 * 8, &newboard[0][0]);

                    //Left diagnoal check
                    if (Leftcheck(CheckerBoard, i, j, player))
                    {
                        //then can move left
                        if (checkKing(i - 1, player))
                            newboard[i - 1][j - 1] = PLAYER2_KING;
                        else
                            newboard[i - 1][j - 1] = PLAYER2;
                        newboard[i][j] = EMPTY_SPACE;
                        //Perform Action
                        action(newboard);
                        copy(&CheckerBoard[0][0], &CheckerBoard[0][0] + 8 * 8, &newboard[0][0]);
                    }
                    //Right diagnoal Check
                    if (Rightcheck(CheckerBoard, i, j, player))
                    {
                        //then can move right
                        if (checkKing(i - 1, player))
                            newboard[i - 1][j + 1] = PLAYER2_KING;
                        else
                            newboard[i - 1][j + 1] = PLAYER2;
                        newboard[i][j] = EMPTY_SPACE;
                        //Perform Action
                        action(newboard);
                        copy(&CheckerBoard[0][0], &CheckerBoard[0][0] + 8 * 8, &newboard[0][0]);
                    }
                    //Check jumps
                    jump(CheckerBoard, i, j, player);
                }
                //When Computer player turned king
                if (player == PLAYER1 && CheckerBoard[i][j] == PLAYER1_KING)
                {
                    char newboard[8][8];
                    copy(&CheckerBoard[0][0], &CheckerBoard[0][0] + 8 * 8, &newboard[0][0]);
                    //Check PLAYER1's left diagnoal
                    if (Leftcheck(CheckerBoard, i, j, PLAYER1))
                    {
                        //then can move left
                        newboard[i + 1][j - 1] = PLAYER1_KING;
                        newboard[i][j] = EMPTY_SPACE;
                        //Perform Action
                        action(newboard);
                        copy(&CheckerBoard[0][0], &CheckerBoard[0][0] + 8 * 8, &newboard[0][0]);
                    }
                    //Check PLAYER1's right diagnoal
                    if (Rightcheck(CheckerBoard, i, j, PLAYER1))
                    {
                        //then can move right
                        newboard[i + 1][j + 1] = PLAYER1_KING;
                        newboard[i][j] = EMPTY_SPACE;
                        //Perform Action
                        action(newboard);
                        copy(&CheckerBoard[0][0], &CheckerBoard[0][0] + 8 * 8, &newboard[0][0]);
                    }
                    //Check PLAYER2's left diagnoal
                    if (Leftcheck(CheckerBoard, i, j, PLAYER2))
                    {
                        //then can move left
                        newboard[i - 1][j - 1] = PLAYER1_KING;
                        newboard[i][j] = EMPTY_SPACE;
                        //Perform Action
                        action(newboard);
                        copy(&CheckerBoard[0][0], &CheckerBoard[0][0] + 8 * 8, &newboard[0][0]);
                    }
                    //Check PLAYER2's right diagnoal
                    if (Rightcheck(CheckerBoard, i, j, PLAYER2))
                    {
                        //I can move right
                        newboard[i - 1][j + 1] = PLAYER1_KING;
                        newboard[i][j] = EMPTY_SPACE;
                        //Perform Action
                        action(newboard);
                        copy(&CheckerBoard[0][0], &CheckerBoard[0][0] + 8 * 8, &newboard[0][0]);
                    }
                    //Checking for jumps
                    jumpKing(CheckerBoard, i, j, player);
                }
                if (player == PLAYER2 && CheckerBoard[i][j] == PLAYER2_KING) //User player turned king
                {
                    char newboard[8][8];
                    copy(&CheckerBoard[0][0], &CheckerBoard[0][0] + 8 * 8, &newboard[0][0]);
                    //Check PLAYER1's left diagnoal
                    if (Leftcheck(CheckerBoard, i, j, PLAYER1))
                    {
                        //then can move left
                        newboard[i + 1][j - 1] = PLAYER2_KING;
                        newboard[i][j] = EMPTY_SPACE;
                        //Perform Action
                        action(newboard);
                        copy(&CheckerBoard[0][0], &CheckerBoard[0][0] + 8 * 8, &newboard[0][0]);
                    }
                    //Check PLAYER1's right diagnoal
                    if (Rightcheck(CheckerBoard, i, j, PLAYER1))
                    {
                        //then can move right
                        newboard[i + 1][j + 1] = PLAYER2_KING;
                        newboard[i][j] = EMPTY_SPACE;
                        //Perform Action
                        action(newboard);
                        copy(&CheckerBoard[0][0], &CheckerBoard[0][0] + 8 * 8, &newboard[0][0]);
                    }
                    //Check PLAYER2's left diagnoal
                    if (Leftcheck(CheckerBoard, i, j, PLAYER2))
                    {
                        //then can move left
                        newboard[i - 1][j - 1] = PLAYER2_KING;
                        newboard[i][j] = EMPTY_SPACE;
                        //Perform Action
                        action(newboard);
                        copy(&CheckerBoard[0][0], &CheckerBoard[0][0] + 8 * 8, &newboard[0][0]);
                    }
                    //Check PLAYER2's right diagnoal
                    if (Rightcheck(CheckerBoard, i, j, PLAYER2))
                    {
                        //then can move right
                        newboard[i - 1][j + 1] = PLAYER2_KING;
                        newboard[i][j] = EMPTY_SPACE;
                        //Perform Action
                        action(newboard);
                        copy(&CheckerBoard[0][0], &CheckerBoard[0][0] + 8 * 8, &newboard[0][0]);
                    }
                    //Checking for jumps
                    jumpKing(CheckerBoard, i, j, player);
                }
            }
        }
    }
}



