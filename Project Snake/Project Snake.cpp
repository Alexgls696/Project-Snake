#include "StartGame.h"
#include "SDL.h"
#include "SDL_Image.h"
#include "Sound.h"
#include <iostream>
#include "SDL_ttf.h"
#include "Records.h"



SDL_Window* window = NULL;

//ИНИЦИАЛИЗАЦИЯ ТЕКСТУР

SDL_Texture* CloseGoodTexture = NULL;
SDL_Texture* NoCloseTexture = NULL;
SDL_Surface* FON = NULL;
SDL_Texture* FON_TEXTURE = NULL;
SDL_Surface* StartGame = NULL;
SDL_Texture* StartGameTexture = NULL;
SDL_Surface* TablRec = NULL;
SDL_Texture* TablRecTexture = NULL;
SDL_Surface* HELP = NULL;
SDL_Texture* HELP_Texture = NULL;
SDL_Surface* CLOSE = NULL;
SDL_Texture* CLOSE_Texture = NULL;
SDL_Surface* GOOD = NULL;
SDL_Surface* NO = NULL;
SDL_Surface* WHITE = NULL;
SDL_Texture* WHITE_Texture = NULL;
SDL_Surface* SettingSurface = NULL;
SDL_Texture* SETTING_Texture = NULL;
SDL_Surface* SettingBackSurface = NULL;
SDL_Texture* SETTING_Texture_Back = NULL;
SDL_Surface* VolumeSurface = NULL;
SDL_Texture* VolumeTexture = NULL;
SDL_Surface* VolumeONSurface = NULL;
SDL_Texture* VolumeONTexture = NULL;
SDL_Surface* VolumeOFFSurface = NULL;
SDL_Texture* VolumeOFFTexture = NULL;
SDL_Surface* NameSurface = NULL;
SDL_Texture* NameTexture = NULL;
SDL_Surface* Rules1Surface = NULL;
SDL_Surface* Rules2Surface = NULL;
SDL_Texture* Rules1Texture = NULL;
SDL_Texture* Rules2Texture = NULL;
SDL_Surface* rightSurface = NULL;
SDL_Surface* leftSurface = NULL;
SDL_Texture* rightTexture = NULL;
SDL_Texture* leftTexture = NULL;
SDL_Surface* ResetButtonSurface = NULL;
SDL_Texture* ResetButtonTexture = NULL;
SDL_Surface* TablicaRecSurface = NULL;
SDL_Texture* TablicaRecTexture = NULL;
SDL_Texture* RecordsScoreTexture = NULL;
SDL_Texture* TextResetTexture = NULL;

//РАСПОЛОЖЕНИЕ ТЕКСТУР

SDL_Rect FON_RECT = { 0,0,1280,720 }; //ФОН
SDL_Rect StartGamePos = { 530,150,220,100 };//НАЧАТЬ ИГРУ РАСП
SDL_Rect TablRecRect = { 530,260,220,100 };//ТАБЛИЦА РЕКОРДОВ РАСПОЛОЖЕНИЕ
SDL_Rect HELP_RECT = { 530,370,220,100 };//СПРАВКА
SDL_Rect CLOSE_RECT = { 530,480,220,100 };//МЕНЮ ЗАКРЫТИЯ
SDL_Rect GOOD_RECT = { 740,340,80,80 }; //ЗАКРЫТИЕ
SDL_Rect NO_RECT = { 480,355,50,50 };//ОТМЕНА закрытия
SDL_Rect WHITE_RECT = { 0,0,1280,720 }; //БЕЛЕНИЕ ФОНА НА ВЕСЬ ЭКРАН
SDL_Rect SETTING_RECT = { 1280 - 70,0,70,70 }; //РАСПОЛОЖЕНИЕ КНОПКИ НАСТРОЕК
SDL_Rect SETTING_RECT_Back = { 330,110,600,600 }; // ЗАДНИЙ ФОН МЕНЮ НАСТРОЕК
SDL_Rect VolumeON_Rect = { 720,290,40,40 };
SDL_Rect VolumeOFF_Rect = { 475,290,40,40 };
SDL_Rect NameRect = { 330,0,600,150 }; // ПОЗИЦИЯ НАЗВАНИЯ
SDL_Rect ResetButtonRect = { 470,420,300,60 };
SDL_Rect FULLSCREEN_RECT = { 720,350,30,30 };

