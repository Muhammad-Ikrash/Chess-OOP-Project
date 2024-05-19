#include "pieces.h"
#include "classChess.h"
#include "raylib.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;


void DrawBoard(Texture2D white_queen, Texture2D white_king, Texture2D white_rook, Texture2D white_knight, Texture2D white_bishop, Texture2D white_pawn, Texture2D black_queen, Texture2D black_king, Texture2D black_rook, Texture2D black_knight, Texture2D black_bishop, Texture2D black_pawn, int chessBoard[8][8])
{


	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (chessBoard[i][j] == 5)
			{
				DrawTexturePro(white_queen, { 0.f,0.f,(float)white_queen.width,(float)white_queen.height }, { left + border + j * box + 3.f,border + i * box + 2.f,100,100 }, { 0.f,0.f }, 0.f, WHITE);
			}
			else if (chessBoard[i][j] == 6)
			{
				DrawTexturePro(white_king, { 0.f,0.f,(float)white_king.width,(float)white_king.height }, { left + border + j * box + 3.f,border + i * box + 2.f,100,100 }, { 0.f,0.f }, 0.f, WHITE);
			}
			else if (chessBoard[i][j] == 2)
			{
				DrawTexturePro(white_rook, { 0.f,0.f,(float)white_rook.width,(float)white_rook.height }, { left + border + j * box + 3.f,border + i * box + 2.f,100,100 }, { 0.f,0.f }, 0.f, WHITE);
			}
			else if (chessBoard[i][j] == 3)
			{
				DrawTexturePro(white_knight, { 0.f,0.f,(float)white_knight.width,(float)white_knight.height }, { left + border + j * box + 3.f,border + i * box + 2.f,100,100 }, { 0.f,0.f }, 0.f, WHITE);
			}
			else if (chessBoard[i][j] == 4)
			{
				DrawTexturePro(white_bishop, { 0.f,0.f,(float)white_bishop.width,(float)white_bishop.height }, { left + border + j * box + 3.f,border + i * box + 2.f,100,100 }, { 0.f,0.f }, 0.f, WHITE);
			}
			else if (chessBoard[i][j] == 1)
			{
				DrawTexturePro(white_pawn, { 0.f,0.f,(float)white_pawn.width,(float)white_pawn.height }, { left + border + j * box + 3.f,border + i * box + 2.f,100,100 }, { 0.f,0.f }, 0.f, WHITE);
			}

			//for black pieces
			else if (chessBoard[i][j] == 11)
			{
				DrawTexturePro(black_queen, { 0.f,0.f,(float)black_queen.width,(float)black_queen.height }, { left + border + j * box + 3.f,border + i * box + 2.f,100,100 }, { 0.f,0.f }, 0.f, WHITE);
			}
			else if (chessBoard[i][j] == 12)
			{
				DrawTexturePro(black_king, { 0.f,0.f,(float)black_king.width,(float)black_king.height }, { left + border + j * box + 3.f,border + i * box + 2.f,100,100 }, { 0.f,0.f }, 0.f, WHITE);
			}
			else if (chessBoard[i][j] == 8)
			{
				DrawTexturePro(black_rook, { 0.f,0.f,(float)black_rook.width,(float)black_rook.height }, { left + border + j * box + 3.f,border + i * box + 2.f,100,100 }, { 0.f,0.f }, 0.f, WHITE);
			}
			else if (chessBoard[i][j] == 9)
			{
				DrawTexturePro(black_knight, { 0.f,0.f,(float)black_knight.width,(float)black_knight.height }, { left + border + j * box + 3.f,border + i * box + 2.f,100,100 }, { 0.f,0.f }, 0.f, WHITE);
			}
			else if (chessBoard[i][j] == 10)
			{
				DrawTexturePro(black_bishop, { 0.f,0.f,(float)black_bishop.width,(float)black_bishop.height }, { left + border + j * box + 3.f,border + i * box + 2.f,100,100 }, { 0.f,0.f }, 0.f, WHITE);
			}
			else if (chessBoard[i][j] == 7)
			{
				DrawTexturePro(black_pawn, { 0.f,0.f,(float)black_pawn.width,(float)black_pawn.height }, { left + border + j * box + 3.f,border + i * box + 2.f,100,100 }, { 0.f,0.f }, 0.f, WHITE);
			}
		}
	}

}

bool disp = false;
bool soundPLay = true;

