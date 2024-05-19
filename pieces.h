#pragma once

#include<iostream>
using namespace std;
struct History
{ // will be used to rewind the moves
    int prevX, prevY, newX, newY;
    int prevNum, newNum;
    History(int _prevX, int _prevY, int _newX, int _newY, int _prevNum, int _newNum) : prevX(_prevX), prevY(_prevY), newX(_newX), newY(_newY), prevNum(_prevNum), newNum(_newNum) {}
};

class pieces
{
protected:
    bool side = 0; // 0 for white, 1 for black
    int type = 0;  // 1 for pawn, 2 for rook, 3 for knight, 4 for bishop, 5 for queen, 6 for king

public:
    pieces(bool side, int type)
    {
        this->side = side;
        this->type = type;
    }
    virtual int fillBoard(int x, int y, int chessBoard[8][8], int colorBoard[8][8], int OppositeColorBoard[8][8]) = 0; // will return the highest number on board

    virtual void showMoves(int x, int y, int chessBoard[8][8], bool checkBoard[8][8], int colorBoard[8][8], int OppositeColorBoard[8][8], bool isKingUnderCheck) = 0;

    virtual bool makeMove(int x, int y, int& prevX, int& prevY, int chessBoard[8][8], bool checkBoard[8][8], int whiteBoard[8][8], int blackBoard[8][8])
    {
        if (x < 8 && y < 8 && x >= 0 && y >= 0 && checkBoard[x][y])
        {
            chessBoard[x][y] = chessBoard[prevX][prevY];
            chessBoard[prevX][prevY] = 0;
            // prevX = x;
            // prevY = y;
            return true;
        }
        return false;
    }
};

enum
{
    white,
    black,
    wpawn = 1,
    wrook = 2,
    wknight = 3,
    wbishop = 4,
    wqueen = 5,
    wking = 6,
    bpawn = 7,
    brook = 8,
    bknight = 9,
    bbishop = 10,
    bqueen = 11,
    bking = 12
};

class king : public pieces
{
public:
    king(bool side) : pieces(side, 6) {};

    int fillBoard(int x, int y, int chessBoard[8][8], int colorBoard[8][8], int OppositeColorBoard[8][8])
    {
        for (int i = x - 1; i < x + 2; i++)
        {
            for (int j = y - 1; j < y + 2; j++)
            {
                if (i < 8 && i >= 0 && j < 8 && j >= 0 && (!OppositeColorBoard[i][j]))/*|| OppositeColorBoard[i][j] == 2))*/
                {
                    if (!colorBoard[i][j] && (!chessBoard[i][j] || (side ? chessBoard[i][j] < 7 : chessBoard[i][j] > 6)))/* || !chessBoard[i][j]))*/
                    {
                        colorBoard[i][j] = 1;
                    }
                }
                else if (i < 8 && i >= 0 && j < 8 && j >= 0 && OppositeColorBoard[i][j] == 2) {
                    if (!colorBoard[i][j] && chessBoard[i][j] && ((side ? chessBoard[i][j] < 7 : chessBoard[i][j] > 6)))
                    {
                        colorBoard[i][j] = 1;
                    }
                }
            }
        }
        int max = 0;
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if (colorBoard[i][j] > max) {
                    max = colorBoard[i][j];
                }
            }
        }
        return max;
    }

    void showMoves(int x, int y, int chessBoard[8][8], bool checkBoard[8][8], int colorBoard[8][8], int OppositeColorBoard[8][8], bool isKingUnderCheck)
    {
        for (int i = -1; i < 2; i++)
        {
            for (int j = -1; j <= 1; j++)
            {
                if (!isKingUnderCheck)
                {
                    if (x + i > 8 || x + i < 0 || y + j > 8 || y + j < 0 || (OppositeColorBoard[x + i][y + j] == 2 /*&& !chessBoard[x + i][y + j]*/) || OppositeColorBoard[x + i][y + j] == 1) // if the move is out of bounds or the location is already covered
                    {
                        continue;
                    }
                    if (chessBoard[x + i][y + j] == 0)
                    {
                        checkBoard[x + i][y + j] = 1;
                    }
                    else if (chessBoard[x + i][y + j] > 6 && !side)
                    {
                        checkBoard[x + i][y + j] = 1;
                    }
                    else if (chessBoard[x + i][y + j] < 7 && side)
                    {
                        checkBoard[x + i][y + j] = 1;
                    }
                }
                else
                {
                    if (x + i > 8 || x + i < 0 || y + j > 8 || y + j < 0) {
                        continue;
                    }
                    if (chessBoard[x + i][y + j] == 0 && OppositeColorBoard[x + i][y + j] == 0)
                    {
                        checkBoard[x + i][y + j] = 1;
                    }
                    if (OppositeColorBoard[x + i][y + j] == 2 && chessBoard[x + i][y + j] && ((side ? chessBoard[x + i][y + j] < 7 : chessBoard[x + i][y + j] > 6)))
                    {
                        checkBoard[x + i][y + j] = 1;
                    }
                    else if (OppositeColorBoard[x + i][y + j] == 0 && !chessBoard[x + i][y + j])
                    {
                        checkBoard[x + i][y + j] = 1;
                    }
                }
            }
        }
    }
};

class queen : public pieces
{
public:
    queen(bool side) : pieces(side, 5) {};

