#include "GameModEasy.h"
#include "GameSetting.h"
#include "Records.h"

//ЗАГРУЗКА ТЕКСТУР----------------------------------------------------------------

TTF_Font* fontScore = NULL;
TTF_Font* SnakeLenTTF = NULL;

SDL_Texture* SNAKE_EASY_TEXTURE = NULL;
SDL_Surface* SNAKE_EASY_SURFACE = NULL;

SDL_Surface* AppleSurface = NULL;
SDL_Texture* AppleTexture = NULL;
SDL_Surface* BananaSurface = NULL;
SDL_Texture* BananaTexture = NULL;
SDL_Surface* KlubnicaSurface = NULL;
SDL_Texture* KlubnicaTexture = NULL;

SDL_Texture* ScoreTexture = NULL;
SDL_Texture* LenSnakeTexture = NULL;

SDL_Surface* MenuIconSurface = NULL;
SDL_Texture* MenuIconTexture = NULL;

SDL_Surface* to_menuSurface = NULL;
SDL_Texture * to_menuTexture = NULL;

//-------------------------------------------------------------------------------
const int WIDTH_EASY1 = 280; // ИГРОВОЕ ПОЛЕ
const int WIDTH_EASY2 = 960;
const int HEIGHT_EASY1 = 0;
const int HEIGHT_EASY2 = 680;

int xE = 600, yE = 720 / 2 - 40; // ТЕКУЩАЯ КООРДИНАТА ГОЛОВЫ ЗМЕЙКИ - ОСНОВНАЯ
int fruitX, fruitY;//Координаты еды
int TempFruitX = 0; int TempFruitY = 0;//Текущая координата еды

int score = 0;    //СЧЕТЧИК ОЧКОВ

bool GameOver = false;
bool LoadTexturesEasyBool = true;
bool chooseFood = true;
bool Left = false, Right = false, Up = false, Down = false;//Направление змейки
bool flagFruit = false;//Проверка возможного спавна еды

bool Pause = false;
bool Restart = false;// Рестарт игры
bool BackToMenu = false;

int SnakeX[324]; int SnakeY[324];  //МАССИВЫ, хранящие координаты змейки. Реализация - Связные списки.
int LenSnake = 1;
int Food_Number; //Номер еды (ТИП)
int randomFood;
int SnakePosX[324]; int SnakePosY[324]; //Необходимы для случайного появления фрукта вне змейки

string text;
string LenSnText;
string LenSn;
string scoreOne;

char LenSnakeChar[35];
char textScore[15];
SDL_Rect TextRect = { 10,5,150,70 }; // Счет
SDL_Rect TextLenSnake = { 10,80,250,70 }; // длина змейки
SDL_Rect CRAY = { 279,0,722,720 }; //Красные границы
SDL_Rect TO_MENU_RECT = { 1230,0,50,50 };
//SDL_Rect 

enum Direction {
	START = 0, LEFT, RIGHT, UP, DOWN
};
Direction Dir;

SDL_Texture* Get_TextTextureEasy(SDL_Renderer*& renderer, char* text, TTF_Font* font) {
	SDL_Surface* TextSurface = NULL;
	SDL_Color fore_color = { 240,100,100 };
	TextSurface = TTF_RenderUTF8_Solid(font, text, fore_color);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, TextSurface);
	SDL_FreeSurface(TextSurface);
	return texture;
}

SDL_Texture* Get_SnakeLenTexture(SDL_Renderer* renderer, char* text, TTF_Font* font) {
	SDL_Surface* Surface = NULL;
	SDL_Color fore_color = { 240,100,100 };
	Surface = TTF_RenderUTF8_Solid(font, text, fore_color);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, Surface);
	SDL_FreeSurface(Surface);
	return texture;
}

void LoadTexturesEasy(SDL_Renderer* renderer) {

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

	MenuIconSurface = IMG_Load("Textures\\MENU_ICON.bmp");
	SDL_SetColorKey(MenuIconSurface, SDL_TRUE, SDL_MapRGB(MenuIconSurface->format, 255, 255, 255));
	MenuIconTexture = SDL_CreateTextureFromSurface(renderer, MenuIconSurface);
	SDL_FreeSurface(MenuIconSurface);

	to_menuSurface = IMG_Load("Textures\\MENU_ICON.bmp");
	SDL_SetColorKey(to_menuSurface, SDL_TRUE, SDL_MapRGB(to_menuSurface->format, 255, 255, 255));
	to_menuTexture = SDL_CreateTextureFromSurface(renderer, to_menuSurface);
	SDL_FreeSurface(to_menuSurface);

}

