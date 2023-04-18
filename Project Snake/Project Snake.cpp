#include "SDL.h"
#include "SDL_Image.h"
#include "Sound.h"
#include <iostream>
#include "SDL_ttf.h"


SDL_Window* window = NULL;
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
    SDL_RenderCopy(MenuRenderer, texture, NULL, &Rect);
}


void ActiveCLOSETexture(SDL_Renderer* MenuRenderer) {
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

void DrawSettingsMenuText(SDL_Renderer*& renderer, SDL_Texture* texture) {
    SDL_Rect Rect = { 470,170,300,70 };
    SDL_RenderCopy(renderer, texture, NULL, &Rect);
}
void DrawFullsreenSettingsMenuText(SDL_Renderer*& renderer, SDL_Texture* texture) {
    SDL_Rect rect = { 500,350,200,30 };
    SDL_RenderCopy(renderer, texture, NULL, &rect);
}
void DrawCloseTextTexture(SDL_Renderer*& renderer, SDL_Texture* texture) {
    SDL_Rect Rect = { 330,200,600,50 };
    SDL_RenderCopy(renderer, texture, NULL, &Rect);
}

SDL_Texture* Get_TextTexture(SDL_Renderer*& renderer, char* text, TTF_Font* font) {
    SDL_Surface* TextSurface = NULL;
    SDL_Color fore_color = { 240,100,100 };
    SDL_Color back_color = { 255,20,20,255 };
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
bool CloseFunction(int x, int y) {
    if ((x > 530 && x < 740) && (y > 380 && y < 480)) {
        return true;
    }
    else
        return false;
}
bool SettingMenuOpen(int x, int y) {
    if ((x >= 1210 && x <= 1280) && (y >= 0 && y <= 70))
        return true;
    return false;
}
bool SettingsMenuClose(int x, int y) {
    if ((x >= 860 && x <= 900) && (y >= 140 && y <= 180))
        return true;
    return false;
}
bool SoundOFFTexture(int& x, int y, int& Value) {
    if ((x >= 475 && x < 515) && (y >= 290 && y <= 330)) {
        Value = 510;
        return true;
    }
    return false;
}
bool SoundONTexture(int& x, int y, int& Value) {
    if ((x >= 720 && x < 760) && (y >= 290 && y <= 330)) {
        Value = 700;
        return true;
    }
    return false;
}
bool FullScreenMode(int x, int y) {
    if ((x >= 720 && x <= 750) && (y >= 353 && y <= 383))
        return true;
    return false;
}
void EditVolume(SDL_Renderer* renderer, SDL_Event event, SDL_Rect& Rect, SDL_Texture* texture, int& x) {
    int y = 300;
    int volume;
    double volumeRez;
    if ((event.button.x >= 520 && event.button.x <= 710) && (event.button.button == SDL_PRESSED)) {
        Rect = { event.button.x - 10,300,20,20 };
        SDL_RenderCopy(renderer, texture, NULL, &Rect);
        x = event.button.x - 10;
        volume = event.button.x - 520;
        volumeRez = (volume / 190.0) * 100;
        Volume(int(volumeRez));
    }

}


int main(int argc, char** argv)
{
    //SDL_DisplayMode displayMode;
    //int request = SDL_GetDesktopDisplayMode(0, &displayMode);
    if (!(init())) {
        std::cout << "Не удалось запустить программу" << std::endl;
    }
    else {
        SDL_Renderer* MenuRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED || SDL_RENDERER_PRESENTVSYNC);//acelerated - аппаратное ускорение, верт синхр.

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

        //Текстура прозрачности (Беление экрана)
        SDL_Surface* WHITE = IMG_Load("Textures\\White.bmp");
        SDL_SetColorKey(WHITE, SDL_TRUE, SDL_MapRGB(WHITE->format, 5, 5, 5));
        SDL_Texture* WHITE_Texture = SDL_CreateTextureFromSurface(MenuRenderer, WHITE);
        SDL_FreeSurface(WHITE);
        SDL_Rect WHITE_RECT = { 0,0,1280,720 };


        SDL_Surface* SettingSurface = IMG_Load("Textures\\Settings.bmp");
        SDL_SetColorKey(SettingSurface, SDL_TRUE, SDL_MapRGB(SettingSurface->format, 255, 255, 255));
        SDL_Texture* SETTING_Texture = SDL_CreateTextureFromSurface(MenuRenderer, SettingSurface);
        SDL_FreeSurface(SettingSurface);
        SDL_Rect SETTING_RECT = { 1280 - 70,0,70,70 };
        DrawTextureMenu(MenuRenderer, SETTING_Texture, SETTING_RECT);

        SDL_Surface* SettingBackSurface = IMG_Load("Textures\\SettingsBack.bmp");
        SDL_SetColorKey(SettingBackSurface, SDL_TRUE, SDL_MapRGB(SettingBackSurface->format, 255, 255, 255));
        SDL_Texture* SETTING_Texture_Back = SDL_CreateTextureFromSurface(MenuRenderer, SettingBackSurface);
        SDL_FreeSurface(SettingBackSurface);
        SDL_Rect SETTING_RECT_Back = { 330,110,600,600 };

        SDL_Surface* VolumeSurface = IMG_Load("Textures\\Volume.bmp");
        SDL_SetColorKey(VolumeSurface, SDL_TRUE, SDL_MapRGB(VolumeSurface->format, 255, 255, 255));
        SDL_Texture* VolumeTexture = SDL_CreateTextureFromSurface(MenuRenderer, VolumeSurface);
        SDL_FreeSurface(VolumeSurface);

        SDL_Surface* VolumeONSurface = IMG_Load("Textures\\SoundON.bmp");
        SDL_SetColorKey(VolumeONSurface, SDL_TRUE, SDL_MapRGB(VolumeONSurface->format, 255, 255, 255));
        SDL_Texture* VolumeONTexture = SDL_CreateTextureFromSurface(MenuRenderer, VolumeONSurface);
        SDL_FreeSurface(VolumeONSurface);
        SDL_Rect VolumeON_Rect = { 720,290,40,40 };

        SDL_Surface* VolumeOFFSurface = IMG_Load("Textures\\SoundOFF.bmp");
        SDL_SetColorKey(VolumeOFFSurface, SDL_TRUE, SDL_MapRGB(VolumeOFFSurface->format, 255, 255, 255));
        SDL_Texture* VolumeOFFTexture = SDL_CreateTextureFromSurface(MenuRenderer, VolumeOFFSurface);
        SDL_FreeSurface(VolumeOFFSurface);
        SDL_Rect VolumeOFF_Rect = { 475,290,40,40 };

        //FULLSCREENRECT
        SDL_Rect FULLSCREEN_RECT = { 720,353,30,30 };




        //ЗВУК

        InitMusic();
        PlayFonMusic();
        Volume(100);
        //ТЕКСТ

        TTF_Init();
        TTF_Font* font = TTF_OpenFont("Text.ttf", 24);
        TTF_Font* SettingFont = TTF_OpenFont("Text.ttf", 56);
        TTF_Font* SettingMenuFont = TTF_OpenFont("Text.ttf", 36);

        char text[] = u8"Вы уверены, что хотите выйти из игры?";
        char FullscreanText[] = u8"Полноэкранный режим";
        char SettingsMenu[] = u8"НАСТРОЙКИ";

        SDL_Texture* CloseTextTexture;
        CloseTextTexture = Get_TextTexture(MenuRenderer, text, font);
        SDL_Texture* SettingMenuTexture = Get_TextTexture(MenuRenderer, SettingsMenu, SettingMenuFont);
        SDL_Texture* FullscreenTexture = Get_TextTexture(MenuRenderer, FullscreanText, SettingFont);


        bool quit = false;
        SDL_Event event;
        int x, y;
        int X_Volume = 700;
        bool MenuClose = false;
        bool MainMenu = true;
        bool SettingMenu = false;
        bool FULLSCREEN_ON = false;
        int Count = 0;
        while (!quit) {
            SDL_PollEvent(&event);
            SDL_GetMouseState(&x, &y);

            if (event.type == SDL_QUIT) {
                quit = true;
            }
            if (MainMenu == true) {

                if ((event.type == SDL_MOUSEBUTTONDOWN) && (event.button.button == SDL_BUTTON_LEFT)) {
                    TapTexture(MenuRenderer, x, y);

                    if (CloseFunction(event.button.x, event.button.y)) {
                        MenuClose = true;
                        MainMenu = false;
                    }
                    if (SettingMenuOpen(event.button.x, event.button.y)) {
                        MainMenu = false;
                        SettingMenu = true;
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

            }
            if (MenuClose == true) {
                SDL_SetTextureAlphaMod(WHITE_Texture, 4);
                DrawTextureMenu(MenuRenderer, WHITE_Texture, WHITE_RECT);
                DrawTextureMenu(MenuRenderer, CloseGoodTexture, GOOD_RECT);
                DrawTextureMenu(MenuRenderer, NoCloseTexture, NO_RECT);
                DrawCloseTextTexture(MenuRenderer, CloseTextTexture);
                if ((event.type == SDL_MOUSEBUTTONDOWN) && (event.button.button == SDL_BUTTON_LEFT)) {
                    if (OK_CLOSE(event.button.x, event.button.y)) {
                        TapSound();
                        SDL_Delay(1000);
                        quit = true;
                    }
                    if (NO_CLOSE(event.button.x, event.button.y)) {
                        MenuClose = false;
                        MainMenu = true;
                        TapSound();
                    }
                }
            }
            if (SettingMenu == true) {

                SDL_SetTextureAlphaMod(WHITE_Texture, 4);
                DrawTextureMenu(MenuRenderer, WHITE_Texture, WHITE_RECT);
                DrawTextureMenu(MenuRenderer, SETTING_Texture_Back, SETTING_RECT_Back);

                SDL_Rect VolumeRect = { X_Volume,300,20,20 };

                SDL_SetRenderDrawColor(MenuRenderer, 0, 0, 0, 0);
                for (int i = 0; i < 3;i++) {
                    SDL_RenderDrawLine(MenuRenderer, 520, 308 + i, 710, 308 + i);
                }
                DrawSettingsMenuText(MenuRenderer, SettingMenuTexture);
                DrawFullsreenSettingsMenuText(MenuRenderer, FullscreenTexture);
                SDL_Rect CloseRect = { 860,140,40,40 };
                DrawTextureMenu(MenuRenderer, NoCloseTexture, CloseRect);
                DrawTextureMenu(MenuRenderer, VolumeTexture, VolumeRect);
                DrawTextureMenu(MenuRenderer, VolumeONTexture, VolumeON_Rect);
                DrawTextureMenu(MenuRenderer, VolumeOFFTexture, VolumeOFF_Rect);

                if ((X_Volume >= X_Volume && X_Volume <= X_Volume + 20) && (y >= 300 && y <= 320)) {
                    EditVolume(MenuRenderer, event, VolumeRect, VolumeTexture, X_Volume);
                }
                if ((event.type == SDL_MOUSEBUTTONDOWN) && (event.button.button == SDL_BUTTON_LEFT)) {
                    if (SoundOFFTexture(x, y, X_Volume)) {
                        Volume(0);
                    }
                    if (SoundONTexture(x, y, X_Volume)) {
                        Volume(100);
                    }
                }
                //}
                if (SettingsMenuClose(event.button.x, event.button.y) && (event.type == SDL_MOUSEBUTTONDOWN) && (event.button.button == SDL_BUTTON_LEFT)) {
                    MainMenu = true;
                    SettingMenu = false;
                    TapSound();
                }
                if (FULLSCREEN_ON == false) {
                    DrawTextureMenu(MenuRenderer, NoCloseTexture, FULLSCREEN_RECT); // FULLSCREEN_TEXTURE
                    if (FullScreenMode(x, y) && (event.type == SDL_MOUSEBUTTONDOWN) && (event.button.button == SDL_BUTTON_LEFT)) {
                        SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
                        FULLSCREEN_ON = true;
                    }
                }
                else {
                    DrawTextureMenu(MenuRenderer, CloseGoodTexture, FULLSCREEN_RECT);
                    if (FullScreenMode(x, y) && (event.type == SDL_MOUSEBUTTONDOWN) && (event.button.button == SDL_BUTTON_LEFT)) {
                        SDL_SetWindowFullscreen(window, 0);
                        SDL_SetWindowSize(window, 1280, 720);
                        FULLSCREEN_ON = false;
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

