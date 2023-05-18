#include "Records.h"

int LastScore;

SDL_Surface* NewRecordMenuSurface = NULL;
SDL_Texture* NewRecordMenuTexture = NULL;
SDL_Surface* LoseRecordSurfaceMenu = NULL;
SDL_Texture* LoseRecordTextureMenu = NULL;
SDL_Surface* Win_Surface = NULL;
SDL_Texture* WinTexture = NULL;

SDL_Surface* ToMenuSurface = NULL;
SDL_Texture* ToMenuTexture = NULL;

SDL_Surface* ReplaySurface = NULL;
SDL_Texture* ReplayTexture = NULL;

SDL_Surface* WHITE_Rec_Surface = NULL;
SDL_Texture* WHITE_Rec_Texture = NULL;

SDL_Texture* OldScoreTexture = NULL;
SDL_Texture* NewScoreTexture = NULL;


SDL_Rect OldRect = { 790,375,50,50 };
SDL_Rect NewRect = { 710,460,50,50 };
SDL_Rect FailOld = { 710,370,50,50 };
SDL_Rect FailNew = { 740,455,50,50 };

SDL_Rect WhiteRecRect = {0,0,1280,720};
SDL_Rect RezRect = { 330, 70, 600, 600 };
SDL_Rect ReplayRect = { 550,550,75,75 };
SDL_Rect ToMenuRect = { 650,550,75,75 };


struct Rec {
	string Game_mode;
	int Score;
	int Score2;
	int Score3;
};
Rec Records[3];

void LoadTexturesRecord(SDL_Renderer* renderer) {
	NewRecordMenuSurface = IMG_Load("Textures\\NewRecord.bmp");
	SDL_SetColorKey(NewRecordMenuSurface, SDL_TRUE, SDL_MapRGB(NewRecordMenuSurface->format, 255, 255, 255));
	NewRecordMenuTexture = SDL_CreateTextureFromSurface(renderer, NewRecordMenuSurface);
	SDL_FreeSurface(NewRecordMenuSurface);

	ReplaySurface = IMG_Load("Textures\\IconReplay.bmp");
	SDL_SetColorKey(ReplaySurface, SDL_TRUE, SDL_MapRGB(ReplaySurface->format, 0, 0, 0));
	ReplayTexture = SDL_CreateTextureFromSurface(renderer, ReplaySurface);
	SDL_FreeSurface(ReplaySurface);

	ToMenuSurface = IMG_Load("Textures\\To_Menu_Icon.bmp");
	SDL_SetColorKey(ToMenuSurface, SDL_TRUE, SDL_MapRGB(ToMenuSurface->format, 1, 2, 3));
	ToMenuTexture = SDL_CreateTextureFromSurface(renderer, ToMenuSurface);
	SDL_FreeSurface(ToMenuSurface);

	LoseRecordSurfaceMenu = IMG_Load("Textures\\LoseRecord.bmp");
	SDL_SetColorKey(LoseRecordSurfaceMenu, SDL_TRUE, SDL_MapRGB(LoseRecordSurfaceMenu->format, 255, 255, 255));
	LoseRecordTextureMenu = SDL_CreateTextureFromSurface(renderer, LoseRecordSurfaceMenu);
	SDL_FreeSurface(LoseRecordSurfaceMenu);

	Win_Surface = IMG_Load("Textures//WIN.bmp");
	SDL_SetColorKey(Win_Surface, SDL_TRUE, SDL_MapRGB(Win_Surface->format, 255, 255, 255));
	WinTexture = SDL_CreateTextureFromSurface(renderer, Win_Surface);
	SDL_FreeSurface(Win_Surface);

	//Текстура прозрачности (Беление экрана)
	WHITE_Rec_Surface = IMG_Load("Textures\\White.bmp");
	SDL_SetColorKey(WHITE_Rec_Surface, SDL_TRUE, SDL_MapRGB(WHITE_Rec_Surface->format, 5, 5, 5));
	WHITE_Rec_Texture = SDL_CreateTextureFromSurface(renderer, WHITE_Rec_Surface);
	SDL_FreeSurface(WHITE_Rec_Surface);
}
void DeleteTexturesRecord() {
	SDL_DestroyTexture(NewRecordMenuTexture);
	SDL_DestroyTexture(NewScoreTexture);
	SDL_DestroyTexture(ReplayTexture);
	SDL_DestroyTexture(OldScoreTexture);
	SDL_DestroyTexture(WHITE_Rec_Texture);
	SDL_DestroyTexture(ToMenuTexture);
	SDL_DestroyTexture(LoseRecordTextureMenu);
}


SDL_Texture* GetRecordTextTexture(SDL_Renderer* renderer,char*text,TTF_Font*font) {
	SDL_Surface* textSurface = NULL;
	SDL_Color forecolor = { 0,0,0 };
	SDL_Color backcolor = { 0,0,0,1 };
	textSurface = TTF_RenderText_Shaded(font, text, forecolor, backcolor);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, textSurface);
	SDL_FreeSurface(textSurface);
	return texture;
}

