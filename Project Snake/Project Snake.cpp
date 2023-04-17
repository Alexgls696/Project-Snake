#include "SDL.h"
#include "SDL_Image.h"
#include "Sound.h"
#include <iostream>
#include "SDL_ttf.h"


SDL_Window *window= NULL;
SDL_Texture* CloseGoodTexture = NULL;
SDL_Texture* NoCloseTexture = NULL;
bool init() {
    bool GREAT = true;
    if (SDL_Init(SDL_INIT_EVERYTHING < 0)) {
        std::cout << "Ошибка, SDL НЕ БЫЛ ЗАПУЩЕН" << SDL_GetError() << std::endl;
        GREAT = false;
    }
    else {
        window = SDL_CreateWindow(u8"Snake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN);
        if (window == NULL) {
            GREAT = false;
            std::cout << "Окно не было создано!" << SDL_GetError() << std::endl;
        }
    }
    return GREAT;
}

void DrawTextureMenu(SDL_Renderer* MenuRenderer, SDL_Texture* texture, SDL_Rect Rect) {
    SDL_RenderCopy(MenuRenderer, texture, NULL,&Rect);
}


void ActiveCLOSETexture(SDL_Renderer*MenuRenderer) {
    SDL_Surface* ActiveClose = IMG_Load("Textures\\CloseGameActive.bmp");
    SDL_SetColorKey(ActiveClose, SDL_TRUE, SDL_MapRGB(ActiveClose->format, 255, 255, 255));
    SDL_Texture* ACTIVE_CLOSE_Texture = SDL_CreateTextureFromSurface(MenuRenderer, ActiveClose);
    SDL_FreeSurface(ActiveClose);
    SDL_Rect ACTIVE_CLOSE_RECT = { 530,380,220,100 };
    DrawTextureMenu(MenuRenderer, ACTIVE_CLOSE_Texture, ACTIVE_CLOSE_RECT);
}
void ActiveHELPTexture(SDL_Renderer* MenuRenderer) {
    SDL_Surface* ActiveHelp = IMG_Load("Textures\\HelpACTIVE.bmp");
    SDL_SetColorKey(ActiveHelp, SDL_TRUE, SDL_MapRGB(ActiveHelp->format, 255, 255, 255));
    SDL_Texture* ACTIVE_HELP_Texture = SDL_CreateTextureFromSurface(MenuRenderer, ActiveHelp);
    SDL_FreeSurface(ActiveHelp);
    SDL_Rect ACTIVE_HELP_RECT = { 530,270,220,100 };
    DrawTextureMenu(MenuRenderer, ACTIVE_HELP_Texture, ACTIVE_HELP_RECT);
}
void ActiveSTARTTexture(SDL_Renderer* MenuRenderer) {
    SDL_Surface* ActiveSTART = IMG_Load("Textures\\StartGameACTIVE.bmp");
    SDL_SetColorKey(ActiveSTART, SDL_TRUE, SDL_MapRGB(ActiveSTART->format, 255, 255, 255));
    SDL_Texture* ACTIVE_START_Texture = SDL_CreateTextureFromSurface(MenuRenderer, ActiveSTART);
    SDL_FreeSurface(ActiveSTART);
    SDL_Rect ACTIVE_START_RECT = { 530,50,220,100 };
    DrawTextureMenu(MenuRenderer, ACTIVE_START_Texture, ACTIVE_START_RECT);
}
void ActiveACHIVTexture(SDL_Renderer* MenuRenderer) {
    SDL_Surface* ActiveSETTINGS = IMG_Load("Textures\\AchivACTIVE.bmp");
    SDL_SetColorKey(ActiveSETTINGS, SDL_TRUE, SDL_MapRGB(ActiveSETTINGS->format, 255, 255, 255));
    SDL_Texture* ACTIVE_SETTINGS_Texture = SDL_CreateTextureFromSurface(MenuRenderer, ActiveSETTINGS);
    SDL_FreeSurface(ActiveSETTINGS);
    SDL_Rect ACTIVE_SETTINGS_RECT = { 530,160,220,100 };
    DrawTextureMenu(MenuRenderer, ACTIVE_SETTINGS_Texture, ACTIVE_SETTINGS_RECT);
}
void ActiveSettingsTexture(SDL_Renderer* MenuRenderer) {
    SDL_Surface* ActiveACHIV = IMG_Load("Textures\\SettingsACTIVE.bmp");
    SDL_SetColorKey(ActiveACHIV, SDL_TRUE, SDL_MapRGB(ActiveACHIV->format, 255, 255, 255));
    SDL_Texture* ACTIVE_ACHIV_Texture = SDL_CreateTextureFromSurface(MenuRenderer, ActiveACHIV);
    SDL_FreeSurface(ActiveACHIV);
    SDL_Rect ACTIVE_ACHIV_RECT = { 1210,0,70,70 };
    DrawTextureMenu(MenuRenderer, ACTIVE_ACHIV_Texture, ACTIVE_ACHIV_RECT);
}


void TapTexture(SDL_Renderer* MenuRenderer, int x, int y) {
    if ((x > 530 && x < 740) && (y > 50 && y < 150)) {
        ActiveSTARTTexture(MenuRenderer);
        TapSound();
    }
    if ((x > 530 && x < 740) && (y > 270 && y < 370)) {
        ActiveHELPTexture(MenuRenderer);
        TapSound();
    }
    if ((x > 530 && x < 740) && (y > 160 && y < 260)) {
        ActiveACHIVTexture(MenuRenderer);
        TapSound();
    }
    if ((x > 530 && x < 740) && (y > 380 && y < 480)) {
        ActiveCLOSETexture(MenuRenderer);
        TapSound();
    }
    if ((x >= 1210 && x <= 1280) && (y >= 0 && y <= 70)) {
        ActiveSettingsTexture(MenuRenderer);
        TapSound();
    }

}


void DrawCloseTextTexture(SDL_Renderer*&renderer,SDL_Texture*texture) {
    SDL_Rect Rect = { 330,200,600,50 };
    SDL_RenderCopy(renderer, texture,NULL,&Rect);
}
SDL_Texture* Get_CloseTextTexture(SDL_Renderer*&renderer,char*text,TTF_Font*font){
    SDL_Surface* TextSurface = NULL;
    SDL_Color fore_color = { 240,100,9 };
    SDL_Color back_color = { 255,20,20 };
    TextSurface = TTF_RenderUTF8_Solid(font, text, fore_color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, TextSurface);
    SDL_FreeSurface(TextSurface);
    return texture;
}

bool OK_CLOSE(int x, int y) {
    if ((x >= 740 && x <= 820) && (y >= 340 && y <= 420)) {
        return true;
    }
    return false;
}
bool NO_CLOSE(int x, int y) {
    if ((x >= 480 && x <= 540) && (y >= 355 && y <= 405))
        return true;
    return false;
}
bool CloseFunction(int x,int y) {
    if ((x > 530 && x < 740) && (y > 380 && y < 480)) {
        return true;
    }
    else
        return false;
}
int main(int argc, char **argv)
{
    if (!(init())) {
        std::cout << "Не удалось запустить программу" << std::endl;
    }
    else {
        SDL_Renderer* MenuRenderer = SDL_CreateRenderer(window, -1, 0);


        //Текстуры меню
        SDL_Surface* FON = IMG_Load("Textures\\FON_MENU.bmp");
        SDL_SetColorKey(FON, SDL_TRUE, SDL_MapRGB(FON->format, 255, 255, 255));
        SDL_Texture* FON_TEXTURE = SDL_CreateTextureFromSurface(MenuRenderer, FON);
        SDL_FreeSurface(FON);
        SDL_Rect FON_RECT = { 0,0,1280,720 };
        DrawTextureMenu(MenuRenderer, FON_TEXTURE, FON_RECT);


        SDL_Surface* StartGame = IMG_Load("Textures\\Startgame.bmp");
        SDL_SetColorKey(StartGame, SDL_TRUE, SDL_MapRGB(StartGame->format, 255, 255, 255));
        SDL_Texture* StartGameTexture = SDL_CreateTextureFromSurface(MenuRenderer, StartGame);
        SDL_FreeSurface(StartGame);
        SDL_Rect StartGamePos = { 530,50,220,100 };
        DrawTextureMenu(MenuRenderer, StartGameTexture, StartGamePos);

        SDL_Surface* TablRec = IMG_Load("Textures\\Achiv.bmp");
        SDL_SetColorKey(TablRec, SDL_TRUE, SDL_MapRGB(TablRec->format, 255, 255, 255));
        SDL_Texture* TablRecTexture = SDL_CreateTextureFromSurface(MenuRenderer, TablRec);
        SDL_FreeSurface(TablRec);
        SDL_Rect TablRecRect = { 530,160,220,100 };
        DrawTextureMenu(MenuRenderer, TablRecTexture, TablRecRect);

        SDL_Surface* HELP = IMG_Load("Textures\\Help.bmp");
        SDL_SetColorKey(HELP, SDL_TRUE, SDL_MapRGB(HELP->format, 255, 255, 255));
        SDL_Texture* HELP_Texture = SDL_CreateTextureFromSurface(MenuRenderer, HELP);
        SDL_FreeSurface(HELP);
        SDL_Rect HELP_RECT = { 530,270,220,100 };
        DrawTextureMenu(MenuRenderer, HELP_Texture, HELP_RECT);

        SDL_Surface* CLOSE = IMG_Load("Textures\\Close Game.bmp");
        SDL_SetColorKey(CLOSE, SDL_TRUE, SDL_MapRGB(CLOSE->format, 255, 255, 255));
        SDL_Texture* CLOSE_Texture = SDL_CreateTextureFromSurface(MenuRenderer, CLOSE);
        SDL_FreeSurface(CLOSE);
        SDL_Rect CLOSE_RECT = { 530,380,220,100 };
        DrawTextureMenu(MenuRenderer, CLOSE_Texture, CLOSE_RECT);

        SDL_Surface* GOOD = IMG_Load("Textures\\YesACTIVE.bmp");
        SDL_SetColorKey(GOOD, SDL_TRUE, SDL_MapRGB(GOOD->format, 255, 255, 255));
        CloseGoodTexture = SDL_CreateTextureFromSurface(MenuRenderer, GOOD);
        SDL_FreeSurface(GOOD);
        SDL_Rect GOOD_RECT = { 740,340,80,80 };

        SDL_Surface* NO = IMG_Load("Textures\\UP_CLOSE.bmp");
        SDL_SetColorKey(NO, SDL_TRUE, SDL_MapRGB(NO->format, 255, 255, 255));
        NoCloseTexture = SDL_CreateTextureFromSurface(MenuRenderer, NO);
        SDL_FreeSurface(NO);
        SDL_Rect NO_RECT = { 480,355,50,50 };
        //Текстура прозрачности
        SDL_Surface* WHITE = IMG_Load("Textures\\White.bmp");
        SDL_SetColorKey(WHITE, SDL_TRUE, SDL_MapRGB(WHITE->format, 5, 5, 5));
        SDL_Texture* WHITE_Texture = SDL_CreateTextureFromSurface(MenuRenderer, WHITE);
        SDL_FreeSurface(WHITE);
        SDL_Rect WHITE_RECT = { 0,0,1280,720 };
        

        SDL_Surface* SettingSurface = IMG_Load("Textures\\Settings.bmp");
        SDL_SetColorKey(SettingSurface, SDL_TRUE, SDL_MapRGB(SettingSurface->format, 255, 255, 255));
        SDL_Texture* SETTING_Texture = SDL_CreateTextureFromSurface(MenuRenderer, SettingSurface);
        SDL_FreeSurface(SettingSurface);
        SDL_Rect SETTING_RECT = { 1280-70,0,70,70 };
        DrawTextureMenu(MenuRenderer, SETTING_Texture, SETTING_RECT);
        
        
        //ЗВУК

        InitMusic();
        PlayFonMusic();
        Volume(30);
        //ТЕКСТ

        TTF_Init();
        TTF_Font* font = TTF_OpenFont("Text.ttf", 24);
        char text[67] = u8"Вы уверены, что хотите выйти из игры?";
        
        SDL_Texture* CloseTextTexture;
        CloseTextTexture = Get_CloseTextTexture(MenuRenderer, text, font);

        bool quit = false;
        SDL_Event event;
        int x, y;
        bool MenuClose = false;
        bool MainMenu = true;
        int Count = 0;
        while (!quit) {
            SDL_PollEvent(&event);
            SDL_GetMouseState(&x, &y);
            
            
            if (event.type == SDL_QUIT) {
                quit = true;
            }
            if (MainMenu == true) {
               
                if ((event.type == SDL_MOUSEBUTTONDOWN) && (event.button.button == SDL_BUTTON_LEFT)) {
                    if (event.button.button == SDL_PRESSED) {
                        TapTexture(MenuRenderer, x, y);
                    }
                }
                if ((event.type == SDL_MOUSEBUTTONUP) && (event.button.button == SDL_BUTTON_LEFT)) {
                    DrawTextureMenu(MenuRenderer, FON_TEXTURE, FON_RECT);
                    DrawTextureMenu(MenuRenderer, StartGameTexture, StartGamePos);
                    DrawTextureMenu(MenuRenderer, TablRecTexture, TablRecRect);
                    DrawTextureMenu(MenuRenderer, CLOSE_Texture, CLOSE_RECT);
                    DrawTextureMenu(MenuRenderer, HELP_Texture, HELP_RECT);
                    DrawTextureMenu(MenuRenderer, SETTING_Texture, SETTING_RECT);
                }
                if ((event.type == SDL_MOUSEBUTTONDOWN) && (event.button.button == SDL_BUTTON_LEFT)) {
                    if (CloseFunction(event.button.x, event.button.y)) {
                        MenuClose = true;
                        MainMenu = false;
                    }
                }
            }
            if (MenuClose == true) {
                SDL_SetTextureAlphaMod(WHITE_Texture, 4);
                DrawTextureMenu(MenuRenderer, WHITE_Texture, WHITE_RECT);
                DrawTextureMenu(MenuRenderer, CloseGoodTexture, GOOD_RECT);
                DrawTextureMenu(MenuRenderer, NoCloseTexture, NO_RECT);
                DrawCloseTextTexture(MenuRenderer, CloseTextTexture);
                if ((event.type == SDL_MOUSEBUTTONDOWN) && (event.button.button == SDL_BUTTON_LEFT)) {
                    if (OK_CLOSE(event.button.x, event.button.y)) {
                        quit = true;
                    }
                    if (NO_CLOSE(event.button.x, event.button.y)) {
                        MenuClose = false;
                        MainMenu = true;
                    }
                }
            }
      
            SDL_RenderPresent(MenuRenderer);
            SDL_Delay(16);
            
        }
        SDL_DestroyTexture(CLOSE_Texture);
        SDL_DestroyTexture(FON_TEXTURE);
        SDL_DestroyTexture(HELP_Texture);
        SDL_DestroyTexture(CLOSE_Texture);
        SDL_DestroyTexture(StartGameTexture);


        SDL_DestroyRenderer(MenuRenderer);
        SDL_DestroyWindow(window);
       
    }
    return 0;
    
}

