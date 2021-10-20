
#include <stdio.h>
#include <iostream>
#include "CheckerBoard.h"

using namespace std;
//******  Functions for the BOARD SETUP,PLAYER AND DISPLAY ******//

/*---- Function:SetBoard()-----*
Purpose: Set the board with respective names for each player.
Input:board[][]
Return Type: void */

void Element::setBoard(char b[][8])
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            CheckerBoard[i][j] = b[i][j];
        }
    }
}

/*---- Function:SetPlayer()-----*
Purpose: Set the player as p
Input: char p
Return Type: void */

void Element::setPlayer(char p)
{
    player = p;
}

//****** Functions for the BOARD SETUP,PLAYER AND DISPLAY ******//

//****** Functions for the CHECKERS GAME ******//

/*---- Function:compare()-----*
Purpose: Used for comparing two boards.
Input: board1[][],board2[][]
Return Type: bool - if the boards are not equal then returns false else true */

bool Element::compare(char s[][8], char d[][8])
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (s[i][j] != d[i][j])
                return false;
        }
    }
    return true;
}

/*---- Function:compare()-----*
Purpose: Position of the piece should be always within limits and should be empty
         where you are about to make a move
Input: checkerboard[][],row,col
Return Type: bool - returns true if purpose is satified else false */

bool Element::ValidPosition(char CheckerBoard[][8], int row, int col)
{
    if (!(row >= 0 && row <= 7 && col >= 0 && col <= 7 && CheckerBoard[row][col] == EMPTY_SPACE))
        return false;
    return true;
}


/*---- Function:leftCorner()-----*
Purpose: To check whether left corner jump is possible or not.
Input: checkerboard[][],row,col,player
Return Type: bool - Returns true if you cannot make a left jump from the current
                    position (row,col) else false */

bool Element::leftCorner(char CheckerBoard[][8], int row, int col, char player)

{
    int mrow, mcol;
    if (player == PLAYER1)
    {
        mrow = row + 2;
        mcol = col - 2;
        if (ValidPosition(CheckerBoard, mrow, mcol))

        {
            if (CheckerBoard[mrow - 1][mcol + 1] == PLAYER2 || CheckerBoard[mrow - 1][mcol + 1] == PLAYER2_KING)
            {
                return false;
            }
        }
    }
    else if (player == PLAYER2)
    {
        mrow = row - 2;
        mcol = col - 2;
        if (ValidPosition(CheckerBoard, mrow, mcol))

        {
            if (CheckerBoard[mrow + 1][mcol + 1] == PLAYER1 || CheckerBoard[mrow + 1][mcol + 1] == PLAYER1_KING)
            {
               return false;
            }
        }
    }
    return true;
}

/*---- Function:rightCorner()-----*
Purpose: To check whether right corner jump is possible or not.
Input: checkerboard[][],row,col,player
Return Type: bool - Returns true if you cannot make a right jump from the current
                    position (row,col) else false */

bool Element::rightCorner(char CheckerBoard[][8], int row, int col, char player)

{
    int mrow, mcol;
    if (player == PLAYER1)
    {
        mrow = row + 2;
        mcol = col + 2;
        if (ValidPosition(CheckerBoard, mrow, mcol))

        {
            if (CheckerBoard[mrow - 1][mcol - 1] == PLAYER2 || CheckerBoard[mrow - 1][mcol - 1] == PLAYER2_KING)
            {

                return false;
            }
        }
    }
    else if (player == PLAYER2)
    {
        mrow = row - 2;
        mcol = col + 2;
        if (ValidPosition(CheckerBoard, mrow, mcol))

        {
            if (CheckerBoard[mrow + 1][mcol - 1] == PLAYER1 || CheckerBoard[mrow + 1][mcol - 1] == PLAYER1_KING)
            {

                return false;
            }
        }
    }
    return true;
}

/*---- Function:Leftcheck()-----*
Purpose: To check whether leftmove is possible or not.
Input: checkerboard[][],row,col,player
Return Type: bool - Returns true if you can move left from the current position
                    (row,col) else false */