void DeleteTexturesEasy() {
	SDL_DestroyTexture(AppleTexture);
	SDL_DestroyTexture(BananaTexture);
	SDL_DestroyTexture(KlubnicaTexture);
	SDL_DestroyTexture(ScoreTexture);
	SDL_DestroyTexture(LenSnakeTexture);
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

int c; // Переменная - проверка  - счетчик ДЛЯ ПОЯВЛЕНИЯ ФРУКТОВ

void FruitSpawn() {
	
	while (!flagFruit) {
		c = 0;
		fruitX = rand() % (WIDTH_EASY2 - WIDTH_EASY1 + 1) + WIDTH_EASY1;
		fruitY = rand() % (HEIGHT_EASY2 - HEIGHT_EASY1 + 1) + HEIGHT_EASY1;
		if (fruitX % 40 == 0 && fruitY % 40 == 0) {
			for (int i = 0; i < LenSnake;i++) {
				if ((fruitX == SnakePosX[i] && fruitY == SnakePosY[i])||(TempFruitX==fruitX&&TempFruitY==fruitY)) { // Проверка неналожения на змейку и на место, где фрукт был в прошлый раз
					c++;
				}
			}
			if (c == 0) {
				TempFruitX = fruitX;
				TempFruitY = fruitY;
				flagFruit = true;
			}
			else
				continue;
		}
	}
}

void RenderGame(SDL_Renderer* RenderGame) {
	

	text = u8"Счёт: ";
	LenSnText = u8"Длина змейки: ";

	LenSn = to_string(LenSnake);
	LenSnText = LenSnText + LenSn;

	scoreOne = to_string(score);
	text = text + scoreOne;

	strcpy_s(textScore, text.c_str()); //Преобразование из string в char*
	strcpy_s(LenSnakeChar, LenSnText.c_str());

	ScoreTexture = Get_TextTextureEasy(RenderGame, textScore, fontScore);
	LenSnakeTexture = Get_SnakeLenTexture(RenderGame, LenSnakeChar, SnakeLenTTF);

	if (chooseFood==true) {//Шансы появления еды определенного типа
		randomFood = rand() % 100;
		if (randomFood < 50)
			Food_Number = 0;
		if (randomFood >= 50 && randomFood < 80)
			Food_Number = 1;
		if (randomFood >= 80 && randomFood < 100)
			Food_Number = 2;
		chooseFood = false;
	}
	SDL_SetRenderDrawColor(RenderGame, 201, 201, 201, 0);//ЦВЕТ ПОЛЯ
	SDL_RenderClear(RenderGame);
	SDL_RenderCopy(RenderGame, ScoreTexture, NULL, &TextRect); //ОТРИСОВКА СЧЕТА
	SDL_RenderCopy(RenderGame, LenSnakeTexture, NULL, &TextLenSnake);//ОТРИСОВКА ДЛИНЫ ЗМЕЙКИ
	SDL_RenderCopy(RenderGame, to_menuTexture, NULL, &TO_MENU_RECT);//ОТРИСОВКА ИКОНКИ МЕНЮ

	SDL_DestroyTexture(LenSnakeTexture); // ДЛЯ ОСВОБОЖДЕНИЯ ПАМЯТИ
	SDL_DestroyTexture(ScoreTexture); // ДЛЯ ОСВОБОЖДЕНИЯ ПАМЯТИ

	SDL_SetRenderDrawColor(RenderGame, 195, 195, 195, 0);//Сеточка
	SetkaEasy(RenderGame);                    //Можно включить по желанию

	SDL_SetRenderDrawColor(RenderGame, 255, 0, 0, 0);

	SDL_RenderDrawRect(RenderGame, &CRAY);

	for (int x = 280; x < 1000;x += 40) {
		for (int y = 0; y < 720; y += 40) {
			if (x == xE && y == yE) {
				SDL_Rect rect = { x, y, 40,40 };
				SDL_RenderCopy(RenderGame, SNAKE_EASY_TEXTURE, NULL, &rect); //ОТРИСОВКА ГОЛОВЫ ЗМЕЙКИ
			}
			for (int i = 0; i < LenSnake;i++) {
				if (SnakeX[i] == x && SnakeY[i] == y) {
					SDL_Rect rect = { SnakeX[i], SnakeY[i], 40,40 };
					SDL_RenderCopy(RenderGame, SNAKE_EASY_TEXTURE, NULL, &rect); //ОТРИСОВКА ГОЛОВЫ И ТЕЛА ЗМЕЙКИ
				}

			}
			if (x == fruitX && y == fruitY) //ОТРИСОВКА ЕДЫ
			{
				SDL_Rect Rect = { fruitX,fruitY,40,40 };
				if (Food_Number == 0)
					SDL_RenderCopy(RenderGame, AppleTexture, NULL, &Rect);
				if (Food_Number == 1)
					SDL_RenderCopy(RenderGame, KlubnicaTexture, NULL, &Rect);
				if (Food_Number == 2)
					SDL_RenderCopy(RenderGame, BananaTexture, NULL, &Rect);
			}
			
		}
	}
}

void Activity(SDL_Event event,bool &Pause) //КНОПКИ И МЫШЬ
{
	int x, y;
	SDL_GetMouseState(&x, &y);
	switch (event.type)
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
			case SDLK_a:
				if (Dir != RIGHT)          // ВЛЕВО
					Dir = LEFT; break;
			case SDLK_w:
				if (Dir != DOWN)         // ВВЕРХ
					Dir = UP; break;
			case SDLK_d:                // ВПРАВО
				if (Dir != LEFT)
					Dir = RIGHT; break;
			case SDLK_s:                // ВНИЗ
				if (Dir != UP)
					Dir = DOWN; break;
			case SDLK_ESCAPE:
				Pause = true;
				cout << "Escape was pressed" << endl; break;
			}
			if((event.type == SDL_MOUSEBUTTONDOWN)&&(event.button.button == SDL_BUTTON_LEFT))
				if (x >= 1230 && x <= 1280 && y >= 0 && y <= 50) //НАЖАТИЕ НА ИКОНКУ ПАУЗЫ
				{
					Pause = true;
				}
}

