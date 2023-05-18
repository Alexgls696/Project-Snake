#pragma once

#include "GameMode.h"
#include "GamePause.h"
#include "GameValues.h"
#include "Records.h"
#include <iostream>
using namespace std;

//ÇÀÃĞÓÇÊÀ ÒÅÊÑÒÓĞ----------------------------------------------------------------
const int WIDTH_HARD1 = 300; // ÈÃĞÎÂÎÅ ÏÎËÅ
const int WIDTH_HARD2 = 960;
const int HEIGHT_HARD1 = 0;
const int HEIGHT_HARD2 = 680;

enum Direction {
	START = 0, LEFT, RIGHT, UP, DOWN
};
Direction DirHard;

ModeHard HardStr;

SDL_Texture* Get_TextTextureHard(SDL_Renderer*& renderer, char* text, TTF_Font* font) {
	SDL_Surface* TextSurface = NULL;
	SDL_Color fore_color = { 240,100,100 };
	TextSurface = TTF_RenderUTF8_Solid(font, text, fore_color);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, TextSurface);
	SDL_FreeSurface(TextSurface);
	return texture;
}

SDL_Texture* Get_SnakeLenTextureHard(SDL_Renderer* renderer, char* text, TTF_Font* font) {
	SDL_Surface* Surface = NULL;
	SDL_Color fore_color = { 240,100,100 };
	Surface = TTF_RenderUTF8_Solid(font, text, fore_color);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, Surface);
	SDL_FreeSurface(Surface);
	return texture;
}

void LoadTexturesHard(SDL_Renderer* renderer) {

	HardStr.SNAKE_HARD_SURFACE = IMG_Load("Textures\\SnakeTextureHard.bmp");
	SDL_SetColorKey(HardStr.SNAKE_HARD_SURFACE, SDL_TRUE, SDL_MapRGB(HardStr.SNAKE_HARD_SURFACE->format, 255, 255, 255));
	HardStr.SNAKE_HARD_TEXTURE = SDL_CreateTextureFromSurface(renderer, HardStr.SNAKE_HARD_SURFACE);
	SDL_FreeSurface(HardStr.SNAKE_HARD_SURFACE);

	HardStr.AppleSurface = IMG_Load("Textures\\apple.bmp");
	SDL_SetColorKey(HardStr.AppleSurface, SDL_TRUE, SDL_MapRGB(HardStr.AppleSurface->format, 255, 255, 255));
	HardStr.AppleTexture = SDL_CreateTextureFromSurface(renderer, HardStr.AppleSurface);
	SDL_FreeSurface(HardStr.AppleSurface);

	HardStr.BananaSurface = IMG_Load("Textures\\BANAN.bmp");
	SDL_SetColorKey(HardStr.BananaSurface, SDL_TRUE, SDL_MapRGB(HardStr.BananaSurface->format, 255, 255, 255));
	HardStr.BananaTexture = SDL_CreateTextureFromSurface(renderer, HardStr.BananaSurface);
	SDL_FreeSurface(HardStr.BananaSurface);

	HardStr.KlubnicaSurface = IMG_Load("Textures\\KLUBNIKA.bmp");
	SDL_SetColorKey(HardStr.KlubnicaSurface, SDL_TRUE, SDL_MapRGB(HardStr.KlubnicaSurface->format, 255, 255, 255));
	HardStr.KlubnicaTexture = SDL_CreateTextureFromSurface(renderer, HardStr.KlubnicaSurface);
	SDL_FreeSurface(HardStr.KlubnicaSurface);

	HardStr.to_menuSurface = IMG_Load("Textures\\MENU_ICON.bmp");
	SDL_SetColorKey(HardStr.to_menuSurface, SDL_TRUE, SDL_MapRGB(HardStr.to_menuSurface->format, 255, 255, 255));
	HardStr.to_menuTexture = SDL_CreateTextureFromSurface(renderer, HardStr.to_menuSurface);
	SDL_FreeSurface(HardStr.to_menuSurface);

	HardStr.HeadSnakeSurface = IMG_Load("Textures\\HeadSnakeHard.bmp");
	SDL_SetColorKey(HardStr.HeadSnakeSurface, SDL_TRUE, SDL_MapRGB(HardStr.HeadSnakeSurface->format, 255, 255, 255));
	HardStr.HeadSnakeTexture = SDL_CreateTextureFromSurface(renderer, HardStr.HeadSnakeSurface);
	SDL_FreeSurface(HardStr.HeadSnakeSurface);

}

