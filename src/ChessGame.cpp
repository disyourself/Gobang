#include "../include/ChessGame.h"
#include <wincontypes.h>

ChessGame::ChessGame (Man *man, AI *ai, Chess *chess)
{
    this->man = man;
    this->ai = ai;
    this->chess = chess;

    man->init (chess);
}

void
ChessGame::play ()
{
    chess->init ();
    while (1)
    {
        // chesser go
        man->go ();
        if (chess->checkOver ())
        {
            chess->init ();
            continue;
        }

        ai->go ();
        if (chess->checkOver ())
        {
            chess->init ();
            continue;
        }
    }
}