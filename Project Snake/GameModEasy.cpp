#include "GameMode.h"
#include "GameSetting.h"
#include "GameValues.h"
#include "Records.h"

//ЗАГРУЗКА ТЕКСТУР----------------------------------------------------------------


const int WIDTH_EASY1 = 280; // ИГРОВОЕ ПОЛЕ
const int WIDTH_EASY2 = 960;
const int HEIGHT_EASY1 = 0;
const int HEIGHT_EASY2 = 680;



enum Direction {
	START = 0, LEFT, RIGHT, UP, DOWN
};
Direction Dir;

ModeEasy EasyStr;

SDL_Texture* Get_TextTextureEasy(SDL_Renderer*& renderer, char* text, TTF_Font* font) {
	SDL_Surface* TextSurface = NULL;
	SDL_Color fore_color = { 240,100,100 };
	TextSurface = TTF_RenderUTF8_Solid(font, text, fore_color);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, TextSurface);
	SDL_FreeSurface(TextSurface);
	return texture;
}

SDL_Texture* Get_SnakeLenTexture(SDL_Renderer* renderer, char* text, TTF_Font* font) {
	SDL_Surface* Surface = NULL;
	SDL_Color fore_color = { 240,100,100 };
	Surface = TTF_RenderUTF8_Solid(font, text, fore_color);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, Surface);
	SDL_FreeSurface(Surface);
	return texture;
}

void LoadTexturesEasy(SDL_Renderer* renderer) {

	EasyStr.SNAKE_EASY_SURFACE = IMG_Load("Textures\\SnakeTextureEasy.bmp");
	SDL_SetColorKey(EasyStr.SNAKE_EASY_SURFACE, SDL_TRUE, SDL_MapRGB(EasyStr.SNAKE_EASY_SURFACE->format, 255, 255, 255));
	EasyStr.SNAKE_EASY_TEXTURE = SDL_CreateTextureFromSurface(renderer, EasyStr.SNAKE_EASY_SURFACE);
	SDL_FreeSurface(EasyStr.SNAKE_EASY_SURFACE);

	EasyStr.AppleSurface = IMG_Load("Textures\\apple.bmp");
	SDL_SetColorKey(EasyStr.AppleSurface, SDL_TRUE, SDL_MapRGB(EasyStr.AppleSurface->format, 255, 255, 255));
	EasyStr.AppleTexture = SDL_CreateTextureFromSurface(renderer, EasyStr.AppleSurface);
	SDL_FreeSurface(EasyStr.AppleSurface);

	EasyStr.BananaSurface = IMG_Load("Textures\\BANAN.bmp");
	SDL_SetColorKey(EasyStr.BananaSurface, SDL_TRUE, SDL_MapRGB(EasyStr.BananaSurface->format, 255, 255, 255));
	EasyStr.BananaTexture = SDL_CreateTextureFromSurface(renderer, EasyStr.BananaSurface);
	SDL_FreeSurface(EasyStr.BananaSurface);

	EasyStr.KlubnicaSurface = IMG_Load("Textures\\KLUBNIKA.bmp");
	SDL_SetColorKey(EasyStr.KlubnicaSurface, SDL_TRUE, SDL_MapRGB(EasyStr.KlubnicaSurface->format, 255, 255, 255));
	EasyStr.KlubnicaTexture = SDL_CreateTextureFromSurface(renderer, EasyStr.KlubnicaSurface);
	SDL_FreeSurface(EasyStr.KlubnicaSurface);

	EasyStr.MenuIconSurface = IMG_Load("Textures\\MENU_ICON.bmp");
	SDL_SetColorKey(EasyStr.MenuIconSurface, SDL_TRUE, SDL_MapRGB(EasyStr.MenuIconSurface->format, 255, 255, 255));
	EasyStr.MenuIconTexture = SDL_CreateTextureFromSurface(renderer, EasyStr.MenuIconSurface);
	SDL_FreeSurface(EasyStr.MenuIconSurface);

	EasyStr.to_menuSurface = IMG_Load("Textures\\MENU_ICON.bmp");
	SDL_SetColorKey(EasyStr.to_menuSurface, SDL_TRUE, SDL_MapRGB(EasyStr.to_menuSurface->format, 255, 255, 255));
	EasyStr.to_menuTexture = SDL_CreateTextureFromSurface(renderer, EasyStr.to_menuSurface);
	SDL_FreeSurface(EasyStr.to_menuSurface);

	EasyStr.HeadSnakeSurface = IMG_Load("Textures\\HeadSnakeEasy.bmp");
	SDL_SetColorKey(EasyStr.HeadSnakeSurface, SDL_TRUE, SDL_MapRGB(EasyStr.HeadSnakeSurface->format, 255, 255, 255));
	EasyStr.HeadSnakeTexture = SDL_CreateTextureFromSurface(renderer, EasyStr.HeadSnakeSurface);
	SDL_FreeSurface(EasyStr.HeadSnakeSurface);

}

