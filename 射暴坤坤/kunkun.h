#pragma once

#include "camera.h"
#include "vector2.h"
#include "animation.h"
#include "prop.h"
#include "gift_prop.h"
#include "random_prop.h"
#include "speed_prop.h"
#include "star_prop.h"
#include "stop_prop.h"

#include <SDL_mixer.h>
#include <vector>

extern Atlas atlas_explosion;

extern Mix_Chunk* sound_explosion;

extern std::vector<Prop*> prop_list;

class KunKun {
public:
	enum class StateKunKun {
		fast,
		medium,
		slow
	};

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


	// 僵尸坤坤死亡后概率掉落物品
	~KunKun() {
		int val = rand() % 1000;
		if (val < 30) {
			Prop* prop = nullptr;
			if (val < 5) prop = new RandomProp(pos);
			else if (val < 10) prop = new GiftProp(pos);
			else if (val < 20) prop = new SpeedProp(pos);
			else if (val < 25) prop = new StarProp(pos);
			else prop = new StopProp(pos);
			prop_list.push_back(prop);
		}
	}

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

	void set_speed_run(float speed_run) {
		this->speed_run = speed_run;
	}

	StateKunKun get_state_kunkun() {
		return state_kunkun;
	}

protected:
	StateKunKun state_kunkun = StateKunKun::fast;	// 初始化坤坤类型为fast
	float speed_run = 10.0f;						// 奔跑速度
	Animation animation_run;						// 奔跑动画

private:
	Vector2 pos;									// 位置
	Animation animation_explosion;					// 死亡动画
	Animation* animation_current = nullptr;			// 实际播放动画

	bool is_alive = true;							// 是否存活
	bool is_valid = true;							// 是否有效


};
