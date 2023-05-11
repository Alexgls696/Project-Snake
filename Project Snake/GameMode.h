#pragma once
#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "Sound.h"
#include "SDL_ttf.h"
#include <ctime>
#include <string>
using namespace std;

void EasyMode(SDL_Renderer* renderer, SDL_Event event, bool& Easy, bool& StartGame);
void NormalMode(SDL_Renderer* renderer, SDL_Event event, bool& Normal, bool& StartGame);
void HardMode(SDL_Renderer* renderer, SDL_Event event, bool& hard, bool& StartGame);


