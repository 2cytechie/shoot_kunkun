#pragma once

#include"camera.h"
#include"vector2.h"
#include"cmath"

#include<SDL.h>

extern SDL_Texture* tex_bullet;

class Bullet {
public:
	Bullet(double angle) {
		this->angle = angle;

		double radians = angle * 3.1415925 / 180;
		velocity.x = (float)std::cos(radians) * speed;
		velocity.y = (float)std::sin(radians) * speed;
	}

	~Bullet() = default;

	void set_pos(const Vector2& pos) {
		this->pos = pos;
	}

	const Vector2& get_pos()const {
		return pos;
	}

	void on_update(float delta) {
		pos += velocity * delta;

		if (pos.x <= 0 || pos.x >= 1280 || pos.y <= 0 || pos.y >= 720) {
			is_valid = false;
		}
	}

	void on_render(const Camera& camera)const {
		const SDL_FRect rect_bullet = { pos.x - 4,pos.y - 2,8,4 };
		camera.render_texture(tex_bullet, nullptr, &rect_bullet, angle, nullptr);
	}

	void on_hit() {
		is_valid = false;
	}

	bool can_remove() const {
		return !is_valid;
	}


private:
	double angle = 0;				// 旋转角度
	Vector2 pos;					// 子弹位置
	Vector2 velocity;				// 子弹当前速度
	bool is_valid = true;			// 子弹是否有效
	float speed = 800.0f;			// 子弹速度

};
