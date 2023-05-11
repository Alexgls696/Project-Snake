#pragma once
#include "GameSetting.h"
#include "GameValues.h"
#include "Records.h"

#include "GameMode.h"
#include "GameSetting.h"
#include "GameValues.h"
#include "Records.h"
#include <iostream>
using namespace std;

//ЗАГРУЗКА ТЕКСТУР----------------------------------------------------------------
const int WIDTH_NORMAL1 = 288; // ИГРОВОЕ ПОЛЕ
const int WIDTH_NORMAL2 = 960;
const int HEIGHT_NORMAL1 = 0;
const int HEIGHT_NORMAL2 = 680;

enum Direction {
	START = 0, LEFT, RIGHT, UP, DOWN
};
Direction DirNormal;

ModeNormal NormalStr;

SDL_Texture* Get_TextTextureNormal(SDL_Renderer*& renderer, char* text, TTF_Font* font) {
	SDL_Surface* TextSurface = NULL;
	SDL_Color fore_color = { 240,100,100 };
	TextSurface = TTF_RenderUTF8_Solid(font, text, fore_color);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, TextSurface);
	SDL_FreeSurface(TextSurface);
	return texture;
}

SDL_Texture* Get_SnakeLenTextureNormal(SDL_Renderer* renderer, char* text, TTF_Font* font) {
	SDL_Surface* Surface = NULL;
	SDL_Color fore_color = { 240,100,100 };
	Surface = TTF_RenderUTF8_Solid(font, text, fore_color);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, Surface);
	SDL_FreeSurface(Surface);
	return texture;
}

void LoadTexturesNormal(SDL_Renderer* renderer) {

	NormalStr.SNAKE_NORMAL_SURFACE = IMG_Load("Textures\\SnakeTextureNormal.bmp");
	SDL_SetColorKey(NormalStr.SNAKE_NORMAL_SURFACE, SDL_TRUE, SDL_MapRGB(NormalStr.SNAKE_NORMAL_SURFACE->format, 255, 255, 255));
	NormalStr.SNAKE_NORMAL_TEXTURE = SDL_CreateTextureFromSurface(renderer, NormalStr.SNAKE_NORMAL_SURFACE);
	SDL_FreeSurface(NormalStr.SNAKE_NORMAL_SURFACE);

	NormalStr.AppleSurface = IMG_Load("Textures\\apple.bmp");
	SDL_SetColorKey(NormalStr.AppleSurface, SDL_TRUE, SDL_MapRGB(NormalStr.AppleSurface->format, 255, 255, 255));
	NormalStr.AppleTexture = SDL_CreateTextureFromSurface(renderer, NormalStr.AppleSurface);
	SDL_FreeSurface(NormalStr.AppleSurface);

	NormalStr.BananaSurface = IMG_Load("Textures\\BANAN.bmp");
	SDL_SetColorKey(NormalStr.BananaSurface, SDL_TRUE, SDL_MapRGB(NormalStr.BananaSurface->format, 255, 255, 255));
	NormalStr.BananaTexture = SDL_CreateTextureFromSurface(renderer, NormalStr.BananaSurface);
	SDL_FreeSurface(NormalStr.BananaSurface);

	NormalStr.KlubnicaSurface = IMG_Load("Textures\\KLUBNIKA.bmp");
	SDL_SetColorKey(NormalStr.KlubnicaSurface, SDL_TRUE, SDL_MapRGB(NormalStr.KlubnicaSurface->format, 255, 255, 255));
	NormalStr.KlubnicaTexture = SDL_CreateTextureFromSurface(renderer, NormalStr.KlubnicaSurface);
	SDL_FreeSurface(NormalStr.KlubnicaSurface);



	NormalStr.to_menuSurface = IMG_Load("Textures\\MENU_ICON.bmp");
	SDL_SetColorKey(NormalStr.to_menuSurface, SDL_TRUE, SDL_MapRGB(NormalStr.to_menuSurface->format, 255, 255, 255));
	NormalStr.to_menuTexture = SDL_CreateTextureFromSurface(renderer, NormalStr.to_menuSurface);
	SDL_FreeSurface(NormalStr.to_menuSurface);

	NormalStr.HeadSnakeSurface = IMG_Load("Textures\\HeadSnakeNormal.bmp");
	SDL_SetColorKey(NormalStr.HeadSnakeSurface, SDL_TRUE, SDL_MapRGB(NormalStr.HeadSnakeSurface->format, 255, 255, 255));
	NormalStr.HeadSnakeTexture = SDL_CreateTextureFromSurface(renderer, NormalStr.HeadSnakeSurface);
	SDL_FreeSurface(NormalStr.HeadSnakeSurface);

}

