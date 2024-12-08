#define SDL_MAIN_HANDLED

#include<iostream>

#include<SDL.h>
#include<SDL_ttf.h>
#include<SDL_mixer.h>
#include<SDL_image.h>

int main() {
	// SDL初始化
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
	Mix_Init(MIX_INIT_MP3);
	TTF_Init();

	// 音频初始化
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

	SDL_Window* window = SDL_CreateWindow(u8"你好，世界！", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,1280,720, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);

	const int FPS = 60;						// 帧率60
	bool is_quit = false;
	SDL_Event event;

	Uint64 last_counter = SDL_GetPerformanceCounter();
	Uint64 counter_freq = SDL_GetPerformanceFrequency();

	while (!is_quit) {
		while (SDL_PollEvent(&event)) {

		}

		Uint64 current_counter = SDL_GetPerformanceCounter();
		double delta = (double)(current_counter - last_counter) / counter_freq;
		last_counter = current_counter;
		if (delta * 1000 < 1000.0 / FPS) {
			SDL_Delay((Uint32)(1000.0 / 60 - delta * 1000));
		}

		// 数据更新

		// 图形渲染


	}

}