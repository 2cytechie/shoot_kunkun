#pragma once

#include "timer.h"
#include "vector2.h"

#include<SDL.h>

class Camera {
public:
	Camera(SDL_Renderer* renderer) {
		this->renderer = renderer;

		timer_shake.set_one_shot(true);
		timer_shake.set_on_timeout([&] {
			is_shaking = false;
			reset();
			});
	}

	~Camera() = default;

	const Vector2& get_pos()const {
		return pos;
	}

	void reset() {
		pos.x = 0;
		pos.y = 0;
	}

	void on_update(float delta) {
		timer_shake.on_update(delta);

		if (is_shaking) {
			pos.x = (-50 + rand() % 100) / 50.0f * shaking_strength;
			pos.y = (-50 + rand() % 100) / 50.0f * shaking_strength;
		}
	}

	void shake(float strength, float duration) {
		is_shaking = true;
		shaking_strength = strength;

		timer_shake.set_wait_time(duration);
		timer_shake.restart();
	}

	void render_texture(SDL_Texture* texture, const SDL_Rect* rect_src,
		const SDL_FRect* rect_dst,double angle, const SDL_FPoint* center) const {
		SDL_FRect rect_dst_win = *rect_dst;
		rect_dst_win.x -= pos.x;
		rect_dst_win.x -= pos.x;

		SDL_RenderCopyExF(renderer, texture, rect_src,
			&rect_dst_win, angle, center, SDL_RendererFlip::SDL_FLIP_NONE);
	}

public:
	SDL_Renderer* renderer;				// 
	Timer timer_shake;					// 窗口抖动
	bool is_shaking = false;			// 窗口是否在抖动
	Vector2 pos;						// 摄像机位置
	float shaking_strength = 0;			// 抖动幅度大小

};

