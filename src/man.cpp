#include "../include/man.h"

void
Man::init (Chess *chess)
{
    this->chess = chess;
}

void
Man::go ()
{
    MOUSEMSG msg;
    ChessPos pos;

    // check pos valid && stepping by call chess object
    while (1)
    {
        msg = GetMouseMsg ();
        if (msg.uMsg == WM_LBUTTONDOWN && chess->clickBoard (msg.x, msg.y, &pos))
            break;
    }

    chess->chessDown (&pos, CHESS_BLACK);
}