struct RecMenu {
    string Game_mode;
    int Score;
    int Score2;
    int Score3;
};
RecMenu RecordsMenu[3];

bool init() //ПРОВЕРКА ЗАПУСКА ОКНА И SDL
{
    bool GREAT = true;
    if (SDL_Init((SDL_INIT_EVERYTHING) < 0)) {
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



bool StartGameButton(int x, int y) {
    if ((x > 530 && x < 740) && (y > 150 && y < 250)) 
        return true;
    return false;
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
    if ((x > 530 && x < 740) && (y > 480 && y < 580)) {
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
    if ((x >= 720 && x <= 750) && (y >= 350 && y <= 380))
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

//ЗАГРУЖАЕТ ТЕКСТУРЫ ГЛАВНОГО МЕНЮ
void LoadTexturesMainMenu(SDL_Renderer* MenuRenderer)
{
    NameSurface = IMG_Load("Textures\\NAME.bmp");
    SDL_SetColorKey(NameSurface, SDL_TRUE, SDL_MapRGB(NameSurface->format, 255, 255, 255));
    NameTexture = SDL_CreateTextureFromSurface(MenuRenderer, NameSurface);
    SDL_FreeSurface(NameSurface);

    FON = IMG_Load("Textures\\FON_MENU.bmp");
    SDL_SetColorKey(FON, SDL_TRUE, SDL_MapRGB(FON->format, 255, 255, 255));
    FON_TEXTURE = SDL_CreateTextureFromSurface(MenuRenderer, FON);
    SDL_FreeSurface(FON);

    StartGame = IMG_Load("Textures\\Startgame.bmp");
    SDL_SetColorKey(StartGame, SDL_TRUE, SDL_MapRGB(StartGame->format, 255, 255, 255));
    StartGameTexture = SDL_CreateTextureFromSurface(MenuRenderer, StartGame);
    SDL_FreeSurface(StartGame);

    TablRec = IMG_Load("Textures\\Achiv.bmp");
    SDL_SetColorKey(TablRec, SDL_TRUE, SDL_MapRGB(TablRec->format, 255, 255, 255));
    TablRecTexture = SDL_CreateTextureFromSurface(MenuRenderer, TablRec);
    SDL_FreeSurface(TablRec);

    HELP = IMG_Load("Textures\\Help.bmp");
    SDL_SetColorKey(HELP, SDL_TRUE, SDL_MapRGB(HELP->format, 255, 255, 255));
    HELP_Texture = SDL_CreateTextureFromSurface(MenuRenderer, HELP);
    SDL_FreeSurface(HELP);

    CLOSE = IMG_Load("Textures\\Close Game.bmp");
    SDL_SetColorKey(CLOSE, SDL_TRUE, SDL_MapRGB(CLOSE->format, 255, 255, 255));
    CLOSE_Texture = SDL_CreateTextureFromSurface(MenuRenderer, CLOSE);
    SDL_FreeSurface(CLOSE);

    GOOD = IMG_Load("Textures\\Yes.bmp");
    SDL_SetColorKey(GOOD, SDL_TRUE, SDL_MapRGB(GOOD->format, 255, 255, 255));
    CloseGoodTexture = SDL_CreateTextureFromSurface(MenuRenderer, GOOD);
    SDL_FreeSurface(GOOD);

    NO = IMG_Load("Textures\\UP_CLOSE.bmp");
    SDL_SetColorKey(NO, SDL_TRUE, SDL_MapRGB(NO->format, 255, 255, 255));
    NoCloseTexture = SDL_CreateTextureFromSurface(MenuRenderer, NO);
    SDL_FreeSurface(NO);

    //Текстура прозрачности (Беление экрана)
    WHITE = IMG_Load("Textures\\White.bmp");
    SDL_SetColorKey(WHITE, SDL_TRUE, SDL_MapRGB(WHITE->format, 5, 5, 5));
    WHITE_Texture = SDL_CreateTextureFromSurface(MenuRenderer, WHITE);
    SDL_FreeSurface(WHITE);

    SettingSurface = IMG_Load("Textures\\Settings.bmp");
    SDL_SetColorKey(SettingSurface, SDL_TRUE, SDL_MapRGB(SettingSurface->format, 255, 255, 255));
    SETTING_Texture = SDL_CreateTextureFromSurface(MenuRenderer, SettingSurface);
    SDL_FreeSurface(SettingSurface);

    SettingBackSurface = IMG_Load("Textures\\SettingsBack.bmp");
    SDL_SetColorKey(SettingBackSurface, SDL_TRUE, SDL_MapRGB(SettingBackSurface->format, 255, 255, 255));
    SETTING_Texture_Back = SDL_CreateTextureFromSurface(MenuRenderer, SettingBackSurface);
    SDL_FreeSurface(SettingBackSurface);

    VolumeSurface = IMG_Load("Textures\\Volume.bmp");
    SDL_SetColorKey(VolumeSurface, SDL_TRUE, SDL_MapRGB(VolumeSurface->format, 255, 255, 255));
    VolumeTexture = SDL_CreateTextureFromSurface(MenuRenderer, VolumeSurface);
    SDL_FreeSurface(VolumeSurface);

    VolumeONSurface = IMG_Load("Textures\\SoundON.bmp");
    SDL_SetColorKey(VolumeONSurface, SDL_TRUE, SDL_MapRGB(VolumeONSurface->format, 255, 255, 255));
    VolumeONTexture = SDL_CreateTextureFromSurface(MenuRenderer, VolumeONSurface);
    SDL_FreeSurface(VolumeONSurface);

    VolumeOFFSurface = IMG_Load("Textures\\SoundOFF.bmp");
    SDL_SetColorKey(VolumeOFFSurface, SDL_TRUE, SDL_MapRGB(VolumeOFFSurface->format, 255, 255, 255));
    VolumeOFFTexture = SDL_CreateTextureFromSurface(MenuRenderer, VolumeOFFSurface);
    SDL_FreeSurface(VolumeOFFSurface);

    Rules1Surface = IMG_Load("Textures\\Rules 1.bmp");
    SDL_SetColorKey(Rules1Surface, SDL_TRUE, SDL_MapRGB(Rules1Surface->format, 25, 25, 25));
    Rules1Texture = SDL_CreateTextureFromSurface(MenuRenderer, Rules1Surface);
    SDL_FreeSurface(Rules1Surface);

    Rules2Surface = IMG_Load("Textures\\Rules 2.bmp");
    SDL_SetColorKey(Rules2Surface, SDL_TRUE, SDL_MapRGB(Rules2Surface->format, 25, 25, 25));
    Rules2Texture = SDL_CreateTextureFromSurface(MenuRenderer, Rules2Surface);
    SDL_FreeSurface(Rules2Surface);

    leftSurface = IMG_Load("Textures\\LEFT.bmp");
    SDL_SetColorKey(leftSurface, SDL_TRUE, SDL_MapRGB(leftSurface->format, 255, 255, 255));
    leftTexture = SDL_CreateTextureFromSurface(MenuRenderer, leftSurface);
    SDL_FreeSurface(leftSurface);

    rightSurface = IMG_Load("Textures\\RIGHT.bmp");
    SDL_SetColorKey(rightSurface, SDL_TRUE, SDL_MapRGB(rightSurface->format, 255, 255, 255));
    rightTexture = SDL_CreateTextureFromSurface(MenuRenderer, rightSurface);
    SDL_FreeSurface(rightSurface);

    ResetButtonSurface = IMG_Load("Textures\\RESET_RECORDS.bmp");
    SDL_SetColorKey(ResetButtonSurface, SDL_TRUE, SDL_MapRGB(ResetButtonSurface->format, 255, 255, 255));
    ResetButtonTexture = SDL_CreateTextureFromSurface(MenuRenderer, ResetButtonSurface);
    SDL_FreeSurface(ResetButtonSurface);

    TablicaRecSurface = IMG_Load("Textures\\TABL.bmp");
    SDL_SetColorKey(TablicaRecSurface, SDL_TRUE, SDL_MapRGB(TablicaRecSurface->format, 25, 255, 255));
    TablicaRecTexture = SDL_CreateTextureFromSurface(MenuRenderer, TablicaRecSurface);
    SDL_FreeSurface(TablicaRecSurface);
}


bool HelpButton(int x, int y) {
    if (y >= 370 && y <= 470 && x >= 530 && x <= 720)
        return true;
    return false;
}
bool TablicaButton(int x, int y) {
    if(y >= 260&&y<=360&&x>=530&&x<=720)
        return true;
    return false;
}
bool ResetRecordsButton(int x, int y) {
    if (x >= 470 && x <= 770 && y >= 420 && y <= 480) 
        return true;
    return false;
}

bool OnceRecMenu = true;
char text[5];
char text2[5];
char text3[5];
SDL_Rect rect = { 0,0,1280,720 };
SDL_Rect CloseRect = { 1230,0,50,50 };
SDL_Rect rectScore = { 460,260,70,100 };

void TablicaRec(SDL_Renderer* renderer, SDL_Event event,bool&MainMenu,bool&TablicaRecordov,TTF_Font *font) {
    setlocale(LC_ALL, "rus");
    if (OnceRecMenu == true) {
        ifstream file("Records.txt");
        if (file) {
            for (int i = 0; i < 3;i++) 
            { file >> RecordsMenu[i].Game_mode >> RecordsMenu[i].Score >> RecordsMenu[i].Score2 >> RecordsMenu[i].Score3; }
            OnceRecMenu = false;
            file.close();
        }
        else {
            cout << "Файл рекордов не был открыт!" << endl;
            MainMenu = true;
            TablicaRecordov = false;
            return;
        }
        SDL_RenderCopy(renderer, TablicaRecTexture, NULL, &rect);
        for (int i = 0; i < 3; i++) {
            _itoa_s(RecordsMenu[i].Score, text, 10);
            RecordsScoreTexture = Get_TextTexture(renderer, text, font);
            SDL_RenderCopy(renderer, RecordsScoreTexture, NULL, &rectScore);

            _itoa_s(RecordsMenu[i].Score2, text2, 10);
            RecordsScoreTexture = Get_TextTexture(renderer, text2, font);
            rectScore.y = 370;
            SDL_RenderCopy(renderer, RecordsScoreTexture, NULL, &rectScore);

            _itoa_s(RecordsMenu[i].Score3, text3, 10);
            rectScore.y = 480;
            RecordsScoreTexture = Get_TextTexture(renderer, text3, font);
            SDL_RenderCopy(renderer, RecordsScoreTexture, NULL, &rectScore);
            rectScore.y = 260;
            rectScore.x += 280;
        }
    }
    
    int x, y;
    rectScore = { 460,260,70,100 };
    SDL_GetMouseState(&x, &y);
    if(event.type=SDL_MOUSEBUTTONDOWN&&event.button.button == SDL_BUTTON_LEFT)
        if (x >= 1230 && x <= 1280 && y >= 0 && y <= 50) {
            MainMenu = true;
            TablicaRecordov = false;
            OnceRecMenu = true;
            TapSound();
        }
    SDL_RenderCopy(renderer, NoCloseTexture, NULL, &CloseRect);
}

bool HelpList1 = true;
bool HelpList2 = false;
SDL_Rect RulesRect = { 0,0,1280,720 };
SDL_Rect RightRulesRect = { 1230,310,50,50 };
SDL_Rect LeftRulesRect = { 1230,370,50,50 };
void Help(SDL_Renderer* renderer, SDL_Event event,bool&MainMenu,bool&Rules)//Правила игры
{
    int x, y;
    SDL_GetMouseState(&x, &y);
    if (HelpList1) {
        SDL_RenderCopy(renderer, Rules1Texture, NULL, &RulesRect);
        SDL_RenderCopy(renderer, rightTexture, NULL, &RightRulesRect);
        if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
            if (x >= 1230 && x <= 1280 && y >= 310 && y <= 360) {
                TapSound();
                HelpList1 = false;
                HelpList2 = true;
            }
    }
    if (HelpList2) {
        SDL_RenderCopy(renderer, Rules2Texture, NULL, &RulesRect);
        SDL_RenderCopy(renderer, leftTexture, NULL, &LeftRulesRect);
        if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
            if (x >= 1230 && x <= 1280 && y >= 370 && y <= 420) {
                TapSound();
                HelpList1 = true;
                HelpList2 = false;
            }
    }
    if(event.type == SDL_MOUSEBUTTONDOWN&&event.button.button==SDL_BUTTON_LEFT)
        if (x >= 1230 && x <= 1280 && y >= 0 && y <= 50) {
            MainMenu = true;
            Rules = false;
            TapSound();
        }
    SDL_RenderCopy(renderer, NoCloseTexture, NULL, &CloseRect);
}

void ResetRecords(SDL_Renderer* MenuRenderer, SDL_Event event, bool& ResetChoose, bool& SettingMenu) {
    ResetRecords(MenuRenderer, event, ResetChoose, SettingMenu);
    SDL_SetTextureAlphaMod(WHITE_Texture, 5);             //Полупрозрачность для меню
    DrawTextureMenu(MenuRenderer, WHITE_Texture, WHITE_RECT);
    DrawTextureMenu(MenuRenderer, CloseGoodTexture, GOOD_RECT);
    DrawTextureMenu(MenuRenderer, NoCloseTexture, NO_RECT);
    DrawCloseTextTexture(MenuRenderer, TextResetTexture);
    if ((event.type == SDL_MOUSEBUTTONDOWN) && (event.button.button == SDL_BUTTON_LEFT)) {
        if (OK_CLOSE(event.button.x, event.button.y)) {
            TapSound();
            ClearRecords();
            ResetChoose = false;
            SettingMenu = true;
        }
        if (NO_CLOSE(event.button.x, event.button.y)) {
            TapSound();
            ResetChoose = false;
            SettingMenu = true;
        }
    }
}
int main(int argc, char** argv)
{
    SDL_DisplayMode displayMode;
    int request = SDL_GetDesktopDisplayMode(0, &displayMode);
    if (!(init())) {
        std::cout << "Не удалось запустить программу" << std::endl;
    }
    else {
        std::cout << SDL_GetNumRenderDrivers() << std::endl;
        SDL_Renderer* MenuRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED || SDL_RENDERER_PRESENTVSYNC);//acelerated - аппаратное ускорение, верт синхр.

    
        //ЗВУК

        InitMusic(); 
        LoadSound(); 
        PlayFonMusic(); 
        LoadTexturesMainMenu(MenuRenderer); 
        ReadRecords();

        TTF_Init();
        TTF_Font* font = TTF_OpenFont("Text.ttf", 24); 
        TTF_Font* SettingFont = TTF_OpenFont("Text.ttf", 56);
        TTF_Font* SettingMenuFont = TTF_OpenFont("Text.ttf", 36);
       

        char text[] = u8"Вы уверены, что хотите выйти из игры?";
        char FullscreanText[] = u8"Полноэкранный режим";
        char SettingsMenu[] = u8"НАСТРОЙКИ";
        char ResetRec[] = u8"Вы уверены, что хотите спросить рекорды?";

       
        TextResetTexture = Get_TextTexture(MenuRenderer, ResetRec, font);
        SDL_Texture* CloseTextTexture;
        CloseTextTexture = Get_TextTexture(MenuRenderer, text, font);
        SDL_Texture* SettingMenuTexture = Get_TextTexture(MenuRenderer, SettingsMenu, SettingMenuFont);
        SDL_Texture* FullscreenTexture = Get_TextTexture(MenuRenderer, FullscreanText, SettingFont);


        bool quit = false;

        int x, y;
        int X_Volume = 700;
        bool MenuClose = false;
        bool MainMenu = true;
        bool SettingMenu = false;
        bool FULLSCREEN_ON = false;
        bool GameStartDiff = false;
        bool LoadDiffTexture = true;
        bool HelpMenu = false;
        bool TablicaRecordov = false;
        bool ResetChoose = false;
        int Count = 0;

        clock_t ESCAPE = clock();//ТАЙМЕР нажатия ESCAPE
        SDL_Event event;
        int i = 0;
        while (!quit) {
            SDL_PollEvent(&event);
            SDL_GetMouseState(&x, &y);//ПОЛУЧЕНИЕ КООРДИНАТ МЫШИ В ЦИКЛЕ

            if (event.type == SDL_QUIT) //Нажание на крестик для выхода
            {
                quit = true;
            }

            if (MainMenu == true) {
                DrawTextureMenu(MenuRenderer, FON_TEXTURE, FON_RECT);
                DrawTextureMenu(MenuRenderer, StartGameTexture, StartGamePos);
                DrawTextureMenu(MenuRenderer, TablRecTexture, TablRecRect);
                DrawTextureMenu(MenuRenderer, HELP_Texture, HELP_RECT);
                DrawTextureMenu(MenuRenderer, CLOSE_Texture, CLOSE_RECT);
                DrawTextureMenu(MenuRenderer, NameTexture, NameRect);

                if ((event.type == SDL_MOUSEBUTTONDOWN) && (event.button.button == SDL_BUTTON_LEFT)) {
                    if (StartGameButton(event.button.x, event.button.y)) {
                        MainMenu = false;
                        GameStartDiff = true;
                        TapSound();
                        continue; // ЧТОБЫ НЕ ПОВТОРЯЛОСЬ НАЖАТИЕ В ДРУГОМ МЕНЮ
                    }
                    if (CloseFunction(event.button.x, event.button.y)) {
                        MenuClose = true;
                        MainMenu = false;
                        TapSound();
                    }
                    if (SettingMenuOpen(event.button.x, event.button.y)) {
                        MainMenu = false;
                        SettingMenu = true;
                        TapSound();
                    }
                    if (HelpButton(event.button.x, event.button.y)) {
                        MainMenu = false;
                        HelpMenu = true;
                        TapSound();
                    }
                    if (TablicaButton(event.button.x, event.button.y)) {
                        MainMenu = false;
                        TablicaRecordov = true;
                        TapSound();
                    }
                }
                //ВРАЩЕНИЕ ШЕСТЕРЕНКИ НАСТРОЕК - НАСТРОЙКИ
           
                    i += 30;
                    SDL_RenderCopyEx(MenuRenderer, SETTING_Texture, NULL, &SETTING_RECT, i * (3.14 / 180), 0, SDL_FLIP_NONE); //ОТОБРАЖЕНИЕ ВРАЩЕНИЯ
                
                if ((event.key.keysym.sym == SDLK_ESCAPE)) {
                    MenuClose = true;
                    MainMenu = false;
                }
            }
            if (MenuClose == true) //МЕНЮ ЗАВЕРШЕНИЯ
            {
                SDL_SetTextureAlphaMod(WHITE_Texture, 8);             //Полупрозрачность для меню
                DrawTextureMenu(MenuRenderer, WHITE_Texture, WHITE_RECT);
                DrawTextureMenu(MenuRenderer, CloseGoodTexture, GOOD_RECT);
                DrawTextureMenu(MenuRenderer, NoCloseTexture, NO_RECT);
                DrawCloseTextTexture(MenuRenderer, CloseTextTexture); // отрисовка текста (не менял функцию, такая же, как и при выходе)
                if ((event.type == SDL_MOUSEBUTTONDOWN) && (event.button.button == SDL_BUTTON_LEFT)) {
                    if (OK_CLOSE(event.button.x, event.button.y)) {
                        TapSound();
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

                SDL_SetTextureAlphaMod(WHITE_Texture, 4); //ПОЛУПРОЗРАЧНОСТЬ
                DrawTextureMenu(MenuRenderer, WHITE_Texture, WHITE_RECT);
                DrawTextureMenu(MenuRenderer, SETTING_Texture_Back, SETTING_RECT_Back);
                SDL_RenderCopy(MenuRenderer, ResetButtonTexture, NULL, &ResetButtonRect);

                SDL_Rect VolumeRect = { X_Volume,300,20,20 };

                SDL_SetRenderDrawColor(MenuRenderer, 0, 0, 0, 0);
                for (int i = 0; i < 3; i++) {
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
                    if (SettingsMenuClose(event.button.x, event.button.y)) {
                        MainMenu = true;
                        SettingMenu = false;
                        TapSound();
                    }
                    if (ResetRecordsButton(event.button.x, event.button.y)) {
                        ResetChoose = true;
                        SettingMenu = false;
                        TapSound();
                    }
                    
                }
            
                if (FULLSCREEN_ON == false) {
                    DrawTextureMenu(MenuRenderer, NoCloseTexture, FULLSCREEN_RECT); // FULLSCREEN_TEXTURE
                    if (FullScreenMode(x, y) && (event.type == SDL_MOUSEBUTTONDOWN) && (event.button.button == SDL_BUTTON_LEFT)) {
                        SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);// SDL_WINDOW_FULLSCREEN);
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
            if (ResetChoose == true) //СБРОС РЕКОРДОВ
            {
               
            }
            if (HelpMenu == true) {
                Help(MenuRenderer, event,MainMenu,HelpMenu);
            }
            if (TablicaRecordov == true) {
                TablicaRec(MenuRenderer, event,MainMenu,TablicaRecordov,SettingFont);
            }
            if (GameStartDiff == true) //ВЫБОР РЕЖИМА ИГРЫ //ВЫБОР СЛОЖНОСТИ
            {
                MenuDiff(MenuRenderer, GameStartDiff, MainMenu, LoadDiffTexture, event, window);
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

