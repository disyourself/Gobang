#pragma once

#include "./AI.h"
#include "./chess.h"
#include "./man.h"

class ChessGame
{
  private:
    Man   *man;
    AI    *ai;
    Chess *chess;

  public:
    ChessGame (Man *man, AI *ai, Chess *chess);

    void play ();
};