#include "GameModEasy.h"
#include <ctime>


SDL_Texture* FON_EASY_TEXTURE = NULL;
SDL_Surface* FON_EASY_SURFACE = NULL;
SDL_Rect FON_EASY_RECT = { 280,0,720,720 };
SDL_Texture* SNAKE_EASY_TEXTURE = NULL;
SDL_Surface* SNAKE_EASY_SURFACE = NULL;

SDL_Surface* AppleSurface = NULL;
SDL_Texture* AppleTexture = NULL;


const int WIDTH_EASY1 = 280;
const int WIDTH_EASY2 = 960;
const int HEIGHT_EASY1 = 0;
const int HEIGHT_EASY2 = 680;

int xE = 600, yE = 720 / 2 - 40, fruitX, fruitY;
int score = 0;
bool GameOver = false;
int SnakeX[324]; int SnakeY[324];
int LenSnake = 1;
const Uint8* keys = SDL_GetKeyboardState(NULL);
void LoadTexturesEasy(SDL_Renderer*renderer) {

	FON_EASY_SURFACE = IMG_Load("Textures\\EASY_FON.bmp");
	SDL_SetColorKey(FON_EASY_SURFACE, SDL_TRUE, SDL_MapRGB(FON_EASY_SURFACE->format, 255, 255, 255));
	FON_EASY_TEXTURE = SDL_CreateTextureFromSurface(renderer, FON_EASY_SURFACE);
	SDL_FreeSurface(FON_EASY_SURFACE);

	SNAKE_EASY_SURFACE = IMG_Load("Textures\\SnakeTextureEasy.bmp");
	SDL_SetColorKey(SNAKE_EASY_SURFACE, SDL_TRUE, SDL_MapRGB(SNAKE_EASY_SURFACE->format, 255, 255, 255));
	SNAKE_EASY_TEXTURE = SDL_CreateTextureFromSurface(renderer, SNAKE_EASY_SURFACE);
	SDL_FreeSurface(SNAKE_EASY_SURFACE);

	AppleSurface = IMG_Load("Textures\\apple.bmp");
	SDL_SetColorKey(AppleSurface, SDL_TRUE, SDL_MapRGB(AppleSurface->format, 255, 255, 255));
	AppleTexture = SDL_CreateTextureFromSurface(renderer, AppleSurface);
	SDL_FreeSurface(AppleSurface);
}
void DeleteTexturesEasy() {
	SDL_DestroyTexture(FON_EASY_TEXTURE);
	SDL_DestroyTexture(AppleTexture);
	SDL_DestroyTexture(SNAKE_EASY_TEXTURE);
}
void SetkaEasy(SDL_Renderer* renderer) {
	for (int i = 0; i < 760; i += 40) {
		SDL_RenderDrawLine(renderer, 280 + i, 0, 280 + i, 720);
	}
	for (int i = 0; i < 760; i += 40) {
		SDL_RenderDrawLine(renderer, 280, i, 1000, i);
	}
}




enum Direction {
	START = 0, LEFT, RIGHT, UP, DOWN
};
Direction Dir;
bool flagFruit = false;
void FruitSpawn() {
	while (flagFruit == false) {
		fruitX = rand() % (WIDTH_EASY2 - WIDTH_EASY1 + 1) + WIDTH_EASY1;
		fruitY = rand() % (HEIGHT_EASY2 - HEIGHT_EASY1 + 1) + HEIGHT_EASY1;
		if (fruitX % 40 == 0 && fruitY % 40 == 0) {
			flagFruit = true;
		}
		else {
			//std::cout << fruitX << " " << fruitY << std::endl;
		}
	}
}
void RenderGame(SDL_Renderer*RenderGame) {

	SDL_SetRenderDrawColor(RenderGame, 0, 0, 0, 0);
	SDL_RenderClear(RenderGame);
	SDL_RenderCopy(RenderGame, FON_EASY_TEXTURE, NULL, &FON_EASY_RECT);
	SDL_SetRenderDrawColor(RenderGame, 255, 255, 255, 0);
	SetkaEasy(RenderGame);
	for (int x = 280; x < 1000;x += 40) {
		for (int y = 0; y < 720; y += 40) {
			if (x == xE && y == yE) {
				SDL_Rect rect = { x, y, 40,40 };
				SDL_RenderCopy(RenderGame, SNAKE_EASY_TEXTURE, NULL, &rect);
			}
			if (x == fruitX && y == fruitY) {
				SDL_Rect AppleRect = { fruitX,fruitY,40,40 };
				SDL_RenderCopy(RenderGame, AppleTexture, NULL, &AppleRect);
			}
			for (int i = 0; i < LenSnake;i++) {
				if (SnakeX[i] == x && SnakeY[i] == y) {
					SDL_Rect rect = { SnakeX[i], SnakeY[i], 40,40 };
					SDL_RenderCopy(RenderGame, SNAKE_EASY_TEXTURE, NULL, &rect);
				}

			}

		}
		
	}//SDL_RenderPresent(RenderGame);
	//SDL_Delay(250);
}