void DrawHome(Texture2D main, Sound click, Chess& obj, int& turn)
{
	DrawTexturePro(main, { 0.0f, 0.0f, (float)main.width, (float)main.height }, { 0.0f, 0.0f, (float)BOARD_WIDTH + 500, (float)BOARD_HEIGHT }, { 0.0f, 0.0f }, 0.0f, WHITE);

	//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	DrawText("Chess Masters", 373, 53, 100, LIGHTRED);
	DrawText("Chess Masters", 370, 50, 100, MAROON);
	DrawRectangle(370, 150, 772, 10, gg);///under lined

	//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	DrawRectangle(500, 500, 500, 100, gg);
	//if mouse is hovered(not pressed) over the start game button then rectangle will change color
	if (GetMouseX() >= 500 && GetMouseX() <= 1000 && GetMouseY() >= 500 && GetMouseY() <= 600)
	{
		DrawRectangle(500, 500, 500, 100, RED);
		SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
	}
	DrawText("Start Game", 603, 528, 50, PURPLE);
	DrawText("Start Game", 600, 525, 50, DARKPURPLE);

	//DrawLine(1000, 0, 1000, 1000, GREEN);
	if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
	{
		if (GetMouseX() >= 500 && GetMouseX() <= 1000 && GetMouseY() >= 500 && GetMouseY() <= 600)
		{
			if (soundPLay)
				PlaySound(click);

			if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
			{
				disp = true;
				return;
			}
		}
	}

	//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	DrawRectangle(500, 700, 500, 100, gg);
	//if mouse is hovered(not pressed) over the load game button then rectangle will change color
	if (GetMouseX() >= 500 && GetMouseX() <= 1000 && GetMouseY() >= 700 && GetMouseY() <= 800)
	{
		DrawRectangle(500, 700, 500, 100, RED);
		SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
	}
	DrawText("Load Game", 603, 728, 50, PURPLE);
	DrawText("Load Game", 600, 725, 50, DARKPURPLE);

	if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
	{
		if (GetMouseX() >= 500 && GetMouseX() <= 1000 && GetMouseY() >= 700 && GetMouseY() <= 800)
		{
			ifstream file("save.txt");
			if (file.is_open())
			{
				file >> turn;
				for (int i = 0; i < 8; i++)
				{
					for (int j = 0; j < 8; j++)
						file >> obj.chessBoard[i][j];
				}
				file.close();
				disp = true;
				if (soundPLay)
					PlaySound(click);
			}
			else {
				DrawText("No saved game found", 500, 500, 50, RED);
				
			}
			
		}
	}


}

void selectCoOrdinates(int& x, int& y, int& x1, int& y1) {
	int tempX = (GetMouseX() - 250 - 74), tempY = (GetMouseY() - 74);
	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
		//DrawText("Select the piece", 1000, 100, 50, RED);
		x = ((tempX >= 0) ? tempX / 106 : -1);
		y = ((tempY >= 0) ? tempY / 106 : -1);
	}
	if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
		//DrawText("Select the destination", 1000, 100, 50, RED);
		x1 = ((tempX >= 0) ? tempX / 106 : -1);
		y1 = ((tempY >= 0) ? tempY / 106 : -1);
	}
}

bool CordinatesAreValid(int& x, int& y, int& x1, int& y1, Chess& obj, int turn) {

	if (obj.check == 3) {
		DrawRectangle(left + border + obj.blackKingX * box, border + obj.blackKingY * box, box, box, RED);
		//cout << "Black King is under check" << endl;
	}
	else if (obj.check == -3) {
		DrawRectangle(left + border + obj.whiteKingX * box, border + obj.whiteKingY * box, box, box, RED);
		//cout << "White King is under check" << endl;
	}

	if (x >= 0 && x < 8 && y >= 0 && y < 8 && x1 >= 0 && x1 < 8 && y1 >= 0 && y1 < 8 && obj.chessBoard[y][x] && ((turn % 2) ? obj.chessBoard[y][x] < 7 : obj.chessBoard[y][x] > 6)) {
		DrawRectangle(left + border + x * box, border + y * box, box, box, GREEN);
		return true;
	}

	

	x1 = -1, y1 = -1;
	return false;
}

void testingDragDrop(int selectX, int selectY, int moveX, int moveY, Chess& obj) {
	swap(obj.chessBoard[selectY][selectX], obj.chessBoard[moveY][moveX]);
}

void saveGame(Chess& obj, int turn) {
	ofstream file("save.txt");

	file << turn << endl;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++)
			file << obj.chessBoard[i][j] << " ";
		file << endl;
	}
	file.close();

}