void DeleteTexturesEasy() {
	SDL_DestroyTexture(EasyStr.AppleTexture);
	SDL_DestroyTexture(EasyStr.BananaTexture);
	SDL_DestroyTexture(EasyStr.KlubnicaTexture);
	SDL_DestroyTexture(EasyStr.ScoreTexture);
	SDL_DestroyTexture(EasyStr.LenSnakeTexture);
	SDL_DestroyTexture(EasyStr.SNAKE_EASY_TEXTURE);
	SDL_DestroyTexture(EasyStr.HeadSnakeTexture);
}

void SetkaEasy(SDL_Renderer* renderer) {
	for (int i = 0; i < 760; i += 40) {
		SDL_RenderDrawLine(renderer, 280 + i, 0, 280 + i, 720);
	}
	for (int i = 0; i < 760; i += 40) {
		SDL_RenderDrawLine(renderer, 280, i, 1000, i);
	}
}

void FruitSpawn() {
	
	while (!EasyStr.flagFruit) {
		EasyStr.c = 0;
		EasyStr.fruitX = rand() % (WIDTH_EASY2 - WIDTH_EASY1 + 1) + WIDTH_EASY1;
		EasyStr.fruitY = rand() % (HEIGHT_EASY2 - HEIGHT_EASY1 + 1) + HEIGHT_EASY1;
		if (EasyStr.fruitX % 40 == 0 && EasyStr.fruitY % 40 == 0) {
			for (int i = 0; i < EasyStr.LenSnake;i++) {
				if ((EasyStr.fruitX == EasyStr.SnakePosX[i] && EasyStr.fruitY == EasyStr.SnakePosY[i])||(EasyStr.TempFruitX== EasyStr.fruitX&& EasyStr.TempFruitY== EasyStr.fruitY)) { // Проверка неналожения на змейку и на место, где фрукт был в прошлый раз
					EasyStr.c++;
				}
			}
			if (EasyStr.c == 0) {
				EasyStr.TempFruitX = EasyStr.fruitX;
				EasyStr.TempFruitY = EasyStr.fruitY;
				EasyStr.flagFruit = true;
			}
			else
				continue;
		}
	}
}

