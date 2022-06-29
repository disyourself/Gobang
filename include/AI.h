#pragma once

#include "./chess.h"
#include <vector>

class AI
{

  private:
    Chess              *chess;
    vector<vector<int>> scoreMap;

  public:
    void init (Chess *chess);

    void go ();


  private:
    void     calculateScore ();
    ChessPos think ();
};