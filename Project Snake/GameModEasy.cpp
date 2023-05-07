#include "GameModEasy.h"
#include "GameSetting.h"
#include "GameValues.h"
#include "Records.h"

//�������� �������----------------------------------------------------------------

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

void FruitSpawn() {
	
	while (!EasyStr.flagFruit) {
		c = 0;
		EasyStr.fruitX = rand() % (WIDTH_EASY2 - WIDTH_EASY1 + 1) + WIDTH_EASY1;
		EasyStr.fruitY = rand() % (HEIGHT_EASY2 - HEIGHT_EASY1 + 1) + HEIGHT_EASY1;
		if (EasyStr.fruitX % 40 == 0 && EasyStr.fruitY % 40 == 0) {
			for (int i = 0; i < EasyStr.LenSnake;i++) {
				if ((EasyStr.fruitX == EasyStr.SnakePosX[i] && EasyStr.fruitY == EasyStr.SnakePosY[i])||(EasyStr.TempFruitX== EasyStr.fruitX&& EasyStr.TempFruitY== EasyStr.fruitY)) { // �������� ����������� �� ������ � �� �����, ��� ����� ��� � ������� ���
					c++;
				}
			}
			if (c == 0) {
				EasyStr.TempFruitX = EasyStr.fruitX;
				EasyStr.TempFruitY = EasyStr.fruitY;
				EasyStr.flagFruit = true;
			}
			else
				continue;
		}
	}
}

