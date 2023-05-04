#include "GameSetting.h"
#include "Sound.h"
#include "GameModEasy.h"

SDL_Surface* BackSurface = NULL;
SDL_Texture* BackTexture = NULL;
SDL_Surface* GoGameSurface = NULL;
SDL_Texture* GoGameTexture = NULL;
SDL_Surface* ReGameSurface = NULL;
SDL_Texture* ReGameTexture = NULL;
SDL_Surface* Pause_MenuSurface = NULL;
SDL_Texture* Pause_MenuTexture = NULL;

SDL_Rect FON_PauseRect = { 0,0,1280,720 };
SDL_Rect GoGameRect = { 530,150,220,100 };
SDL_Rect ReGameRect = { 530,260,220,100 };
SDL_Rect MainRect = { 530,370,220,100 };



bool GoGameHit(int x, int y){
	if ((x >= 530 && x <= 750) && (y >= 150 && y <= 250)) {
		TapSound();
		return true;
	}
	return false;
}

bool ReGameHit(int x, int y) {
	if ((x >= 530 && x <= 750) && (y >= 260 && y <= 360)) {
		TapSound();
		return true;
	}
	return false;
	
}

bool BackMenuHit(int x, int y) {
	if ((x >= 530 && x <= 750) && (y >= 370 && y <= 470)) {
		TapSound();
		return true;
	}
	return false;
}

void DrawGameMenuTexture(SDL_Renderer* renderer) {
	SDL_RenderCopy(renderer, Pause_MenuTexture, NULL, &FON_PauseRect);
	SDL_RenderCopy(renderer, GoGameTexture, NULL, &GoGameRect);
	SDL_RenderCopy(renderer, ReGameTexture, NULL, &ReGameRect);
	//SDL_RenderCopy(renderer, BackTexture, NULL, &MainRect);
	SDL_RenderCopyEx(renderer, BackTexture, NULL, &MainRect, 0, NULL, SDL_FLIP_NONE); //¬ращение текстуры на определенный угол!
}

void LoadTextureGameMenu(SDL_Renderer*renderer) {
	GoGameSurface = IMG_Load("Textures\\gogame.bmp");
	SDL_SetColorKey(GoGameSurface, SDL_TRUE, SDL_MapRGB(GoGameSurface->format, 255, 255, 255));
	GoGameTexture = SDL_CreateTextureFromSurface(renderer, GoGameSurface);
	SDL_FreeSurface(GoGameSurface);

	ReGameSurface = IMG_Load("Textures\\regame.bmp");
	SDL_SetColorKey(ReGameSurface, SDL_TRUE, SDL_MapRGB(ReGameSurface->format, 255, 255, 255));
	ReGameTexture = SDL_CreateTextureFromSurface(renderer, ReGameSurface);
	SDL_FreeSurface(ReGameSurface);

	BackSurface = IMG_Load("Textures\\BackMenu.bmp");
	SDL_SetColorKey(BackSurface, SDL_TRUE, SDL_MapRGB(BackSurface->format, 255, 255, 255));
	BackTexture = SDL_CreateTextureFromSurface(renderer, BackSurface);
	SDL_FreeSurface(BackSurface);

	Pause_MenuSurface = IMG_Load("Textures\\White.bmp");
	SDL_SetColorKey(Pause_MenuSurface, SDL_TRUE, SDL_MapRGB(Pause_MenuSurface->format, 5, 5, 5));
	Pause_MenuTexture = SDL_CreateTextureFromSurface(renderer, Pause_MenuSurface);
	SDL_FreeSurface(Pause_MenuSurface);
	SDL_SetTextureAlphaMod(Pause_MenuTexture, 4);
}

void DeleteTexturesGameMenu() {
	SDL_DestroyTexture(BackTexture);
	SDL_DestroyTexture(GoGameTexture);
	SDL_DestroyTexture(ReGameTexture);
	SDL_DestroyTexture(Pause_MenuTexture);

}

int countRepeat = 1; // —четчик количества загрузок текстур
void GameSettings(SDL_Renderer* renderer, SDL_Event event, bool& Pause,bool&Restart,bool&BackToMenu) {
	int x, y;
	Mix_PauseMusic();
	if (countRepeat == 1) //„тобы текстуры загружались 1 раз при паузе
	{
		LoadTextureGameMenu(renderer);
		countRepeat++;	
	}
	SDL_GetMouseState(&x, &y);

	if ((event.type == SDL_MOUSEBUTTONDOWN) && (event.button.button == SDL_BUTTON_LEFT)) {
		if (GoGameHit(x, y)) {
			Mix_ResumeMusic();
			Pause = false;
			DeleteTexturesGameMenu(); //очищает пам€ть при каждом сворачивании окна паузы
			countRepeat = 1;
			return;
		}
		if (ReGameHit(x, y)) {
			Mix_ResumeMusic();
			Restart = true;
			Pause = false;
			DeleteTexturesGameMenu();
			countRepeat = 1;
			return;
		}
		if (BackMenuHit(x,y)){
			Pause = false;
			BackToMenu = true;
			DeleteTexturesGameMenu();
			countRepeat = 1;
			return;
		}
		
	}

	DrawGameMenuTexture(renderer);
		switch (event.type)
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {

			case SDLK_ESCAPE:
				Pause = false;
				Mix_ResumeMusic();
				DeleteTexturesGameMenu();
				countRepeat = 1;
				cout << "Game continue" << endl; break;
			}

	SDL_RenderPresent(renderer);

}