void RenderGame(SDL_Renderer* RenderGame) {
	

	EasyStr.text = u8"Счёт: ";
	EasyStr.LenSnText = u8"Длина змейки: ";

	EasyStr.LenSn = to_string(EasyStr.LenSnake);
	EasyStr.LenSnText = EasyStr.LenSnText + EasyStr.LenSn;

	EasyStr.scoreOne = to_string(EasyStr.score);
	EasyStr.text = EasyStr.text + EasyStr.scoreOne;

	strcpy_s(EasyStr.textScore, EasyStr.text.c_str()); //Преобразование из string в char*
	strcpy_s(EasyStr.LenSnakeChar, EasyStr.LenSnText.c_str());

	EasyStr.ScoreTexture = Get_TextTextureEasy(RenderGame, EasyStr.textScore, EasyStr.fontScore);
	EasyStr.LenSnakeTexture = Get_SnakeLenTexture(RenderGame, EasyStr.LenSnakeChar, EasyStr.SnakeLenTTF);

	if (EasyStr.chooseFood==true) {//Шансы появления еды определенного типа
		EasyStr.randomFood = rand() % 100;
		if (EasyStr.randomFood < 50)
			EasyStr.Food_Number = 0;
		if (EasyStr.randomFood >= 50 && EasyStr.randomFood < 80)
			EasyStr.Food_Number = 1;
		if (EasyStr.randomFood >= 80 && EasyStr.randomFood < 100)
			EasyStr.Food_Number = 2;
		EasyStr.chooseFood = false; // ЧТОБЫ ЕДА менялась один раз
	}
	SDL_SetRenderDrawColor(RenderGame, 201, 201, 201, 0);//ЦВЕТ ПОЛЯ
	SDL_RenderClear(RenderGame);
	SDL_RenderCopy(RenderGame, EasyStr.ScoreTexture, NULL, &EasyStr.TextRect); //ОТРИСОВКА СЧЕТА
	SDL_RenderCopy(RenderGame, EasyStr.LenSnakeTexture, NULL, &EasyStr.TextLenSnake);//ОТРИСОВКА ДЛИНЫ ЗМЕЙКИ
	SDL_RenderCopy(RenderGame, EasyStr.to_menuTexture, NULL, &EasyStr.TO_MENU_RECT);//ОТРИСОВКА ИКОНКИ МЕНЮ

	SDL_DestroyTexture(EasyStr.LenSnakeTexture); // ДЛЯ ОСВОБОЖДЕНИЯ ПАМЯТИ
	SDL_DestroyTexture(EasyStr.ScoreTexture); // ДЛЯ ОСВОБОЖДЕНИЯ ПАМЯТИ

	SDL_SetRenderDrawColor(RenderGame, 195, 195, 195, 0);//Сеточка
	SetkaEasy(RenderGame);                    //Можно включить по желанию

	SDL_SetRenderDrawColor(RenderGame, 255, 0, 0, 0);

	SDL_RenderDrawRect(RenderGame, &EasyStr.CRAY);

	for (int x = 280; x < 1000;x += 40) {
		for (int y = 0; y < 720; y += 40) {
			if (x == EasyStr.xE && y == EasyStr.yE) {
				SDL_Rect rect = { x, y, 40,40 };
				//ОТРИСОВКА ГОЛОВЫ ЗМЕЙКИ
				if (Dir==RIGHT)
				SDL_RenderCopy(RenderGame, EasyStr.HeadSnakeTexture, NULL, &rect);
				if (Dir == LEFT)
					SDL_RenderCopyEx(RenderGame, EasyStr.HeadSnakeTexture, NULL, &rect,0,0,SDL_FLIP_HORIZONTAL); //ОТРИСОВКА ГОЛОВЫ ЗМЕЙКИ
				if (Dir == UP)
					SDL_RenderCopyEx(RenderGame, EasyStr.HeadSnakeTexture, NULL, &rect, 270, 0, SDL_FLIP_NONE);
				if (Dir == DOWN)
					SDL_RenderCopyEx(RenderGame, EasyStr.HeadSnakeTexture, NULL, &rect, 90, 0, SDL_FLIP_NONE);
				if(Dir==START)
					SDL_RenderCopy(RenderGame, EasyStr.HeadSnakeTexture, NULL, &rect);



			}
			for (int i = 0; i < EasyStr.LenSnake;i++) {
				if (EasyStr.SnakeX[i] == x && EasyStr.SnakeY[i] == y) {
					SDL_Rect rect = { EasyStr.SnakeX[i], EasyStr.SnakeY[i], 40,40 };
					SDL_RenderCopy(RenderGame, EasyStr.SNAKE_EASY_TEXTURE, NULL, &rect); //ОТРИСОВКА ГОЛОВЫ И ТЕЛА ЗМЕЙКИ
				}
			}
			if (x == EasyStr.fruitX && y == EasyStr.fruitY) //ОТРИСОВКА ЕДЫ
			{
				SDL_Rect Rect = { EasyStr.fruitX,EasyStr.fruitY,40,40 };
				if (EasyStr.Food_Number == 0)
					SDL_RenderCopy(RenderGame, EasyStr.AppleTexture, NULL, &Rect);
				if (EasyStr.Food_Number == 1)
					SDL_RenderCopy(RenderGame, EasyStr.KlubnicaTexture, NULL, &Rect);
				if (EasyStr.Food_Number == 2)
					SDL_RenderCopy(RenderGame, EasyStr.BananaTexture, NULL, &Rect);
			}
		}
	}
}

