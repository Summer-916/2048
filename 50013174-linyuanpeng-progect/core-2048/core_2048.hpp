// - core.hpp

#ifndef CORE_HPP
#define CORE_HPP

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;

// - Global variable zone
int surfaceBoard[4][4] = {};
int exponentBoard[4][4] = {};
int currentScore = 0;
int highestScore=0;
bool goOn = true; // - Decide whether to end the program
string name = "None";

// - Core function declare zone
void randomTile();
void boardUpdate();
void upMove();
void downMove();
void leftMove();
void rightMove();
bool hasValidMove();
bool gameIsOver();
bool successful(int limit);

void randomTile(){
    srand(time(0));

    // - Generate the value of a single tile

    int random = 0;
    int a = rand() % 10;
    if (a != 9)
        random = 1;
    else
        random = 2;

    // - Generate the values of row and col
    int index = 0;
    int count = 0;
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            if (!exponentBoard[i][j])
                count++;
        }
    }

    bool fun = false;

    index = rand() % count + 1;
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            if (!exponentBoard[i][j])
                index--;

            if (index == 0)
            {
                exponentBoard[i][j] = random;
                fun = true;
            }

            if (fun)
                index--;
        }
    }
}

void boardUpdate(){
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {

            // - Change exponent into true value
            int a = exponentBoard[i][j];
            if (!a)
                surfaceBoard[i][j] = 0;
            else
                surfaceBoard[i][j] = int(pow(2, a));
        }
    }
}

void upMove() {
    // Move
    for (int j = 0; j < 4; j++)
    {
        vector<int> subCol;
        for (int i = 0; i < 4; i++)
        {
            if (exponentBoard[i][j] != 0)
            {
                subCol.push_back(exponentBoard[i][j]);
                exponentBoard[i][j] = 0;
            }
        }
        int sizeOfSubrow = subCol.size();
        for (int i = 0; i < sizeOfSubrow; i++)
        {
            exponentBoard[i][j] = subCol[i];
        }
    }
    // Merge
    for (int j = 0; j < 4; j++)
    {
        for (int i = 0; i < 3;i++)
        {
            if (exponentBoard[i][j] != 0 && exponentBoard[i][j] == exponentBoard[i + 1][j])
            {
                exponentBoard[i][j] += 1;
                exponentBoard[i + 1][j] = 0;

                int score = exponentBoard[i][j];
                currentScore += pow(2, score);
            }
        }
    }

    // Move
    for (int j = 0; j < 4; j++)
    {
        vector<int> subCol;
        for (int i = 0; i < 4; i++)
        {
            if (exponentBoard[i][j] != 0)
            {
                subCol.push_back(exponentBoard[i][j]);
                exponentBoard[i][j] = 0;
            }
        }
        int sizeOfSubrow = subCol.size();
        for (int i = 0; i < sizeOfSubrow; i++)
        {
            exponentBoard[i][j] = subCol[i];
        }
    }
}

void downMove() {
    // Move
    for (int j = 0; j < 4; j++)
    {
        vector<int> subCol;
        for (int i = 3; i >= 0; i--)
        {
            if (exponentBoard[i][j] != 0)
            {
                subCol.push_back(exponentBoard[i][j]);
                exponentBoard[i][j] = 0;
            }
        }
        int sizeOfSubrow = subCol.size();
        for (int i = 3; i >= 4 - sizeOfSubrow; i--)
        {
            exponentBoard[i][j] = subCol[3 - i];
        }
    }
    // Merge
    for (int j = 0; j < 4; j++)
    {
        for (int i = 3; i > 0;)
        {
            if (exponentBoard[i][j] == exponentBoard[i - 1][j] && exponentBoard[i][j] != 0)
            {
                exponentBoard[i][j] += 1;
                int score = exponentBoard[i][j];
                currentScore += pow(2, score);
                exponentBoard[i - 1][j] = 0;
                i -= 2;
            }
            else
                i--;
        }
    }
    // Move
    for (int j = 0; j < 4; j++)
    {
        vector<int> subCol;
        for (int i = 3; i >= 0; i--)
        {
            if (exponentBoard[i][j] != 0)
            {
                subCol.push_back(exponentBoard[i][j]);
                exponentBoard[i][j] = 0;
            }
        }
        int sizeOfSubrow = subCol.size();
        for (int i = 3; i >= 4 - sizeOfSubrow; i--)
        {
            exponentBoard[i][j] = subCol[3 - i];
        }
    }
}