void GameOptions(Sound click, Chess& obj, int& turn)
{

	DrawRectangle(10, 40, 150, 40, RED);
	DrawText("Game Options", 20, 50, 20, BLACK);
	if (GetMouseX() >= 10 && GetMouseX() <= 160 && GetMouseY() >= 90 && GetMouseY() <= 130) SetMouseCursor(MOUSE_CURSOR_POINTING_HAND); //new game
	if (GetMouseX() >= 10 && GetMouseX() <= 160 && GetMouseY() >= 140 && GetMouseY() <= 180) SetMouseCursor(MOUSE_CURSOR_POINTING_HAND); //rewind
	if (GetMouseX() >= 10 && GetMouseX() <= 160 && GetMouseY() >= 190 && GetMouseY() <= 230) SetMouseCursor(MOUSE_CURSOR_POINTING_HAND); //exit
	if (GetMouseX() >= 10 && GetMouseX() <= 160 && GetMouseY() >= 240 && GetMouseY() <= 280) SetMouseCursor(MOUSE_CURSOR_POINTING_HAND); //save and exit
	if (GetMouseX() >= 10 && GetMouseX() <= 160 && GetMouseY() >= 290 && GetMouseY() <= 330) SetMouseCursor(MOUSE_CURSOR_POINTING_HAND); //sound on/off
	SetMouseCursor(MOUSE_CURSOR_ARROW); //default cursor


	DrawRectangle(10, 90, 150, 40, BLACK);
	DrawText("New Game", 20, 100, 20, WHITE);

	DrawRectangle(10, 140, 150, 40, BLACK);
	DrawText("Rewind Move", 20, 150, 20, WHITE);

	DrawRectangle(10, 190, 150, 40, BLACK);
	DrawText("Exit Game", 20, 200, 20, WHITE);

	DrawRectangle(10, 240, 150, 40, BLACK);
	DrawText("Save and Exit", 20, 250, 20, WHITE);

	DrawRectangle(10, 290, 150, 40, BLACK);
	DrawText("Sound On/Off", 20, 300, 20, WHITE);

	///=====new game

	if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
	{
		if (GetMouseX() >= 10 && GetMouseX() <= 160 && GetMouseY() >= 90 && GetMouseY() <= 130)
		{
			obj.readyBoardforNewGame();
			turn = 1;

			if (soundPLay)	PlaySound(click);
			//code here
		}
	}

	///====REWIND ======	

	if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
	{
		if (GetMouseX() >= 10 && GetMouseX() <= 160 && GetMouseY() >= 140 && GetMouseY() <= 180)
		{
			//saveGame();
			obj.undoMove(turn);
			if (soundPLay)	PlaySound(click);
			//code here
		}
	}

	///====EXIT GAME ======
	if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
	{
		if (GetMouseX() >= 10 && GetMouseX() <= 160 && GetMouseY() >= 190 && GetMouseY() <= 230)
		{
			obj.readyBoardforNewGame();
			turn = 1;
			disp = false;
			if (soundPLay)	PlaySound(click);
		}
	}

	///SAVE AND EXIT GAME

	if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
	{
		if (GetMouseX() >= 10 && GetMouseX() <= 160 && GetMouseY() >= 240 && GetMouseY() <= 280)
		{
			saveGame(obj, turn);
			obj.readyBoardforNewGame();
			turn = 1;
			disp = false;
			if (soundPLay)	PlaySound(click);
		}
	}

	///sound off 
	if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
	{
		if (GetMouseX() >= 10 && GetMouseX() <= 160 && GetMouseY() >= 290 && GetMouseY() <= 330)
		{
			if (soundPLay)
				soundPLay = false;
			else
				soundPLay = true;

			if (soundPLay)	PlaySound(click);

		}
	}
}



void drawGradient()
{
	Rectangle rec = { 0, 0, 1500, 1000 };
	Color color1 = { 0, 0, 50, 255 }; // Very dark blue
	Color color2 = { 0, 0, 0, 255 };  // Black
	DrawRectangleGradientV(0, 0, 1500, 1000, color1, color2);
}

int loadRecWidth = 10; //variable for rectangle width, which will increase with time
double prevTime = 0;

void drawLoadingBarBoundingBox()
{
	DrawLine(445, 490, 445, 510, RED);
	DrawLine(1005, 490, 1005, 510, RED);
	DrawLine(445, 490, 1005, 490, RED);
	DrawLine(445, 510, 1005, 510, RED);
}


void drawLoadingBar()
{
	drawLoadingBarBoundingBox();
	Rectangle loadingBar = { 450,495,loadRecWidth,10 };
	DrawRectangleRec(loadingBar, RED);

	if (GetTime() >= prevTime)
	{
		loadRecWidth += 3;
		prevTime = GetTime();
	}
}


void loadingScreen()
{
	drawGradient();
	DrawText("L\tO	A	D	I	N	G . . .", 485, 430, 47, RED);

	if (loadRecWidth <= 550)
		drawLoadingBar();
	if (loadRecWidth > 550 && GetTime() <= 6.0)
	{
		drawLoadingBarBoundingBox();
		Rectangle loadingBar = { 450,495,550,10 };
		DrawRectangleRec(loadingBar, RED);
	}
}

bool winTime = false;

double tt = 0;


void displayWinner(int x)
{
	DrawRectangle(0, 0, 1500, 1000, { 30,10,70,170 });
	if (x == 3)
	{
		DrawText("White Wins!", 600, 425, 50, RED);

	}
	else if (x == -3)
	{
		DrawText("Black Wins!", 600, 425, 50, RED);
	}
}


