#pragma once
#include <iostream>
#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include "SDL_image.h"

using namespace std;

void GameSettings(SDL_Renderer* renderer, SDL_Event event, bool& Pause,bool&Restart,bool&BackToMenu);


