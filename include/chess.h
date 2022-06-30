#pragma once

#include "graphics.h"
#include <vector>

using namespace std;

struct ChessPos
{
    int row;
    int col;
    ChessPos () {}
    ChessPos (int r, int c) : row (r), col (c) {}
};

enum chess_kind_t
{
    CHESS_WHITHE = -1,
    CHESS_BLACK = 1
};

class Chess
{

  private:
    IMAGE chessBlackImg;
    IMAGE chessWhiteImg;

    int   gradeSize; // board size (13,15,17,19)
    int   margin_x;  // horizontal margin
    int   margin_y;  // vertical margin
    float chessSize; // size of chess

    // map    0: null 1: black -1: white
    vector<vector<int>> chessMap;
    bool                playerFlag; // true: black false: white

  public:
    ChessPos lastPos; // lateset chess position

  public:
    Chess (int gradesize, int marginX, int marginY, float chesssize);

  public:
    void init ();
    bool clickBoard (int x, int y, ChessPos *pos);
    void chessDown (ChessPos *pos, chess_kind_t kind);
    // get the size of board
    int  getGradeSize ();
    bool checkOver ();
    void updateGameMap (ChessPos *pos);
    int  getChessData (int row, int col);

  private:
    bool checkWin ();

  public:
    void printMap ();
};
