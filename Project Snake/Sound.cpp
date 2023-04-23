#include "Sound.h"

Mix_Chunk* Tap = NULL;
Mix_Music* Ambient = NULL;
Mix_Music*LevelEasy = NULL;
Mix_Chunk* UKUS = NULL;

void Volume(int volume) {
	Mix_VolumeMusic(volume);
}

void PlayFonMusic() {
	Ambient = Mix_LoadMUS("Sound\\Ambient.mp3");
	Mix_PlayMusic(Ambient, -1);
}
void TapSound() {
	Tap = Mix_LoadWAV("Sound\\TAP.mp3");
	Mix_PlayChannel(-1, Tap, 0);
}
void PlayEasySound() {
	LevelEasy = Mix_LoadMUS("Sound\\FON_EASY_SOUND.mp3");
	Mix_PlayMusic(LevelEasy, -1);
}
void UKUS_Sound() {
	UKUS = Mix_LoadWAV("Sound\\KUSI.mp3");
	Mix_PlayChannel(-1, UKUS, 0);
}
void InitMusic() {
	Mix_Init(0);
	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024);
}