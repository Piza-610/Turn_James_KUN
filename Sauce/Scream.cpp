#include <iostream>
#include <SDL.h>
#include "Scream.h"

int main(){
    SDL_Init(SDL_INIT_AUDIO); // SDLの初期化

    SDL_AudioSpec wavSpec;
    Uint32 wavLength;
    Uint8 *wavBuffer;

    // WAVファイルの読み込み
    if(SDL_LoadWAV("https://www.ne.jp/asahi/music/myuu/wave/menuettm.mp3", &wavSpec, &wavBuffer, &wavLength) == NULL) {
        std::cerr << "WAVファイルの読み込みに失敗しました: " << SDL_GetError() << std::endl;
        return 1;
    }

    // ここで再生処理を行う

    SDL_FreeWAV(wavBuffer); // WAVデータの解放
    SDL_Quit(); // SDLの終了処理
    return 0;
}


// g++ Scream.cpp -o Scream
// sudo apt-get install libsdl1.2-dev