void DeleteTexturesHard() {
	SDL_DestroyTexture(HardStr.AppleTexture);
	SDL_DestroyTexture(HardStr.BananaTexture);
	SDL_DestroyTexture(HardStr.KlubnicaTexture);
	SDL_DestroyTexture(HardStr.ScoreTexture);
	SDL_DestroyTexture(HardStr.LenSnakeTexture);
	SDL_DestroyTexture(HardStr.SNAKE_HARD_TEXTURE);
}

void Setkahard(SDL_Renderer* renderer) {
	for (int i = 0; i < 760; i += 60) {
		SDL_RenderDrawLine(renderer, 300 + i, 0, 300 + i, 720);
	}
	for (int i = 0; i < 760; i += 60) {
		SDL_RenderDrawLine(renderer, 300, i, 1000, i);
	}
}

void FruitSpawnHard() {
	while (!HardStr.flagFruit) {
		HardStr.c = 0;
		HardStr.fruitX = rand() % (WIDTH_HARD2 - WIDTH_HARD1 + 1) + WIDTH_HARD1;
		HardStr.fruitY = rand() % (HEIGHT_HARD2 - HEIGHT_HARD1 + 1) + HEIGHT_HARD1;
		if (HardStr.fruitX % 60 == 0 && HardStr.fruitY % 60 == 0){
				for (int i = 0; i < HardStr.LenSnake; i++) {
					if ((HardStr.fruitX == HardStr.SnakePosX[i] && HardStr.fruitY == HardStr.SnakePosY[i]) || (HardStr.TempFruitX == HardStr.fruitX && HardStr.TempFruitY == HardStr.fruitY)) { // Ïğîâåğêà íåíàëîæåíèÿ íà çìåéêó è íà ìåñòî, ãäå ôğóêò áûë â ïğîøëûé ğàç
						HardStr.c++;
					}
				}
				if (HardStr.c == 0) {
					HardStr.TempFruitX = HardStr.fruitX;
					HardStr.TempFruitY = HardStr.fruitY;
					HardStr.flagFruit = true;


				}
				else
					continue;
			}
	}
}
void RenderGameHard(SDL_Renderer* RenderGame) {


	HardStr.text = u8"Ñ÷¸ò: ";
	HardStr.LenSnText = u8"Äëèíà çìåéêè: ";

	HardStr.LenSn = to_string(HardStr.LenSnake);
	HardStr.LenSnText = HardStr.LenSnText + HardStr.LenSn;
	HardStr.scoreOne = to_string(HardStr.score);
	HardStr.text = HardStr.text + HardStr.scoreOne;

	strcpy_s(HardStr.textScore, HardStr.text.c_str()); //Ïğåîáğàçîâàíèå èç string â char*
	strcpy_s(HardStr.LenSnakeChar, HardStr.LenSnText.c_str());

	HardStr.ScoreTexture = Get_TextTextureHard(RenderGame, HardStr.textScore, HardStr.fontScore);
	HardStr.LenSnakeTexture = Get_SnakeLenTextureHard(RenderGame, HardStr.LenSnakeChar, HardStr.SnakeLenTTF);

	if (HardStr.chooseFood == true) {//Øàíñû ïîÿâëåíèÿ åäû îïğåäåëåííîãî òèïà
		HardStr.randomFood = rand() % 100;
		if (HardStr.randomFood < 50)
			HardStr.Food_Number = 0;
		if (HardStr.randomFood >= 50 && HardStr.randomFood < 80)
			HardStr.Food_Number = 1;
		if (HardStr.randomFood >= 80 && HardStr.randomFood < 100)
			HardStr.Food_Number = 2;
		HardStr.chooseFood = false; // ×ÒÎÁÛ ÅÄÀ ìåíÿëàñü îäèí ğàç
	}
	SDL_SetRenderDrawColor(RenderGame, 201, 201, 201, 0);//ÖÂÅÒ ÏÎËß
	SDL_RenderClear(RenderGame);
	SDL_RenderCopy(RenderGame, HardStr.ScoreTexture, NULL, &HardStr.TextRect); //ÎÒĞÈÑÎÂÊÀ Ñ×ÅÒÀ
	SDL_RenderCopy(RenderGame, HardStr.LenSnakeTexture, NULL, &HardStr.TextLenSnake);//ÎÒĞÈÑÎÂÊÀ ÄËÈÍÛ ÇÌÅÉÊÈ
	SDL_RenderCopy(RenderGame, HardStr.to_menuTexture, NULL, &HardStr.TO_MENU_RECT);//ÎÒĞÈÑÎÂÊÀ ÈÊÎÍÊÈ ÌÅÍŞ

	SDL_DestroyTexture(HardStr.LenSnakeTexture); // ÄËß ÎÑÂÎÁÎÆÄÅÍÈß ÏÀÌßÒÈ
	SDL_DestroyTexture(HardStr.ScoreTexture); // ÄËß ÎÑÂÎÁÎÆÄÅÍÈß ÏÀÌßÒÈ

	SDL_SetRenderDrawColor(RenderGame, 195, 195, 195, 0);//Ñåòî÷êà
	Setkahard(RenderGame);                    //Ìîæíî âêëş÷èòü ïî æåëàíèş

	SDL_SetRenderDrawColor(RenderGame, 255, 0, 0, 0);

	SDL_RenderDrawRect(RenderGame, &HardStr.CRAY);

	for (int x = 300; x < 1000;x += 60) {
		for (int y = 0; y < 720; y += 60) {
			if (x == HardStr.xE && y == HardStr.yE) {
				SDL_Rect rect = { x, y, 60,60 };

				if (DirHard == RIGHT)
					SDL_RenderCopy(RenderGame, HardStr.HeadSnakeTexture, NULL, &rect);
				if (DirHard == LEFT)
					SDL_RenderCopyEx(RenderGame, HardStr.HeadSnakeTexture, NULL, &rect, 0, 0, SDL_FLIP_HORIZONTAL); //ÎÒĞÈÑÎÂÊÀ ÃÎËÎÂÛ ÇÌÅÉÊÈ
				if (DirHard == UP)
					SDL_RenderCopyEx(RenderGame, HardStr.HeadSnakeTexture, NULL, &rect, 270, 0, SDL_FLIP_NONE);
				if (DirHard == DOWN)
					SDL_RenderCopyEx(RenderGame, HardStr.HeadSnakeTexture, NULL, &rect, 90, 0, SDL_FLIP_NONE);
				if (DirHard == START)
					SDL_RenderCopy(RenderGame, HardStr.HeadSnakeTexture, NULL, &rect);
			}
			for (int i = 0; i < HardStr.LenSnake;i++) {
				if (HardStr.SnakeX[i] == x && HardStr.SnakeY[i] == y) {
					SDL_Rect rect = { HardStr.SnakeX[i], HardStr.SnakeY[i],60, 60 };
					SDL_RenderCopy(RenderGame, HardStr.SNAKE_HARD_TEXTURE, NULL, &rect); //ÎÒĞÈÑÎÂÊÀ ÃÎËÎÂÛ È ÒÅËÀ ÇÌÅÉÊÈ
				}
			}

		}
	}
	for (int x = 300; x < 1000; x++)
		for (int y = 0; y < 720; y++) {
			if (x == HardStr.fruitX && y == HardStr.fruitY) //ÎÒĞÈÑÎÂÊÀ ÅÄÛ
			{
				SDL_Rect Rect = { HardStr.fruitX,HardStr.fruitY, 60, 60 };
				if (HardStr.Food_Number == 0)
					SDL_RenderCopy(RenderGame, HardStr.AppleTexture, NULL, &Rect);
				if (HardStr.Food_Number == 1)
					SDL_RenderCopy(RenderGame, HardStr.KlubnicaTexture, NULL, &Rect);
				if (HardStr.Food_Number == 2)
					SDL_RenderCopy(RenderGame, HardStr.BananaTexture, NULL, &Rect);
			}
		}
}