//const Uint8 *keystates = SDL_GetKeyboardState(NULL);
void Activity(SDL_Event event) {

	switch (event.type)
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
			case SDLK_a:      // ÂËÅÂÎ
				Dir = LEFT; break;
			case SDLK_w:      // ÂÂÅÐÕ
				Dir = UP; break;
			case SDLK_d:      // ÂÏÐÀÂÎ
				Dir = RIGHT; break;
			case SDLK_s:      // ÂÍÈÇ
				Dir = DOWN; break;
			case SDLK_ESCAPE: break;
				cout << "Escape was pressed" << endl;
			}
}

bool Left = false, Right = false, Up = false, Down = false;
void GameLogicEasy() {
	int LastX = SnakeX[0], LastY = SnakeY[0];
	int LastXX, LastYY;
	SnakeX[0] = xE;
	SnakeY[0] = yE;

	for (int i = 1; i < LenSnake;i++) {
		LastXX = SnakeX[i];
		LastYY = SnakeY[i];
		SnakeX[i] = LastX;
		SnakeY[i] = LastY;
		LastX = LastXX;
		LastY = LastYY;
	}
	
		switch (Dir) {
		case LEFT:      // ÂËÅÂÎ
			Left = true;
			Right = false;
			Down = false;
			Up = false;
			break;
			cout << "OK" << endl;
		case UP:      // ÂÂÅÐÕ
			Left = false;
			Right = false;
			Down = false;
			Up = true;
			break;
		case RIGHT:      // ÂÏÐÀÂÎ
			Left = false;
			Right = true;
			Down = false;
			Up = false
				; break;
		case DOWN:      // ÂÍÈÇ
			Left = false;
			Right = false;
			Down = true;
			Up = false;
			break;
		}
		
		

	if (Right == true)
		xE += 40;
	if (Left == true)
		xE -= 40;
	if (Up == true)
		yE -= 40;
	if (Down == true)
		yE += 40;

	if ((xE == fruitX) && (yE == fruitY)) {
		score += 2;
		fruitX = 0;
		fruitY = 0;
		LenSnake++;
		flagFruit = false;
		FruitSpawn();
	}
	for (int i = 1; i < LenSnake;i++) { //Ïðîâåðêà íå áûë ëè ñúåäåí õâîñò
		//if (SnakeX[i] == xE && SnakeY[i] == yE)
			//cout << "GameOver!" << endl;
			//GameOver = true;
	}
	cout << xE << " " << yE << endl;
	if ((xE < 280 || xE > 960) || (yE < 0 || yE > 680)) {
		cout << "GameOver!" << endl; GameOver = true;
	}
}

bool LoadTexturesEasyBool = true;
clock_t start = clock();//Íåîáõîäèì äëÿ îòâÿçêè FPS ïðèëîæåíèÿ îò èãðû
void EasyMode(SDL_Renderer* renderer, SDL_Event event,bool &Easy,bool &StartGame) {
	if (LoadTexturesEasyBool == true) {
		LoadTexturesEasy(renderer);
		Dir = START;
		LoadTexturesEasyBool = false;
	}
	if (GameOver == false) {
		Activity(event);
		if (clock() - start >= 500) {
			FruitSpawn();
			GameLogicEasy();
			RenderGame(renderer);
			start = clock();
			SDL_RenderPresent(renderer);
		}	
	}
	else {
		Easy = false;
		StartGame = false;
		LoadTexturesEasyBool = true;
		DeleteTexturesEasy();
		//return;
	}
	
	SDL_Delay(16);

}