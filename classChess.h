#pragma once
#include<iostream>
#include<stack>
#include"pieces.h"
#include"raylib.h"

using namespace std;

#define BOARD_SIZE 8
#define BOARD_WIDTH 1000
#define BOARD_HEIGHT 1000
#define WINDOWS_WIDTH 1500
#define WINDOW_HEIGHT 1000
#define left 250
#define right 1250
#define border 74
#define box 106



class Chess
{

private:
public:
    int chessBoard[8][8] = {};
    bool checkBoard[8][8] = {};
    int whiteBoard[8][8] = {}; // to mark checked places for white pieces
    int blackBoard[8][8] = {}; // to mark checked places for black pieces
    int OldWhiteBoard[8][8] = {};
    int OldBlackBoard[8][8] = {};
    pieces* singlePiece = nullptr;
	int whiteKingX = 0, whiteKingY = 0, blackKingX = 0, blackKingY = 0;
    int check = 0;
    stack<History> history;
    pieces* pointer[13];

    //========================================================================================================================
    //========================================================================================================================

    void resetCheckBoard()
    {
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                checkBoard[i][j] = 0;
            }
        }
    }

    Chess()
    {

        pointer[1] = new pawn(0);
        pointer[2] = new rook(0);
        pointer[3] = new knight(0);
        pointer[4] = new bishop(0);
        pointer[5] = new queen(0);
        pointer[6] = new king(0);
        pointer[7] = new pawn(1);
        pointer[8] = new rook(1);
        pointer[9] = new knight(1);
        pointer[10] = new bishop(1);
        pointer[11] = new queen(1);
        pointer[12] = new king(1);
        check = -1;
    }

    ~Chess()
    {
        for (int i = 1; i < 13; i++)
        {
            delete pointer[i];
        }
    }

    void DrawGreen(Rectangle vmr, Color color) {


        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                if (checkBoard[i][j] == 1)
                {
                    DrawRectangle(left + border + i * box, border + j * box, box, box, GREEN); // Position and size of the rectangle
                    //DrawRectangleRec(vmr, color);
                }

            }
        }

    }

    void resetChessBoard()
    {

        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                checkBoard[i][j] = 0;
                whiteBoard[i][j] = 0;
                blackBoard[i][j] = 0;
                chessBoard[i][j] = 0;
            }
        }

        chessBoard[0][0] = 8;
        chessBoard[0][1] = 9;
        chessBoard[0][2] = 10;
        chessBoard[0][3] = 11;
        chessBoard[0][4] = 12;
        chessBoard[0][5] = 10;
        chessBoard[0][6] = 9;
        chessBoard[0][7] = 8;
        for (int i = 0; i < 8; i++)
        {
            chessBoard[1][i] = 7;
            chessBoard[6][i] = 1;
        }
        chessBoard[7][0] = 2;
        chessBoard[7][1] = 3;
        chessBoard[7][2] = 4;
        chessBoard[7][3] = 5;
        chessBoard[7][4] = 6;
        chessBoard[7][5] = 4;
        chessBoard[7][6] = 3;
        chessBoard[7][7] = 2;
    }

    void displayBoard()
    {
        cout << "The board is :                     The available moves are : " << endl;
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                cout << chessBoard[i][j] << " ";
            }
            cout << "                   ";
            for (int j = 0; j < 8; j++)
            {
                cout << checkBoard[i][j] << " ";
            }
            cout << endl;
        }

        cout << "\n\nThe White Board is :                     The Black Board is : " << endl;
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                cout << whiteBoard[i][j] << " ";
            }
            cout << "                   ";
            for (int j = 0; j < 8; j++)
            {
                cout << blackBoard[i][j] << " ";
            }
            cout << endl;
        }
    }

    void displayBoard(const int i)
    {
        cout << "The board is :                     The available moves are : " << endl;
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                cout << chessBoard[i][j] << " ";
            }
            cout << "                   ";
            for (int j = 0; j < 8; j++)
            {
                cout << checkBoard[i][j] << " ";
            }
            cout << endl;
        }
    }

    int markBoard(int turn)
    { // to fill the matrices whiteBoard and blackBoard
        int valWhite = 0, valBlack = 0;
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                OldWhiteBoard[i][j] = whiteBoard[i][j];
                OldBlackBoard[i][j] = blackBoard[i][j];
                whiteBoard[i][j] = 0;
                blackBoard[i][j] = 0;
            }
        }

        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {

                // filling the boards with all the possible moves of the pieces
                if (turn % 2 && chessBoard[i][j] > 6)
                {
                    valBlack = pointer[chessBoard[i][j]]->fillBoard(i, j, chessBoard, blackBoard, OldWhiteBoard);
                }
                else if (turn % 2 == 0 && chessBoard[i][j] > 0 && chessBoard[i][j] < 7)
                {
                    valWhite = pointer[chessBoard[i][j]]->fillBoard(i, j, chessBoard, whiteBoard, OldBlackBoard);
                }
				if (chessBoard[i][j] == 6)
                {
					whiteKingX = j;
					whiteKingY = i;
				}
                else if (chessBoard[i][j] == 12)
                {
					blackKingX = j;
					blackKingY = i;
				}
            }
        }

        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {

                // filling the boards with all the possible moves of the pieces
                if (turn % 2 == 0 && chessBoard[i][j] > 6)
                {
                    valBlack = pointer[chessBoard[i][j]]->fillBoard(i, j, chessBoard, blackBoard, OldWhiteBoard);
                }
                else if (turn % 2 && chessBoard[i][j] > 0 && chessBoard[i][j] < 7)
                {
                    valWhite = pointer[chessBoard[i][j]]->fillBoard(i, j, chessBoard, whiteBoard, OldBlackBoard);
                }
            }
        }

        if (valWhite == 3)
        {
            //cout << "Black King is under check" << endl;
			//DrawRectangle(left + border + blackKingX * box, border + blackKingY * box, box, box, RED);
            return 3;
        }
        else if (valBlack == 3)
        {
			//DrawRectangle(left + border + whiteKingX * box, border + whiteKingY * box, box, box, RED);
            //cout << "White King is under check" << endl;
            return -3;
        }
        else
        {
            return ((valWhite < valBlack) ? valWhite : valBlack);
        }
    }

    void readyBoardforNewGame() {
		for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
				chessBoard[i][j] = checkBoard[i][j] = whiteBoard[i][j] = blackBoard[i][j] = OldWhiteBoard[i][j] = OldBlackBoard[i][j] = 0;
			}
		}
		whiteKingX = whiteKingY = blackKingX = blackKingY = 0;
        while (!history.empty()) {
			history.pop();
        }
        check = -1;
        resetChessBoard();
    }

    void pawnPromotion() {
		for (int i = 0; i < 8; i++) {
			if (chessBoard[0][i] == 1) {
                DrawRectangle(125, 1000 / 2 - 100, 1250, 200, { 255,255,255, 170 });
				DrawText("Choose the piece you want to promote your pawn to", 340, 1000 / 2 - 90, 30, BLACK);
				DrawRectangle(235, 1000 / 2 - 30, 200, 60, WHITE);
				DrawText("QUEEN", 250, 1000 / 2 - 20, 50, BLACK);
                DrawRectangle( 500, 1000 / 2 - 30, 170, 60, WHITE);
				DrawText("ROOK", 515, 1000 / 2 - 20, 50, BLACK);
                DrawRectangle(735, 1000 / 2 - 30, 220, 60, WHITE);
				DrawText("KNIGHT", 750, 1000 / 2 - 20, 50, BLACK);
                DrawRectangle(1015, 1000 / 2 - 30, 220, 60, WHITE);
				DrawText("BISHOP", 1030, 1000 / 2 - 20, 50, BLACK);
				if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    if (GetMouseX() > 235 && GetMouseX() < 435 && GetMouseY() > 1000 / 2 - 30 && GetMouseY() < 1000 / 2 + 30) {
						chessBoard[0][i] = 5;
                    }
                    else if (GetMouseX() > 500 && GetMouseX() < 670 && GetMouseY() > 1000 / 2 - 30 && GetMouseY() < 1000 / 2 + 30) {
                        chessBoard[0][i] = 2;
					}
					else if (GetMouseX() > 735 && GetMouseX() < 955 && GetMouseY() > 1000 / 2 - 30 && GetMouseY() < 1000 / 2 + 30) {
						chessBoard[0][i] = 3;
					}
					else if (GetMouseX() > 1015 && GetMouseX() < 1235 && GetMouseY() > 1000 / 2 - 30 && GetMouseY() < 1000 / 2 + 30) {
						chessBoard[0][i] = 4;
					}
                }
                break;
			}
			if (chessBoard[7][i] == 7) {
                DrawRectangle(125, 1000 / 2 - 100, 1250, 200, { 255,255,255, 170 });
                DrawText("Choose the piece you want to promote your pawn to", 340, 1000 / 2 - 90, 30, BLACK);
                DrawRectangle(235, 1000 / 2 - 30, 200, 60, RAYWHITE);
                DrawText("QUEEN", 250, 1000 / 2 - 20, 50, BLACK);
                DrawRectangle(500, 1000 / 2 - 30, 170, 60, RAYWHITE);
                DrawText("ROOK", 515, 1000 / 2 - 20, 50, BLACK);
                DrawRectangle(735, 1000 / 2 - 30, 220, 60, RAYWHITE);
                DrawText("KNIGHT", 750, 1000 / 2 - 20, 50, BLACK);
                DrawRectangle(1015, 1000 / 2 - 30, 220, 60, RAYWHITE);
                DrawText("BISHOP", 1030, 1000 / 2 - 20, 50, BLACK);
				if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    if (GetMouseX() > 235 && GetMouseX() < 435 && GetMouseY() > 1000 / 2 - 30 && GetMouseY() < 1000 / 2 + 30) {
						chessBoard[7][i] = 11;
					}
                    else if (GetMouseX() > 500 && GetMouseX() < 670 && GetMouseY() > 1000 / 2 - 30 && GetMouseY() < 1000 / 2 + 30) {
						chessBoard[7][i] = 8;
					}
                    else if (GetMouseX() > 735 && GetMouseX() < 955 && GetMouseY() > 1000 / 2 - 30 && GetMouseY() < 1000 / 2 + 30) {
						chessBoard[7][i] = 9;
					}
                    else if (GetMouseX() > 1015 && GetMouseX() < 1235 && GetMouseY() > 1000 / 2 - 30 && GetMouseY() < 1000 / 2 + 30) {
						chessBoard[7][i] = 10;
					}
				}

			}
		}

    }

	void undoMove(int &turn) {
		
        for (int i = 0; i < 2; i++) {

            if (!history.empty()) {
			    History temp = history.top();
			    history.pop();
			    chessBoard[temp.prevY][temp.prevX] = temp.prevNum;
			    chessBoard[temp.newY][temp.newX] = temp.newNum;
                turn--;
		    }
        }
	}

    bool HasGameEnded(int turn) {
        check = markBoard(turn);
        bool isWhiteKingAlive = false, isBlackKingAlive = false;

        for (int i = 0; i < 64; i++) {
            if (chessBoard[i / 8][i % 8] == 6) {
                isWhiteKingAlive = true;
            }
            if (chessBoard[i / 8][i % 8] == 12) {
                isBlackKingAlive = true;
            }
        }

        int tempBoard[8][8] = { 0 };
        bool canCheckBeRemoved = (abs(check) != 3);
        for (int i = 0; i < 8 && !canCheckBeRemoved; i++) {
            for (int j = 0; j < 8; j++) {

                if (check == 3 && whiteBoard[i][j] == 2 && blackBoard[i][j] /*|| pointer[12]->fillBoard(blackKingX, blackKingY, chessBoard, tempBoard, whiteBoard) != 0*/) {
                    canCheckBeRemoved = true;
                    break;
                }
                if (check == -3 && blackBoard[i][j] == 2 && whiteBoard[i][j] /*|| pointer[6]->fillBoard(whiteKingX, whiteKingY, chessBoard, tempBoard, whiteBoard) != 0*/) {
                    canCheckBeRemoved = true;
                    break;
                }
            }
        }

		if (!isWhiteKingAlive) {
            check = -3;
            return true;
        }
		else if (!isBlackKingAlive) {
			check = 3;
			return true;
		}

        if (check == -3 && pointer[6]->fillBoard(whiteKingY, whiteKingX, chessBoard, tempBoard, blackBoard) != 0) {
			canCheckBeRemoved = true;
        }
		else if (check == 3 && pointer[12]->fillBoard(blackKingY, blackKingX, chessBoard, tempBoard, whiteBoard) != 0) {
			canCheckBeRemoved = true;
        }


        if (canCheckBeRemoved) {
            return false;
        }
        else if (check == 0 || !canCheckBeRemoved) {
            return true;
        }
    }


    bool takeTurn(int prevX, int prevY, int& NewX, int& NewY) {
        resetCheckBoard();
        if (chessBoard[prevY][prevX] > 6) {
            pointer[chessBoard[prevY][prevX]]->showMoves(prevY, prevX, chessBoard, checkBoard, blackBoard, whiteBoard, check == 3);

        }
        else {
			pointer[chessBoard[prevY][prevX]]->showMoves(prevY, prevX, chessBoard, checkBoard, whiteBoard, blackBoard, check == -3);
        }

		int newNum = chessBoard[NewY][NewX];
		int prevNum = chessBoard[prevY][prevX];
        if (pointer[chessBoard[prevY][prevX]]->makeMove(NewY, NewX, prevY, prevX, chessBoard, checkBoard, whiteBoard, blackBoard)) {
			history.push(History(prevX, prevY, NewX, NewY, prevNum, newNum));
            NewX = NewY = -1;
			return true;
		}
        NewX = NewY = -1;
        return false;
    }

    void testingChessBoardSet() {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                chessBoard[i][j] = 0;
            }
        }
        chessBoard[7][7] = 12;
        chessBoard[7][5] = 6;
    }
    //========================================================================================================================
    // friend functions
    // friend void king::showMoves(int x, int y, int chessBoard[8][8], bool checkBoard[8][8], bool whiteBoard[8][8], bool blackBoard[8][8]);
	friend ostream& operator<<(ostream& out, int chessBoard[8][8]);
    friend ostream& operator << (ostream& out, Chess& obj);
};

ostream& operator << (ostream& out, Chess& obj) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            out << obj.chessBoard[i][j] << endl;
        }
        cout << endl;
    }
    return out;
}

ostream& operator << (ostream& out, int chessBoard[8][8]) {
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++) {
			out << chessBoard[i][j] << " ";
        }
        out << endl;
    }
	return out;
}