void RenderGame(SDL_Renderer* RenderGame) {
	

	text = u8"����: ";
	LenSnText = u8"����� ������: ";

	LenSn = to_string(EasyStr.LenSnake);
	LenSnText = LenSnText + LenSn;

	scoreOne = to_string(EasyStr.score);
	text = text + scoreOne;

	strcpy_s(textScore, text.c_str()); //�������������� �� string � char*
	strcpy_s(LenSnakeChar, LenSnText.c_str());

	ScoreTexture = Get_TextTextureEasy(RenderGame, textScore, fontScore);
	LenSnakeTexture = Get_SnakeLenTexture(RenderGame, LenSnakeChar, SnakeLenTTF);

	if (EasyStr.chooseFood==true) {//����� ��������� ��� ������������� ����
		randomFood = rand() % 100;
		if (randomFood < 50)
			Food_Number = 0;
		if (randomFood >= 50 && randomFood < 80)
			Food_Number = 1;
		if (randomFood >= 80 && randomFood < 100)
			Food_Number = 2;
		EasyStr.chooseFood = false; // ����� ��� �������� ���� ���
	}
	SDL_SetRenderDrawColor(RenderGame, 201, 201, 201, 0);//���� ����
	SDL_RenderClear(RenderGame);
	SDL_RenderCopy(RenderGame, ScoreTexture, NULL, &TextRect); //��������� �����
	SDL_RenderCopy(RenderGame, LenSnakeTexture, NULL, &TextLenSnake);//��������� ����� ������
	SDL_RenderCopy(RenderGame, to_menuTexture, NULL, &TO_MENU_RECT);//��������� ������ ����

	SDL_DestroyTexture(LenSnakeTexture); // ��� ������������ ������
	SDL_DestroyTexture(ScoreTexture); // ��� ������������ ������

	SDL_SetRenderDrawColor(RenderGame, 195, 195, 195, 0);//�������
	SetkaEasy(RenderGame);                    //����� �������� �� �������

	SDL_SetRenderDrawColor(RenderGame, 255, 0, 0, 0);

	SDL_RenderDrawRect(RenderGame, &CRAY);

	for (int x = 280; x < 1000;x += 40) {
		for (int y = 0; y < 720; y += 40) {
			if (x == EasyStr.xE && y == EasyStr.yE) {
				SDL_Rect rect = { x, y, 40,40 };
				SDL_RenderCopy(RenderGame, SNAKE_EASY_TEXTURE, NULL, &rect); //��������� ������ ������
			}
			for (int i = 0; i < EasyStr.LenSnake;i++) {
				if (EasyStr.SnakeX[i] == x && EasyStr.SnakeY[i] == y) {
					SDL_Rect rect = { EasyStr.SnakeX[i], EasyStr.SnakeY[i], 40,40 };
					SDL_RenderCopy(RenderGame, SNAKE_EASY_TEXTURE, NULL, &rect); //��������� ������ � ���� ������
				}

			}
			if (x == EasyStr.fruitX && y == EasyStr.fruitY) //��������� ���
			{
				SDL_Rect Rect = { EasyStr.fruitX,EasyStr.fruitY,40,40 };
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

void Activity(SDL_Event event,bool &Pause) //������ � ����
{
	int x, y;
	SDL_GetMouseState(&x, &y);
	switch (event.type)
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
			case SDLK_a:
				if (Dir != RIGHT)          // �����
					Dir = LEFT; break;
			case SDLK_w:
				if (Dir != DOWN)         // �����
					Dir = UP; break;
			case SDLK_d:                // ������
				if (Dir != LEFT)
					Dir = RIGHT; break;
			case SDLK_s:                // ����
				if (Dir != UP)
					Dir = DOWN; break;
			case SDLK_ESCAPE:
				Pause = true;
				cout << "Escape was pressed" << endl; break;
			}
			if((event.type == SDL_MOUSEBUTTONDOWN)&&(event.button.button == SDL_BUTTON_LEFT))
				if (x >= 1230 && x <= 1280 && y >= 0 && y <= 50) //������� �� ������ �����
				{
					Pause = true;
				}
}

void GameLogicEasy() {
	//���������� ���������� � �������� ���� ������ � ������� �������� ������
	int LastX = EasyStr.SnakeX[0], LastY = EasyStr.SnakeY[0];
	int LastXX, LastYY;
	EasyStr.SnakeX[0] = EasyStr.xE;
	EasyStr.SnakeY[0] = EasyStr.yE;

	for (int i = 0; i < EasyStr.LenSnake;i++) {
		LastXX = EasyStr.SnakeX[i];
		LastYY = EasyStr.SnakeY[i];
		EasyStr.SnakeX[i] = LastX;
		EasyStr.SnakeY[i] = LastY;
		LastX = LastXX;
		LastY = LastYY;
		EasyStr.SnakePosX[i] = LastX; //��������� ���������� ������ � ������� �� � ������
		EasyStr.SnakePosY[i] = LastY;
	}
	switch (Dir) {
	case LEFT:      // �����
		EasyStr.Left = true;
		EasyStr.Right = false;
		EasyStr.Down = false;
		EasyStr.Up = false;
		break;
		cout << "OK" << endl;
	case UP:      // �����
		EasyStr.Left = false;
		EasyStr.Right = false;
		EasyStr.Down = false;
		EasyStr.Up = true;
		break;
	case RIGHT:      // ������
		EasyStr.Left = false;
		EasyStr.Right = true;
		EasyStr.Down = false;
		EasyStr.Up = false
			; break;
	case DOWN:      // ����
		EasyStr.Left = false;
		EasyStr.Right = false;
		EasyStr.Down = true;
		EasyStr.Up = false;
		break;
	}
	if (EasyStr.Right == true)
		EasyStr.xE += 40;
	if (EasyStr.Left == true)
		EasyStr.xE -= 40;
	if (EasyStr.Up == true)
		EasyStr.yE -= 40;
	if (EasyStr.Down == true)
		EasyStr.yE += 40;

	if ((EasyStr.xE == EasyStr.fruitX) && (EasyStr.yE == EasyStr.fruitY)) { // ���� ����� ��� ������
		if (Food_Number == 0)
			EasyStr.score++;
		if (Food_Number == 1)
			EasyStr.score += 2;
		if (Food_Number == 2)
			EasyStr.score += 3;
		EasyStr.LenSnake++;
		EasyStr.flagFruit = false;
		EasyStr.chooseFood = true;
		FruitSpawn();
		UKUS_Sound();
	}
	for (int i = 1; i < EasyStr.LenSnake;i++) { //�������� �� ��� �� ������ �����
		if (EasyStr.SnakeX[i] == EasyStr.xE && EasyStr.SnakeY[i] == EasyStr.yE) {
			cout << "GameOver!" << endl;
			GameOver = true;
		}
	}
	if ((EasyStr.xE < 280 || EasyStr.xE > 960) || (EasyStr.yE < 0 || EasyStr.yE > 680)) { // ������� ������ �� ����� ����
		cout << "GameOver!" << endl; GameOver = true;
	}
}

//_______________________________________________________________________________
clock_t start = clock();    //��������� ��� ������� FPS ���������� �� ����!!!!!!!
//_______________________________________________________________________________

bool NewRecordMenuFlag = false;
int NewRecord, OldRecord;
void EasyMode(SDL_Renderer* renderer, SDL_Event event, bool& Easy, bool& StartGame) {
	if (!Pause) {
		if (EasyStr.LoadTexturesEasyBool) { //��, ��� ����� ��������� 1 ���
			LoadTexturesEasy(renderer);
			Dir = START;
			PlayEasySound();
			fontScore = TTF_OpenFont("Text.ttf", 54);
			SnakeLenTTF = TTF_OpenFont("Text.ttf", 48);
			EasyStr.LoadTexturesEasyBool = false;
			ReadRecords();
		}
		if (GameOver == false) //�������� ����� ����
		{
			Activity(event,Pause);
			if (clock() - start >= 500) { //���������� ������� ���� - �������� ��������
				FruitSpawn();
				GameLogicEasy();
				RenderGame(renderer);
				start = clock();
				SDL_RenderPresent(renderer);
			}
		}
		else //���� ��������
		{
			if (NewRecordMenuFlag == false) {
				if (CheckNewRecord(EasyStr.score, 0,NewRecord,OldRecord)) //�������� ������ �������, ��� ������ � ����
					NewRecordMenuFlag = true;
			}
			if(NewRecordMenuFlag)
				NewRecordMenu(renderer, event, BackToMenu, Restart,NewRecord,OldRecord,NewRecordMenuFlag);
			else {
				Easy = false;
			StartGame = false;
			EasyStr.Right = false;
			EasyStr.Left = false;
			EasyStr.Down = false;
			EasyStr.Up = false;
			GameOver = false;
			EasyStr.LoadTexturesEasyBool = true;
			Dir = START;
			EasyStr.score = 0;
			EasyStr.xE = 600, EasyStr.yE = 720 / 2 - 40;
			DeleteTexturesEasy();
			PlayFonMusic();
			for (int i = 0; i < EasyStr.LenSnake; i++)
			{
				EasyStr.SnakeX[i] = 0; EasyStr.SnakeY[i] = 0;
			}
			EasyStr.LenSnake = 1;
			}
		}
		
	}
	else //���� ������ ������� ��������
	{
		GameSettings(renderer, event, Pause,Restart,BackToMenu);
	}
	if (Restart) //���������� ������
	{
		Easy = true;
		EasyStr.Right = false;
		EasyStr.Left = false;
		EasyStr.Down = false;
		EasyStr.Up = false;
		GameOver = false;
		Dir = START;
		EasyStr.LoadTexturesEasyBool = false;
		EasyStr.score = 0;
		EasyStr.xE = 600, EasyStr.yE = 720 / 2 - 40;

		for (int i = 0; i < EasyStr.LenSnake; i++)
		{
			EasyStr.SnakeX[i] = 0; EasyStr.SnakeY[i] = 0;
		}
		EasyStr.LenSnake = 1;
		Restart = false;
		PlayEasySound();
		EasyMode(renderer, event, Easy, StartGame);
	}
	if (BackToMenu) //���� ��� ������� � ������� ����
	{
		Easy = false;
		StartGame = false;
		EasyStr.Right = false;
		EasyStr.Left = false;
		EasyStr.Down = false;
		EasyStr.Up = false;
		GameOver = false;
		EasyStr.LoadTexturesEasyBool = true;
		Dir = START;

		EasyStr.score = 0;
		EasyStr.xE = 600, EasyStr.yE = 720 / 2 - 40;

		DeleteTexturesEasy();
		PlayFonMusic();
		for (int i = 0; i < EasyStr.LenSnake; i++)
		{
			EasyStr.SnakeX[i] = 0; EasyStr.SnakeY[i] = 0;
		}
		EasyStr.LenSnake = 1;
		BackToMenu = false;
	}
	SDL_Delay(16);
}