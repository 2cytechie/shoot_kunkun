#pragma once

#include <SDL.h>
#include <SDL_image.h>

#include <vector>
#include <string>

class Atlas {
public:
	Atlas() = default;
	~Atlas() {
		// ÊÍ·ÅÄÚ´æ
		for (SDL_Texture* texture : tex_list) {
			SDL_DestroyTexture(texture);
		}
	}

	void load(SDL_Renderer* renderer,const char* path_template,int num) {
		tex_list.clear();
		tex_list.resize(num);

		for (int i = 0; i < num; i++) {
			char path_file[256];
			sprintf_s(path_file, path_template, i + 1);
			SDL_Texture* texture = IMG_LoadTexture(renderer, path_file);
			tex_list[i] = texture;
		}
	}

	void clear() {
		tex_list.clear();
	}

	int get_size() {
		return (int)tex_list.size();
	}

	SDL_Texture* get_texture(int idx) {
		if (idx < 0 || idx >= tex_list.size()) return nullptr;

		return tex_list[idx];
	}

	void add_image(SDL_Texture* img) {
		tex_list.push_back(img);
	}

private:
	std::vector<SDL_Texture*> tex_list;

};