    int fillBoard(int x, int y, int chessBoard[8][8], int colorBoard[8][8], int OppositeColorBoard[8][8])
    {
        int max = 0;
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if (colorBoard[i][j] > max) {
                    max = colorBoard[i][j];
                }
            }
        }
        if (OppositeColorBoard[x][y] == 2) {
            return max;
        }
        bool skipped = false;
        for (int i = 1; x + i < 8 && y + i < 8; i++)
        {
            if (chessBoard[x + i][y + i] == 0 && !skipped)
            {
                if (!colorBoard[x + i][y + i])
                {
                    colorBoard[x + i][y + i] = 1;
                }
            }
            else if (side && chessBoard[x + i][y + i] > 6 && !skipped || !side && chessBoard[x + i][y + i] < 7 && !skipped)
            {
                if (!colorBoard[x + i][y + i])
                {
                    colorBoard[x + i][y + i] = 1; // marks covered piece down right
                }
                skipped = true;
                break;
            }
            else if (side && chessBoard[x + i][y + i] == 6 || !side && chessBoard[x + i][y + i] == 12)
            {
                for (int j = x, k = y; j < x + i && k < y + i; j++, k++)
                {
                    colorBoard[j][k] = 2;
                }
                if (!skipped)
                {
                    colorBoard[x][y] = 2;         // marks the piece itself as for releasing check
                    colorBoard[x + i][y + i] = 3; // marks the king under check
                    for (int k = x + i + 1, l = y + i + 1; k < 8 && l < 8; k++, l++) {
                        colorBoard[k][l] = 1;
                    }
                }
                break;
            }
            else if (!skipped && (side && chessBoard[x + i][y + i] < 7 || !side && chessBoard[x + i][y + i] > 6))
            {
                if (!colorBoard[x + i][y + i])
                {
                    colorBoard[x + i][y + i] = 1; // marks pinned piece down right
                }
                skipped = true;
            }
            else if (skipped && (side && chessBoard[x + i][y + i] < 7 || !side && chessBoard[x + i][y + i] > 6)) {
                break;
            }

        }

        skipped = false;
        for (int i = 1; x - i >= 0 && y - i >= 0; i++)
        {
            if (chessBoard[x - i][y - i] == 0 && !skipped)
            {
                if (!colorBoard[x - i][y - i])
                {
                    colorBoard[x - i][y - i] = 1;
                }
            }
            else if (side && chessBoard[x - i][y - i] > 6 && !skipped || !side && chessBoard[x - i][y - i] < 7 && !skipped)
            {
                if (!colorBoard[x - i][y - i])
                {
                    colorBoard[x - i][y - i] = 1; // marks covered piece up left
                }
                skipped = true;
                break;
            }
            else if (side && chessBoard[x - i][y - i] == 6 || !side && chessBoard[x - i][y - i] == 12)
            {
                for (int j = x, k = y; j > x - i && k > y - i; j--, k--)
                {
                    colorBoard[j][k] = 2;
                }
                if (!skipped)
                {
                    colorBoard[x][y] = 2;         // marks the piece itself as for releasing check
                    colorBoard[x - i][y - i] = 3; // marks the king under check
                    for (int k = x - i - 1, l = y - i - 1; k >= 0 && l >= 0; k--, l--) {
                        colorBoard[k][l] = 1;
                    }
                }
                break;
            }
            else if (!skipped && (side && chessBoard[x - i][y - i] < 7 || !side && chessBoard[x - i][y - i] > 6))
            {
                if (!colorBoard[x - i][y - i])
                {
                    colorBoard[x - i][y - i] = 1; // marks pinned piece up left
                }
                skipped = true;
            }
            else if (skipped && (side && chessBoard[x - i][y - i] < 7 || !side && chessBoard[x - i][y - i] > 6)) {
                break;
            }
        }

        skipped = false;
        for (int i = 1; x + i < 8 && y - i >= 0; i++)
        {
            if (chessBoard[x + i][y - i] == 0 && !skipped)
            {
                if (!colorBoard[x + i][y - i])
                {
                    colorBoard[x + i][y - i] = 1;
                }
            }
            else if (side && chessBoard[x + i][y - i] > 6 && !skipped || !side && chessBoard[x + i][y - i] < 7 && !skipped)
            {
                if (!colorBoard[x + i][y - i])
                {
                    colorBoard[x + i][y - i] = 1; // marks covered piece down left
                }
                skipped = true;
                break;
            }
            else if (side && chessBoard[x + i][y - i] == 6 || !side && chessBoard[x + i][y - i] == 12)
            {
                for (int j = x, k = y; j < x + i && k > y - i; j++, k--)
                {
                    colorBoard[j][k] = 2;
                }
                if (!skipped)
                {
                    colorBoard[x][y] = 2;         // marks the piece itself as for releasing check
                    colorBoard[x + i][y - i] = 3; // marks the king under check
                    for (int k = x + i + 1, l = y - i - 1; k < 8 && l >= 0; k++, l--) {
                        colorBoard[k][l] = 1;
                    }
                }
                break;
            }
            else if (!skipped && (side && chessBoard[x + i][y - i] < 7 || !side && chessBoard[x + i][y - i] > 6))
            {
                if (!colorBoard[x + i][y - i])
                {
                    colorBoard[x + i][y - i] = 1; // marks pinned piece down left
                }
                skipped = true;
            }
            else if (skipped && (side && chessBoard[x + i][y - i] < 7 || !side && chessBoard[x + i][y - i] > 6)) {
                break;
            }
        }

        skipped = false;
        for (int i = 1; x - i >= 0 && y + i < 8; i++)
        {
            if (chessBoard[x - i][y + i] == 0 && !skipped)
            {
                if (!colorBoard[x - i][y + i])
                {
                    colorBoard[x - i][y + i] = 1;
                }
            }
            else if (side && chessBoard[x - i][y + i] > 6 && !skipped || !side && chessBoard[x - i][y + i] < 7 && !skipped)
            {
                if (!colorBoard[x - i][y + i])
                {
                    colorBoard[x - i][y + i] = 1; // marks covered piece up right
                }
                skipped = true;
                break;
            }
            else if (side && chessBoard[x - i][y + i] == 6 || !side && chessBoard[x - i][y + i] == 12)
            {
                for (int j = x, k = y; j > x - i && k < y + i; j--, k++)
                {
                    colorBoard[j][k] = 2;
                }
                if (!skipped)
                {
                    colorBoard[x][y] = 2;         // marks the piece itself as for releasing check
                    colorBoard[x - i][y + i] = 3; // marks the king under check
                    for (int k = x - i - 1, l = y + i + 1; k >= 0 && l < 8; k--, l++) {
                        colorBoard[k][l] = 1;
                    }
                }
                break;
            }
            else if (!skipped && (side && chessBoard[x - i][y + i] < 7 || !side && chessBoard[x - i][y + i] > 6))
            {
                if (!colorBoard[x - i][y + i])
                {
                    colorBoard[x - i][y + i] = 1; // marks pinned piece up right
                }
                skipped = true;
            }
            else if (skipped && (side && chessBoard[x - i][y + i] < 7 || !side && chessBoard[x - i][y + i] > 6)) {
                break;
            }
        }

        skipped = false;
        for (int i = 1; x + i < 8; i++)
        {
            if (!skipped && chessBoard[x + i][y] == 0)
            {
                if (!colorBoard[x + i][y])
                {
                    colorBoard[x + i][y] = 1;
                }
            }
            else if (!skipped && (side && chessBoard[x + i][y] > 6 || !side && chessBoard[x + i][y] < 7))
            {
                if (!colorBoard[x + i][y])
                {
                    colorBoard[x + i][y] = 1; // marks covered Piece down
                }
                skipped = true;
                break;
            }
            else if ((side && chessBoard[x + i][y] == 6 || !side && chessBoard[x + i][y] == 12))
            {
                for (int j = x; j <= x + i; j++)
                {
                    colorBoard[j][y] = 2; // marks pinned piece within king
                }
                if (!skipped)
                {
                    colorBoard[x + i][y] = 3;
                    colorBoard[x][y] = 2;
                    for (int k = x + i + 1; k < 8; k++)
                    {
                        colorBoard[k][y] = 1;
                    }
                }
                break;
            }
            else if (!skipped && (side && chessBoard[x + i][y] < 7 || !side && chessBoard[x + i][y] > 6))
            {
                if (!colorBoard[x + i][y])
                {
                    colorBoard[x + i][y] = 1; // marks location in case if the piece is pinned
                }
                skipped = true;
            }
            else if (skipped && (side && chessBoard[x + i][y] < 7 || !side && chessBoard[x + i][y] > 6)) {
                break;
            }
        }

        skipped = false;
        for (int i = 1; x - i >= 0; i++)
        {
            if (!skipped && chessBoard[x - i][y] == 0)
            {
                if (!colorBoard[x - i][y])
                {
                    colorBoard[x - i][y] = 1;
                }
            }
            else if (!skipped && (side && chessBoard[x - i][y] > 6 || !side && chessBoard[x - i][y] < 7))
            {
                if (!colorBoard[x - i][y])
                {
                    colorBoard[x - i][y] = 1; // marks covered Piece up
                }
                skipped = true;
                break;
            }
            else if ((side && chessBoard[x - i][y] == 6 || !side && chessBoard[x - i][y] == 12))
            {
                for (int j = x; j >= x - i; j--)
                {
                    colorBoard[j][y] = 2; // marks pinned piece within king
                }
                if (!skipped)
                {
                    colorBoard[x - i][y] = 3;
                    colorBoard[x][y] = 2;
                    for (int k = x - i - 1; k >= 0; k--)
                    {
                        colorBoard[k][y] = 1;
                    }
                }
                break;
            }
            else if (!skipped && (side && chessBoard[x - i][y] < 7 || !side && chessBoard[x - i][y] > 6))
            {
                if (!colorBoard[x - i][y])
                {
                    colorBoard[x - i][y] = 1; // marks location in case if the piece is pinned
                }
                skipped = true;
            }
            else if (skipped && (side && (side && chessBoard[x - i][y] < 7 || !side && chessBoard[x - i][y] > 6))) {
                break;
            }
        }

        skipped = false;
        for (int i = 1; y + i < 8; i++)
        {
            if (!skipped && chessBoard[x][y + i] == 0)
            {
                if (!colorBoard[x][y + i])
                {
                    colorBoard[x][y + i] = 1;
                }
            }
            else if (!skipped && (side && chessBoard[x][y + i] > 6 || !side && chessBoard[x][y + i] < 7))
            {
                if (!colorBoard[x][y + i])
                {
                    colorBoard[x][y + i] = 1; // marks covered Piece right
                }
                skipped = true;
                break;
            }
            else if ((side && chessBoard[x][y + i] == 6 || !side && chessBoard[x][y + i] == 12))
            {
                for (int j = y; j <= y + i; j++)
                {
                    colorBoard[x][j] = 2; // marks pinned piece within king
                }
                if (!skipped)
                {
                    colorBoard[x][y + i] = 3;
                    colorBoard[x][y] = 2;
                    for (int k = y + i + 1; k < 8; k++)
                    {
                        colorBoard[x][k] = 1;
                    }
                }
                break;
            }
            else if (!skipped && (side && chessBoard[x][y + i] < 7 || !side && chessBoard[x][y + i] > 6))
            {
                if (!colorBoard[x][y + i])
                {
                    colorBoard[x][y + i] = 1; // marks location in case if the piece is pinned
                }
                skipped = true;
            }
            else if (skipped && (side && chessBoard[x][y + i] < 7 || !side && chessBoard[x][y + i] > 6)) {
                break;
            }
        }

        skipped = false;
        for (int i = 1; y - i >= 0; i++)
        {
            if (!skipped && chessBoard[x][y - i] == 0)
            {
                if (!colorBoard[x][y - i])
                {
                    colorBoard[x][y - i] = 1;
                }
            }
            else if (!skipped && (side && chessBoard[x][y - i] > 6 || !side && chessBoard[x][y - i] < 7))
            {
                if (!colorBoard[x][y - i])
                {
                    colorBoard[x][y - i] = 1; // marks covered Piece left
                }
                skipped = true;
                break;
            }
            else if ((side && chessBoard[x][y - i] == 6 || !side && chessBoard[x][y - i] == 12))
            {
                for (int j = y; j >= y - i; j--)
                {
                    colorBoard[x][j] = 2; // marks pinned piece within king
                }
                if (!skipped)
                {
                    colorBoard[x][y - i] = 3;
                    colorBoard[x][y] = 2;
                    for (int k = y - i - 1; k >= 0; k--)
                    {
                        colorBoard[x][k] = 1;
                    }
                }
                break;
            }
            else if (!skipped && (side && chessBoard[x][y - i] < 7 || !side && chessBoard[x][y - i] > 6))
            {
                if (!colorBoard[x][y - i])
                {
                    colorBoard[x][y - i] = 1; // marks location in case if the piece is pinned
                }
                skipped = true;
            }
            else if (skipped && (side && chessBoard[x][y - i] < 7 || !side && chessBoard[x][y - i] > 6)) {
                break;
            }
        }

        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                if (colorBoard[i][j] > max)
                {
                    max = colorBoard[i][j];
                }
            }
        }

        return max;
    }

    void showMoves(int x, int y, int chessBoard[8][8], bool checkBoard[8][8], int colorBoard[8][8], int OppositeColorBoard[8][8], bool isKingUnderCheck)
    {
        isKingUnderCheck = (isKingUnderCheck || (OppositeColorBoard[x][y] == 2)); // if the piece is pinned treats it as if the king is under check
        bool diagonal = true, straight = true, cont = true, contStraight = true;
        for (int i = 1; i + x < 8; i++)
        {                                                                                                                                                                         // move down and down right
            if (isKingUnderCheck && contStraight && OppositeColorBoard[i + x][y] == 2 && (!chessBoard[i + x][y] || (side ? chessBoard[i + x][y] < 7 : chessBoard[i + x][y] > 6))) // if the king is under check move the boxes which eliminate check
            {
                checkBoard[i + x][y] = 1;
                if (chessBoard[i + x][y])
                {
                    contStraight = false;
                }
            }
            else if (isKingUnderCheck && contStraight && chessBoard[i + x][y] && OppositeColorBoard[i + x][y] == 2)
            {
                contStraight = false;
            }
            if (isKingUnderCheck && cont && y - i >= 0 && OppositeColorBoard[i + x][y - i] == 2 && (!chessBoard[i + x][y - i] || (side ? chessBoard[i + x][y - i] < 7 : chessBoard[i + x][y - i] > 6)))
            {
                checkBoard[i + x][y + i] = 1;
                if (chessBoard[i + x][y - i])
                {
                    cont = false;
                }
            }
            else if (isKingUnderCheck && cont && chessBoard[i + x][y - i] && OppositeColorBoard[i + x][y - i] == 2)
            {
                cont = false;
            }
            else if (isKingUnderCheck && (OppositeColorBoard[i + x][y] != 2 || OppositeColorBoard[i + x][y - i] != 2))
            {
                continue;
            }
            else if (chessBoard[i + x][y] == 0 && straight) // movements if the king is not under check
            {
                checkBoard[i + x][y] = 1;
            }
            else if (chessBoard[i + x][y] > 6 && !side && straight)
            {
                checkBoard[i + x][y] = 1;
                straight = false;
            }
            else if (chessBoard[i + x][y] < 7 && side && straight)
            {
                checkBoard[i + x][y] = 1;
                straight = false;
            }
            else
            {
                straight = false;
            }

            if (!isKingUnderCheck && i + y < 8)
            {
                if (chessBoard[i + x][i + y] == 0 && diagonal)
                {
                    checkBoard[i + x][i + y] = 1;
                }
                else if (chessBoard[i + x][i + y] > 6 && !side && diagonal)
                {
                    checkBoard[i + x][i + y] = 1;
                    diagonal = false;
                }
                else if (chessBoard[i + x][i + y] < 7 && side && diagonal)
                {
                    checkBoard[i + x][i + y] = 1;
                    diagonal = false;
                }
                else
                {
                    diagonal = false;
                }
            }
        }

        contStraight = true, cont = true;
        diagonal = true, straight = true;
        for (int i = 1; i <= x; i++)
        { // move up and up left

            if (isKingUnderCheck && contStraight && OppositeColorBoard[x - i][y] == 2 && (!chessBoard[x - i][y] || (side ? chessBoard[x - i][y] < 7 : chessBoard[x - i][y] > 6))) // if the king is under check move the boxes which eliminate check
            {
                checkBoard[x - i][y] = 1;
                if (chessBoard[x - i][y])
                {
                    contStraight = false;
                }
            }
            else if (isKingUnderCheck && contStraight && chessBoard[x - i][y] && OppositeColorBoard[x - i][y] == 2)
            {
                contStraight = false;
            }
            if (isKingUnderCheck && cont && y + i < 8 && OppositeColorBoard[x - i][y - i] == 2 && (!chessBoard[x - i][y - i] || (side ? chessBoard[x - i][y - i] < 7 : chessBoard[x - i][y - i] > 6)))
            {
                checkBoard[x - i][y - i] = 1;
                if (chessBoard[x - i][y - i])
                {
                    cont = false;
                }
            }
            else if (isKingUnderCheck && cont && chessBoard[x - i][y + i] && OppositeColorBoard[x - i][y + i] == 2)
            {
                cont = false;
            }
            else if (isKingUnderCheck && (OppositeColorBoard[x - i][y] != 2 || OppositeColorBoard[x - i][y - i] != 2))
            {
                continue;
            }
            else if (chessBoard[x - i][y] == 0 && straight) // movements if the king is not under check
            {
                checkBoard[x - i][y] = 1;
            }
            else if (chessBoard[x - i][y] > 6 && !side && straight)
            {
                checkBoard[x - i][y] = 1;
                straight = false;
            }
            else if (chessBoard[x - i][y] < 7 && side && straight)
            {
                checkBoard[x - i][y] = 1;
                straight = false;
            }
            else
            {
                straight = false;
            }

            if (!isKingUnderCheck && y - i >= 0)
            {
                if (chessBoard[x - i][y - i] == 0 && diagonal)
                {
                    checkBoard[x - i][y - i] = 1;
                }
                else if (chessBoard[x - i][y - i] > 6 && !side && diagonal)
                {
                    checkBoard[x - i][y - i] = 1;
                    diagonal = false;
                }
                else if (chessBoard[x - i][y - i] < 7 && side && diagonal)
                {
                    checkBoard[x - i][y - i] = 1;
                    diagonal = false;
                }
                else
                {
                    diagonal = false;
                }
            }
        }
        contStraight = true, cont = true;
        diagonal = true, straight = true;
        for (int i = 1; i <= y; i++)
        { // move left and down left

            if (isKingUnderCheck && contStraight && OppositeColorBoard[x][y - i] == 2 && (!chessBoard[x][y - i] || (side ? chessBoard[x][y - i] < 7 : chessBoard[x][y - i] > 6))) // if the king is under check move the boxes which eliminate check
            {
                checkBoard[x][y - i] = 1;
                if (checkBoard[x][y - i])
                {
                    contStraight = false;
                }
            }
            else if (isKingUnderCheck && contStraight && chessBoard[x][y - i] && OppositeColorBoard[x][y - i] == 2)
            {
                contStraight = false;
            }
            if (isKingUnderCheck && cont && x + i < 8 && OppositeColorBoard[x + i][y - i] == 2 && (!chessBoard[x + i][y - i] || (side ? chessBoard[x + i][y - i] < 7 : chessBoard[x + i][y - i] > 6)))
            {
                checkBoard[x + i][y - i] = 1;
                if (chessBoard[x + i][y - i])
                {
                    cont = false;
                }
            }
            else if (isKingUnderCheck && cont && chessBoard[x + i][y - i] && OppositeColorBoard[x + i][y - i] == 2)
            {
                cont = false;
            }
            else if (isKingUnderCheck && (OppositeColorBoard[x][y - i] != 2 || OppositeColorBoard[x + i][y - i] != 2))
            {
                continue;
            }
            else if (chessBoard[x][y - i] == 0 && straight) // movements if the king is not under check
            {
                checkBoard[x][y - i] = 1;
            }
            else if (chessBoard[x][y - i] > 6 && !side && straight)
            {
                checkBoard[x][y - i] = 1;
                straight = false;
            }
            else if (chessBoard[x][y - i] < 7 && side && straight)
            {
                checkBoard[x][y - i] = 1;
                straight = false;
            }
            else
            {
                straight = false;
            }

            if (!isKingUnderCheck && x + i < 8)
            {
                if (chessBoard[x + i][y - i] == 0 && diagonal)
                {
                    checkBoard[x + i][y - i] = 1;
                }
                else if (chessBoard[x + i][y - i] > 6 && !side && diagonal)
                {
                    checkBoard[x + i][y - i] = 1;
                    diagonal = false;
                }
                else if (chessBoard[x + i][y - i] < 7 && side && diagonal)
                {
                    checkBoard[x + i][y - i] = 1;
                    diagonal = false;
                }
                else
                {
                    diagonal = false;
                }
            }
        }

        contStraight = true, cont = true;
        diagonal = true, straight = true;
        for (int i = 1; i + y < 8; i++)
        { // move right and up right

            if (isKingUnderCheck && contStraight && OppositeColorBoard[x][i + y] == 2 && (!chessBoard[x][i + y] || (side ? chessBoard[x][i + y] < 7 : chessBoard[x][i + y] > 6))) // if the king is under check move the boxes which eliminate check
            {
                checkBoard[x][i + y] = 1;
                if (chessBoard[x][i + y])
                {
                    contStraight = false;
                }
            }
            else if (isKingUnderCheck && contStraight && chessBoard[x][i + y] && OppositeColorBoard[x][i + y] == 2)
            {
                contStraight = false;
            }
            if (isKingUnderCheck && cont && x - i >= 0 && OppositeColorBoard[x - i][i + y] == 2 && (!chessBoard[x - i][i + y] || (side ? chessBoard[x - i][i + y] < 7 : chessBoard[x - i][i + y] > 6)))
            {
                checkBoard[x - i][i + y] = 1;
                if (chessBoard[x - i][i + y])
                {
                    cont = false;
                }
            }
            else if (isKingUnderCheck && cont && chessBoard[x - i][i + y] && OppositeColorBoard[x - i][i + y] == 2)
            {
                cont = false;
            }
            else if (isKingUnderCheck && (OppositeColorBoard[x][i + y] != 2 || OppositeColorBoard[x - i][i + y] != 2))
            {
                continue;
            }
            else if (chessBoard[x][i + y] == 0 && straight) // movements if the king is not under check
            {
                checkBoard[x][i + y] = 1;
            }
            else if (chessBoard[x][i + y] > 6 && !side && straight)
            {
                checkBoard[x][i + y] = 1;
                straight = false;
            }
            else if (chessBoard[x][i + y] < 7 && side && straight)
            {
                checkBoard[x][i + y] = 1;
                straight = false;
            }
            else
            {
                straight = false;
            }

            if (!isKingUnderCheck && x - i >= 0)
            {
                if (chessBoard[x - i][i + y] == 0)
                {
                    checkBoard[x - i][i + y] = 1;
                }
                else if (chessBoard[x - i][i + y] > 6 && !side)
                {
                    checkBoard[x - i][i + y] = 1;
                    break;
                }
                else if (chessBoard[x - i][i + y] < 7 && side)
                {
                    checkBoard[x - i][i + y] = 1;
                    break;
                }
                else
                {
                    break;
                }
            }
        }
    }
};