bool Element::Leftcheck(char CheckerBoard[][8], int row, int col, char player)

{
    int mrow=0, mcol = 0;
    if (player == PLAYER1)
    {
        mrow = row + 1;
        mcol = col - 1;
    }
    else if (player == PLAYER2)
    {
        mrow = row - 1;
        mcol = col - 1;
    }
    return ValidPosition(CheckerBoard, mrow, mcol);
}

/*---- Function:Rightcheck()-----*
Purpose: To check whether rightmove is possible or not.
Input: checkerboard[][],row,col,player
Return Type: bool - Returns true if you can move right from the current position
                    (row,col) else false */

bool Element::Rightcheck(char CheckerBoard[][8], int row, int col, char player)
{

    int mrow = 0, mcol = 0;
    if (player == PLAYER1)
    {
        mrow = row + 1;
        mcol = col + 1;
    }
    else if (player == PLAYER2)
    {
        mrow = row - 1;
        mcol = col + 1;
    }
    return ValidPosition(CheckerBoard, mrow, mcol);
}

/*---- Function:jump()-----*
Purpose: To perform leftjump or rightjump by checking left and right corner
         is performed by the piece.
Input: checkerboard[][],row,col,player
Return Type: void */


void Element::jump(char CheckerBoard[][8], int row, int col, char player)
{

    int mrow, mcol;
    mrow = row;
    mcol = col;
    char newboard[8][8];
    //create a copy of board
    copy(&CheckerBoard[0][0], &CheckerBoard[0][0] + 8 * 8, &newboard[0][0]);
    leftJump(newboard, row, col, player, mrow, mcol);
    /*
    Check whether the newboard is changed --- compare newboard with checkerboard based on left and right corner
    If changed then perform action
    */
    if (!compare(CheckerBoard, newboard) && leftCorner(newboard, mrow, mcol, player) && rightCorner(newboard, mrow, mcol, player))

    {
        //Perform Action
        action(newboard);
    }

    // copy back board in newboard and call jumpright else call jumpight
    copy(&CheckerBoard[0][0], &CheckerBoard[0][0] + 8 * 8, &newboard[0][0]);
    rightJump(newboard, row, col, player, mrow, mcol);
    /*
     Check whether the newboard is changed --- compare newboard with checkerboard based on left and right corner
     If changed then perform action
     */
    if (!compare(CheckerBoard, newboard) && leftCorner(newboard, mrow, mcol, player) && rightCorner(newboard, mrow, mcol, player))

    {
        //Perform Action
        action(newboard);
    }
    copy(&CheckerBoard[0][0], &CheckerBoard[0][0] + 8 * 8, &newboard[0][0]);
}

/*---- Function:leftJump()-----*
Purpose: To perform leftjump and check if the new position will make the current player a king or not
Input: checkerboard[][],row,col,player,reference to row,col
Return Type: void */

void Element::leftJump(char newboard[][8], int row, int col, char player, int& crow, int& ccol)
{
    int mrow, mcol;
    if (player == PLAYER1)
    {
        mrow = row + 2;
        mcol = col - 2;
        if (ValidPosition(newboard, mrow, mcol))

        {
            if (newboard[mrow - 1][mcol + 1] == PLAYER2 || newboard[mrow - 1][mcol + 1] == PLAYER2_KING)
            {
                //Can make a left jump
                newboard[mrow - 1][mcol + 1] = EMPTY_SPACE;
                newboard[row][col] = EMPTY_SPACE;
                //Checking if the new position will make the current player a king or not
                crow = mrow;
                ccol = mcol;
                if (checkKing(mrow, player))
                    newboard[mrow][mcol] = PLAYER1_KING;
                else
                {
                    newboard[mrow][mcol] = PLAYER1;
                    jump(newboard, mrow, mcol, player);
                }
            }
        }
    }
    else if (player == PLAYER2)
    {
        mrow = row - 2;
        mcol = col - 2;
        if (ValidPosition(newboard, mrow, mcol))

        {
            if (newboard[mrow + 1][mcol + 1] == PLAYER1 || newboard[mrow + 1][mcol + 1] == PLAYER1_KING)
            {
                //Can make a left jump
                newboard[mrow + 1][mcol + 1] = EMPTY_SPACE;
                newboard[row][col] = EMPTY_SPACE;
                //Checking if the new position will make the current player a king or not
                crow = mrow;
                ccol = mcol;
                if (checkKing(mrow, player))
                    newboard[mrow][mcol] = PLAYER2_KING;
                else
                {
                    newboard[mrow][mcol] = PLAYER2;
                    jump(newboard, mrow, mcol, player);
                }
            }
        }
    }
}

