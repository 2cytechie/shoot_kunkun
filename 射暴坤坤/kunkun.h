#pragma once

#include "camera.h"
#include "vector2.h"
#include "animation.h"

#include <SDL_mixer.h>

extern Atlas atlas_explosion;

extern Mix_Chunk* sound_explosion;

class KunKun {
public:
	KunKun() {
		animation_run.set_loop(true);
		animation_run.set_interval(0.1f);

		animation_explosion.set_loop(false);
		animation_explosion.set_interval(0.08f);
		animation_explosion.add_frame(&atlas_explosion);
		animation_explosion.set_on_finished([&]() {
			is_valid = false;
			});

		pos.x = 40.0f + (rand() % 1200);
		pos.y = -50;
	}

	~KunKun() = default;

	const Vector2& get_pos()const {
		return pos;
	}

	void on_update(float delta) {
		if (is_alive) pos.y += speed_run * delta;

		animation_current = (is_alive ? &animation_run : &animation_explosion);
		animation_current->set_pos(pos);
		animation_current->on_update(delta);
	}

	void on_render(const Camera& camera)const {
		animation_current->on_render(camera);
	}

	void on_hurt() {
		is_alive = false;

		Mix_PlayChannel(-1, sound_explosion, 0);
	}

	void make_invalid() {
		is_valid = false;
	}

	bool check_alive()const {
		return is_alive;
	}

	bool can_remove()const {
		return !is_valid;
	}

protected:
	float speed_run = 10.0f;						// �����ٶ�
	Animation animation_run;						// ���ܶ���

private:
	Vector2 pos;									// λ��
	Animation animation_explosion;					// ��������
	Animation* animation_current = nullptr;			// ʵ�ʲ��Ŷ���

	bool is_alive = true;							// �Ƿ���
	bool is_valid = true;							// �Ƿ���Ч

};