void leftMove() {
    // Move
    for (int i = 0; i < 4; i++)
    {
        vector<int> subRow;
        for (int j = 0; j < 4; j++)
        {
            if (exponentBoard[i][j] != 0)
            {
                subRow.push_back(exponentBoard[i][j]);
                exponentBoard[i][j] = 0;
            }
        }
        int sizeOfSubrow = subRow.size();
        for (int j = 0; j < sizeOfSubrow; j++)
        {
            exponentBoard[i][j] = subRow[j];
        }
    }
    // Merge
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4;)
        {
            if (exponentBoard[i][j] == exponentBoard[i][j + 1] && exponentBoard[i][j] != 0)
            {
                exponentBoard[i][j] += 1;
                int score = exponentBoard[i][j];
                currentScore += pow(2, score);
                exponentBoard[i][j + 1] = 0;
                j += 2;
            }
            else
                j++;
        }
    }
    // Move
    for (int i = 0; i < 4; i++)
    {
        vector<int> subRow;
        for (int j = 0; j < 4; j++)
        {
            if (exponentBoard[i][j] != 0)
            {
                subRow.push_back(exponentBoard[i][j]);
                exponentBoard[i][j] = 0;
            }
        }
        int sizeOfSubrow = subRow.size();
        for (int j = 0; j < sizeOfSubrow; j++)
        {
            exponentBoard[i][j] = subRow[j];
        }
    }
}

void rightMove(){
    // Move
    for (int i = 0; i < 4; i++)
    {
        vector<int> subRow;
        for (int j = 3; j >= 0; j--)
        {
            if (exponentBoard[i][j] != 0)
            {
                subRow.push_back(exponentBoard[i][j]);
                exponentBoard[i][j] = 0;
            }
        }
        int sizeOfSubrow = subRow.size();
        for (int j = 3; j >= 4 - sizeOfSubrow; j--)
        {
            exponentBoard[i][j] = subRow[3 - j];
        }
    }
    // Merge
    for (int i = 0; i < 4; i++)
    {
        for (int j = 3; j >= 0;)
        {
            if (exponentBoard[i][j] == exponentBoard[i][j - 1] && exponentBoard[i][j] != 0)
            {
                exponentBoard[i][j] += 1;
                int score = exponentBoard[i][j];
                currentScore += pow(2, score);
                exponentBoard[i][j - 1] = 0;
                j -= 2;
            }
            else
                j--;
        }
    }
    // Move
    for (int i = 0; i < 4; i++)
    {
        vector<int> subRow;
        for (int j = 3; j >= 0; j--)
        {
            if (exponentBoard[i][j] != 0)
            {
                subRow.push_back(exponentBoard[i][j]);
                exponentBoard[i][j] = 0;
            }
        }
        int sizeOfSubrow = subRow.size();
        for (int j = 3; j >= 4 - sizeOfSubrow; j--)
        {
            exponentBoard[i][j] = subRow[3 - j];
        }
    }
}

bool hasValidMove(){
    // Check row move
    for (int i = 0; i < 4; i++)
    {
        for (int j = 1; j < 3; j++)
        {
            if (exponentBoard[i][j] == exponentBoard[i][j - 1] || exponentBoard[i][j] == exponentBoard[i][j + 1])
                return true;
        }
    }
    // Check col move
    for (int i = 1; i < 3; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (exponentBoard[i][j] == exponentBoard[i - 1][j] || exponentBoard[i][j] == exponentBoard[i + 1][j])
                return true;
        }
    }
    return false;
}

bool gameIsOver(){
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (exponentBoard[i][j] == 0)
                return false;
        }
    }
    if (hasValidMove())
        return false;
    return true;
}

bool successful(int limit){
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (surfaceBoard[i][j] == limit)
            {
                return true;
            }
        }
    }
    return false;
}





#endif