/*---- Function:rightJump()-----*
Purpose: To perform rightJump and check if the new position will make the current player a king or not
Input: checkerboard[][],row,col,player,reference to row,col
Return Type: void */

void Element::rightJump(char newboard[][8], int row, int col, char player, int& crow, int& ccol)
{
    int mrow, mcol;
    if (player == PLAYER1)
    {
        mrow = row + 2;
        mcol = col + 2;
        if (ValidPosition(newboard, mrow, mcol))

        {
            if (newboard[mrow - 1][mcol - 1] == PLAYER2 || newboard[mrow - 1][mcol - 1] == PLAYER2_KING)
            {
                // can make a left jump
                newboard[mrow - 1][mcol - 1] = EMPTY_SPACE;
                newboard[row][col] = EMPTY_SPACE;
                crow = mrow;
                ccol = mcol;
                //Checking if the new position will make the current player a king or not
                if (checkKing(mrow, player))
                    newboard[mrow][mcol] = PLAYER1_KING;
                else
                {
                    newboard[mrow][mcol] = PLAYER1;
                    jump(newboard, mrow, mcol, player);
                }
            }
        }
    }
    else if (player == PLAYER2)
    {
        mrow = row - 2;
        mcol = col + 2;
        if (ValidPosition(newboard, mrow, mcol))

        {
            if (newboard[mrow + 1][mcol - 1] == PLAYER1 || newboard[mrow + 1][mcol - 1] == PLAYER1_KING)
            {
                //can make a left jump
                newboard[mrow + 1][mcol - 1] = EMPTY_SPACE;
                newboard[row][col] = EMPTY_SPACE;
                crow = mrow;
                ccol = mcol;
                //Checking if the new position will make the current player a king or not
                if (checkKing(mrow, player))
                    newboard[mrow][mcol] = PLAYER2_KING;
                else
                {
                    newboard[mrow][mcol] = PLAYER2;
                    jump(newboard, mrow, mcol, player);
                }
            }
        }
    }
}


/*---- Function:checkKing()-----*
Purpose: To check whether that piece is a king depending upon where it is on the board.
Input: row,player
Return Type: bool -- return true if it is king else false */


bool Element::checkKing(int row, char player)
{
    if (player == PLAYER1 && row == 7)
    {
        return true;
    }
    if (player == PLAYER2 && row == 0)
    {
        return true;
    }
    return false;
}

/*---- Function:kingLeftCorner()-----*
Purpose: To check for the king position if it falls in left corner.
Input: board[][],row,col,player
Return Type: bool -- return true if the proper move is made else false */

bool Element::kingLeftCorner(char newboard[][8], int row, int col, char player)
{
    int mrow, mcol;
    if (player == PLAYER1)
    {
        mrow = row + 2;
        mcol = col - 2;
        if (ValidPosition(newboard, mrow, mcol))

        {
            if (newboard[mrow - 1][mcol + 1] == PLAYER2 || newboard[mrow - 1][mcol + 1] == PLAYER2_KING)
            {
                return false;
            }
        }
    }
    else if (player == PLAYER2)
    {
        mrow = row + 2;
        mcol = col - 2;
        if (ValidPosition(newboard, mrow, mcol))

        {
            if (newboard[mrow - 1][mcol + 1] == PLAYER1 || newboard[mrow - 1][mcol + 1] == PLAYER1_KING)
            {
                return false;
            }
        }
    }
    return true;
}

