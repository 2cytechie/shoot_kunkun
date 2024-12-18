#pragma once

#include <SDL_image.h>

#include "timer.h"
#include "camera.h"
#include "vector2.h"

extern SDL_Texture* tex_prop_attention;
extern SDL_Texture* tex_prop_gift;
extern SDL_Texture* tex_prop_speed;
extern SDL_Texture* tex_prop_star;
extern SDL_Texture* tex_prop_stop;

class Prop {
public:
	enum class StateProp {
		Attention,
		Gift,
		Speed,
		Star,
		Stop,
		blink
	};

public:
	Prop() {
		timer_idle.set_one_shot(true);
		timer_idle.set_wait_time(7.0f);
		timer_idle.set_on_timeout([&]() {
			is_idle = false;
			});

		timer_blink.set_one_shot(true);
		timer_blink.set_wait_time(3.0f);
		timer_blink.set_on_timeout([&]() {
			is_alive = false;
			});

		timer_interval.set_one_shot(false);
		timer_interval.set_wait_time(0.5f);
		timer_interval.set_on_timeout([&]() {
			timer_interval.restart();
			tex_prop_current = nullptr;
			});
	}

	~Prop() = default;

	void set_pos(Vector2 pos) {
		this->pos = pos;
	}

	const Vector2 get_pos()const {
		return pos;
	}

	bool check_alive() {
		return !is_alive;
	}

	bool is_pick_up(Vector2 mouse_pos) {
		if (mouse_pos.x >= pos.x - rect.w / 2 && mouse_pos.x <= pos.x + rect.w / 2
			&& mouse_pos.y >= pos.y - rect.h / 2 && mouse_pos.y + rect.h / 2) {
			is_alive = false;
			return true;
		}
		return false;
	}

	void on_update(float delta) {
		if (is_idle) {
			timer_idle.on_update(delta);
		}
		else {
			timer_blink.on_update(delta);
			timer_interval.on_update(delta);
		}
	}

	void on_render(const Camera& camera) {
		camera.render_texture(tex_prop_current, nullptr, &rect, 0, nullptr);
	}

private:
	SDL_Texture* tex_prop_current = nullptr;		// 当前道具图片
	SDL_FRect rect = { 0 };							// 道具图片尺寸
	StateProp state_prop;							// 当前道具
	Timer timer_idle;								// 正常状态时间
	Timer timer_blink;								// 消失前闪烁时间
	Timer timer_interval;							// 闪烁间隔
	Vector2 pos;									// 道具中心点位置

	bool is_idle = true;							// 是否为正常状态
	bool is_alive = true;							// 是否存活

};
