#include "../include/AI.h"
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <wingdi.h>

void
AI::init (Chess *chess)
{
    this->chess = chess;

    int size = chess->getGradeSize ();
    for (int i = 0; i < size; i++)
    {
        vector<int> row (size, 0);
        scoreMap.push_back (row);
    }
}

void
AI::go ()
{
    ChessPos pos = think ();
    chess->chessDown (&pos, CHESS_WHITHE);
}


/**
 * @brief BUG HERE!!!
 * something wrong with weight calculate method
 */
void
AI::calculateScore ()
{
    int personNum = 0; // player(BLACK)'s adjancent chess;
    int aiNum = 0;     // AI(White)'s adjacent chess;
    int emptyNum = 0;  // empty num of that direction

    for (auto &i : scoreMap)
        for (int &j : i)
            j = 0;

    int size = scoreMap.size ();

    // TODO: update calculate weight algorithme
    for (int row = 0; row < scoreMap.size (); ++row)
        for (int col = 0; col < scoreMap.size (); ++col)
        {
            // caculate every point
            if (chess->getChessData (row, col) != 0)
                continue;

            // 8 directions
            for (int y = -1; y <= 0; y++)
                for (int x = -1; x < 1; x++)
                {


                    // init
                    aiNum = 0;
                    personNum = 0;
                    emptyNum = 0;

                    if (y == 0 && x == 0)
                        continue;
                    if (y == 0 && x != 0)
                        continue;

                    // Assume Black at this pos
                    // Forwad
                    for (int i = 1; i <= 4; i++)
                    {
                        int curRow = row + i * y;
                        int curCol = col + i * x;

                        if (curRow >= 0 && curRow < size
                            && curCol >= 0 && curCol < size)
                        {
                            if (chess->getChessData (curRow, curCol) == 1)
                                personNum++;
                            else if (chess->getChessData (curRow, curCol) == 0)
                            {
                                ++emptyNum;
                                break;
                            }
                            else
                                break;
                        }
                    }
                    // Reversed
                    for (int i = 1; i <= 4; i++)
                    {
                        int curRow = row - i * y;
                        int curCol = col - i * x;

                        if (curRow >= 0 && curRow < size
                            && curCol >= 0 && curCol < size)
                        {
                            if (chess->getChessData (curRow, curCol) == 1)
                                personNum++;
                            else if (chess->getChessData (curRow, curCol) == 0)
                            {
                                ++emptyNum;
                                break;
                            }
                            else
                                break;
                        }
                    }
                    // Scores
                    if (personNum == 1)
                        scoreMap[row][col] += 10;
                    else if (personNum == 2)
                    {
                        // dead 3
                        if (emptyNum == 1)
                        {
                            scoreMap[row][col] += 30;
                        }
                        // live 3
                        else if (emptyNum == 2)
                        {
                            scoreMap[row][col] += 40;
                        }
                    }
                    else if (personNum == 3)
                    {
                        // dead 4
                        if (emptyNum == 1)
                            scoreMap[row][col] += 300;
                        // live 4
                        else if (emptyNum == 2)
                            scoreMap[row][col] += 500;
                    }
                    else if (personNum >= 4)
                    {
                        scoreMap[row][col] += 25000;
                    }


                    // Asumme white
                    emptyNum = 0;
                    // Forwad
                    for (int i = 1; i <= 4; i++)
                    {
                        int curRow = row + i * y;
                        int curCol = col + i * x;

                        if (curRow >= 0 && curRow < size
                            && curCol >= 0 && curCol < size)
                        {
                            if (chess->getChessData (curRow, curCol) == -1)
                                ++aiNum;
                            else if (chess->getChessData (curRow, curCol) == 0)
                            {
                                ++emptyNum;
                                break;
                            }
                            else
                                break;
                        }
                    }
                    // Reversed
                    for (int i = 1; i <= 4; i++)
                    {
                        int curRow = row - i * y;
                        int curCol = col - i * x;

                        if (curRow >= 0 && curRow < size
                            && curCol >= 0 && curCol < size)
                        {
                            if (chess->getChessData (curRow, curCol) == -1)
                                aiNum++;
                            else if (chess->getChessData (curRow, curCol) == 0)
                            {
                                ++emptyNum;
                                break;
                            }
                            else
                                break;
                        }
                    }
                    // Scores
                    if (aiNum == 0)
                    {
                        scoreMap[row][col] += 5;
                    }
                    else if (aiNum == 1)
                        scoreMap[row][col] += 20;
                    else if (aiNum == 2)
                    {
                        // dead 3
                        if (emptyNum == 1)
                        {
                            scoreMap[row][col] += 30;
                        }
                        // live 3
                        else if (emptyNum == 2)
                        {
                            scoreMap[row][col] += 100;
                        }
                    }
                    else if (aiNum == 3)
                    {
                        // dead 4
                        if (emptyNum == 1)
                            scoreMap[row][col] += 60;
                        // live 4
                        else if (emptyNum == 2)
                            scoreMap[row][col] += 10000;
                    }
                    else if (aiNum >= 4)
                    {
                        scoreMap[row][col] += 30000;
                    }
                }
        }
}

ChessPos
AI::think ()
{
    this->calculateScore ();

    vector<ChessPos> maxPoints;

    int max = 0;

    int size = chess->getGradeSize ();

    for (int row = 0; row < size; row++)
        for (int col = 0; col < size; ++col)
            if (chess->getChessData (row, col) == 0)
            {
                if (scoreMap[row][col] > max)
                {
                    max = scoreMap[row][col];
                    maxPoints.clear ();
                    maxPoints.push_back (ChessPos (row, col));
                }
                else if (scoreMap[row][col] == max)
                {
                    maxPoints.push_back (ChessPos (row, col));
                }
            }

    int index = rand () % maxPoints.size ();


    return maxPoints[index];
}