void DeleteTexturesNormal() {
	SDL_DestroyTexture(NormalStr.AppleTexture);
	SDL_DestroyTexture(NormalStr.BananaTexture);
	SDL_DestroyTexture(NormalStr.KlubnicaTexture);
	SDL_DestroyTexture(NormalStr.ScoreTexture);
	SDL_DestroyTexture(NormalStr.LenSnakeTexture);
	SDL_DestroyTexture(NormalStr.SNAKE_NORMAL_TEXTURE);
}

void SetkaNormal(SDL_Renderer* renderer) {
	for (int i = 0; i < 760; i += 48) {
		SDL_RenderDrawLine(renderer, 288 + i, 0, 288 + i, 720);
	}
	for (int i = 0; i < 760; i += 48) {
		SDL_RenderDrawLine(renderer, 288, i, 1000, i);
	}
}

void FruitSpawnNormal() {
	while (!NormalStr.flagFruit) {
		NormalStr.c = 0;
		NormalStr.fruitX = rand() % (WIDTH_NORMAL2 - WIDTH_NORMAL1 + 1) + WIDTH_NORMAL1;
		NormalStr.fruitY = rand() % (HEIGHT_NORMAL2 - HEIGHT_NORMAL1 + 1) + HEIGHT_NORMAL1;
		if (NormalStr.fruitX % 48 == 0 && NormalStr.fruitY % 48 == 0) 
			if (!(NormalStr.fruitX >= 528 && NormalStr.fruitY >= 240 && NormalStr.fruitX < 768 && NormalStr.fruitY < 480)) {
			for (int i = 0; i < NormalStr.LenSnake; i++) {
				if ((NormalStr.fruitX == NormalStr.SnakePosX[i] && NormalStr.fruitY == NormalStr.SnakePosY[i]) || (NormalStr.TempFruitX == NormalStr.fruitX && NormalStr.TempFruitY == NormalStr.fruitY)) { // Проверка неналожения на змейку и на место, где фрукт был в прошлый раз
					NormalStr.c++;
				}
			}
			if (NormalStr.c == 0) {
				NormalStr.TempFruitX = NormalStr.fruitX;
				NormalStr.TempFruitY = NormalStr.fruitY;
				NormalStr.flagFruit = true;
				
				
			}
			else
				continue;
		}
	}
}
SDL_Rect SectionRect;
void RenderGameNormal(SDL_Renderer* RenderGame) {


	NormalStr.text = u8"Счёт: ";
	NormalStr.LenSnText = u8"Длина змейки: ";

	NormalStr.LenSn = to_string(NormalStr.LenSnake);
	NormalStr.LenSnText = NormalStr.LenSnText + NormalStr.LenSn;
	NormalStr.scoreOne = to_string(NormalStr.score);
	NormalStr.text = NormalStr.text + NormalStr.scoreOne;

	strcpy_s(NormalStr.textScore, NormalStr.text.c_str()); //Преобразование из string в char*
	strcpy_s(NormalStr.LenSnakeChar, NormalStr.LenSnText.c_str());

	NormalStr.ScoreTexture = Get_TextTextureNormal(RenderGame, NormalStr.textScore, NormalStr.fontScore);
	NormalStr.LenSnakeTexture = Get_SnakeLenTextureNormal(RenderGame, NormalStr.LenSnakeChar, NormalStr.SnakeLenTTF);

	if (NormalStr.chooseFood == true) {//Шансы появления еды определенного типа
		NormalStr.randomFood = rand() % 100;
		if (NormalStr.randomFood < 50)
			NormalStr.Food_Number = 0;
		if (NormalStr.randomFood >= 50 && NormalStr.randomFood < 80)
			NormalStr.Food_Number = 1;
		if (NormalStr.randomFood >= 80 && NormalStr.randomFood < 100)
			NormalStr.Food_Number = 2;
		NormalStr.chooseFood = false; // ЧТОБЫ ЕДА менялась один раз
	}
	SDL_SetRenderDrawColor(RenderGame, 201, 201, 201, 0);//ЦВЕТ ПОЛЯ
	SDL_RenderClear(RenderGame);
	SDL_RenderCopy(RenderGame, NormalStr.ScoreTexture, NULL, &NormalStr.TextRect); //ОТРИСОВКА СЧЕТА
	SDL_RenderCopy(RenderGame, NormalStr.LenSnakeTexture, NULL, &NormalStr.TextLenSnake);//ОТРИСОВКА ДЛИНЫ ЗМЕЙКИ
	SDL_RenderCopy(RenderGame, NormalStr.to_menuTexture, NULL, &NormalStr.TO_MENU_RECT);//ОТРИСОВКА ИКОНКИ МЕНЮ

	SDL_DestroyTexture(NormalStr.LenSnakeTexture); // ДЛЯ ОСВОБОЖДЕНИЯ ПАМЯТИ
	SDL_DestroyTexture(NormalStr.ScoreTexture); // ДЛЯ ОСВОБОЖДЕНИЯ ПАМЯТИ

	SDL_SetRenderDrawColor(RenderGame, 195, 195, 195, 0);//Сеточка
	SetkaNormal(RenderGame);                    //Можно включить по желанию

	SDL_SetRenderDrawColor(RenderGame, 255, 0, 0, 0);

	SDL_RenderDrawRect(RenderGame, &NormalStr.CRAY);

	for (int x = 288; x < 1000;x += 48) {
		for (int y = 0; y < 720; y += 48) {
			if (x == NormalStr.xE && y == NormalStr.yE) {
				SDL_Rect rect = { x, y, 48,48 };
				SectionRect = { x,y,48,48 };



				if (DirNormal == RIGHT)
					SDL_RenderCopy(RenderGame, NormalStr.HeadSnakeTexture, NULL, &rect);
				if (DirNormal == LEFT)
					SDL_RenderCopyEx(RenderGame, NormalStr.HeadSnakeTexture, NULL, &rect, 0, 0, SDL_FLIP_HORIZONTAL); //ОТРИСОВКА ГОЛОВЫ ЗМЕЙКИ
				if (DirNormal == UP)
					SDL_RenderCopyEx(RenderGame, NormalStr.HeadSnakeTexture, NULL, &rect, 270, 0, SDL_FLIP_NONE);
				if (DirNormal == DOWN)
					SDL_RenderCopyEx(RenderGame, NormalStr.HeadSnakeTexture, NULL, &rect, 90, 0, SDL_FLIP_NONE);
				if (DirNormal == START)
					SDL_RenderCopy(RenderGame, NormalStr.HeadSnakeTexture, NULL, &rect);
			}
			for (int i = 0; i < NormalStr.LenSnake;i++) {
				if (NormalStr.SnakeX[i] == x && NormalStr.SnakeY[i] == y) {
					SDL_Rect rect = { NormalStr.SnakeX[i], NormalStr.SnakeY[i],48, 48 };
					SDL_RenderCopy(RenderGame, NormalStr.SNAKE_NORMAL_TEXTURE, NULL, &rect); //ОТРИСОВКА ГОЛОВЫ И ТЕЛА ЗМЕЙКИ
				}
			}

		}
	}
	for (int x = 288; x < 1000; x++)
		for (int y = 0; y < 720; y++) {
			if (x == NormalStr.fruitX && y == NormalStr.fruitY) //ОТРИСОВКА ЕДЫ
			{
				SDL_Rect Rect = { NormalStr.fruitX,NormalStr.fruitY, 48, 48 };
				if (NormalStr.Food_Number == 0)
					SDL_RenderCopy(RenderGame, NormalStr.AppleTexture, NULL, &Rect);
				if (NormalStr.Food_Number == 1)
					SDL_RenderCopy(RenderGame, NormalStr.KlubnicaTexture, NULL, &Rect);
				if (NormalStr.Food_Number == 2)
					SDL_RenderCopy(RenderGame, NormalStr.BananaTexture, NULL, &Rect);
			}
		}
	SDL_SetRenderDrawColor(RenderGame, 0, 0, 0, 0);//ПРЕПЯТСТВИЕ!
	SDL_Rect STENA = { 528,240,240,240 };
	SDL_RenderFillRect(RenderGame, &STENA);
	SDL_SetRenderDrawColor(RenderGame, 255, 0, 0, 0);
	SDL_Rect limit = { 527,239,241,241 };
	SDL_RenderDrawRect(RenderGame, &limit);

	//if (SDL_HasIntersection(&SectionRect, &STENA)) //другой вид проверки
	//{
		//cout << "GameOver!" << endl; NormalStr.GameOver = true;
	//}
	//------------------------------------------УСЛОВИЕ СТОЛКНОВЕНИЯ СО СТЕНОЙ В ЦЕНТРЕ
	if (NormalStr.xE >= 528 && NormalStr.yE >= 240 && NormalStr.xE < 768 && NormalStr.yE < 480) {
		cout << "GameOver!" << endl; PlayFail(); NormalStr.GameOver = true;
	}
}

