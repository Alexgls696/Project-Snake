#pragma once
#include <string>

#include <iostream>
#include <fstream>
#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_Image.h"
using namespace std;

void ReadRecords();
void NewRecordMenu(SDL_Renderer* renderer, SDL_Event event, bool& BackToMenu, bool& Restart, int NewRecord, int OldRecord, bool& NewRecordMenuFlag, bool& check);
void LoseMenu(SDL_Renderer* renderer, SDL_Event event, bool& BackToMenu, bool& Restart, int NewRecord, int OldRecord, bool& LoseMenuFlag, bool& check);
void ClearRecords();
bool CheckNewRecord(int Score, int GameMode, int& NewRecord, int& OldRecord);


