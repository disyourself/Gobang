/**
 * @file main.cpp
 * @author disyourself@qq.com
 * @brief  Gobang
 * @version 0.1
 * @date 2022-06-28

  Development Log:
    1. import resources
    2. design the frame (classes that need)

 * @copyright Copyright (c) 2022
 *
 */

#include "./include/ChessGame.h"

int
main (int argc, char **argv)
{
    Chess chess (13, 44, 43, 67.3);
    Man   man;
    AI    ai;

    ChessGame game (&man, &ai, &chess);

    game.play ();

    return 0;
}