void Activity(SDL_Event event,bool &Pause) //КНОПКИ И МЫШЬ
{
	int x, y;
	SDL_GetMouseState(&x, &y);
	switch (event.type)
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
			case SDLK_a:
				if (Dir != RIGHT)          // ВЛЕВО
					Dir = LEFT; break;
			case SDLK_w:
				if (Dir != DOWN)         // ВВЕРХ
					Dir = UP; break;
			case SDLK_d:                // ВПРАВО
				if (Dir != LEFT)
					Dir = RIGHT; break;
			case SDLK_s:                // ВНИЗ
				if (Dir != UP)
					Dir = DOWN; break;
			case SDLK_ESCAPE:
				Pause = true;
				cout << "Escape was pressed" << endl; break;
			}
			if((event.type == SDL_MOUSEBUTTONDOWN)&&(event.button.button == SDL_BUTTON_LEFT))
				if (x >= 1230 && x <= 1280 && y >= 0 && y <= 50) //НАЖАТИЕ НА ИКОНКУ ПАУЗЫ
				{
					Pause = true;
				}
}

void GameLogicEasy() {
	//Реализация нарастания и поворота тела змейки с помощью связного списка
	int LastX = EasyStr.SnakeX[0], LastY = EasyStr.SnakeY[0];
	int LastXX, LastYY;
	EasyStr.SnakeX[0] = EasyStr.xE;
	EasyStr.SnakeY[0] = EasyStr.yE;

	for (int i = 0; i < EasyStr.LenSnake;i++) {
		LastXX = EasyStr.SnakeX[i];
		LastYY = EasyStr.SnakeY[i];
		EasyStr.SnakeX[i] = LastX;
		EasyStr.SnakeY[i] = LastY;
		LastX = LastXX;
		LastY = LastYY;
		EasyStr.SnakePosX[i] = LastX; //Запомнить координаты змейки и занести из в массив
		EasyStr.SnakePosY[i] = LastY;
	}
	switch (Dir) {
	case LEFT:      // ВЛЕВО
		EasyStr.Left = true;
		EasyStr.Right = false;
		EasyStr.Down = false;
		EasyStr.Up = false;
		break;
	case UP:      // ВВЕРХ
		EasyStr.Left = false;
		EasyStr.Right = false;
		EasyStr.Down = false;
		EasyStr.Up = true;
		break;
	case RIGHT:      // ВПРАВО
		EasyStr.Left = false;
		EasyStr.Right = true;
		EasyStr.Down = false;
		EasyStr.Up = false
			; break;
	case DOWN:      // ВНИЗ
		EasyStr.Left = false;
		EasyStr.Right = false;
		EasyStr.Down = true;
		EasyStr.Up = false;
		break;
	}
	if (EasyStr.Right == true)
		EasyStr.xE += 40;
	if (EasyStr.Left == true)
		EasyStr.xE -= 40;
	if (EasyStr.Up == true)
		EasyStr.yE -= 40;
	if (EasyStr.Down == true)
		EasyStr.yE += 40;

	if ((EasyStr.xE == EasyStr.fruitX) && (EasyStr.yE == EasyStr.fruitY)) { // Если фрукт был съеден
		if (EasyStr.Food_Number == 0)
			EasyStr.score++;
		if (EasyStr.Food_Number == 1)
			EasyStr.score += 2;
		if (EasyStr.Food_Number == 2)
			EasyStr.score += 3;
		EasyStr.LenSnake++;
		EasyStr.flagFruit = false;
		EasyStr.chooseFood = true;
		FruitSpawn();
		UKUS_Sound();
	}
	for (int i = 1; i < EasyStr.LenSnake;i++) { //Проверка не был ли съеден хвост
		if (EasyStr.SnakeX[i] == EasyStr.xE && EasyStr.SnakeY[i] == EasyStr.yE) {
			cout << "GameOver!" << endl;
			PlayFail();
			EasyStr.GameOver = true;
		}
	}
	if ((EasyStr.xE < 280 || EasyStr.xE > 960) || (EasyStr.yE < 0 || EasyStr.yE > 680)) { // Условие выхода за рамки поля
		cout << "GameOver!" << endl; PlayFail(); EasyStr.GameOver = true;
	}
}

//_______________________________________________________________________________
clock_t start = clock();    //Необходим для отвязки FPS приложения от игры!!!!!!!
//_______________________________________________________________________________


