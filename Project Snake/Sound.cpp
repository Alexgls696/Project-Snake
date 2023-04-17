#include "Sound.h"
Mix_Chunk* Tap = NULL;
Mix_Music* Ambient = NULL;


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
void InitMusic() {
	Mix_Init(0);
	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024);
}