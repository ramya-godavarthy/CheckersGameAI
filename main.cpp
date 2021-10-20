#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include "CheckerBoard.h"
#include "Algorithm.h"

using namespace std;
using namespace std::chrono;
int evalp1;
int evalp2;
int comp1,comp2;
int depth;

int opt;
int TotalElements = 0;
int TotalElementsp1 = 0; // Total Elements Expanded by Player 1
int TotalElementsp2 = 0;  // Total Elements Expanded by Player 2
int TotalElementsGenp1; // Total Elements Generated by Player 1
int TotalElementsGenp2;  // Total Elements Generated by Player 2
int ElementSize = 42;
int TotalMemp1; // Total Memory used by Player 1
int TotalMemp2;  // Total Memory used by Player 2
double Player1Time = 0; // time taken by Player 1
double Player2Time = 0; // time taken by Player 2
int moveCount = 0;
vector<Element> bestPath;
void printEval();

/*---- Function:PrintBoard()-----*
Purpose: Prints the board
Input: board[][]
Return Type: void */

void printBoard(char boardsetup[][8])
{
    cout << endl << "=========================" << endl;
    for (int i = 0; i < 8; i++)
    {
        if (i == 0)
        {
            cout << "-------------------" << endl;
            cout << "R/C 0 1 2 3 4 5 6 7" << endl;
            cout << "-------------------";
            cout << endl;
        }
        cout << " |" << i << "|";
        for (int j = 0; j < 8; j++)
        {
            cout << boardsetup[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl << "=========================" << endl;
}


//******  COMPUTER VS COMPUTER ******//

/* Game Functions*/
/*---- Function:Computer Vs Computer -----*
//Purpose: Game playing function Computer Vs Computer using MinMaxAB or Alpha Beta Search
//Input: board[][],row,col,flag,compare row,compare col,compare board[][],compare flag
//Return Type: void */
void comp1vscomp2(int &row, int &column, int &nrow, int &ncolumn, bool &flag, bool &flag2, char CheckerBoard[][8])
{
    while (flag2)
    {
        opt = 1;
        Element test;
        test.setBoard(CheckerBoard);
        test.setPlayer(PLAYER1);
        test.move = 0;
        auto start = high_resolution_clock::now();
        if(comp1 == 1)
        alpha_beta_search(test, CheckerBoard);
        else if (comp1 == 2)
        Element c1 = MinMaxAB(test, test.move, test.player, 120, -100);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        Player1Time += duration.count();
        if (comp1 == 2)
        {
        for (int k = bestPath.size() - 1; k >= 0; k--)
        {
            if (bestPath[k].move == 1)
            {
                for (int i = 0; i < 8; i++)
                {
                    for (int j = 0; j < 8; j++)
                    {
                        //find child with move 0 and then store it into board
                        CheckerBoard[i][j] = bestPath[k].CheckerBoard[i][j];
                    }
                }
                break;
            }
        }
        }
        cout << "After Computer X Turn board is:" << endl;
        moveCount++;
        printBoard(CheckerBoard);
        Element test1;
        test1.setBoard(CheckerBoard);
        test1.setPlayer(PLAYER2);
        test1.move = 0;
        test1.moves();
        //Subtract the size of moves() from TotalElements
        TotalElements -= test1.childs.size();
        TotalElementsp1 += TotalElements;
        TotalElementsGenp1 += test1.childs.size();
        TotalMemp1 = ElementSize * TotalElementsGenp1;
        TotalElements = 0;
        if (test1.terminal())
        {
            cout << "Length of Game Path:" << moveCount << endl;
            cout << "Total Number of Nodes Generated by Computer 1: " << TotalElementsp1 << endl;
            cout << "Total Number of Nodes Generated by Computer 2: " << TotalElementsp2 << endl;
            cout << "Total Number of Nodes Expanded by Computer 1: " << TotalElementsGenp1 << endl;
            cout << "Total Number of Nodes Expanded by Computer 2: " << TotalElementsGenp2 << endl;
            cout << "Time taken by Computer 1: " << Player1Time << " microseconds" << endl;
            cout << "Time taken by Computer 2: " << Player2Time << " microseconds" << endl;
            cout << "Computer 1's Memory Consumption was: " << TotalMemp1 << "bytes" <<endl;
            cout << "Computer 2's Memory Consumption was: " << TotalMemp2 << "bytes" <<endl;
            printEval();
            int w = test1.evaluate();
            if (w == 100)
            {
                cout << "Computer X[1] Won the game" << endl;
                exit(0);
            }
        }
        if (moveCount >= 101)
        {
            cout << "Oops!! Game is  Tie" << endl;
            cout << "Length of Game Path:" << moveCount << endl;
            cout << "Total Number of Nodes Generated by Computer 1: " << TotalElementsp1 << endl;
            cout << "Total Number of Nodes Generated by Computer 2: " << TotalElementsp2 << endl;
            cout << "Total Number of Nodes Expanded by Computer 1: " << TotalElementsGenp1 << endl;
            cout << "Total Number of Nodes Expanded by Computer 2: " << TotalElementsGenp2 << endl;
            cout << "Time taken by Computer 1: " << Player1Time << " microseconds" << endl;
            cout << "Time taken by Computer 2: " << Player2Time << " microseconds" << endl;
            cout << "Computer 1's Memory Consumption was: " << TotalMemp1 << endl;
            cout << "Computer 2's Memory Consumption was: " << TotalMemp2 << endl;
            printEval();
            exit(0);
        }
        
        if(comp2 == 2)
        {bestPath.clear();}
        opt = 2;
        Element test2;
        test2.setBoard(CheckerBoard);
        test2.setPlayer(PLAYER2);
        test2.move = 0;
        start = high_resolution_clock::now();
        if(comp2 == 1)
        alpha_beta_search(test2, CheckerBoard);
        else if(comp2 == 2)
        Element c2 = MinMaxAB(test2, test2.move, test2.player, 120, -100);
        stop = high_resolution_clock::now();
        duration = duration_cast<microseconds>(stop - start);
        Player2Time += duration.count();
        if(comp2 == 2)
        {
        for (int k = bestPath.size() - 1; k >= 0; k--)
        {
            if (bestPath[k].move == 1)
            {
                for (int i = 0; i < 8; i++)
                {
                    for (int j = 0; j < 8; j++)
                    {
                        //find child with move 0 and then store it into board
                        CheckerBoard[i][j] = bestPath[k].CheckerBoard[i][j];
                    }
                }
                break;
            }
        }
        }
        cout << "After Computer O Turn board is:" << endl;
        moveCount++;
        printBoard(CheckerBoard);
        Element test3;
        test3.setBoard(CheckerBoard);
        test3.setPlayer(PLAYER1);
        test3.move = 0;
        test3.moves();
        //Subtract the size of moves() from TotalElements
        TotalElements -= test3.childs.size();
        TotalElementsp2 += TotalElements;
        TotalElementsGenp2 += test3.childs.size();
        TotalMemp2 = ElementSize * TotalElementsGenp2;
        TotalElements = 0;
        if (test3.terminal())
        {
            cout << "Length of Game Path:" << moveCount << endl;
            cout << "Total Number of Nodes Generated by Computer 1: " << TotalElementsp1 << endl;
            cout << "Total Number of Nodes Generated by Computer 2: " << TotalElementsp2 << endl;
            cout << "Total Number of Nodes Expanded by Computer 1: " << TotalElementsGenp1 << endl;
            cout << "Total Number of Nodes Expanded by Computer 2: " << TotalElementsGenp2 << endl;
            cout << "Time taken by Computer 1: " << Player1Time << " microseconds" << endl;
            cout << "Time taken by Computer 2: " << Player2Time << " microseconds" << endl;
            cout << "Computer 1's Memory Consumption was: " << TotalMemp1 << endl;
            cout << "Computer 2's Memory Consumption was: " << TotalMemp2 << endl;
            printEval();
            int w = test3.evaluate();
            if (w == 100)
            {
                cout << "Computer O[2] Won the game" << endl;
                exit(0);
            }
        }
        if (moveCount >= 101)
        {
            cout << "Oops!! Game is  Tie" << endl;
            cout << "Length of Game Path:" << moveCount << endl;
            cout << "Total Number of Nodes Generated by Computer 1: " << TotalElementsp1 << endl;
            cout << "Total Number of Nodes Generated by Computer 2: " << TotalElementsp2 << endl;
            cout << "Total Number of Nodes Expanded by Computer 1: " << TotalElementsGenp1 << endl;
            cout << "Total Number of Nodes Expanded by Computer 2: " << TotalElementsGenp2 << endl;
            cout << "Time taken by Computer 1: " << Player1Time << " microseconds" << endl;
            cout << "Time taken by Computer 2: " << Player2Time << " microseconds" << endl;
            cout << "Computer 1's Memory Consumption was: " << TotalMemp1 << endl;
            cout << "Computer 2's Memory Consumption was: " << TotalMemp2 << endl;
            printEval();
            exit(0);
        }
    }
}

//****** END OF SECTION 5: COMPUTER VS COMPUTER  ******//

void printEval()
{
        cout << "Computer 1's Evaluation Function is: " << evalp1 << endl;
        cout << "Computer 2's Evaluation Function is: " << evalp2 << endl;
}


//****** START OF SECTION 6: MAIN DRIVER FUNCTION ******//

int main()
{
    int row, column, nrow, ncolumn;
    bool flag = false;
    bool flag2 = true;

    char CheckerBoard[8][8] =
    {
        {EMPTY_SPACE, PLAYER1, EMPTY_SPACE, PLAYER1, EMPTY_SPACE, PLAYER1, EMPTY_SPACE, PLAYER1},
        {PLAYER1, EMPTY_SPACE, PLAYER1, EMPTY_SPACE, PLAYER1, EMPTY_SPACE, PLAYER1, EMPTY_SPACE},
        {EMPTY_SPACE, PLAYER1, EMPTY_SPACE, PLAYER1, EMPTY_SPACE, PLAYER1, EMPTY_SPACE, PLAYER1},
        {EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE},
        {EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE},
        {PLAYER2, EMPTY_SPACE, PLAYER2, EMPTY_SPACE, PLAYER2, EMPTY_SPACE, PLAYER2, EMPTY_SPACE},
        {EMPTY_SPACE, PLAYER2, EMPTY_SPACE, PLAYER2, EMPTY_SPACE, PLAYER2, EMPTY_SPACE, PLAYER2},
        {PLAYER2, EMPTY_SPACE, PLAYER2, EMPTY_SPACE, PLAYER2, EMPTY_SPACE, PLAYER2, EMPTY_SPACE},
    };

    cout << "\t\t Welcome to Checkers Game" << endl;
    cout << "\t\t LET'S START!!" << endl;
    cout<<"Enter your choice for Computer 1"<<endl;
    cout<<"1.Computer 1 - Alpha-Beta-Search"<<endl;
    cout<<"2.Computer 1 - MinMaxAB"<<endl;
    cout << "Choose one of the above options: ";
    do
    {
        cin >> comp1;
    } while (!(comp1 >= 1 && comp2 <= 2));

    cout << "Choose ANY ONE of the below evaluation function for computer 1" << endl << endl;
    cout << "1.Eval 1" << endl;
    cout << "2.Eval 2" << endl;
    cout << "3.Eval 3" << endl;
    do
    {
        cin >> evalp1;
    } while (!(evalp1 >= 1 && evalp1 <= 3));

    cout<<"Enter your choice for Computer 2:"<<endl;
    cout<<"1.Computer 2 - Alpha-Beta-Search"<<endl;
    cout<<"2.Computer 2 - MinMaxAB"<<endl;

    do
    {
        cin >> comp2;
    } while (!(comp2 >= 1 && comp2 <= 2));

    cout << "Choose ANY ONE of the below evaluation function for computer 2" << endl;
    cout << "1.Eval 1" << endl;
    cout << "2.Eval 2" << endl;
    cout << "3.Eval 3" << endl;
    do
    {
        cin >> evalp2;
    } while (!(evalp2 >= 1 && evalp2 <= 3));

    cout<<"\nChoose the depth of algorithms (2 or 4): "<<endl;
    cin >> depth;

    comp1vscomp2(row, column, nrow, ncolumn, flag, flag2, CheckerBoard);

}

//****** END MAIN DRIVER FUNCTION ******//
//**************** END OF CHECKERS GAME ***************//
