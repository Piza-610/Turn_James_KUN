#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include "Scream.h"

#define WAV_PATH "../Sounds/aaaa.wav"

Mix_Chunk *wave = NULL;
Mix_Music *music = NULL;


int main(int argc, char* argv[]){

        // Initialize SDL.
        if (SDL_Init(SDL_INIT_AUDIO) < 0)
                return -1;

        // Initialize SDL_mixer 
        if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 )
                return -1;

        // 効果音のロード 
        wave = Mix_LoadWAV(WAV_PATH);
        if (wave == NULL)
                return -1;


        // 効果音を一度だけ再生
        if ( Mix_PlayChannel(-1, wave, 0) == -1 )
                return -1;

        while ( Mix_PlayingMusic() ) ;

        Mix_FreeChunk(wave);
 
        // quit SDL_mixer
        Mix_CloseAudio();

        return 0;
}

// g++ -I /usr/include/SDL2 -D_REENTRANT Turn_The_Neck/Sauce/Scream.cpp -o Scream -lSDL2
// sudo apt-get install libsdl2-dev -y
// 参考　https://k38.hatenadiary.jp/entry/2018/10/26/005855