void ActivityHard(SDL_Event event, bool& Pause) //ÊÍÎÏÊÈ È ÌÛØÜ
{
	int x, y;
	SDL_GetMouseState(&x, &y);
	switch (event.type)
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
			case SDLK_a:
				if (DirHard != RIGHT)          // ÂËÅÂÎ
					DirHard = LEFT; break;
			case SDLK_LEFT:
				if (DirHard != RIGHT)          // ÂËÅÂÎ
					DirHard = LEFT; break;
			case SDLK_w:
				if (DirHard != DOWN)         // ÂÂÅĞÕ
					DirHard = UP; break;
			case SDLK_UP:
				if (DirHard != DOWN)         // ÂÂÅĞÕ
					DirHard = UP; break;
			case SDLK_d:                // ÂÏĞÀÂÎ
				if (DirHard != LEFT)
					DirHard = RIGHT; break;
			case SDLK_RIGHT:
				if (DirHard != LEFT)
					DirHard = RIGHT; break;
			case SDLK_s:                // ÂÍÈÇ
				if (DirHard != UP)
					DirHard = DOWN; break;
			case SDLK_DOWN:
				if (DirHard != UP)
					DirHard = DOWN; break;
			case SDLK_ESCAPE:
				Pause = true;
				cout << "Escape was pressed" << endl; break;
			}
			if ((event.type == SDL_MOUSEBUTTONDOWN) && (event.button.button == SDL_BUTTON_LEFT))
				if (x >= 1230 && x <= 1280 && y >= 0 && y <= 50) //ÍÀÆÀÒÈÅ ÍÀ ÈÊÎÍÊÓ ÏÀÓÇÛ
				{
					Pause = true;
				}
}