/*---- Function:kingLeftCorner()-----*
Purpose: To check for the king position if it falls in right corner.
Input: board[][],row,col,player
Return Type: bool -- return true if the proper move is made else false */


bool Element::kingRightCorner(char newboard[][8], int row, int col, char player)
{
    int mrow, mcol;
    if (player == PLAYER1)
    {
        mrow = row + 2;
        mcol = col + 2;
        if (ValidPosition(newboard, mrow, mcol))

        {
            if (newboard[mrow - 1][mcol - 1] == PLAYER2 || newboard[mrow - 1][mcol - 1] == PLAYER2_KING)
            {
                return false;
            }
        }
    }
    else if (player == PLAYER2)
    {
        mrow = row + 2;
        mcol = col + 2;
        if (ValidPosition(newboard, mrow, mcol))

        {
            if (newboard[mrow - 1][mcol - 1] == PLAYER1 || newboard[mrow - 1][mcol - 1] == PLAYER1_KING)
            {
                return false;
            }
        }
    }
    return true;
}

/*---- Function:kingTopLeftCorner()-----*
Purpose: To check for the king position if it falls in top left corner.
Input: board[][],row,col,player
Return Type: bool -- return true if the proper move is made else false */

bool Element::kingTopLeftCorner(char newboard[][8], int row, int col, char player)
{
    int mrow, mcol;
    if (player == PLAYER1)
    {
        mrow = row - 2;
        mcol = col - 2;
        if (ValidPosition(newboard, mcol, mcol))

        {
            if (newboard[mrow + 1][mcol + 1] == PLAYER2 || newboard[mrow + 1][mcol + 1] == PLAYER2_KING)
            {
                return false;
            }
        }
    }
    else if (player == PLAYER2)
    {
        mrow = row - 2;
        mcol = col - 2;
        if (ValidPosition(newboard, mrow, mcol))

        {
            if (newboard[mrow + 1][mcol + 1] == PLAYER1 || newboard[mrow + 1][mcol + 1] == PLAYER1_KING)
            {
                return false;
            }
        }
    }
    return true;
}

/*---- Function:kingTopRightCorner()-----*
Purpose: To check for the king position if it falls in top right corner.
Input: board[][],row,col,player
Return Type: bool -- return true if the proper move is made else false */

bool Element::kingTopRightCorner(char newboard[][8], int row, int col, char player)
{
    int mrow, mcol;
    if (player == PLAYER1)
    {
        mrow = row - 2;
        mcol = col + 2;
        if (ValidPosition(newboard, mrow, mcol))

        {
            if (newboard[mrow + 1][mcol - 1] == PLAYER2 || newboard[mrow + 1][mcol - 1] == PLAYER2_KING)
            {
                return false;
            }
        }
    }
    else if (player == PLAYER2)
    {
        mrow = row - 2;
        mcol = col + 2;
        if (ValidPosition(newboard, mrow, mcol))

        {
            if (newboard[mrow + 1][mcol - 1] == PLAYER1 || newboard[mrow + 1][mcol - 1] == PLAYER1_KING)
            {
                return false;
            }
        }
    }
    return true;
}


/*---- Function:kingLeftTop()-----*
Purpose: To check for the king position if it falls in left top.
Input: board[][],row,col,player,refernce to row,col
Return Type:void*/


void Element::kingLeftTop(char newboard[][8], int row, int col, char player, int& crow, int& ccol)
{
    int mrow, mcol;
    if (player == PLAYER1)
    {
        mrow = row - 2;
        mcol = col - 2;
        if (ValidPosition(newboard, mrow, mcol))

        {
            if (newboard[mrow + 1][mcol + 1] == PLAYER2 || newboard[mrow + 1][mcol + 1] == PLAYER2_KING)
            {
                newboard[mrow + 1][mcol + 1] = EMPTY_SPACE;
                newboard[row][col] = EMPTY_SPACE;
                crow = mrow;
                ccol = mcol;
                newboard[mrow][mcol] = PLAYER1_KING;
                jumpKing(newboard, mrow, mcol, player);
            }
        }
    }
    else if (player == PLAYER2)
    {
        mrow = row - 2;
        mcol = col - 2;
        if (ValidPosition(newboard, mrow, mcol))

        {
            if (newboard[mrow + 1][mcol + 1] == PLAYER1 || newboard[mrow + 1][mcol + 1] == PLAYER1_KING)
            {
                //Then i can make a left jump
                newboard[mrow + 1][mcol + 1] = EMPTY_SPACE;
                newboard[row][col] = EMPTY_SPACE;
                crow = mrow;
                ccol = mcol;
                newboard[mrow][mcol] = PLAYER2_KING;
                jumpKing(newboard, mrow, mcol, player);
            }
        }
    }
}


