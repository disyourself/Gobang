#include "../include/chess.h"
#include "mmsystem.h"
#include <cmath>
#include <iostream>
#include <winuser.h>


void
putimagePNG (int picture_x, int picture_y, IMAGE *picture)
{
    // get video memory ptr of draw device
    DWORD *dst = GetImageBuffer ();
    DWORD *draw = GetImageBuffer ();
    // get picture's mermory ptr
    DWORD *src = GetImageBuffer (picture);

    int picture_width = picture->getwidth ();
    int picture_height = picture->getheight ();
    int graphWidth = getwidth ();
    int graphHeight = getheight ();
    int dstX = 0;

    // implenment map transparent; Bayes (±¥“∂Àπ) theorem; formula: Cp = ao*FP+(1-ap)*BP
    for (int iy = 0; iy < picture_height; iy++)
    {
        for (int ix = 0; ix < picture_width; ix++)
        {
            int srcX = ix + iy * picture_width;        // conner mark of pic in memroy
            int sa = ((src[srcX] & 0xff000000) >> 24); // 0XAArrggbb; AA: transparence
            int sr = ((src[srcX] & 0xff0000) >> 16);   // get the R of RGB
            int sg = ((src[srcX] & 0xff00) >> 8);      // G
            int sb = src[srcX] & 0xff;                 // B
            if (ix >= 0 && ix <= graphWidth && iy >= 0 && iy <= graphHeight && dstX <= graphWidth * graphHeight)
            {
                dstX = (ix + picture_x) + (iy + picture_y) * graphWidth;
                int dr = ((dst[dstX] & 0xff0000) >> 16);
                int dg = ((dst[dstX] & 0xff00) >> 8);
                int db = dst[dstX] & 0xff;

                draw[dstX] = ((sr * sa / 255 + dr * (255 - sa) / 255) << 16)
                             | ((sg * sa / 255 + dg * (255 - sa) / 255) << 8)
                             | (sb * sa / 255 + db * (255 - sa) / 255);
            }
        }
    }
}


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

    loadimage (nullptr, "../res/∆Â≈Ã2.jpg");

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

    bool ret = false;

    // check the distance of 4 conners of one block area
    int col = (x - margin_x) / chessSize;
    int row = (y - margin_y) / chessSize;
    int leftTopPosX = margin_x + chessSize * col;
    int leftTopPosY = margin_y + chessSize * row;
    int offset = chessSize * 0.4;

    int len;

    do // left top conner
    {
        len = sqrtf (powf ((x - leftTopPosX), 2) + powf ((y - leftTopPosY), 2));

        if (len < offset)
        {
            pos->row = row;
            pos->col = col;
            if (chessMap[pos->row][pos->col] == 0)
                ret = true;
            break;
        }
    } while (0);

    do // right top conner
    {

        int x2 = leftTopPosX + chessSize;
        int y2 = leftTopPosY + chessSize;

        len = sqrtf (powf ((x - x2), 2) + powf ((y - y2), 2));

        if (len < offset)
        {
            pos->row = row;
            pos->col = col + 1;
            if (chessMap[pos->row][pos->col] == 0)
                ret = true;
            break;
        }
    } while (0);

    do // right top conner
    {

        int x2 = leftTopPosX + chessSize;
        int y2 = leftTopPosY;

        len = sqrtf (powf ((x - x2), 2) + powf ((y - y2), 2));

        if (len < offset)
        {
            pos->row = row;
            pos->col = col + 1;
            if (chessMap[pos->row][pos->col] == 0)
                ret = true;
            break;
        }
    } while (0);


    do // left botttom conner
    {

        int x2 = leftTopPosX;
        int y2 = leftTopPosY + chessSize;

        len = sqrtf (powf ((x - x2), 2) + powf ((y - y2), 2));

        if (len < offset)
        {
            pos->row = row + 1;
            pos->col = col;
            if (chessMap[pos->row][pos->col] == 0)
                ret = true;
            break;
        }
    } while (0);

    do // right bottom conner
    {

        int x2 = leftTopPosX + chessSize;
        int y2 = leftTopPosY + chessSize;

        len = sqrtf (powf ((x - x2), 2) + powf ((y - y2), 2));

        if (len < offset)
        {
            pos->row = row + 1;
            pos->col = col + 1;
            if (chessMap[pos->row][pos->col] == 0)
                ret = true;
            break;
        }
    } while (0);


    return ret;
}

void
Chess::chessDown (ChessPos *pos, chess_kind_t kind)
{
    int x = margin_x + chessSize * pos->col - chessSize / 2;
    int y = margin_x + chessSize * pos->row - chessSize / 2;

    if (kind == CHESS_WHITHE)
        putimagePNG (x, y, &chessWhiteImg);
    else
        putimagePNG (x, y, &chessBlackImg);

    updateGameMap (pos);

    printMap ();
}

int
Chess::getGradeSize ()
{
    return this->gradeSize;
}

bool
Chess::checkOver ()
{
    return false;
}

void
Chess::printMap ()
{
    for (auto &i : this->chessMap)
    {
        for (auto &j : i)
            cout << j << " ";
        cout << endl;
    }
}

void
Chess::updateGameMap (ChessPos *pos)
{
    chessMap[pos->row][pos->col] = playerFlag ? CHESS_BLACK : CHESS_WHITHE;
    playerFlag = !playerFlag;
}

int
Chess::getChessData (int row, int col)
{
    return chessMap[row][col];
}