void GameLogicHard() {
	//Ğåàëèçàöèÿ íàğàñòàíèÿ è ïîâîğîòà òåëà çìåéêè
	int LastX = HardStr.SnakeX[0], LastY = HardStr.SnakeY[0];
	int LastXX, LastYY;
	HardStr.SnakeX[0] = HardStr.xE;
	HardStr.SnakeY[0] = HardStr.yE;

	for (int i = 0; i < HardStr.LenSnake;i++) {
		LastXX = HardStr.SnakeX[i];
		LastYY = HardStr.SnakeY[i];
		HardStr.SnakeX[i] = LastX;
		HardStr.SnakeY[i] = LastY;
		LastX = LastXX;
		LastY = LastYY;
		HardStr.SnakePosX[i] = LastX; //Çàïîìíèòü êîîğäèíàòû çìåéêè è çàíåñòè èõ â ìàññèâ
		HardStr.SnakePosY[i] = LastY;
	}
	switch (DirHard) {
	case LEFT:      // ÂËÅÂÎ
		HardStr.Left = true;
		HardStr.Right = false;
		HardStr.Down = false;
		HardStr.Up = false;
		break;
	case UP:      // ÂÂÅĞÕ
		HardStr.Left = false;
		HardStr.Right = false;
		HardStr.Down = false;
		HardStr.Up = true;
		break;
	case RIGHT:      // ÂÏĞÀÂÎ
		HardStr.Left = false;
		HardStr.Right = true;
		HardStr.Down = false;
		HardStr.Up = false
			; break;
	case DOWN:      // ÂÍÈÇ
		HardStr.Left = false;
		HardStr.Right = false;
		HardStr.Down = true;
		HardStr.Up = false;
		break;
	}
	if (HardStr.Right == true)
		HardStr.xE += 60;
	if (HardStr.Left == true)
		HardStr.xE -= 60;
	if (HardStr.Up == true)
		HardStr.yE -= 60;
	if (HardStr.Down == true)
		HardStr.yE += 60;

	if ((HardStr.xE == HardStr.fruitX) && (HardStr.yE == HardStr.fruitY)) { // Åñëè ôğóêò áûë ñúåäåí
		if (HardStr.Food_Number == 0)
			HardStr.score++;
		if (HardStr.Food_Number == 1)
			HardStr.score += 2;
		if (HardStr.Food_Number == 2)
			HardStr.score += 3;
		HardStr.LenSnake++;
		HardStr.flagFruit = false;
		HardStr.chooseFood = true;
		FruitSpawnHard();
		UKUS_Sound();
	}
	if (HardStr.LenSnake == 144) {
		HardStr.WIN = true;
		HardStr.GameOver = true;
	}
	for (int i = 1; i < HardStr.LenSnake;i++) { //Ïğîâåğêà íå áûë ëè ñúåäåí õâîñò
		if (HardStr.SnakeX[i] == HardStr.xE && HardStr.SnakeY[i] == HardStr.yE) {
			cout << "GameOver!" << endl;
			HardStr.GameOver = true;
		}
	}
	if ((HardStr.xE < 280 || HardStr.xE > 960) || (HardStr.yE < 0 || HardStr.yE > 680)) { // Óñëîâèå âûõîäà çà ğàìêè ïîëÿ
		cout << "GameOver!" << endl; HardStr.GameOver = true;
	}

}

//_______________________________________________________________________________
clock_t startHard = clock();    //Íåîáõîäèì äëÿ îòâÿçêè FPS ïğèëîæåíèÿ îò èãğû!!!!!!!
//_______________________________________________________________________________