void EasyMode(SDL_Renderer* renderer, SDL_Event event, bool& Easy, bool& StartGame) {
	if (!EasyStr.Pause) {
		if (EasyStr.LoadTexturesEasyBool) { //ТО, ЧТО НУЖНО ЗАГРУЗИТЬ 1 РАЗ
			LoadTexturesEasy(renderer);
			Dir = START;
			PlayEasySound();
			EasyStr.fontScore = TTF_OpenFont("Text.ttf", 54);
			EasyStr.SnakeLenTTF = TTF_OpenFont("Text.ttf", 48);
			EasyStr.LoadTexturesEasyBool = false;
			ReadRecords();
		}
		if (EasyStr.GameOver == false) //ОСНОВНАЯ ЧАСТЬ ИГРЫ
		{
			Activity(event, EasyStr.Pause);
			if (clock() - start >= 500) { //Обновление рендера игры - КОНТРОЛЬ СКОРОСТИ
				FruitSpawn();
				GameLogicEasy();
				RenderGame(renderer);
				start = clock();
				SDL_RenderPresent(renderer);
			}
		}
		else //ЕСЛИ ИГРА ЗЕВЕРШЕНА
		{
			if (EasyStr.check == true) {
				if (CheckNewRecord(EasyStr.score, 0, EasyStr.NewRecord, EasyStr.OldRecord)) //Проверка нового рекорда, его запись в ФАЙЛ
				{
					EasyStr.NewRecordMenuFlag = true;
					EasyStr.check = false;
				}
				else {
					EasyStr.LoseMenuFlag = true;
					EasyStr.check = false;
				}
			}
				if (EasyStr.NewRecordMenuFlag)
					NewRecordMenu(renderer, event, EasyStr.BackToMenu, EasyStr.Restart, EasyStr.NewRecord, EasyStr.OldRecord, EasyStr.NewRecordMenuFlag, EasyStr.check);
				if (EasyStr.LoseMenuFlag)
					LoseMenu(renderer, event, EasyStr.BackToMenu, EasyStr.Restart, EasyStr.NewRecord, EasyStr.OldRecord, EasyStr.LoseMenuFlag, EasyStr.check);
			}
		}
	
	else //ЕСЛИ НАЖАТА КЛАВИША НАСТРОЕК
	{
		GameSettings(renderer, event, EasyStr.Pause, EasyStr.Restart, EasyStr.BackToMenu);
	}
	if (EasyStr.Restart) //ПЕРЕЗАПУСК УРОВНЯ
	{
		Easy = true;
		EasyStr.Right = false;
		EasyStr.Left = false;
		EasyStr.Down = false;
		EasyStr.Up = false;
		EasyStr.GameOver = false;
		Dir = START;
		EasyStr.LoadTexturesEasyBool = false;
		EasyStr.score = 0;
		EasyStr.xE = 600, EasyStr.yE = 720 / 2 - 40;

		for (int i = 0; i < EasyStr.LenSnake; i++)
		{
			EasyStr.SnakeX[i] = 0; EasyStr.SnakeY[i] = 0;
		}
		EasyStr.LenSnake = 1;
		EasyStr.Restart = false;
		EasyStr.flagFruit = false;
		PlayEasySound();
		EasyMode(renderer, event, Easy, StartGame);
	}
	if (EasyStr.BackToMenu) //ЕСЛИ БЫЛ ВОЗВРАТ В ГЛАВНОЕ МЕНЮ
	{
		Easy = false;
		StartGame = false;
		EasyStr.Right = false;
		EasyStr.Left = false;
		EasyStr.Down = false;
		EasyStr.Up = false;
		EasyStr.GameOver = false;
		EasyStr.LoadTexturesEasyBool = true;
		Dir = START;

		EasyStr.score = 0;
		EasyStr.xE = 600, EasyStr.yE = 720 / 2 - 40;
		EasyStr.flagFruit = false;
		DeleteTexturesEasy();
		PlayFonMusic();
		for (int i = 0; i < EasyStr.LenSnake; i++)
		{
			EasyStr.SnakeX[i] = 0; EasyStr.SnakeY[i] = 0;
		}
		EasyStr.LenSnake = 1;
		EasyStr.BackToMenu = false;
	}
}