int main() {


	InitWindow(WINDOWS_WIDTH, WINDOW_HEIGHT, "Chess");

	Image icon = LoadImage("8.png");
	SetWindowIcon(icon);
	InitAudioDevice();
	ShowCursor();
	SetTargetFPS(60);

	///loading textures
	Texture2D board = LoadTexture("newb.png");
	Texture2D main = LoadTexture("mainpage.png");
	Texture2D newmain = LoadTexture("newmain.png");
	Texture2D white_queen = LoadTexture("5.png");
	Texture2D white_king = LoadTexture("6.png");
	Texture2D white_rook = LoadTexture("2.png");
	Texture2D white_knight = LoadTexture("3.png");
	Texture2D white_bishop = LoadTexture("4.png");
	Texture2D white_pawn = LoadTexture("1.png");
	Texture2D black_queen = LoadTexture("11.png");
	Texture2D black_king = LoadTexture("12.png");
	Texture2D black_rook = LoadTexture("8.png");
	Texture2D black_knight = LoadTexture("9.png");
	Texture2D black_bishop = LoadTexture("10.png");
	Texture2D black_pawn = LoadTexture("7.png");

	///loading audio
	Sound move = LoadSound("piecemove.wav");
	Sound click = LoadSound("click.wav");

	Chess obj;
	obj.resetChessBoard();
	obj.testingChessBoardSet();
	int selectX = -1, selectY = -1, MoveX = -1, MoveY = -1, turn = 1;
	while (!WindowShouldClose()) {
		BeginDrawing();
		//ClearBackground(WHITE);
		ClearBackground({ 0, 0, 50, 255 });

		if (GetTime() <= 6.0)
			loadingScreen();

		else if (disp && !obj.HasGameEnded(turn))
		{
			selectCoOrdinates(selectX, selectY, MoveX, MoveY);
			DrawTexturePro(board, { 0.0f, 0.0f, (float)board.width, (float)board.height }, { (float)left, 0.0f, (float)BOARD_WIDTH, (float)BOARD_HEIGHT }, { 0.0f, 0.0f }, 0.0f, WHITE);

			///=======================================================
			// testing
			//DrawRectangle(20, 500, 100, 250, BLACK);
			DrawText("Turn: ", 20, 500, 80, WHITE);
			//DrawRectangle(40, 600, 60, 150, BLACK);
			DrawText((turn % 2) ? "White" : "Black", 40, 600, 50, WHITE);
			///=======================================================
			GameOptions(click, obj, turn);

			if (CordinatesAreValid(selectX, selectY, MoveX, MoveY, obj, turn) && obj.takeTurn(selectX, selectY, MoveX, MoveY))
			{

				if (soundPLay)
					PlaySound(move);
				turn++;
				selectX = -1, selectY = -1, MoveX = -1, MoveY = -1;
			}
			DrawBoard(white_queen, white_king, white_rook, white_knight, white_bishop, white_pawn, black_queen, black_king, black_rook, black_knight, black_bishop, black_pawn, obj.chessBoard);
			obj.pawnPromotion();

		}
		else if (obj.check == -3 || obj.check == 3)
		{

			DrawTexturePro(board, { 0.0f, 0.0f, (float)board.width, (float)board.height }, { (float)left, 0.0f, (float)BOARD_WIDTH, (float)BOARD_HEIGHT }, { 0.0f, 0.0f }, 0.0f, WHITE);
			DrawBoard(white_queen, white_king, white_rook, white_knight, white_bishop, white_pawn, black_queen, black_king, black_rook, black_knight, black_bishop, black_pawn, obj.chessBoard);

			if (winTime == false)
			{
				tt = GetTime();
				winTime = true;
			}

			displayWinner(obj.check);
			if (GetTime() >= tt + 5.0)
			{
				obj.readyBoardforNewGame();
				winTime = false;
				disp = false;
			}
			turn = 1;
		}
		else
		{
			DrawHome(main, click, obj, turn);
		}

		EndDrawing();
	}
	CloseWindow();

	///Unloading Textures
	UnloadTexture(board);
	UnloadTexture(main);
	UnloadTexture(white_queen);
	UnloadTexture(white_king);
	UnloadTexture(white_rook);
	UnloadTexture(white_knight);
	UnloadTexture(white_bishop);
	UnloadTexture(white_pawn);
	UnloadTexture(black_queen);
	UnloadTexture(black_king);
	UnloadTexture(black_rook);
	UnloadTexture(black_knight);
	UnloadTexture(black_bishop);
	UnloadTexture(black_pawn);
	///Unloading Audio
	UnloadSound(move);
	UnloadSound(click);


	return 0;
}