void GameLogicEasy() {
	//Реализация нарастания и поворота тела змейки с помощью связного списка
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
		SnakePosX[i] = LastX; //Запомнить координаты змейки и занести из в массив
		SnakePosY[i] = LastY;
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

	if ((xE == fruitX) && (yE == fruitY)) { // Если фрукт был съеден
		if (Food_Number == 0)
			score++;
		if (Food_Number == 1)
			score += 2;
		if (Food_Number == 2)
			score += 3;
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

//_______________________________________________________________________________
clock_t start = clock();    //Необходим для отвязки FPS приложения от игры!!!!!!!
//_______________________________________________________________________________

bool NewRecordMenuFlag = false;
int NewRecord, OldRecord;
void EasyMode(SDL_Renderer* renderer, SDL_Event event, bool& Easy, bool& StartGame) {
	if (!Pause) {
		if (LoadTexturesEasyBool) { //ТО, ЧТО НУЖНО ЗАГРУЗИТЬ 1 РАЗ
			LoadTexturesEasy(renderer);
			Dir = START;
			PlayEasySound();
			fontScore = TTF_OpenFont("Text.ttf", 54);
			SnakeLenTTF = TTF_OpenFont("Text.ttf", 48);
			LoadTexturesEasyBool = false;
			ReadRecords();
		}
		if (GameOver == false) //ОСНОВНАЯ ЧАСТЬ ИГРЫ
		{
			Activity(event,Pause);
			if (clock() - start >= 500) { //Обновление рендера игры - КОНТРОЛЬ СКОРОСТИ
				FruitSpawn();
				GameLogicEasy();
				RenderGame(renderer);
				start = clock();
				SDL_RenderPresent(renderer);
			}
		}
		else //ЕСЛИ ПРОИГРЫШ
		{
			if (NewRecordMenuFlag == false) {
				if (CheckNewRecord(score, 0,NewRecord,OldRecord)) //Проверка нового рекорда, его запись в ФАЙЛ
					NewRecordMenuFlag = true;
			}
			if(NewRecordMenuFlag)
				NewRecordMenu(renderer, event, BackToMenu, Restart,NewRecord,OldRecord,NewRecordMenuFlag);
			else {
				Easy = false;
			StartGame = false;
			Right = false;
			Left = false;
			Down = false;
			Up = false;
			GameOver = false;
			LoadTexturesEasyBool = true;
			Dir = START;
			score = 0;
			xE = 600, yE = 720 / 2 - 40;
			DeleteTexturesEasy();
			PlayFonMusic();
			for (int i = 0; i < LenSnake; i++)
			{
				SnakeX[i] = 0; SnakeY[i] = 0;
			}
			LenSnake = 1;
			}
		}
		
	}
	else //ЕСЛИ НАЖАТА КЛАВИША НАСТРОЕК
	{
		GameSettings(renderer, event, Pause,Restart,BackToMenu);
	}
	if (Restart) //ПЕРЕЗАПУСК УРОВНЯ
	{
		Easy = true;
		Right = false;
		Left = false;
		Down = false;
		Up = false;
		GameOver = false;
		Dir = START;
		LoadTexturesEasyBool = false;
		score = 0;
		xE = 600, yE = 720 / 2 - 40;

		for (int i = 0; i < LenSnake; i++)
		{
			SnakeX[i] = 0; SnakeY[i] = 0;
		}
		LenSnake = 1;
		Restart = false;
		PlayEasySound();
		EasyMode(renderer, event, Easy, StartGame);
	}
	if (BackToMenu) //ЕСЛИ БЫЛ ВОЗВРАТ В ГЛАВНОЕ МЕНЮ
	{
		Easy = false;
		StartGame = false;
		Right = false;
		Left = false;
		Down = false;
		Up = false;
		GameOver = false;
		LoadTexturesEasyBool = true;
		Dir = START;

		score = 0;
		xE = 600, yE = 720 / 2 - 40;

		DeleteTexturesEasy();
		PlayFonMusic();
		for (int i = 0; i < LenSnake; i++)
		{
			SnakeX[i] = 0; SnakeY[i] = 0;
		}
		LenSnake = 1;
		BackToMenu = false;
	}
	SDL_Delay(16);
}