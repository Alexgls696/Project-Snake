#include "StartGame.h"
#include "Sound.h"
#include <ctime>
#include "GameModEasy.h"
#include "SDL_ttf.h"

//ÒÅÊÑÒÓÐÛ ÌÅÍÞ
SDL_Texture* EasyUpTexture = NULL;
SDL_Texture* NormalUpTexture = NULL;
SDL_Texture* HardUpTexture = NULL;
SDL_Texture* BackUpTexture = NULL;
SDL_Texture* FONTexture = NULL;

SDL_Surface* EasyUpSurface = NULL;
SDL_Surface* NormalUpSurface = NULL;
SDL_Surface* HardUpSurface = NULL;
SDL_Surface* BackUpSurface = NULL;
SDL_Surface* FONSurface = NULL;
SDL_Rect FON_Rect = { 0,0,1280,720 };
SDL_Rect EasyRect = { 530,50,220,100 };
SDL_Rect NormalRect = { 530,160,220,100 };
SDL_Rect HardRect = { 530,270,220,100 };
SDL_Rect BackRect = { 530,380,220,100 };

bool Easy = false;
bool Normal = false;
bool Hard = false;
bool StartGame = false;

void TapDiff(int x, int y, bool& Back, SDL_Renderer* renderer, bool& Easy, bool& Normal, bool& Hard, bool &StartGame) {
	if ((x > 530 && x < 740) && (y > 50 && y < 150)) {
		TapSound();
		SDL_RenderClear(renderer);
		Easy = true;
		StartGame = true;
		
		std::cout << "Easy mod started" << std::endl;
	}
	if ((x > 530 && x < 740) && (y > 160 && y < 260)) {
		TapSound();
		std::cout << "Normal mod started" << std::endl;
	}
	if ((x > 530 && x < 740) && (y > 270 && y < 370)) {
		TapSound();
		std::cout << "Hard mod started" << std::endl;
	}
	if ((x > 530 && x < 740) && (y > 380 && y < 480)) {
		TapSound();
		std::cout << "MenuDiff Closed" << std::endl;
		Back = true;
	}
}


void LoadTextures(SDL_Renderer* renderer) {
	EasyUpSurface = IMG_Load("Textures\\EASY_UP.bmp");
	SDL_SetColorKey(EasyUpSurface, SDL_TRUE, SDL_MapRGB(EasyUpSurface->format, 255, 255, 255));
	EasyUpTexture = SDL_CreateTextureFromSurface(renderer, EasyUpSurface);
	SDL_FreeSurface(EasyUpSurface);
	
	NormalUpSurface = IMG_Load("Textures\\NORMAL_UP.bmp");
	SDL_SetColorKey(NormalUpSurface, SDL_TRUE, SDL_MapRGB(NormalUpSurface->format, 255, 255, 255));
	NormalUpTexture = SDL_CreateTextureFromSurface(renderer, NormalUpSurface);
	SDL_FreeSurface(NormalUpSurface);

	HardUpSurface = IMG_Load("Textures\\HARD_UP.bmp");
	SDL_SetColorKey(HardUpSurface, SDL_TRUE, SDL_MapRGB(HardUpSurface->format, 255, 255, 255));
	HardUpTexture = SDL_CreateTextureFromSurface(renderer, HardUpSurface);
	SDL_FreeSurface(HardUpSurface);
	
	BackUpSurface = IMG_Load("Textures\\BACK_UP.bmp");
	SDL_SetColorKey(BackUpSurface, SDL_TRUE, SDL_MapRGB(BackUpSurface->format, 255, 255, 255));
	BackUpTexture = SDL_CreateTextureFromSurface(renderer, BackUpSurface);
	SDL_FreeSurface(BackUpSurface);

	FONSurface = IMG_Load("Textures\\FON_MENU.bmp");
	SDL_SetColorKey(FONSurface, SDL_TRUE, SDL_MapRGB(FONSurface->format, 255, 255, 255));
	FONTexture = SDL_CreateTextureFromSurface(renderer, FONSurface);
	SDL_FreeSurface(FONSurface);

}

void DrawTextureMenu(SDL_Renderer* renderer) {
	SDL_RenderCopy(renderer, FONTexture, NULL, &FON_Rect);
	SDL_RenderCopy(renderer, EasyUpTexture, NULL, &EasyRect);
	SDL_RenderCopy(renderer, NormalUpTexture, NULL, &NormalRect);
	SDL_RenderCopy(renderer, HardUpTexture, NULL, &HardRect);
	SDL_RenderCopy(renderer, BackUpTexture, NULL, &BackRect);
}

void MenuDiff(SDL_Renderer* renderer, bool& FlagDiffMenu, bool& MainMenu, bool& LoadTexture,SDL_Event event,SDL_Window*window) {
	srand(time(NULL));

	bool Back = false;
	bool GameMenu = false;
	int x, y;

	SDL_GetMouseState(&x, &y);
	if (Back == false && StartGame == false) {
		if (LoadTexture == true) {
			LoadTextures(renderer);
			LoadTexture = false;
		}
		DrawTextureMenu(renderer);
		if ((event.type == SDL_MOUSEBUTTONDOWN) && (event.button.button == SDL_BUTTON_LEFT)) {
			TapDiff(x, y, Back, renderer, Easy, Normal, Hard, StartGame);
		}
		SDL_RenderPresent(renderer);
		SDL_Delay(16);
	}
	if (Back == true) {
		SDL_DestroyTexture(EasyUpTexture);
		SDL_DestroyTexture(NormalUpTexture);
		SDL_DestroyTexture(HardUpTexture);
		SDL_DestroyTexture(BackUpTexture);
		SDL_DestroyTexture(FONTexture);


		MainMenu = true;
		LoadTexture = true;
		FlagDiffMenu = false;
		return;
	}
	if (Easy == true) {

		EasyMode(renderer, event,Easy,StartGame);
	}
}