class bishop : public pieces
{
public:
    bishop(bool side) : pieces(side, 4) {};

    int fillBoard(int x, int y, int chessBoard[8][8], int colorBoard[8][8], int OppositeColorBoard[8][8])
    {
        int max = 0;
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if (colorBoard[i][j] > max) {
                    max = colorBoard[i][j];
                }
            }
        }
        if (OppositeColorBoard[x][y] == 2) {
            return max;
        }
        //bool kingUnderCheck = false;
        //bool side = chessBoard[x][y] > 6;
        bool skipped = false;
        for (int i = 1; x + i < 8 && y + i < 8; i++)
        {
            if (chessBoard[x + i][y + i] == 0 && !skipped)
            {
                if (!colorBoard[x + i][y + i])
                {
                    colorBoard[x + i][y + i] = 1;
                }
            }
            else if (side && chessBoard[x + i][y + i] > 6 && !skipped || !side && chessBoard[x + i][y + i] < 7 && !skipped)
            {
                if (!colorBoard[x + i][y + i])
                {
                    colorBoard[x + i][y + i] = 1; // marks covered piece down right
                }
                skipped = true;
                break;
            }
            else if (side && chessBoard[x + i][y + i] == 6 || !side && chessBoard[x + i][y + i] == 12)
            {
                for (int j = x, k = y; j < x + i && k < y + i; j++, k++)
                {
                    colorBoard[j][k] = 2;
                }
                if (!skipped)
                {
                    colorBoard[x][y] = 2;         // marks the piece itself as for releasing check
                    colorBoard[x + i][y + i] = 3; // marks the king under check
                    for (int k = x + i + 1, l = y + i + 1; k < 8 && l < 8; k++, l++) {
                        colorBoard[k][l] = 1;
                    }
                }
                break;
            }
            else if (!skipped && (side && chessBoard[x + i][y + i] < 7 || !side && chessBoard[x + i][y + i] > 6))
            {
                if (!colorBoard[x + i][y + i])
                {
                    colorBoard[x + i][y + i] = 1; // marks pinned piece down right
                }
                skipped = true;
            }
            else if (skipped && (side && chessBoard[x + i][y + i] < 7 || !side && chessBoard[x + i][y + i] > 6)) {
                break;
            }

        }

        skipped = false;
        for (int i = 1; x - i >= 0 && y - i >= 0; i++)
        {
            if (chessBoard[x - i][y - i] == 0 && !skipped)
            {
                if (!colorBoard[x - i][y - i])
                {
                    colorBoard[x - i][y - i] = 1;
                }
            }
            else if (side && chessBoard[x - i][y - i] > 6 && !skipped || !side && chessBoard[x - i][y - i] < 7 && !skipped)
            {
                if (!colorBoard[x - i][y - i])
                {
                    colorBoard[x - i][y - i] = 1; // marks covered piece up left
                }
                skipped = true;
                break;
            }
            else if (side && chessBoard[x - i][y - i] == 6 || !side && chessBoard[x - i][y - i] == 12)
            {
                for (int j = x, k = y; j > x - i && k > y - i; j--, k--)
                {
                    colorBoard[j][k] = 2;
                }
                if (!skipped)
                {
                    colorBoard[x][y] = 2;         // marks the piece itself as for releasing check
                    colorBoard[x - i][y - i] = 3; // marks the king under check
                    for (int k = x - i - 1, l = y - i - 1; k >= 0 && l >= 0; k--, l--) {
                        colorBoard[k][l] = 1;
                    }
                }
                break;
            }
            else if (!skipped && (side && chessBoard[x - i][y - i] < 7 || !side && chessBoard[x - i][y - i] > 6))
            {
                if (!colorBoard[x - i][y - i])
                {
                    colorBoard[x - i][y - i] = 1; // marks pinned piece up left
                }
                skipped = true;
            }
            else if (skipped && (side && chessBoard[x - i][y - i] < 7 || !side && chessBoard[x - i][y - i] > 6)) {
                break;
            }
        }

        skipped = false;
        for (int i = 1; x + i < 8 && y - i >= 0; i++)
        {
            if (chessBoard[x + i][y - i] == 0 && !skipped)
            {
                if (!colorBoard[x + i][y - i])
                {
                    colorBoard[x + i][y - i] = 1;
                }
            }
            else if (side && chessBoard[x + i][y - i] > 6 && !skipped || !side && chessBoard[x + i][y - i] < 7 && !skipped)
            {
                if (!colorBoard[x + i][y - i])
                {
                    colorBoard[x + i][y - i] = 1; // marks covered piece down left
                }
                skipped = true;
                break;
            }
            else if (side && chessBoard[x + i][y - i] == 6 || !side && chessBoard[x + i][y - i] == 12)
            {
                for (int j = x, k = y; j < x + i && k > y - i; j++, k--)
                {
                    colorBoard[j][k] = 2;
                }
                if (!skipped)
                {
                    colorBoard[x][y] = 2;         // marks the piece itself as for releasing check
                    colorBoard[x + i][y - i] = 3; // marks the king under check
                    for (int k = x + i + 1, l = y - i - 1; k < 8 && l >= 0; k++, l--) {
                        colorBoard[k][l] = 1;
                    }
                }
                break;
            }
            else if (!skipped && (side && chessBoard[x + i][y - i] < 7 || !side && chessBoard[x + i][y - i] > 6))
            {
                if (!colorBoard[x + i][y - i])
                {
                    colorBoard[x + i][y - i] = 1; // marks pinned piece down left
                }
                skipped = true;
            }
            else if (skipped && (side && chessBoard[x + i][y - i] < 7 || !side && chessBoard[x + i][y - i] > 6)) {
                break;
            }
        }

        skipped = false;
        for (int i = 1; x - i >= 0 && y + i < 8; i++)
        {
            if (chessBoard[x - i][y + i] == 0 && !skipped)
            {
                if (!colorBoard[x - i][y + i])
                {
                    colorBoard[x - i][y + i] = 1;
                }
            }
            else if (side && chessBoard[x - i][y + i] > 6 && !skipped || !side && chessBoard[x - i][y + i] < 7 && !skipped)
            {
                if (!colorBoard[x - i][y + i])
                {
                    colorBoard[x - i][y + i] = 1; // marks covered piece up right
                }
                skipped = true;
                break;
            }
            else if (side && chessBoard[x - i][y + i] == 6 || !side && chessBoard[x - i][y + i] == 12)
            {
                for (int j = x, k = y; j > x - i && k < y + i; j--, k++)
                {
                    colorBoard[j][k] = 2;
                }
                if (!skipped)
                {
                    colorBoard[x][y] = 2;         // marks the piece itself as for releasing check
                    colorBoard[x - i][y + i] = 3; // marks the king under check
                    for (int k = x - i - 1, l = y + i + 1; k >= 0 && l < 8; k--, l++) {
                        colorBoard[k][l] = 1;
                    }
                }
                break;
            }
            else if (!skipped && (side && chessBoard[x - i][y + i] < 7 || !side && chessBoard[x - i][y + i] > 6))
            {
                if (!colorBoard[x - i][y + i])
                {
                    colorBoard[x - i][y + i] = 1; // marks pinned piece up right
                }
                skipped = true;
            }
            else if (skipped && (side && chessBoard[x - i][y + i] < 7 || !side && chessBoard[x - i][y + i] > 6)) {
                break;
            }
        }

        // return kingUnderCheck;

        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                if (colorBoard[i][j] > max)
                {
                    max = colorBoard[i][j];
                }
            }
        }
        return max;
    }

    void showMoves(int x, int y, int chessBoard[8][8], bool checkBoard[8][8], int colorBoard[8][8], int OppositeColorBoard[8][8], bool isKingUnderCheck)
    {

        isKingUnderCheck = (isKingUnderCheck || (OppositeColorBoard[x][y] == 2)); // if the piece is pinned treats it as if the king is under check
        for (int i = 1; i + x < 8 && i + y < 8; i++)
        { // move down right

            if (isKingUnderCheck && OppositeColorBoard[i + x][i + y] == 2 && (!chessBoard[x + i][i + y] || (side ? chessBoard[i + x][i + y] < 7 : chessBoard[i + x][i + y] > 6)))
            {
                checkBoard[i + x][i + y] = 1;
                if (chessBoard[x + i][i + y])
                {
                    break;
                }
            }
            else if (isKingUnderCheck && chessBoard[i + x][i + y] && OppositeColorBoard[i + x][i + y] == 2)
            {
                break;
            }
            else if (isKingUnderCheck && OppositeColorBoard[i + x][i + y] != 2)
            {
                continue;
            }
            else if (chessBoard[i + x][i + y] == 0)
            {
                checkBoard[i + x][i + y] = 1;
            }
            else if (chessBoard[i + x][i + y] > 6 && !side)
            {
                checkBoard[i + x][i + y] = 1;
                break;
            }
            else if (chessBoard[i + x][i + y] < 7 && side)
            {
                checkBoard[i + x][i + y] = 1;
                break;
            }
            else
            {
                break;
            }
        }

        for (int i = 1; x - i >= 0 && i + y < 8; i++)
        { // move up right

            if (isKingUnderCheck && OppositeColorBoard[x - i][i + y] == 2 && (!chessBoard[x - i][i + y] || (side ? chessBoard[x - i][i + y] < 7 : chessBoard[x - i][i + y] > 6)))
            {
                checkBoard[x - i][i + y] = 1;
                if (chessBoard[x - i][i + y])
                {
                    break;
                }
            }
            else if (isKingUnderCheck && chessBoard[x - i][i + y] && OppositeColorBoard[x - i][i + y] == 2)
            {
                break;
            }
            else if (isKingUnderCheck && OppositeColorBoard[x - i][i + y] != 2)
            {
                continue;
            }
            else if (chessBoard[x - i][i + y] == 0)
            {
                checkBoard[x - i][i + y] = 1;
            }
            else if (chessBoard[x - i][i + y] > 6 && !side)
            {
                checkBoard[x - i][i + y] = 1;
                break;
            }
            else if (chessBoard[x - i][i + y] < 7 && side)
            {
                checkBoard[x - i][i + y] = 1;
                break;
            }
            else
            {
                break;
            }
        }

        for (int i = 1; i + x < 8 && y - i >= 0; i++)
        { // move down left
            if (isKingUnderCheck && OppositeColorBoard[i + x][y - i] == 2 && (!chessBoard[i + x][y - i] || (side ? chessBoard[i + x][y - i] < 7 : chessBoard[i + x][y - i] > 6)))
            {
                checkBoard[i + x][y - i] = 1;
                if (chessBoard[i + x][y - i])
                {
                    break;
                }
            }
            else if (isKingUnderCheck && chessBoard[i + x][y - i] && OppositeColorBoard[i + x][y - i] == 2)
            {
                break;
            }
            else if (isKingUnderCheck && OppositeColorBoard[i + x][y - i] != 2)
            {
                continue;
            }
            else if (chessBoard[i + x][y - i] == 0)
            {
                checkBoard[i + x][y - i] = 1;
            }
            else if (chessBoard[i + x][y - i] > 6 && !side)
            {
                checkBoard[i + x][y - i] = 1;
                break;
            }
            else if (chessBoard[i + x][y - i] < 7 && side)
            {
                checkBoard[i + x][y - i] = 1;
                break;
            }
            else
            {
                break;
            }
        }

        for (int i = 1; x - i >= 0 && y - i >= 0; i++)
        { // move up left

            if (isKingUnderCheck && OppositeColorBoard[x - i][y - i] == 2 && (!chessBoard[x - i][y - i] || (side ? chessBoard[x - i][y - i] < 7 : chessBoard[x - i][y - i] > 6)))
            {
                checkBoard[x - i][y - i] = 1;
                if (chessBoard[x - i][y - i])
                {
                    break;
                }
            }
            else if (isKingUnderCheck && chessBoard[x - i][y - i] && OppositeColorBoard[x - i][y - i] == 2)
            {
                break;
            }
            else if (isKingUnderCheck && OppositeColorBoard[x - i][y - i] != 2)
            {
                continue;
            }
            else if (chessBoard[x - i][y - i] == 0)
            {
                checkBoard[x - i][y - i] = 1;
            }
            else if (chessBoard[x - i][y - i] > 6 && !side)
            {
                checkBoard[x - i][y - i] = 1;
                break;
            }
            else if (chessBoard[x - i][y - i] < 7 && side)
            {
                checkBoard[x - i][y - i] = 1;
                break;
            }
            else
            {
                break;
            }
        }
    }
};

