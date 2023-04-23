#include "GameModEasy.h"

SDL_Texture* FON_EASY_TEXTURE = NULL;
SDL_Surface* FON_EASY_SURFACE = NULL;
SDL_Rect FON_EASY_RECT = { 280,0,720,720 };
SDL_Texture* SNAKE_EASY_TEXTURE = NULL;
SDL_Surface* SNAKE_EASY_SURFACE = NULL;

SDL_Surface* AppleSurface = NULL;
SDL_Texture* AppleTexture = NULL;
SDL_Surface* BananaSurface = NULL;
SDL_Texture* BananaTexture = NULL;
SDL_Surface* KlubnicaSurface = NULL;
SDL_Texture* KlubnicaTexture = NULL;

SDL_Texture* ScoreTexture = NULL;

const int WIDTH_EASY1 = 280;
const int WIDTH_EASY2 = 960;
const int HEIGHT_EASY1 = 0;
const int HEIGHT_EASY2 = 680;

int xE = 600, yE = 720 / 2 - 40, fruitX, fruitY;

int score = 0;

bool GameOver = false;
int SnakeX[324]; int SnakeY[324];
int LenSnake = 1;

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

	BananaSurface = IMG_Load("Textures\\BANAN.bmp");
	SDL_SetColorKey(BananaSurface, SDL_TRUE, SDL_MapRGB(BananaSurface->format, 255, 255, 255));
	BananaTexture = SDL_CreateTextureFromSurface(renderer, BananaSurface);
	SDL_FreeSurface(BananaSurface);

	KlubnicaSurface = IMG_Load("Textures\\KLUBNIKA.bmp");
	SDL_SetColorKey(KlubnicaSurface, SDL_TRUE, SDL_MapRGB(KlubnicaSurface->format, 255, 255, 255));
	KlubnicaTexture = SDL_CreateTextureFromSurface(renderer, KlubnicaSurface);
	SDL_FreeSurface(KlubnicaSurface);

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
SDL_Texture* Get_TextTextureEasy(SDL_Renderer*& renderer, char* text, TTF_Font* font) {
	SDL_Surface* TextSurface = NULL;
	SDL_Color fore_color = { 240,100,100 };
	SDL_Color back_color = { 255,20,20,255 };
	TextSurface = TTF_RenderUTF8_Solid(font, text, fore_color);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, TextSurface);
	SDL_FreeSurface(TextSurface);
	return texture;
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
	}
}

string Food[3];
int Food_Number;
int randomFood;
bool chooseFood = true;

TTF_Font* fontScore;
void RenderGame(SDL_Renderer*RenderGame) {
	fontScore = TTF_OpenFont("FontScore.ttf", 54);
	string text = u8"Счёт ";
	string scoreOne = to_string(score);
	text = text + scoreOne;

	char textScore[15];
	strcpy_s(textScore,text.c_str()); //Преобразование из string в char*
	SDL_Rect TextRect = { 10,5,150,70 };

	ScoreTexture = Get_TextTextureEasy(RenderGame,textScore, fontScore);
	
	Food[0] = "Яблоко";
	Food[1] = "Клубника";
	Food[2] = "Банан";
	if (chooseFood == true) {//Шансы появления еды определенного типа
		randomFood = rand() % 100;
		if (randomFood < 50)
			Food_Number = 0;
		if (randomFood >= 50 && randomFood < 80)
			Food_Number = 1;
		if (randomFood >= 80 && randomFood < 100)
			Food_Number = 2;
		chooseFood = false;
	}
	SDL_SetRenderDrawColor(RenderGame, 201, 201, 201, 0);
	SDL_RenderClear(RenderGame);
	SDL_RenderCopy(RenderGame, FON_EASY_TEXTURE, NULL, &FON_EASY_RECT);
	SDL_RenderCopy(RenderGame, ScoreTexture, NULL, &TextRect);

	SDL_SetRenderDrawColor(RenderGame, 195, 195, 195, 0);
	SetkaEasy(RenderGame);                    //Можно включить по желанию

	SDL_SetRenderDrawColor(RenderGame, 255, 0, 0, 0);

	SDL_Rect CRAY = { 279,0,722,720 };
	SDL_RenderDrawRect(RenderGame, &CRAY);

	for (int x = 280; x < 1000;x += 40) {
		for (int y = 0; y < 720; y += 40) {
			if (x == xE && y == yE) {
				SDL_Rect rect = { x, y, 40,40 };
				SDL_RenderCopy(RenderGame, SNAKE_EASY_TEXTURE, NULL, &rect);
			}
			if (x == fruitX && y == fruitY) {
				SDL_Rect Rect = { fruitX,fruitY,40,40 };
				if(Food_Number==0)
					SDL_RenderCopy(RenderGame, AppleTexture, NULL, &Rect);
				if (Food_Number == 1)
					SDL_RenderCopy(RenderGame, KlubnicaTexture, NULL, &Rect);
				if (Food_Number == 2)
					SDL_RenderCopy(RenderGame, BananaTexture, NULL, &Rect);
			}
			for (int i = 0; i < LenSnake;i++) {
				if (SnakeX[i] == x && SnakeY[i] == y) {

					SDL_Rect rect = { SnakeX[i], SnakeY[i], 40,40 };
					SDL_RenderCopy(RenderGame, SNAKE_EASY_TEXTURE, NULL, &rect);
				}

			}

		}
		
	}
}


