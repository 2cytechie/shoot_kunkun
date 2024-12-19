#pragma once

#include <SDL_image.h>

#include "timer.h"
#include "camera.h"
#include "vector2.h"

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
		timer_interval.set_wait_time(0.5f);
		timer_interval.set_on_timeout([&]() {
			timer_interval.restart();
			tex_prop = nullptr;
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
		return !is_alive;
	}

	bool is_pick_up(Vector2 mouse_pos) {
		if (mouse_pos.x >= rect.x && mouse_pos.x <= rect.x+rect.w
			&& mouse_pos.y >= rect.y && mouse_pos.y <= rect.y+rect.h) {
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
		camera.render_texture(tex_prop, nullptr, &rect, 0, nullptr);
	}

protected:
	SDL_Texture* tex_prop = nullptr;				// ����ͼƬ
	SDL_FRect rect = { 0 };							// ����ͼƬλ�úͳߴ�
	Timer timer_idle;								// ����״̬ʱ��
	Timer timer_blink;								// ��ʧǰ��˸ʱ��
	Timer timer_interval;							// ��˸���

private:
	bool is_idle = true;							// �Ƿ�Ϊ����״̬
	bool is_alive = true;							// �Ƿ���

};
