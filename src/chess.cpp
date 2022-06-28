#include "../include/chess.h"
#include "mmsystem.h"
#include <winuser.h>


Chess::Chess (int gradesize, int marginX, int marginY, float chesssize)
    : gradeSize (gradesize), margin_x (marginX),
      margin_y (marginY), chessSize (chesssize)
{
    this->playerFlag = CHESS_BLACK;

    for (int i = 0; i < gradesize; ++i)
    {
        vector<int> row (gradesize, 0);
        chessMap.push_back (row);
    }
}

void
Chess::init ()
{
    // Crate game window
    initgraph (897, 895);

    loadimage (0, "../res/∆Â≈Ã2.jpg");

    // bgm
    mciSendString ("play ../res/start.wav", 0, 0, 0);

    // the image of chess
    loadimage (&chessBlackImg, "../res/black.png", chessSize, chessSize, true);
    loadimage (&chessWhiteImg, "../res/white.png", chessSize, chessSize, true);

    // reset chess board to zero
    for (auto &i : chessMap)
        for (auto &j : i)
            j = 0;

    // player flag
    playerFlag = true;
}

bool
Chess::clickBoard (int x, int y, ChessPos *pos)
{

    return false;
}

void
Chess::chessDown (ChessPos *pos, chess_kind_t kind)
{
}

int
Chess::getGradeSize ()
{
    return 0;
}

bool
Chess::checkOver ()
{
    return false;
}