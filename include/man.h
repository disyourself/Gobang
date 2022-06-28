#pragma once

#include "./chess.h"

class Man
{
  private:
    Chess *chess;

  public:
    void init (Chess *chess);
    void go ();
};