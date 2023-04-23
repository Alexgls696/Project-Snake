#pragma once
#include "SDL.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"
#include "SDL_Image.h"
#include <iostream>
#include <Windows.h>
using namespace std;
void MenuDiff(SDL_Renderer *renderer, bool &FlagDiffMenu,bool &MainMenu,bool &LoadDiffTexture,SDL_Event event,SDL_Window*window);