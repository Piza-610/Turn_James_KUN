#include <iostream>
#include <SDL.h>
#include "Scream.h"

void audio_callback(void* userdata, Uint8* stream, int len) {
    SDL_AudioSpec* wavSpec = (SDL_AudioSpec*)userdata;
    Uint8* wavBuffer = wavSpec->userdata;

    if (wavSpec->size == 0) {
        return;
    }

    len = (len > wavSpec->size ? wavSpec->size : len);
    SDL_memcpy(stream, wavBuffer, len);
    wavBuffer += len;
    wavSpec->userdata = wavBuffer;
    wavSpec->size -= len;
}

int main(){
    SDL_Init(SDL_INIT_AUDIO); // SDLの初期化

    SDL_AudioSpec wavSpec;
    Uint32 wavLength;
    Uint8 *wavBuffer;

    // WAVファイルの読み込み
    if(SDL_LoadWAV("../Sounds/baby.wav", &wavSpec, &wavBuffer, &wavLength) == NULL) {
        std::cerr << "WAVファイルの読み込みに失敗しました: " << SDL_GetError() << std::endl;
        return 1;
    }

    wavSpec.callback = audio_callback;
    wavSpec.userdata = wavBuffer;
    wavSpec.size = wavLength;

    // オーディオデバイスを開く
    if (SDL_OpenAudio(&wavSpec, NULL) < 0) {
        std::cerr << "オーディオデバイスのオープンに失敗しました: " << SDL_GetError() << std::endl;
        SDL_FreeWAV(wavBuffer);
        SDL_Quit();
        return 1;
    }

    // オーディオ再生開始
    SDL_PauseAudio(0);

    // 再生が終了するまで待機
    while (wavSpec.size > 0) {
        SDL_Delay(100);
    }

    // 資源解放
    SDL_CloseAudio();
    SDL_FreeWAV(wavBuffer);
    SDL_Quit();
    return 0;
}
// g++ -I /usr/include/SDL2 -D_REENTRANT Turn_The_Neck/Sauce/Scream.cpp -o Scream -lSDL2
// sudo apt-get install libsdl2-dev -y