/*---- Function:kingRightTop()-----*
Purpose: To check for the king position if it falls in right top.
Input: board[][],row,col,player,refernce to row,col
Return Type: void */

void Element::kingRightTop(char newboard[][8], int row, int col, char player, int& crow, int& ccol)
{
    int mrow, mcol;
    if (player == PLAYER1)
    {
        mrow = row - 2;
        mcol = col + 2;
        if (ValidPosition(newboard, mrow, mcol))

        {
            if (newboard[mrow + 1][mcol - 1] == PLAYER2 || newboard[mrow + 1][mcol - 1] == PLAYER2_KING)
            {
                newboard[mrow + 1][mcol - 1] = EMPTY_SPACE;
                newboard[row][col] = EMPTY_SPACE;
                crow = mrow;
                ccol = mcol;
                newboard[mrow][mcol] = PLAYER1_KING;
                jumpKing(newboard, mrow, mcol, player);
            }
        }
    }
    else if (player == PLAYER2)
    {
        mrow = row - 2;
        mcol = col + 2;
        if (ValidPosition(newboard, mrow, mcol))

        {
            if (newboard[mrow + 1][mcol - 1] == PLAYER1 || newboard[mrow + 1][mcol - 1] == PLAYER1_KING)
            {
                //Then i can make a left jump
                newboard[mrow + 1][mcol - 1] = EMPTY_SPACE;
                newboard[row][col] = EMPTY_SPACE;
                crow = mrow;
                ccol = mcol;
                newboard[mrow][mcol] = PLAYER2_KING;
                jumpKing(newboard, mrow, mcol, player);
            }
        }
    }
}

/*---- Function:kingLeftJump()-----*
Purpose: King jump to the left is made
Input: board[][],row,col,player,reference to col,row
Return Type: void */

void Element::kingLeftJump(char newboard[][8], int row, int col, char player, int& crow, int& ccol)
{
    int nrow, ncol;
    if (player == PLAYER1)
    {
        nrow = row + 2;
        ncol = col - 2;
        if (ValidPosition(newboard, nrow, ncol))

        {
            if (newboard[nrow - 1][ncol + 1] == PLAYER2 || newboard[nrow - 1][ncol + 1] == PLAYER2_KING)
            {
                newboard[nrow - 1][ncol + 1] = EMPTY_SPACE;
                newboard[row][col] = EMPTY_SPACE;
                crow = nrow;
                ccol = ncol;
                newboard[nrow][ncol] = PLAYER1_KING;
                jumpKing(newboard, nrow, ncol, player);
            }
        }
    }
    else if (player == PLAYER2)
    {
        nrow = row + 2;
        ncol = col - 2;
        if (ValidPosition(newboard, nrow, ncol))

        {
            if (newboard[nrow - 1][ncol + 1] == PLAYER1 || newboard[nrow - 1][ncol + 1] == PLAYER1_KING)
            {
                //Then i can make a left jump
                newboard[nrow - 1][ncol + 1] = EMPTY_SPACE;
                newboard[row][col] = EMPTY_SPACE;
                crow = nrow;
                ccol = ncol;
                newboard[nrow][ncol] = PLAYER2_KING;
                jumpKing(newboard, nrow, ncol, player);
            }
        }
    }
}

/*---- Function:kingRightJump()-----*
Purpose: King jump to the right is made
Input: board[][],row,col,player,reference to col,row
Return Type: void */