void ActivityNormal(SDL_Event event, bool& Pause) //КНОПКИ И МЫШЬ
{
	int x, y;
	SDL_GetMouseState(&x, &y);
	switch (event.type)
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
			case SDLK_a:
				if (DirNormal != RIGHT)          // ВЛЕВО
					DirNormal = LEFT; break;
			case SDLK_w:
				if (DirNormal != DOWN)         // ВВЕРХ
					DirNormal = UP; break;
			case SDLK_d:                // ВПРАВО
				if (DirNormal != LEFT)
					DirNormal = RIGHT; break;
			case SDLK_s:                // ВНИЗ
				if (DirNormal != UP)
					DirNormal = DOWN; break;
			case SDLK_ESCAPE:
				Pause = true;
				cout << "Escape was pressed" << endl; break;
			}
			if ((event.type == SDL_MOUSEBUTTONDOWN) && (event.button.button == SDL_BUTTON_LEFT))
				if (x >= 1230 && x <= 1280 && y >= 0 && y <= 50) //НАЖАТИЕ НА ИКОНКУ ПАУЗЫ
				{
					Pause = true;
				}
}

void GameLogicNormal() {
	//Реализация нарастания и поворота тела змейки с помощью связного списка
	int LastX = NormalStr.SnakeX[0], LastY = NormalStr.SnakeY[0];
	int LastXX, LastYY;
	NormalStr.SnakeX[0] = NormalStr.xE;
	NormalStr.SnakeY[0] = NormalStr.yE;

	for (int i = 0; i < NormalStr.LenSnake;i++) {
		LastXX = NormalStr.SnakeX[i];
		LastYY = NormalStr.SnakeY[i];
		NormalStr.SnakeX[i] = LastX;
		NormalStr.SnakeY[i] = LastY;
		LastX = LastXX;
		LastY = LastYY;
		NormalStr.SnakePosX[i] = LastX; //Запомнить координаты змейки и занести из в массив
		NormalStr.SnakePosY[i] = LastY;
	}
	switch (DirNormal) {
	case LEFT:      // ВЛЕВО
		NormalStr.Left = true;
		NormalStr.Right = false;
		NormalStr.Down = false;
		NormalStr.Up = false;
		break;
	case UP:      // ВВЕРХ
		NormalStr.Left = false;
		NormalStr.Right = false;
		NormalStr.Down = false;
		NormalStr.Up = true;
		break;
	case RIGHT:      // ВПРАВО
		NormalStr.Left = false;
		NormalStr.Right = true;
		NormalStr.Down = false;
		NormalStr.Up = false
			; break;
	case DOWN:      // ВНИЗ
		NormalStr.Left = false;
		NormalStr.Right = false;
		NormalStr.Down = true;
		NormalStr.Up = false;
		break;
	}
	if (NormalStr.Right == true)
		NormalStr.xE += 48;
	if (NormalStr.Left == true)
		NormalStr.xE -= 48;
	if (NormalStr.Up == true)
		NormalStr.yE -= 48;
	if (NormalStr.Down == true)
		NormalStr.yE += 48;

	if ((NormalStr.xE == NormalStr.fruitX) && (NormalStr.yE == NormalStr.fruitY)) { // Если фрукт был съеден
		if (NormalStr.Food_Number == 0)
			NormalStr.score++;
		if (NormalStr.Food_Number == 1)
			NormalStr.score += 2;
		if (NormalStr.Food_Number == 2)
			NormalStr.score += 3;
		NormalStr.LenSnake++;
		NormalStr.flagFruit = false;
		NormalStr.chooseFood = true;
		FruitSpawnNormal();
		UKUS_Sound();
	}
	for (int i = 1; i < NormalStr.LenSnake;i++) { //Проверка не был ли съеден хвост
		if (NormalStr.SnakeX[i] == NormalStr.xE && NormalStr.SnakeY[i] == NormalStr.yE) {
			cout << "GameOver!" << endl;
			 PlayFail();
			NormalStr.GameOver = true;
		}
	}
	if ((NormalStr.xE < 280 || NormalStr.xE > 960) || (NormalStr.yE < 0 || NormalStr.yE > 680)) { // Условие выхода за рамки поля
		cout << "GameOver!" << endl;  PlayFail(); NormalStr.GameOver = true;
	}
	
}

