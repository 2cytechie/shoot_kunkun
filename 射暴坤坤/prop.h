#pragma once

#include <SDL_image.h>

#include "timer.h"
#include "camera.h"
#include "vector2.h"

extern bool is_fire_key_down;

class Prop {
public:
	Prop() {
		timer_idle.set_one_shot(true);
		timer_idle.set_wait_time(10.0f);
		timer_idle.set_on_timeout([&]() {
			is_idle = false;
			});

		timer_blink.set_one_shot(true);
		timer_blink.set_wait_time(5.0f);
		timer_blink.set_on_timeout([&]() {
			is_alive = false;
			});

		timer_interval.set_one_shot(false);
		timer_interval.set_wait_time(0.2f);
		timer_interval.set_on_timeout([&]() {
			timer_interval.restart();
			is_disappear = !is_disappear;
			});
	}

	~Prop() = default;

	void set_pos(Vector2 pos) {
		rect.x = pos.x - rect.w / 2;
		rect.y = pos.y - rect.h / 2;
	}

	const Vector2 get_pos()const {
		return Vector2(rect.x + rect.w / 2, rect.y + rect.h / 2);
	}

	bool check_alive() {
		return is_alive;
	}

	bool can_remove() {
		return !is_alive;
	}

	bool is_pick_up(Vector2 mouse_pos) {
		if (mouse_pos.x >= rect.x && mouse_pos.x <= rect.x+rect.w
			&& mouse_pos.y >= rect.y && mouse_pos.y <= rect.y+rect.h
			&& is_fire_key_down) {
			is_alive = false;
			return true;
		}
		return false;
	}

	virtual  void on_update(float delta) {}

	void on_render(const Camera& camera) {
		camera.render_texture(tex_prop, nullptr, &rect, 0, nullptr);
	}

protected:
	SDL_Texture* tex_prop = nullptr;				// 道具图片
	SDL_FRect rect = { 0 };							// 道具图片位置和尺寸
	Timer timer_idle;								// 正常状态时间
	Timer timer_blink;								// 消失前闪烁时间
	Timer timer_interval;							// 闪烁间隔
	bool is_idle = true;							// 是否为正常状态
	bool is_disappear = false;						// 是否消失

private:
	bool is_alive = true;							// 是否存活

};