void Activity(SDL_Event event) {

	switch (event.type)
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
			case SDLK_a:
				if(Dir!=RIGHT)          // ВЛЕВО
				Dir = LEFT; break;
			case SDLK_w: 
				if(Dir != DOWN)         // ВВЕРХ
				Dir = UP; break;
			case SDLK_d:                // ВПРАВО
				if(Dir != LEFT)
				Dir = RIGHT; break;
			case SDLK_s:                // ВНИЗ
				if (Dir != UP)         
				Dir = DOWN; break;
			case SDLK_ESCAPE:
				cout << "Escape was pressed" << endl; break;
			}
}

bool Left = false, Right = false, Up = false, Down = false;

void GameLogicEasy() {
	int LastX = SnakeX[0], LastY = SnakeY[0];
	int LastXX, LastYY;
	SnakeX[0] = xE;
	SnakeY[0] = yE;

	for (int i = 0; i < LenSnake;i++) {
		LastXX = SnakeX[i];
		LastYY = SnakeY[i];
		SnakeX[i] = LastX;
		SnakeY[i] = LastY;
		LastX = LastXX;
		LastY = LastYY;
	}
	
		switch (Dir) {
		case LEFT:      // ВЛЕВО
			Left = true;
			Right = false;
			Down = false;
			Up = false;
			break;
			cout << "OK" << endl;
		case UP:      // ВВЕРХ
			Left = false;
			Right = false;
			Down = false;
			Up = true;
			break;
		case RIGHT:      // ВПРАВО
			Left = false;
			Right = true;
			Down = false;
			Up = false
				; break;
		case DOWN:      // ВНИЗ
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
		if (Food_Number == 0)
			score++;
		if (Food_Number == 1)
			score += 2;
		if (Food_Number == 2)
			score += 3;
		
		fruitX = 0;
		fruitY = 0;
		LenSnake++;
		flagFruit = false;
		chooseFood = true;
		FruitSpawn();
		UKUS_Sound();
	}
	for (int i = 1; i < LenSnake;i++) { //Проверка не был ли съеден хвост
		if (SnakeX[i] == xE && SnakeY[i] == yE) {
			cout << "GameOver!" << endl;
			GameOver = true;
		}
	}
	if ((xE < 280 || xE > 960) || (yE < 0 || yE > 680)) { // Условие выхода за рамки поля
		cout << "GameOver!" << endl; GameOver = true;
	}
}

bool LoadTexturesEasyBool = true;

//_______________________________________________________________________________
clock_t start = clock();    //Необходим для отвязки FPS приложения от игры!!!!!!!
//_______________________________________________________________________________


void EasyMode(SDL_Renderer* renderer, SDL_Event event,bool &Easy,bool &StartGame) {
	if (LoadTexturesEasyBool == true) {
		LoadTexturesEasy(renderer);
		Dir = START;
		LoadTexturesEasyBool = false;
		PlayEasySound();
	}
	if (GameOver == false) {
		Activity(event);
		if (clock() - start >= 500) { //Обновление рендера игры
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
		GameOver = false;
		LoadTexturesEasyBool = true;
		score = 0;
		xE = 600, yE = 720 / 2 - 40;
		
		DeleteTexturesEasy();
		PlayFonMusic();
		for (int i = 0; i < LenSnake;i++)
		{
			SnakeX[i] = 0; SnakeY[i] = 0;
		}
			LenSnake = 1;
	}
	
	SDL_Delay(16);

}