class knight : public pieces
{
public:
    knight(bool side) : pieces(side, 3) {};

    int fillBoard(int x, int y, int chessBoard[8][8], int colorBoard[8][8], int OppositeColorBoard[8][8])
    {
        int max = 0;
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if (colorBoard[i][j] > max) {
                    max = colorBoard[i][j];
                }
            }
        }
        if (OppositeColorBoard[x][y] == 2) {
            return max;
        }
        bool kingUnderCheck = false;
        if (x + 2 < 8)
        {
            if (y + 1 < 8)
            { // movement to down right
                if (chessBoard[x + 2][y + 1] == 0)
                {
                    if (!colorBoard[x + 2][y + 1])
                    {
                        colorBoard[x + 2][y + 1] = 1;
                    }
                }
                else if (side && chessBoard[x + 2][y + 1] == 6 || !side && chessBoard[x + 2][y + 1] == 12)
                {
                    colorBoard[x + 2][y + 1] = 3;
                    colorBoard[x][y] = 2;
                    kingUnderCheck = true;
                }
                else
                {
                    if (!colorBoard[x + 2][y + 1])
                    {
                        colorBoard[x + 2][y + 1] = 1;
                    }
                }

                // movement to down left
                if (chessBoard[x + 2][y - 1] == 0)
                {
                    if (!colorBoard[x + 2][y - 1])
                    {
                        colorBoard[x + 2][y - 1] = 1;
                    }
                }
                else if (side && chessBoard[x + 2][y - 1] == 6 || !side && chessBoard[x + 2][y - 1] == 12)
                {
                    colorBoard[x + 2][y - 1] = 3;
                    colorBoard[x][y] = 2;
                    kingUnderCheck = true;
                }
                else
                {
                    if (!colorBoard[x + 2][y - 1])
                    {
                        colorBoard[x + 2][y - 1] = 1;
                    }
                }
            }
        }

        if (x - 2 >= 0)
        {
            if (y + 1 < 8)
            { // movement to up right
                if (chessBoard[x - 2][y + 1] == 0)
                {
                    if (!colorBoard[x - 2][y + 1])
                    {
                        colorBoard[x - 2][y + 1] = 1;
                    }
                }
                else if (side && chessBoard[x - 2][y + 1] == 6 || !side && chessBoard[x - 2][y + 1] == 12)
                {
                    colorBoard[x - 2][y + 1] = 3;
                    colorBoard[x][y] = 2;
                    kingUnderCheck = true;
                }
                else
                {
                    if (!colorBoard[x - 2][y + 1])
                    {
                        colorBoard[x - 2][y + 1] = 1;
                    }
                }

                // movement to up left
                if (chessBoard[x - 2][y - 1] == 0)
                {
                    if (!colorBoard[x - 2][y - 1])
                    {
                        colorBoard[x - 2][y - 1] = 1;
                    }
                }
                else if (side && chessBoard[x - 2][y - 1] == 6 || !side && chessBoard[x - 2][y - 1] == 12)
                {
                    colorBoard[x - 2][y - 1] = 3;
                    colorBoard[x][y] = 2;
                    kingUnderCheck = true;
                }
                else
                {
                    if (!colorBoard[x - 2][y - 1])
                    {
                        colorBoard[x - 2][y - 1] = 1;
                    }
                }
            }
        }

        if (y + 2 < 8)
        {
            if (x + 1 < 8)
            { // movement to right down
                if (chessBoard[x + 1][y + 2] == 0)
                {
                    if (!colorBoard[x + 1][y + 2])
                    {
                        colorBoard[x + 1][y + 2] = 1;
                    }
                }
                else if (side && chessBoard[x + 1][y + 2] == 6 || !side && chessBoard[x + 1][y + 2] == 12)
                {
                    colorBoard[x + 1][y + 2] = 3;
                    colorBoard[x][y] = 2;
                    kingUnderCheck = true;
                }
                else
                {
                    if (!colorBoard[x + 1][y + 2])
                    {
                        colorBoard[x + 1][y + 2] = 1;
                    }
                }

                // movement to right up
                if (chessBoard[x - 1][y + 2] == 0)
                {
                    if (!colorBoard[x - 1][y + 2])
                    {
                        colorBoard[x - 1][y + 2] = 1;
                    }
                }
                else if (side && chessBoard[x - 1][y + 2] == 6 || !side && chessBoard[x - 1][y + 2] == 12)
                {
                    colorBoard[x - 1][y + 2] = 3;
                    colorBoard[x][y] = 2;
                    kingUnderCheck = true;
                }
                else
                {
                    if (!colorBoard[x - 1][y + 2])
                    {
                        colorBoard[x - 1][y + 2] = 1;
                    }
                }
            }
        }

        if (y - 2 >= 0)
        {
            if (x + 1 < 8)
            { // movement to left down
                if (chessBoard[x + 1][y - 2] == 0)
                {
                    if (!colorBoard[x + 1][y - 2])
                    {
                        colorBoard[x + 1][y - 2] = 1;
                    }
                }
                else if (side && chessBoard[x + 1][y - 2] == 6 || !side && chessBoard[x + 1][y - 2] == 12)
                {
                    colorBoard[x + 1][y - 2] = 3;
                    colorBoard[x][y] = 2;
                    kingUnderCheck = true;
                }
                else
                {
                    if (!colorBoard[x + 1][y - 2])
                    {
                        colorBoard[x + 1][y - 2] = 1;
                    }
                }

                // movement to left up
                if (chessBoard[x - 1][y - 2] == 0)
                {
                    if (!colorBoard[x - 1][y - 2])
                    {
                        colorBoard[x - 1][y - 2] = 1;
                    }
                }
                else if (side && chessBoard[x - 1][y - 2] == 6 || !side && chessBoard[x - 1][y - 2] == 12)
                {
                    colorBoard[x - 1][y - 2] = 3;
                    colorBoard[x][y] = 2;
                    kingUnderCheck = true;
                }
                else
                {
                    if (!colorBoard[x - 1][y - 2])
                    {
                        colorBoard[x - 1][y - 2] = 1;
                    }
                }
            }
        }
        // return kingUnderCheck;

        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                if (colorBoard[i][j] > max)
                {
                    max = colorBoard[i][j];
                }
            }
        }
        return max;
    }

    void showMoves(int x, int y, int chessBoard[8][8], bool checkBoard[8][8], int colorBoard[8][8], int OppositeColorBoard[8][8], bool isKingUnderCheck)
    {
        isKingUnderCheck = ((OppositeColorBoard[x][y] == 2) || isKingUnderCheck);
        if (x + 2 < 8)
        {
            if (y + 1 < 8)
            { // movement to down right

                if (isKingUnderCheck && OppositeColorBoard[x + 2][y + 1] == 2 && (!chessBoard[x + 2][y + 1] || (side && chessBoard[x + 2][y + 1] < 7) || (!side && chessBoard[x + 2][y + 1] > 6)))
                {
                    checkBoard[x + 2][y + 1] = 1;
                }
                else if (!isKingUnderCheck)
                {
                    if (chessBoard[x + 2][y + 1] == 0)
                    {
                        checkBoard[x + 2][y + 1] = 1;
                    }
                    else if (chessBoard[x + 2][y + 1] > 6 && !side)
                    {
                        checkBoard[x + 2][y + 1] = 1;
                    }
                    else if (chessBoard[x + 2][y + 1] < 7 && side)
                    {
                        checkBoard[x + 2][y + 1] = 1;
                    }
                }
            }
            if (y - 1 >= 0)
            { // movement to down left
                if (isKingUnderCheck && OppositeColorBoard[x + 2][y - 1] == 2 && (!chessBoard[x + 2][y - 1] || (side && chessBoard[x + 2][y - 1] < 7) || (!side && chessBoard[x + 2][y - 1] > 6)))
                {
                    checkBoard[x + 2][y - 1] = 1;
                }
                else if (!isKingUnderCheck)
                {
                    if (chessBoard[x + 2][y - 1] == 0)
                    {
                        checkBoard[x + 2][y - 1] = 1;
                    }
                    else if (chessBoard[x + 2][y - 1] > 6 && !side)
                    {
                        checkBoard[x + 2][y - 1] = 1;
                    }
                    else if (chessBoard[x + 2][y - 1] < 7 && side)
                    {
                        checkBoard[x + 2][y - 1] = 1;
                    }
                }
            }
        }
        if (x - 2 >= 0)
        {
            if (y + 1 < 8)
            { // movement to up right

                if (isKingUnderCheck && OppositeColorBoard[x - 2][y + 1] == 2 && (!chessBoard[x - 2][y + 1] || (side && chessBoard[x - 2][y + 1] < 7) || (!side && chessBoard[x - 2][y + 1] > 6)))
                {
                    checkBoard[x - 2][y + 1] = 1;
                }
                else if (!isKingUnderCheck)
                {
                    if (chessBoard[x - 2][y + 1] == 0)
                    {
                        checkBoard[x - 2][y + 1] = 1;
                    }
                    else if (chessBoard[x - 2][y + 1] > 6 && !side)
                    {
                        checkBoard[x - 2][y + 1] = 1;
                    }
                    else if (chessBoard[x - 2][y + 1] < 7 && side)
                    {
                        checkBoard[x - 2][y + 1] = 1;
                    }
                }
            }
            if (y - 1 >= 0)
            { // movement to up left

                if (isKingUnderCheck && OppositeColorBoard[x - 2][y - 1] == 2 && (!chessBoard[x - 2][y - 1] || (side && chessBoard[x - 2][y - 1] < 7) || (!side && chessBoard[x - 2][y - 1] > 6)))
                {
                    checkBoard[x - 2][y - 1] = 1;
                }
                else if (!isKingUnderCheck)
                {
                    if (chessBoard[x - 2][y - 1] == 0)
                    {
                        checkBoard[x - 2][y - 1] = 1;
                    }
                    else if (chessBoard[x - 2][y - 1] > 6 && !side)
                    {
                        checkBoard[x - 2][y - 1] = 1;
                    }
                    else if (chessBoard[x - 2][y - 1] < 7 && side)
                    {
                        checkBoard[x - 2][y - 1] = 1;
                    }
                }
            }
        }
        if (y + 2 < 8)
        {
            if (x + 1 < 8)
            { // movement to right down

                if (isKingUnderCheck && OppositeColorBoard[x + 1][y + 2] == 2 && (!chessBoard[x + 1][y + 2] || (side && chessBoard[x + 1][y + 2] < 7) || (!side && chessBoard[x + 1][y + 2] > 6)))
                {
                    checkBoard[x + 1][y + 2] = 1;
                }
                else if (!isKingUnderCheck)
                {
                    if (chessBoard[x + 1][y + 2] == 0)
                    {
                        checkBoard[x + 1][y + 2] = 1;
                    }
                    else if (chessBoard[x + 1][y + 2] > 6 && !side)
                    {
                        checkBoard[x + 1][y + 2] = 1;
                    }
                    else if (chessBoard[x + 1][y + 2] < 7 && side)
                    {
                        checkBoard[x + 1][y + 2] = 1;
                    }
                }
            }
            if (x - 1 >= 0)
            { // movement to left down

                if (isKingUnderCheck && OppositeColorBoard[x - 1][y + 2] == 2 && (!chessBoard[x - 1][y + 2] || (side && chessBoard[x - 1][y + 2] < 7) || (!side && chessBoard[x - 1][y + 2] > 6)))
                {
                    checkBoard[x - 1][y + 2] = 1;
                }
                else if (!isKingUnderCheck)
                {
                    if (chessBoard[x - 1][y + 2] == 0)
                    {
                        checkBoard[x - 1][y + 2] = 1;
                    }
                    else if (chessBoard[x - 1][y + 2] > 6 && !side)
                    {
                        checkBoard[x - 1][y + 2] = 1;
                    }
                    else if (chessBoard[x - 1][y + 2] < 7 && side)
                    {
                        checkBoard[x - 1][y + 2] = 1;
                    }
                }
            }
        }
        if (y - 2 >= 0)
        {
            if (x + 1 < 8)
            { // movement to right up

                if (isKingUnderCheck && OppositeColorBoard[x + 1][y - 2] == 2 && (!chessBoard[x + 1][y - 2] || (side && chessBoard[x + 1][y - 2] < 7) || (!side && chessBoard[x + 1][y - 2] > 6)))
                {
                    checkBoard[x + 1][y - 2] = 1;
                }
                else if (!isKingUnderCheck)
                {
                    if (chessBoard[x + 1][y - 2] == 0)
                    {
                        checkBoard[x + 1][y - 2] = 1;
                    }
                    else if (chessBoard[x + 1][y - 2] > 6 && !side)
                    {
                        checkBoard[x + 1][y - 2] = 1;
                    }
                    else if (chessBoard[x + 1][y - 2] < 7 && side)
                    {
                        checkBoard[x + 1][y - 2] = 1;
                    }
                }
            }
            if (x - 1 >= 0)
            { // movement to left up

                if (isKingUnderCheck && OppositeColorBoard[x - 1][y - 2] == 2 && (!chessBoard[x - 1][y - 2] || (side && chessBoard[x - 1][y - 2] < 7) || (!side && chessBoard[x - 1][y - 2] > 6)))
                {
                    checkBoard[x - 1][y - 2] = 1;
                }
                else if (!isKingUnderCheck)
                {
                    if (chessBoard[x - 1][y - 2] == 0)
                    {
                        checkBoard[x - 1][y - 2] = 1;
                    }
                    else if (chessBoard[x - 1][y - 2] > 6 && !side)
                    {
                        checkBoard[x - 1][y - 2] = 1;
                    }
                    else if (chessBoard[x - 1][y - 2] < 7 && side)
                    {
                        checkBoard[x - 1][y - 2] = 1;
                    }
                }
            }
        }
    }
};

