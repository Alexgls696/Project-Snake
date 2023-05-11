#pragma once
#include "SDL.h"
#include "SDL_Image.h"
#include "SDL_ttf.h"
#include <iostream>
using namespace std;

//-------------------------------------------------------------------------------



struct ModeEasy {
	int xE = 600, yE = 720 / 2 - 40;  // ТЕКУЩАЯ КООРДИНАТА ГОЛОВЫ ЗМЕЙКИ - ОСНОВНАЯ
	int fruitX, fruitY;//Координаты еды
	int TempFruitX = 0; int TempFruitY = 0;//Текущая координата еды
	int score = 0;    //СЧЕТЧИК ОЧКОВ
	int SnakeX[324]; int SnakeY[324];  //МАССИВЫ, хранящие координаты змейки. Реализация - Связные списки.
	bool LoadTexturesEasyBool = true;
	bool flagFruit = false;//Проверка возможного спавна еды
	bool chooseFood = true; // Шансы появления еды опр типа 1 раз
	bool Left = false, Right = false, Up = false, Down = false;//Направление змейки
	int LenSnake = 1;
	int SnakePosX[324]; int SnakePosY[324]; //Необходимы для случайного появления фрукта вне змейки
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
	SDL_Texture* to_menuTexture = NULL;

	SDL_Surface* HeadSnakeSurface = NULL;
	SDL_Texture* HeadSnakeTexture = NULL;

	int c; // Переменная - проверка  - счетчик ДЛЯ ПОЯВЛЕНИЯ ФРУКТОВ
	bool GameOver = false;
	bool Pause = false;
	bool Restart = false;// Рестарт игры
	bool BackToMenu = false;
	bool NewRecordMenuFlag = false;
	bool LoseMenuFlag = false;
	int NewRecord, OldRecord;
	bool check = true;

	int Food_Number; //Номер еды (ТИП)
	int randomFood;

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
};




struct ModeNormal {
	int xE = 288, yE = 0;  // ТЕКУЩАЯ КООРДИНАТА ГОЛОВЫ ЗМЕЙКИ - ОСНОВНАЯ
	int fruitX, fruitY;//Координаты еды
	int TempFruitX = 0; int TempFruitY = 0;//Текущая координата еды
	int score = 0;    //СЧЕТЧИК ОЧКОВ
	int SnakeX[225]; int SnakeY[225];  //МАССИВЫ, хранящие координаты змейки. Реализация - Связные списки.
	bool LoadTexturesEasyBool = true;
	bool flagFruit = false;//Проверка возможного спавна еды
	bool chooseFood = true; // Шансы появления еды опр типа 1 раз
	bool Left = false, Right = false, Up = false, Down = false;//Направление змейки
	int LenSnake = 1;
	int SnakePosX[225]; int SnakePosY[225]; //Необходимы для случайного появления фрукта вне змейки
	TTF_Font* fontScore = NULL;
	TTF_Font* SnakeLenTTF = NULL;

	SDL_Texture* SNAKE_NORMAL_TEXTURE = NULL;
	SDL_Surface* SNAKE_NORMAL_SURFACE = NULL;

	SDL_Surface* AppleSurface = NULL;
	SDL_Texture* AppleTexture = NULL;
	SDL_Surface* BananaSurface = NULL;
	SDL_Texture* BananaTexture = NULL;
	SDL_Surface* KlubnicaSurface = NULL;
	SDL_Texture* KlubnicaTexture = NULL;

	SDL_Texture* ScoreTexture = NULL;
	SDL_Texture* LenSnakeTexture = NULL;


	SDL_Surface* to_menuSurface = NULL;
	SDL_Texture* to_menuTexture = NULL;

	SDL_Surface* HeadSnakeSurface = NULL;
	SDL_Texture* HeadSnakeTexture = NULL;

	int c; // Переменная - проверка  - счетчик ДЛЯ ПОЯВЛЕНИЯ ФРУКТОВ
	bool GameOver = false;
	bool Pause = false;
	bool Restart = false;// Рестарт игры
	bool BackToMenu = false;
	bool NewRecordMenuFlag = false;
	bool LoseMenuFlag = false;
	int NewRecord, OldRecord;
	bool check = true;

	int Food_Number; //Номер еды (ТИП)
	int randomFood;

	string text;
	string LenSnText;
	string LenSn;
	string scoreOne;

	char LenSnakeChar[35];
	char textScore[15];
	SDL_Rect TextRect = { 10,5,150,70 }; // Счет
	SDL_Rect TextLenSnake = { 10,80,250,70 }; // длина змейки
	SDL_Rect CRAY = { 287,0,722,720 }; //Красные границы
	SDL_Rect TO_MENU_RECT = { 1230,0,50,50 };
};

struct ModeHard {
	int xE = 600, yE = 360;  // ТЕКУЩАЯ КООРДИНАТА ГОЛОВЫ ЗМЕЙКИ - ОСНОВНАЯ
	int fruitX, fruitY;//Координаты еды
	int TempFruitX = 0; int TempFruitY = 0;//Текущая координата еды
	int score = 0;    //СЧЕТЧИК ОЧКОВ
	int SnakeX[144]; int SnakeY[144];  //МАССИВЫ, хранящие координаты змейки. Реализация - Связные списки.
	bool LoadTexturesEasyBool = true;
	bool flagFruit = false;//Проверка возможного спавна еды
	bool chooseFood = true; // Шансы появления еды опр типа 1 раз
	bool Left = false, Right = false, Up = false, Down = false;//Направление змейки
	int LenSnake = 1;
	int SnakePosX[144]; int SnakePosY[144]; //Необходимы для случайного появления фрукта вне змейки
	TTF_Font* fontScore = NULL;
	TTF_Font* SnakeLenTTF = NULL;

	SDL_Texture* SNAKE_HARD_TEXTURE = NULL;
	SDL_Surface* SNAKE_HARD_SURFACE = NULL;

	SDL_Surface* AppleSurface = NULL;
	SDL_Texture* AppleTexture = NULL;
	SDL_Surface* BananaSurface = NULL;
	SDL_Texture* BananaTexture = NULL;
	SDL_Surface* KlubnicaSurface = NULL;
	SDL_Texture* KlubnicaTexture = NULL;

	SDL_Texture* ScoreTexture = NULL;
	SDL_Texture* LenSnakeTexture = NULL;


	SDL_Surface* to_menuSurface = NULL;
	SDL_Texture* to_menuTexture = NULL;

	SDL_Surface* HeadSnakeSurface = NULL;
	SDL_Texture* HeadSnakeTexture = NULL;

	int c; // Переменная - проверка  - счетчик ДЛЯ ПОЯВЛЕНИЯ ФРУКТОВ
	bool GameOver = false;
	bool Pause = false;
	bool Restart = false;// Рестарт игры
	bool BackToMenu = false;
	bool NewRecordMenuFlag = false;
	bool LoseMenuFlag = false;
	int NewRecord, OldRecord;
	bool check = true;

	int Food_Number; //Номер еды (ТИП)
	int randomFood;

	string text;
	string LenSnText;
	string LenSn;
	string scoreOne;

	char LenSnakeChar[35];
	char textScore[15];
	SDL_Rect TextRect = { 10,5,150,70 }; // Счет
	SDL_Rect TextLenSnake = { 10,80,250,70 }; // длина змейки
	SDL_Rect CRAY = { 300,0,722,720 }; //Красные границы
	SDL_Rect TO_MENU_RECT = { 1230,0,50,50 };
};


