#pragma once

#include <SDL_image.h>

#include "timer.h"
#include "camera.h"
#include "vector2.h"

extern bool is_fire_key_down;

class Prop {
public:
	enum class StateProp{
		gift,
		speed,
		star,
		stop
	};

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

		timer_using.set_one_shot(true);
		timer_using.set_on_timeout([&] {
			is_alive = false;
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

	StateProp get_state_prop() {
		return state_prop;
	}

	bool get_pick_up() {
		return is_pick_up;
	}

	bool chack_pick_up(Vector2 mouse_pos) {
		if (!is_pick_up) {
			if (mouse_pos.x >= rect.x && mouse_pos.x <= rect.x + rect.w
				&& mouse_pos.y >= rect.y && mouse_pos.y <= rect.y + rect.h
				&& is_fire_key_down) {
				is_pick_up = true;
				is_disappear = true;
				return true;
			}
		}
		return false;
	}

	void on_update(float delta) {
		if (is_idle) {
			timer_idle.on_update(delta);
		}
		else {
			timer_blink.on_update(delta);
			if (!is_pick_up) timer_interval.on_update(delta);
			else timer_using.on_update(delta);
		}
	}

	void on_render(const Camera& camera) {
		if (!is_disappear) {
			camera.render_texture(tex_prop, nullptr, &rect, 0, nullptr);
		}
	}

protected:
	SDL_Texture* tex_prop = nullptr;				// 道具图片
	SDL_FRect rect = { 0 };							// 道具图片位置和尺寸
	Timer timer_idle;								// 正常状态时间
	Timer timer_blink;								// 消失前闪烁时间
	Timer timer_interval;							// 闪烁间隔
	Timer timer_using;								// 道具正在使用时长
	StateProp state_prop = StateProp::gift;			// 初始化物品为gift

private:
	bool is_alive = true;							// 是否存活
	bool is_idle = true;							// 是否为正常状态
	bool is_pick_up = false;						// 是否捡起
	bool is_disappear = false;						// 是否消失

};