class rook : public pieces
{
public:
    rook(bool side) : pieces(side, 2) {};

    int fillBoard(int x, int y, int chessBoard[8][8], int colorBoard[8][8], int OppositeColorBoard[8][8])
    {
        int max = 0;
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if (colorBoard[i][j] > max) {
                    max = colorBoard[i][j];
                }
            }
        }
        if (OppositeColorBoard[x][y] == 2) {
            return max;
        }
        bool skipped = false;
        for (int i = 1; x + i < 8; i++)
        {
            if (!skipped && chessBoard[x + i][y] == 0)
            {
                if (!colorBoard[x + i][y])
                {
                    colorBoard[x + i][y] = 1;
                }
            }
            else if (!skipped && (side && chessBoard[x + i][y] > 6 || !side && chessBoard[x + i][y] < 7))
            {
                if (!colorBoard[x + i][y])
                {
                    colorBoard[x + i][y] = 1; // marks covered Piece down
                }
                skipped = true;
                break;
            }
            else if ((side && chessBoard[x + i][y] == 6 || !side && chessBoard[x + i][y] == 12))
            {
                for (int j = x; j <= x + i; j++)
                {
                    colorBoard[j][y] = 2; // marks pinned piece within king
                }
                if (!skipped)
                {
                    colorBoard[x + i][y] = 3;
                    colorBoard[x][y] = 2;
                    for (int k = x + i + 1; k < 8; k++)
                    {
                        colorBoard[k][y] = 1;
                    }
                }
                break;
            }
            else if (!skipped && (side && chessBoard[x + i][y] < 7 || !side && chessBoard[x + i][y] > 6))
            {
                if (!colorBoard[x + i][y])
                {
                    colorBoard[x + i][y] = 1; // marks location in case if the piece is pinned
                }
                skipped = true;
            }
            else if (skipped && (side && chessBoard[x + i][y] < 7 || !side && chessBoard[x + i][y] > 6)) {
                break;
            }
        }

        skipped = false;
        for (int i = 1; x - i >= 0; i++)
        {
            if (!skipped && chessBoard[x - i][y] == 0)
            {
                if (!colorBoard[x - i][y])
                {
                    colorBoard[x - i][y] = 1;
                }
            }
            else if (!skipped && (side && chessBoard[x - i][y] > 6 || !side && chessBoard[x - i][y] < 7))
            {
                if (!colorBoard[x - i][y])
                {
                    colorBoard[x - i][y] = 1; // marks covered Piece up
                }
                skipped = true;
                break;
            }
            else if ((side && chessBoard[x - i][y] == 6 || !side && chessBoard[x - i][y] == 12))
            {
                for (int j = x; j >= x - i; j--)
                {
                    colorBoard[j][y] = 2; // marks pinned piece within king
                }
                if (!skipped)
                {
                    colorBoard[x - i][y] = 3;
                    colorBoard[x][y] = 2;
                    for (int k = x - i - 1; k >= 0; k--)
                    {
                        colorBoard[k][y] = 1;
                    }
                }
                break;
            }
            else if (!skipped && (side && chessBoard[x - i][y] < 7 || !side && chessBoard[x - i][y] > 6))
            {
                if (!colorBoard[x - i][y])
                {
                    colorBoard[x - i][y] = 1; // marks location in case if the piece is pinned
                }
                skipped = true;
            }
            else if (skipped && (side && (side && chessBoard[x - i][y] < 7 || !side && chessBoard[x - i][y] > 6))) {
                break;
            }
        }

        skipped = false;
        for (int i = 1; y + i < 8; i++)
        {
            if (!skipped && chessBoard[x][y + i] == 0)
            {
                if (!colorBoard[x][y + i])
                {
                    colorBoard[x][y + i] = 1;
                }
            }
            else if (!skipped && (side && chessBoard[x][y + i] > 6 || !side && chessBoard[x][y + i] < 7))
            {
                if (!colorBoard[x][y + i])
                {
                    colorBoard[x][y + i] = 1; // marks covered Piece right
                }
                skipped = true;
                break;
            }
            else if ((side && chessBoard[x][y + i] == 6 || !side && chessBoard[x][y + i] == 12))
            {
                for (int j = y; j <= y + i; j++)
                {
                    colorBoard[x][j] = 2; // marks pinned piece within king
                }
                if (!skipped)
                {
                    colorBoard[x][y + i] = 3;
                    colorBoard[x][y] = 2;
                    for (int k = y + i + 1; k < 8; k++)
                    {
                        colorBoard[x][k] = 1;
                    }
                }
                break;
            }
            else if (!skipped && (side && chessBoard[x][y + i] < 7 || !side && chessBoard[x][y + i] > 6))
            {
                if (!colorBoard[x][y + i])
                {
                    colorBoard[x][y + i] = 1; // marks location in case if the piece is pinned
                }
                skipped = true;
            }
            else if (skipped && (side && chessBoard[x][y + i] < 7 || !side && chessBoard[x][y + i] > 6)) {
                break;
            }
        }

        skipped = false;
        for (int i = 1; y - i >= 0; i++)
        {
            if (!skipped && chessBoard[x][y - i] == 0)
            {
                if (!colorBoard[x][y - i])
                {
                    colorBoard[x][y - i] = 1;
                }
            }
            else if (!skipped && (side && chessBoard[x][y - i] > 6 || !side && chessBoard[x][y - i] < 7))
            {
                if (!colorBoard[x][y - i])
                {
                    colorBoard[x][y - i] = 1; // marks covered Piece left
                }
                skipped = true;
                break;
            }
            else if ((side && chessBoard[x][y - i] == 6 || !side && chessBoard[x][y - i] == 12))
            {
                for (int j = y; j >= y - i; j--)
                {
                    colorBoard[x][j] = 2; // marks pinned piece within king
                }
                if (!skipped)
                {
                    colorBoard[x][y - i] = 3;
                    colorBoard[x][y] = 2;
                    for (int k = y - i - 1; k >= 0; k--)
                    {
                        colorBoard[x][k] = 1;
                    }
                }
                break;
            }
            else if (!skipped && (side && chessBoard[x][y - i] < 7 || !side && chessBoard[x][y - i] > 6))
            {
                if (!colorBoard[x][y - i])
                {
                    colorBoard[x][y - i] = 1; // marks location in case if the piece is pinned
                }
                skipped = true;
            }
            else if (skipped && (side && chessBoard[x][y - i] < 7 || !side && chessBoard[x][y - i] > 6)) {
                break;
            }
        }
        // return kingUnderCheck;

        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                if (colorBoard[i][j] > max)
                {
                    max = colorBoard[i][j];
                }
            }
        }
        return max;
    }

    void showMoves(int x, int y, int chessBoard[8][8], bool checkBoard[8][8], int colorBoard[8][8], int OppositeColorBoard[8][8], bool isKingUnderCheck)
    {
        isKingUnderCheck = (isKingUnderCheck || OppositeColorBoard[x][y] == 2);
        for (int i = 1; i + x < 8; i++)
        { // down movement
            if (isKingUnderCheck && OppositeColorBoard[i + x][y] == 2 && (!chessBoard[i + x][y] || (side ? chessBoard[i + x][y] < 7 : chessBoard[i + x][y] > 6)))
            {
                checkBoard[i + x][y] = 1;
                if (chessBoard[i + x][y])
                {
                    break;
                }
            }
            else if (isKingUnderCheck && chessBoard[x + i][y] && OppositeColorBoard[x + i][y] == 2)
            {
                break;
            }
            else if (isKingUnderCheck && OppositeColorBoard[i + x][y] != 2)
            {
                continue;
            }
            else if (chessBoard[i + x][y] == 0)
            {
                checkBoard[i + x][y] = 1;
            }
            else if (chessBoard[i + x][y] > 6 && !side)
            {
                checkBoard[i + x][y] = 1;
                break;
            }
            else if (chessBoard[i + x][y] < 7 && side)
            {
                checkBoard[i + x][y] = 1;
                break;
            }
            else
            {
                break;
            }
        }

        for (int i = 1; x - i >= 0; i++)
        { // up movement

            if (isKingUnderCheck && OppositeColorBoard[x - i][y] == 2 && (!chessBoard[x - i][y] || (side ? chessBoard[x - i][y] < 7 : chessBoard[x - i][y] > 6)))
            {
                checkBoard[x - i][y] = 1;
                if (chessBoard[x - i][y])
                {
                    break;
                }
            }
            else if (isKingUnderCheck && chessBoard[x - i][y] && OppositeColorBoard[x - i][y] == 2)
            {
                break;
            }
            else if (isKingUnderCheck && OppositeColorBoard[x - i][y] != 2)
            {
                continue;
            }
            else if (chessBoard[x - i][y] == 0)
            {
                checkBoard[x - i][y] = 1;
            }
            else if (chessBoard[x - i][y] > 6 && !side)
            {
                checkBoard[x - i][y] = 1;
                break;
            }
            else if (chessBoard[x - i][y] < 7 && side)
            {
                checkBoard[x - i][y] = 1;
                break;
            }
            else
            {
                break;
            }
        }

        for (int i = 1; y + i < 8; i++)
        { // right movement

            if (isKingUnderCheck && OppositeColorBoard[x][y + i] == 2 && (!chessBoard[x][y + i] || (side ? chessBoard[x][y + i] < 7 : chessBoard[x][y + i] > 6)))
            {
                checkBoard[x][y + i] = 1;
                if (chessBoard[x][y + i])
                {
                    break;
                }
            }
            else if (isKingUnderCheck && chessBoard[x][y + i] && OppositeColorBoard[x][y + i] == 2)
            {
                break;
            }
            else if (isKingUnderCheck && OppositeColorBoard[x][y + i] != 2)
            {
                continue;
            }
            else if (chessBoard[x][y + i] == 0)
            {
                checkBoard[x][y + i] = 1;
            }
            else if (chessBoard[x][y + i] > 6 && !side)
            {
                checkBoard[x][y + i] = 1;
                break;
            }
            else if (chessBoard[x][y + i] < 7 && side)
            {
                checkBoard[x][y + i] = 1;
                break;
            }
            else
            {
                break;
            }
        }

        for (int i = 1; y - i >= 0; i++)
        { // left movement

            if (isKingUnderCheck && OppositeColorBoard[x][y - i] == 2 && (!chessBoard[x][y - i] || (side ? chessBoard[x][y - i] < 7 : chessBoard[x][y - i] > 6)))
            {
                checkBoard[x][y - i] = 1;
                if (chessBoard[x][y - i])
                {
                    break;
                }
            }
            else if (isKingUnderCheck && chessBoard[x][y - i] && OppositeColorBoard[x][y - i] == 2)
            {
                break;
            }
            else if (isKingUnderCheck && OppositeColorBoard[x][y - i] != 2)
            {
                continue;
            }
            else if (chessBoard[x][y - i] == 0)
            {
                checkBoard[x][y - i] = 1;
            }
            else if (chessBoard[x][y - i] > 6 && !side)
            {
                checkBoard[x][y - i] = 1;
                break;
            }
            else if (chessBoard[x][y - i] < 7 && side)
            {
                checkBoard[x][y - i] = 1;
                break;
            }
            else
            {
                break;
            }
        }
    }
};