void HardMode(SDL_Renderer* renderer, SDL_Event event, bool& Normal, bool& StartGame) {
	if (!HardStr.Pause) {
		if (HardStr.LoadTexturesEasyBool) { //ÒÎ, ×ÒÎ ÍÓÆÍÎ ÇÀÃĞÓÇÈÒÜ 1 ĞÀÇ
			LoadTexturesHard(renderer);
			DirHard = START;
			PlayHardSound();
			HardStr.fontScore = TTF_OpenFont("Text.ttf", 54);
			HardStr.SnakeLenTTF = TTF_OpenFont("Text.ttf", 48);
			HardStr.LoadTexturesEasyBool = false;
			ReadRecords();
		}
		if (HardStr.GameOver == false) //ÎÑÍÎÂÍÀß ×ÀÑÒÜ ÈÃĞÛ
		{
			ActivityHard(event, HardStr.Pause);
			if (clock() - startHard >= 250) { //Îáíîâëåíèå ğåíäåğà èãğû - ÊÎÍÒĞÎËÜ ÑÊÎĞÎÑÒÈ
				FruitSpawnHard();
				GameLogicHard();
				RenderGameHard(renderer);
				startHard = clock();
				SDL_RenderPresent(renderer);
			}
		}
		else //ÅÑËÈ ÈÃĞÀ ÇÀÂÅĞØÅÍÀ
		{
			if (HardStr.check == true&&HardStr.WIN==false) {
				if (CheckNewRecord(HardStr.score, 2, HardStr.NewRecord, HardStr.OldRecord)) //Ïğîâåğêà íîâîãî ğåêîğäà, åãî çàïèñü â ÔÀÉË
				{
					HardStr.NewRecordMenuFlag = true;
					HardStr.check = false;
				}
				else {
					HardStr.LoseMenuFlag = true;
					HardStr.check = false;
				}
			}
			if (HardStr.NewRecordMenuFlag)
				NewRecordMenu(renderer, event, HardStr.BackToMenu, HardStr.Restart, HardStr.NewRecord, HardStr.OldRecord, HardStr.NewRecordMenuFlag, HardStr.check);
			if (HardStr.LoseMenuFlag)
				LoseMenu(renderer, event, HardStr.BackToMenu, HardStr.Restart, HardStr.NewRecord, HardStr.OldRecord, HardStr.LoseMenuFlag, HardStr.check);

			if (HardStr.WIN == true) {
				if (HardStr.check == true) {
					if (CheckNewRecord(HardStr.score, 2, HardStr.NewRecord, HardStr.OldRecord)) //Ïğîâåğêà íîâîãî ğåêîğäà, åãî çàïèñü â ÔÀÉË)
						HardStr.check = false;
					else
						HardStr.check = false;
				}

				WinMenu(renderer, event, HardStr.BackToMenu, HardStr.Restart, HardStr.NewRecord, HardStr.OldRecord, HardStr.WIN, HardStr.check);
			}
		}
	}

	else //ÅÑËÈ ÍÀÆÀÒÀ ÊËÀÂÈØÀ ÍÀÑÒĞÎÅÊ
	{
		GameSettings(renderer, event, HardStr.Pause, HardStr.Restart, HardStr.BackToMenu);
	}
	if (HardStr.Restart) //ÏÅĞÅÇÀÏÓÑÊ ÓĞÎÂÍß
	{
		Normal = true;
		HardStr.Right = false;
		HardStr.Left = false;
		HardStr.Down = false;
		HardStr.Up = false;
		HardStr.GameOver = false;
		DirHard = START;
		HardStr.LoadTexturesEasyBool = false;
		HardStr.score = 0;
		HardStr.xE = 600, HardStr.yE = 360;

		for (int i = 0; i < HardStr.LenSnake; i++)
		{
			HardStr.SnakeX[i] = 0; HardStr.SnakeY[i] = 0;
		}
		HardStr.LenSnake = 1;
		HardStr.Restart = false;
		HardStr.flagFruit = false;
		PlayHardSound();
		HardMode(renderer, event, Normal, StartGame);
	}
	if (HardStr.BackToMenu) //ÅÑËÈ ÁÛË ÂÎÇÂĞÀÒ Â ÃËÀÂÍÎÅ ÌÅÍŞ
	{
		Normal = false;
		StartGame = false;
		HardStr.Right = false;
		HardStr.Left = false;
		HardStr.Down = false;
		HardStr.Up = false;
		HardStr.GameOver = false;
		HardStr.LoadTexturesEasyBool = true;
		DirHard = START;

		HardStr.score = 0;
		HardStr.xE = 600, HardStr.yE = 360;
		HardStr.flagFruit = false;
		DeleteTexturesHard();
		PlayFonMusic();
		for (int i = 0; i < HardStr.LenSnake; i++)
		{
			HardStr.SnakeX[i] = 0; HardStr.SnakeY[i] = 0;
		}
		HardStr.LenSnake = 1;
		HardStr.BackToMenu = false;
	}
}