void Element::kingRightJump(char newboard[][8], int row, int col, char player, int& crow, int& ccol)
{
    int nrow, ncol;
    if (player == PLAYER1)
    {
        nrow = row + 2;
        ncol = col + 2;
        if (ValidPosition(newboard, nrow, ncol))

        {
            if (newboard[nrow - 1][ncol - 1] == PLAYER2 || newboard[nrow - 1][ncol - 1] == PLAYER2_KING)
            {
                newboard[nrow - 1][ncol - 1] = EMPTY_SPACE;
                newboard[row][col] = EMPTY_SPACE;
                crow = nrow;
                ccol = ncol;
                newboard[nrow][ncol] = PLAYER1_KING;
                jumpKing(newboard, nrow, ncol, player);
            }
        }
    }
    else if (player == PLAYER2)
    {
        nrow = row + 2;
        ncol = col + 2;
        if (ValidPosition(newboard, nrow, ncol))

        {
            if (newboard[nrow - 1][ncol - 1] == PLAYER1 || newboard[nrow - 1][ncol - 1] == PLAYER1_KING)
            {
                //Then i can make a left jump
                newboard[nrow - 1][ncol - 1] = EMPTY_SPACE;
                newboard[row][col] = EMPTY_SPACE;
                crow = nrow;
                ccol = ncol;
                newboard[nrow][ncol] = PLAYER2_KING;
                jumpKing(newboard, nrow, ncol, player);
            }
        }
    }
}



/*---- Function:jumpKing()-----*
Purpose: King jump is made by checking whether it can jump to left,right,lefttop or righttop
Input: board[][],row,col,player
Return Type: void */


void Element::jumpKing(char CheckerBoard[][8], int row, int col, char player)
{
    int crow, ccol;
    crow = row;
    ccol = col;
    char newboard[8][8];
    copy(&CheckerBoard[0][0], &CheckerBoard[0][0] + 8 * 8, &newboard[0][0]);

    kingLeftJump(newboard, row, col, player, crow, ccol);
    if (!compare(CheckerBoard, newboard) && kingLeftCorner(newboard, crow, ccol, player) && kingRightCorner(newboard, crow, ccol, player) && kingTopLeftCorner(newboard, crow, ccol, player) && kingTopRightCorner(newboard, crow, ccol, player))
    {
        //Perform Action
        action(newboard);
    }
    copy(&CheckerBoard[0][0], &CheckerBoard[0][0] + 8 * 8, &newboard[0][0]);

    kingRightJump(newboard, row, col, player, crow, ccol);
    if (!compare(CheckerBoard, newboard) && kingLeftCorner(newboard, crow, ccol, player) && kingRightCorner(newboard, crow, ccol, player) && kingTopLeftCorner(newboard, crow, ccol, player) && kingTopRightCorner(newboard, crow, ccol, player))
    {
        //Perform Action
        action(newboard);
    }
    copy(&CheckerBoard[0][0], &CheckerBoard[0][0] + 8 * 8, &newboard[0][0]);

    kingLeftTop(newboard, row, col, player, crow, ccol);
    if (!compare(CheckerBoard, newboard) && kingLeftCorner(newboard, crow, ccol, player) && kingRightCorner(newboard, crow, ccol, player) && kingTopLeftCorner(newboard, crow, ccol, player) && kingTopRightCorner(newboard, crow, ccol, player))
    {
        //Perform Action
        action(newboard);
    }
    copy(&CheckerBoard[0][0], &CheckerBoard[0][0] + 8 * 8, &newboard[0][0]);

    kingRightTop(newboard, row, col, player, crow, ccol);
    if (!compare(CheckerBoard, newboard) && kingLeftCorner(newboard, crow, ccol, player) && kingRightCorner(newboard, crow, ccol, player) && kingTopLeftCorner(newboard, crow, ccol, player) && kingTopRightCorner(newboard, crow, ccol, player))
    {
        //Perform Action
        action(newboard);
    }
    copy(&CheckerBoard[0][0], &CheckerBoard[0][0] + 8 * 8, &newboard[0][0]);
}

//****** END OF Functions for the CHECKERS GAME ******//
