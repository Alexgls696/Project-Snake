#pragma once
#include <iostream>
#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include "SDL_image.h"

using namespace std;

void WinMenu(SDL_Renderer* renderer, SDL_Event event, bool& StartGame);
void LoseMenu(SDL_Renderer* renderer, SDL_Event event, bool& StartGame);