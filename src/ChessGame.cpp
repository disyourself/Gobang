#include "../include/ChessGame.h"
#include <conio.h>
#include <iostream>
#include <stdlib.h>
ChessGame::ChessGame (Man *man, AI *ai, Chess *chess)
{
    this->man = man;
    this->ai = ai;
    this->chess = chess;

    man->init (chess);
    ai->init (chess);
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

        if (_kbhit ())
            if (_getch () == 'q')
                exit (0);
    }
}