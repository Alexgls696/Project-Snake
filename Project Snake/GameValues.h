#pragma once

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
};
ModeEasy EasyStr;
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


enum Direction {
	START = 0, LEFT, RIGHT, UP, DOWN
};
Direction Dir;