class pawn : public pieces
{
public:
    pawn(bool side) : pieces(side, 1) {};

    int fillBoard(int x, int y, int chessBoard[8][8], int colorBoard[8][8], int OppositeColorBoard[8][8])
    {
        int max = 0;
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if (colorBoard[i][j] > max) {
                    max = colorBoard[i][j];
                }
            }
        }
        if (OppositeColorBoard[x][y] == 2) {
            return max;
        }
        bool kingUnderCheck = false;
        if (side)
        {
            if (chessBoard[x + 1][y + 1] == 6 && x + 1 < 8 && y + 1 < 8)
            {
                colorBoard[x + 1][y + 1] = 3;
                colorBoard[x][y] = 2;
                kingUnderCheck = true;
            }
            else if (x + 1 < 8 && y + 1 < 8)
            {
                if (!colorBoard[x + 1][y + 1] && OppositeColorBoard[x + 1][y + 1] != 2)
                {
                    colorBoard[x + 1][y + 1] = 1;
                }
            }
            if (chessBoard[x + 1][y - 1] == 6 && x + 1 < 8 && y - 1 >= 0)
            {
                colorBoard[x + 1][y - 1] = 3;
                colorBoard[x][y] = 2;
                kingUnderCheck = true;
            }
            else if (x + 1 < 8 && y - 1 >= 0)
            {
                if (!colorBoard[x + 1][y - 1] && OppositeColorBoard[x + 1][y - 1] != 2)
                {
                    colorBoard[x + 1][y - 1] = 1;
                }
            }
        }
        else
        {
            if (chessBoard[x - 1][y + 1] == 12 && x - 1 >= 0 && y + 1 < 8)
            {
                colorBoard[x - 1][y + 1] = 3;
                colorBoard[x][y] = 2;
                kingUnderCheck = true;
            }
            else if (x - 1 >= 0 && y + 1 < 8)
            {
                if (!colorBoard[x - 1][y + 1] && OppositeColorBoard[x - 1][y + 1] != 2)
                {
                    colorBoard[x - 1][y + 1] = 1;
                }
            }
            if (chessBoard[x - 1][y - 1] == 12 && x - 1 >= 0 && y - 1 >= 0)
            {
                colorBoard[x - 1][y - 1] = 3;
                colorBoard[x][y] = 2;
                kingUnderCheck = true;
            }
            else if (x - 1 >= 0 && y - 1 >= 0)
            {
                if (!colorBoard[x - 1][y - 1] && OppositeColorBoard[x - 1][y - 1] != 2)
                {
                    colorBoard[x - 1][y - 1] = 1;
                }
            }
        }

        // return kingUnderCheck;

        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                if (colorBoard[i][j] > max)
                {
                    max = colorBoard[i][j];
                }
            }
        }
        return max;
    }

    void showMoves(int x, int y, int chessBoard[8][8], bool checkBoard[8][8], int colorBoard[8][8], int OppositeColorBoard[8][8], bool isKingUnderCheck)
    {
        //bool side = chessBoard[x][y] > 6;
        isKingUnderCheck = (OppositeColorBoard[x][y] == 2 || isKingUnderCheck);

        if (side)
        {
           /* if ((x < 7 && y < 7 && chessBoard[x + 1][y + 1] < 7 && chessBoard[x + 1][y + 1] != 0 && !isKingUnderCheck) || (OppositeColorBoard[x + 1][y + 1] == 2 && ((side ? chessBoard[x + 1][y + 1] < 7 : chessBoard[x + 1][y + 1] > 6)) && isKingUnderCheck))*/
            if ((x < 7 && y < 7 && chessBoard[x + 1][y + 1] < 7 && chessBoard[x + 1][y + 1] && !isKingUnderCheck) || (OppositeColorBoard[x + 1][y + 1] == 2 && chessBoard[x + 1][y + 1] < 7 && chessBoard[x + 1][y + 1] && isKingUnderCheck))
            { // black pawn kill right
                checkBoard[x + 1][y + 1] = 1;
            }
            /*if ((x < 7 && y > 0 && chessBoard[x + 1][y - 1] < 7 && chessBoard[x + 1][y - 1] && !isKingUnderCheck) || (OppositeColorBoard[x + 1][y - 1] == 2 && ((side ? chessBoard[x + 1][y - 1] < 7 : chessBoard[x + 1][y - 1] > 6)) && isKingUnderCheck))*/
            if ((x < 7 && y > 0 && chessBoard[x + 1][y - 1] < 7 && chessBoard[x + 1][y - 1] && !isKingUnderCheck) || (OppositeColorBoard[x + 1][y - 1] == 2 && chessBoard[x + 1][y - 1] < 7 && chessBoard[x + 1][y - 1] && isKingUnderCheck))
            { // black pawn kill left
                checkBoard[x + 1][y - 1] = 1;
            }
            if ((x < 7 && chessBoard[x + 1][y] == 0 && !isKingUnderCheck) || (OppositeColorBoard[x + 1][y] == 2 && !chessBoard[x + 1][y] && isKingUnderCheck))
            { // black pawn move 1 step down
                checkBoard[x + 1][y] = 1;
                if ((chessBoard[x + 2][y] == 0 && x == 1 && !isKingUnderCheck) || (OppositeColorBoard[x + 2][y] == 2 && x == 1 && !chessBoard[x + 2][y] && isKingUnderCheck))
                { // black pawn move 2 steps down
                    checkBoard[x + 2][y] = 1;
                }
            }
        }
        else
        {

            if ((x > 0 && y < 7 && chessBoard[x - 1][y + 1] > 6 && chessBoard[x - 1][y + 1] != 0 && !isKingUnderCheck) || (OppositeColorBoard[x - 1][y + 1] == 2 && ((side ? chessBoard[x - 1][y + 1] < 7 : chessBoard[x - 1][y + 1] > 6)) && isKingUnderCheck))
            { // white pawn kill right
                checkBoard[x - 1][y + 1] = 1;
            }
            if ((x > 0 && y > 0 && chessBoard[x - 1][y - 1] > 6 && chessBoard[x - 1][y - 1] != 0 && !isKingUnderCheck) || (OppositeColorBoard[x - 1][y - 1] == 2 && ((side ? chessBoard[x - 1][y - 1] < 7 : chessBoard[x - 1][y - 1] > 6)) && isKingUnderCheck))
            { // white pawn kill left
                checkBoard[x - 1][y - 1] = 1;
            }
            if ((chessBoard[x - 1][y] == 0 && x > 0 && !isKingUnderCheck) || (OppositeColorBoard[x - 1][y] == 2 && !chessBoard[x - 1][y] && isKingUnderCheck))
            { // white pawn move 1 step up
                checkBoard[x - 1][y] = 1;
                if ((chessBoard[x - 2][y] == 0 && x == 6 && !isKingUnderCheck) || (OppositeColorBoard[x - 2][y] == 2 && x == 6 && !chessBoard[x - 2][y] && isKingUnderCheck))
                { // white pawn move 2 steps up
                    checkBoard[x - 2][y] = 1;
                }
            }
        }
    }

    bool makeMove(int x, int y, int& prevX, int& prevY, int chessBoard[8][8], bool checkBoard[8][8], bool whiteBoard[8][8], bool blackBoard[8][8])
    {
        if (checkBoard[x][y] && x < 8 && y < 8 && x >= 0 && y >= 0)
        {
            chessBoard[x][y] = chessBoard[prevX][prevY];
            chessBoard[prevX][prevY] = 0;
            // prevX = x;
            // prevY = y;

            // upgrading the pawn
            if (x == 0 || x == 7)
            {
                cout << "Enter the piece you want to convert to : ";
                int type = 1;
                if (!side)
                {
                    while (type < 2 || type > 5)
                    {
                        cin >> type;
                        if (type < 2 || type > 5)
                        {
                            cout << "Invalid type, please enter again : ";
                        }
                    }
                }
                else
                {
                    while (type < 8 || type > 11)
                    {
                        cin >> type;
                        if (type < 8 || type > 11)
                        {
                            cout << "Invalid type, please enter again : ";
                        }
                    }
                    chessBoard[x][y] = type;
                }
            }
            return true; // returns true if move is made
        }
        return false; // returns false if no move is made
    }
};