char OldRec[10];
char NewRec[10];

bool OnceRec = true;
TTF_Font* font = NULL;

void ClearRecords() {
	setlocale(LC_ALL, "rus");
	ofstream file("Records.txt");
	if (file) {
		file << "Easy 0 0 0" << endl;
		file << "Normal 0 0 0" << endl;
		file << "hard 0 0 0" << endl;
		file.close();
		cout << "Рекорды очищены" << endl;
	}
	else {
		cout << "ФАЙЛ НЕ БЫЛ ОТКРЫТ ДЛЯ ОЧИСТКИ!" << endl;
	}
}
void ReadRecords() {
	
	ifstream file("Records.txt");
	if (!file)
		cout << "Не удалось открыть файл рекордов." << endl;
	else
	{
		for (int i = 0; i < 3;i++) {
			file >> Records[i].Game_mode >> Records[i].Score >> Records[i].Score2 >> Records[i].Score3;
		}
		file.close();
	}
}
void LoseMenu(SDL_Renderer* renderer, SDL_Event event, bool& BackToMenu, bool& Restart, int NewRecord, int OldRecord, bool& LoseMenuFlag,bool&check) {
	int x, y;
	if (OnceRec == true) {
		font = TTF_OpenFont("Text.ttf", 80);
		_itoa_s(NewRecord, NewRec, 10);
		_itoa_s(OldRecord, OldRec, 10);
		OldScoreTexture = GetRecordTextTexture(renderer, OldRec, font);
		NewScoreTexture = GetRecordTextTexture(renderer, NewRec, font);
		LoadTexturesRecord(renderer);
		OnceRec = false;
	}

	SDL_SetTextureAlphaMod(WHITE_Rec_Texture, 3);
	SDL_RenderCopy(renderer, WHITE_Rec_Texture, NULL, &WhiteRecRect);
	SDL_RenderCopy(renderer, LoseRecordTextureMenu, NULL, &RezRect);
	SDL_RenderCopy(renderer, ToMenuTexture, NULL, &ToMenuRect);
	SDL_RenderCopy(renderer, ReplayTexture, NULL, &ReplayRect);
	SDL_RenderCopy(renderer, OldScoreTexture, NULL, &FailOld);
	SDL_RenderCopy(renderer, NewScoreTexture, NULL, &FailNew);

	SDL_GetMouseState(&x, &y);
	if ((event.type == SDL_MOUSEBUTTONDOWN) && (event.button.button == SDL_BUTTON_LEFT)) {
		if (x >= 550 && x <= 625 && y >= 550 && y <= 625)//Replay
		{
			LoseMenuFlag = false;
			OnceRec = true;
			Restart = true;
			check = true;
			DeleteTexturesRecord();
			TTF_CloseFont(font);

		}
		if (x >= 650 && x <= 725 && y >= 550 && y <= 625)//Возврат в меню 
		{
			LoseMenuFlag = false;
			BackToMenu = true;
			OnceRec = true;
			check = true;
			DeleteTexturesRecord();
			TTF_CloseFont(font);
		}
	}
	SDL_RenderPresent(renderer);
}
void NewRecordMenu(SDL_Renderer* renderer,SDL_Event event, bool& BackToMenu, bool& Restart, int NewRecord, int OldRecord,bool &NewRecordMenuFlag,bool&check) {
	int x, y;
	if (OnceRec == true) {
		
		 font = TTF_OpenFont("Text.ttf", 50);
		_itoa_s(NewRecord, NewRec, 10);
		_itoa_s(OldRecord, OldRec, 10);
		OldScoreTexture = GetRecordTextTexture(renderer, OldRec, font);
		NewScoreTexture = GetRecordTextTexture(renderer, NewRec, font);
		LoadTexturesRecord(renderer);
		OnceRec = false;
	}

	SDL_SetTextureAlphaMod(WHITE_Rec_Texture, 3);
	SDL_RenderCopy(renderer, WHITE_Rec_Texture, NULL, &WhiteRecRect);
	SDL_RenderCopy(renderer, NewRecordMenuTexture, NULL, &RezRect);
	SDL_RenderCopy(renderer, ToMenuTexture, NULL, &ToMenuRect);
	SDL_RenderCopy(renderer, ReplayTexture, NULL, &ReplayRect);
	SDL_RenderCopy(renderer, OldScoreTexture, NULL, &OldRect);
	SDL_RenderCopy(renderer, NewScoreTexture, NULL, &NewRect);
	
	SDL_GetMouseState(&x, &y);
	if ((event.type == SDL_MOUSEBUTTONDOWN) && (event.button.button == SDL_BUTTON_LEFT)) {
		if (x >= 550 && x <= 625 && y >= 550 && y <= 625)//Replay
		{
			NewRecordMenuFlag = false;
			OnceRec = true;
			Restart = true;
			check = true;
			DeleteTexturesRecord();
			TTF_CloseFont(font);

		}
		
		if (x >= 650 && x <= 725 && y >= 550 && y <= 625)//Возврат в меню 
		{
			NewRecordMenuFlag = false;
			BackToMenu = true;
			OnceRec = true;
			check = true;
			DeleteTexturesRecord();
			TTF_CloseFont(font);
		}
	}
	SDL_RenderPresent(renderer);
}
void WinMenu(SDL_Renderer* renderer, SDL_Event event, bool& BackToMenu, bool& Restart, int NewRecord, int OldRecord, bool& WinMenuFlag, bool& check) {
	 {
		int x, y;
		if (OnceRec == true) {
			font = TTF_OpenFont("Text.ttf", 80);
			_itoa_s(NewRecord, NewRec, 10);
			_itoa_s(OldRecord, OldRec, 10);
			OldScoreTexture = GetRecordTextTexture(renderer, OldRec, font);
			NewScoreTexture = GetRecordTextTexture(renderer, NewRec, font);
			LoadTexturesRecord(renderer);
			OnceRec = false;
		}

		SDL_SetTextureAlphaMod(WHITE_Rec_Texture, 3);
		SDL_RenderCopy(renderer, WHITE_Rec_Texture, NULL, &WhiteRecRect);
		SDL_RenderCopy(renderer, WinTexture, NULL, &RezRect);
		SDL_RenderCopy(renderer, ToMenuTexture, NULL, &ToMenuRect);
		SDL_RenderCopy(renderer, ReplayTexture, NULL, &ReplayRect);
		SDL_Rect FailOldWin = { 760,370,50,50 };
		SDL_Rect FailNewWin = { 700,450,50,50 };
		SDL_RenderCopy(renderer, OldScoreTexture, NULL, &FailOldWin);
		SDL_RenderCopy(renderer, NewScoreTexture, NULL, &FailNewWin);

		SDL_GetMouseState(&x, &y);
		if ((event.type == SDL_MOUSEBUTTONDOWN) && (event.button.button == SDL_BUTTON_LEFT)) {
			if (x >= 550 && x <= 625 && y >= 550 && y <= 625)  //Replay
			{
				WinMenuFlag = false;
				OnceRec = true;
				Restart = true;
				check = true;
				DeleteTexturesRecord();
				TTF_CloseFont(font);
			}
			if (x >= 650 && x <= 725 && y >= 550 && y <= 625)//Возврат в меню 
			{
				WinMenuFlag = false;
				BackToMenu = true;
				OnceRec = true;
				check = true;
				DeleteTexturesRecord();
				TTF_CloseFont(font);
			}
		}
		SDL_RenderPresent(renderer);
	}
}
bool CheckNewRecord(int Score,int GameMode,int &NewRecord, int &OldRecord) {
	setlocale(LC_ALL, "rus");
	Rec Records[3];
	bool new_record = false;
	ifstream file("Records.txt");
	if (!file)
		cout << "Не удалось открыть файл рекордов." << endl;
	else
	{
		for (int i = 0; i < 3; i++) {
			file >> Records[i].Game_mode >> Records[i].Score >> Records[i].Score2 >> Records[i].Score3;
		}
		file.close();
		for (int i = 0; i < 3; i++) {
			if (i == GameMode) {
				if (Score > Records[i].Score) {
					OldRecord = Records[i].Score; //Запомнить старый рекорд
					Records[i].Score = Score;
					NewRecord = Score; // Запомнить новый рекорд
					new_record = true;
					break;
				}
				if (Score > Records[i].Score2 && Score < Records[i].Score) {
					OldRecord = Records[i].Score; //Запомнить старый рекорд
					Records[i].Score2 = Score;
					NewRecord = Score;
					
					break;
				}
				if (Score > Records[i].Score3 && Score < Records[i].Score2) {
					OldRecord = Records[i].Score; //Запомнить старый рекорд
					Records[i].Score3 = Score;
					NewRecord = Score;
					
					break;
				}
				else {
					OldRecord = Records[i].Score; 
					NewRecord = Score;
				}
			}
		}
	}
	ofstream new_file("Records.txt");
			if (new_record == true) {
				
				for (int i = 0; i < 3;i++) {
					new_file << Records[i].Game_mode << " " << Records[i].Score << " " << Records[i].Score2<<" " << Records[i].Score3<< endl;
				}
				cout << "Новые рекорды успешно записаны в файл" << endl;
				new_file.close();
				return true;
			}
			else {
				for (int i = 0; i < 3;i++) {
					new_file << Records[i].Game_mode << " " << Records[i].Score << " " << Records[i].Score2 << " " << Records[i].Score3 << endl;
				}
				cout << "Рекорд не был побит" << endl;
				cout << "Файл с рекордами обновлен" << endl;
				return false;
			}
}