//_______________________________________________________________________________
clock_t startNormal = clock();    //Необходим для отвязки FPS приложения от игры!!!!!!!
//_______________________________________________________________________________


void NormalMode(SDL_Renderer* renderer, SDL_Event event, bool& Normal, bool& StartGame) {
	if (!NormalStr.Pause) {
		if (NormalStr.LoadTexturesEasyBool) { //ТО, ЧТО НУЖНО ЗАГРУЗИТЬ 1 РАЗ
			LoadTexturesNormal(renderer);
			DirNormal = START;
			PlayNormalSound();
			NormalStr.fontScore = TTF_OpenFont("Text.ttf", 54);
			NormalStr.SnakeLenTTF = TTF_OpenFont("Text.ttf", 48);
			NormalStr.LoadTexturesEasyBool = false;
			ReadRecords();
		}
		if (NormalStr.GameOver == false) //ОСНОВНАЯ ЧАСТЬ ИГРЫ
		{
			ActivityNormal(event, NormalStr.Pause);
			if (clock() - startNormal >= 333) { //Обновление рендера игры - КОНТРОЛЬ СКОРОСТИ
				FruitSpawnNormal();
				GameLogicNormal();
				RenderGameNormal(renderer);
				startNormal = clock();
				SDL_RenderPresent(renderer);
			}
		}
		else //ЕСЛИ ИГРА ЗЕВЕРШЕНА
		{
			if (NormalStr.check == true) {
				if (CheckNewRecord(NormalStr.score, 1, NormalStr.NewRecord, NormalStr.OldRecord)) //Проверка нового рекорда, его запись в ФАЙЛ
				{
					NormalStr.NewRecordMenuFlag = true;
					NormalStr.check = false;
				}
				else {
					NormalStr.LoseMenuFlag = true;
					NormalStr.check = false;
				}
			}
			if (NormalStr.NewRecordMenuFlag)
				NewRecordMenu(renderer, event, NormalStr.BackToMenu, NormalStr.Restart, NormalStr.NewRecord, NormalStr.OldRecord, NormalStr.NewRecordMenuFlag, NormalStr.check);
			if (NormalStr.LoseMenuFlag)
				LoseMenu(renderer, event, NormalStr.BackToMenu, NormalStr.Restart, NormalStr.NewRecord, NormalStr.OldRecord, NormalStr.LoseMenuFlag, NormalStr.check);
		}
	}

	else //ЕСЛИ НАЖАТА КЛАВИША НАСТРОЕК
	{
		GameSettings(renderer, event, NormalStr.Pause, NormalStr.Restart, NormalStr.BackToMenu);
	}
	if (NormalStr.Restart) //ПЕРЕЗАПУСК УРОВНЯ
	{
		Normal = true;
		NormalStr.Right = false;
		NormalStr.Left = false;
		NormalStr.Down = false;
		NormalStr.Up = false;
		NormalStr.GameOver = false;
		DirNormal = START;
		NormalStr.LoadTexturesEasyBool = false;
		NormalStr.score = 0;
		NormalStr.xE = 288, NormalStr.yE = 0;

		for (int i = 0; i < NormalStr.LenSnake; i++)
		{
			NormalStr.SnakeX[i] = 0; NormalStr.SnakeY[i] = 0;
		}
		NormalStr.LenSnake = 1;
		NormalStr.Restart = false;
		NormalStr.flagFruit = false;
		PlayNormalSound();
		NormalMode(renderer, event, Normal, StartGame);
	}
	if (NormalStr.BackToMenu) //ЕСЛИ БЫЛ ВОЗВРАТ В ГЛАВНОЕ МЕНЮ
	{
		Normal = false;
		StartGame = false;
		NormalStr.Right = false;
		NormalStr.Left = false;
		NormalStr.Down = false;
		NormalStr.Up = false;
		NormalStr.GameOver = false;
		NormalStr.LoadTexturesEasyBool = true;
		DirNormal = START;

		NormalStr.score = 0;
		NormalStr.xE = 288, NormalStr.yE = 0;
		NormalStr.flagFruit = false;
		DeleteTexturesNormal();
		PlayFonMusic();
		for (int i = 0; i < NormalStr.LenSnake; i++)
		{
			NormalStr.SnakeX[i] = 0; NormalStr.SnakeY[i] = 0;
		}
		NormalStr.LenSnake = 1;
		NormalStr.BackToMenu = false;
	}
}