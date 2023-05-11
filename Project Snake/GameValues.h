#pragma once
#include "SDL.h"
#include "SDL_Image.h"
#include <iostream>
#include "SDL_ttf.h"

using namespace std;

//-------------------------------------------------------------------------------
const int WIDTH_EASY1 = 280; // ������� ����
const int WIDTH_EASY2 = 960;
const int HEIGHT_EASY1 = 0;
const int HEIGHT_EASY2 = 680;


struct ModeEasy {
	int xE = 600, yE = 720 / 2 - 40;  // ������� ���������� ������ ������ - ��������
	int fruitX, fruitY;//���������� ���
	int TempFruitX = 0; int TempFruitY = 0;//������� ���������� ���
	int score = 0;    //������� �����
	int SnakeX[324]; int SnakeY[324];  //�������, �������� ���������� ������. ���������� - ������� ������.
	bool LoadTexturesEasyBool = true;
	bool flagFruit = false;//�������� ���������� ������ ���
	bool chooseFood = true; // ����� ��������� ��� ��� ���� 1 ���
	bool Left = false, Right = false, Up = false, Down = false;//����������� ������
	int LenSnake = 1;
	int SnakePosX[324]; int SnakePosY[324]; //���������� ��� ���������� ��������� ������ ��� ������
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

	int c; // ���������� - ��������  - ������� ��� ��������� �������
	bool GameOver = false;
	bool Pause = false;
	bool Restart = false;// ������� ����
	bool BackToMenu = false;
	bool NewRecordMenuFlag = false;
	bool LoseMenuFlag = false;
	int NewRecord, OldRecord;
	bool check = true;

	int Food_Number; //����� ��� (���)
	int randomFood;

	string text;
	string LenSnText;
	string LenSn;
	string scoreOne;

	char LenSnakeChar[35];
	char textScore[15];
	SDL_Rect TextRect = { 10,5,150,70 }; // ����
	SDL_Rect TextLenSnake = { 10,80,250,70 }; // ����� ������
	SDL_Rect CRAY = { 279,0,722,720 }; //������� �������
	SDL_Rect TO_MENU_RECT = { 1230,0,50,50 };
};




struct ModeNormal {
	int xE = 600, yE = 720 / 2 - 40;  // ������� ���������� ������ ������ - ��������
	int fruitX, fruitY;//���������� ���
	int TempFruitX = 0; int TempFruitY = 0;//������� ���������� ���
	int score = 0;    //������� �����
	int SnakeX[225]; int SnakeY[225];  //�������, �������� ���������� ������. ���������� - ������� ������.
	bool LoadTexturesEasyBool = true;
	bool flagFruit = false;//�������� ���������� ������ ���
	bool chooseFood = true; // ����� ��������� ��� ��� ���� 1 ���
	bool Left = false, Right = false, Up = false, Down = false;//����������� ������
	int LenSnake = 1;
	int SnakePosX[225]; int SnakePosY[225]; //���������� ��� ���������� ��������� ������ ��� ������
};


