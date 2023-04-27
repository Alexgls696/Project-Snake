#include "GameSetting.h"

SDL_Surface* BackSurface = NULL;
SDL_Texture* BackTexture = NULL;
SDL_Surface* GoGameSurface = NULL;
SDL_Texture* GoGameTexture = NULL;
SDL_Surface* ReGameSurface = NULL;
SDL_Texture* ReGameTexture = NULL;
SDL_Surface* Pause_MenuSurface = NULL;
SDL_Texture* Pause_MenuTexture = NULL;


SDL_Rect FON_PauseRect = { 0,0,1280,720 };
SDL_Rect GoGameRect = { 530,50,220,100 };
SDL_Rect ReGameRect = { 530,160,220,100 };
SDL_Rect MainRect = { 530,270,220,100 };

bool GoGameHit(int x, int y){
	return true;
}
bool ReGameHit(int x, int y) {
	return true;
}
bool GoMenuHit(int x, int y) {
	return true;
}
void DrawGameMenuTexture(SDL_Renderer* renderer) {
	SDL_RenderCopy(renderer, GoGameTexture, NULL, &GoGameRect);
	SDL_RenderCopy(renderer, ReGameTexture, NULL, &ReGameRect);
	SDL_RenderCopy(renderer, BackTexture, NULL, &MainRect);
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

	Pause_MenuSurface = IMG_Load("Textures\\gogame.bmp");
	SDL_SetColorKey(Pause_MenuSurface, SDL_TRUE, SDL_MapRGB(Pause_MenuSurface->format, 255, 255, 255));
	Pause_MenuTexture = SDL_CreateTextureFromSurface(renderer, Pause_MenuSurface);
	SDL_FreeSurface(Pause_MenuSurface);
}

int countRepeat = 1;
void GameSettings(SDL_Renderer* renderer, SDL_Event event, bool& SettingOn) {
	if (countRepeat == 1) {
		LoadTextureGameMenu(renderer);
		countRepeat++;
	}
	DrawGameMenuTexture(renderer);
		switch (event.type)
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {

			case SDLK_ESCAPE:
				SettingOn = false;
				cout << "Escape was pressed" << endl; break;
			}

	SDL_RenderPresent(renderer);
	SDL_Delay(16);

}