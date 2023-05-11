#include "Sound.h"

Mix_Chunk* Tap = NULL;
Mix_Music* Ambient = NULL;
Mix_Music* LevelEasy = NULL;
Mix_Chunk* UKUS = NULL;
Mix_Music* LevelNormal = NULL;
Mix_Music* LevelHard = NULL;
Mix_Chunk* Fail = NULL;

void Volume(int volume) {
	Mix_VolumeMusic(volume);
}

void PlayFonMusic() {
	Mix_PlayMusic(Ambient, -1);
}
void TapSound() {
	Mix_PlayChannel(-1, Tap, 0);
}
void PlayEasySound() {
	Mix_PlayMusic(LevelEasy, -1);
}
void UKUS_Sound() {
	Mix_PlayChannel(-1, UKUS, 0);
}
void  PlayNormalSound() {
	Mix_PlayMusic(LevelNormal, -1);
}
void PlayHardSound() {
	Mix_PlayMusic(LevelHard, -1);
}
void PlayFail() {
	Mix_PlayChannel(-1, Fail, 0);
}
void LoadSound() {
	Ambient = Mix_LoadMUS("Sound\\Ambient.mp3");
	Tap = Mix_LoadWAV("Sound\\TAP.mp3");
	LevelEasy = Mix_LoadMUS("Sound\\FON_EASY_SOUND.mp3");
	UKUS = Mix_LoadWAV("Sound\\KUSI.mp3");
	LevelNormal = Mix_LoadMUS("Sound\\FON_NORMAL_SOUND.mp3");
	LevelHard = Mix_LoadMUS("Sound\\FON_HARD_SOUND.mp3");
	Fail = Mix_LoadWAV("Sound\\UDAR.mp3");
}
void InitMusic() {
	Mix_Init(0);
	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024);
}