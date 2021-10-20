
#ifndef CheckerBoard_h
#define CheckerBoard_h
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Defining the Player Variables
#define EMPTY_SPACE  '_'
#define PLAYER1  'X'
#define PLAYER2  'O'
#define PLAYER1_KING 'K' // Player King 1
#define PLAYER2_KING 'L' // Player King 2

extern int opt;
extern int evalp1;
extern int evalp2;
extern int TotalElements;

class Element
{
public:

    char CheckerBoard[8][8]{}, player{};
    vector<Element>childs;
    int v{};
    int move{};

    //****** SECTION 1 : Functions for the EVALUATION FUNCTION ******//
    int  evaluate();
    int EvalValue();
   // int DefendingNeighbors(char state[][8], int row, int col);
   // void printEval();
    //***************************************//

    //****** SECTION 2: Functions for the BOARD SETUP,PLAYER AND DISPLAY ******//
    void setBoard(char b[][8]);
    void setPlayer(char);
    //***************************************//

    //****** SECTION 3: Functions for the CHECKERS GAME ******//
    bool terminal() const;
    void action(char newboard[][8]);
    void moves();
    static bool compare(char[][8], char[][8]);
    static bool ValidPosition(char CheckerBoard[][8], int row, int col);

    static bool leftCorner(char CheckerBoard[][8], int row, int col, char player);
    static bool rightCorner(char CheckerBoard[][8], int row, int col, char player);
    static bool Leftcheck(char CheckerBoard[][8], int row, int col, char player);
    static bool Rightcheck(char CheckerBoard[][8], int row, int col, char player);

    void jump(char[][8], int, int, char);
    void leftJump(char newboard[][8], int row, int col, char player, int&, int&);
    void rightJump(char newboard[][8], int row, int col, char player, int&, int&);


    static bool checkKing(int row, char player);
    static bool kingLeftCorner(char newboard[][8], int row, int col, char player);
    static bool kingRightCorner(char newboard[][8], int row, int col, char player);
    static bool kingTopLeftCorner(char newboard[][8], int row, int col, char player);
    static bool kingTopRightCorner(char newboard[][8], int row, int col, char player);

    void jumpKing(char[][8], int, int, char);
    void kingLeftTop(char newboard[][8], int row, int col, char player, int& crow, int& ccol);
    void kingRightTop(char newboard[][8], int row, int col, char player, int& crow, int& ccol);
    void kingLeftJump(char newboard[][8], int row, int col, char player, int& crow, int& ccol);
    void kingRightJump(char newboard[][8], int row, int col, char player, int& crow, int& ccol);
    //***************************************//
};

#endif /* CheckerBoard_h */
