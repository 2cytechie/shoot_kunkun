#pragma once

#include "prop.h"

extern SDL_Texture* tex_random_prop;

class RandomProp : public Prop {
public:
	RandomProp(Vector2 pos) {
		tex_prop = tex_random_prop;
		int val = rand() % 10;
		if (val < 1) {
			state_prop = StateProp::gift;
			timer_using.set_wait_time(0.001f);
		}
		else if (val < 5) {
			state_prop = StateProp::speed;
			timer_using.set_wait_time(5.0f);
		}
		else if(val < 8) {
			state_prop = StateProp::star;
			timer_using.set_wait_time(2.5f);
		}
		else {
			state_prop = StateProp::stop;
			timer_using.set_wait_time(3.0f);
		}

		int width, height;
		SDL_QueryTexture(tex_prop, nullptr, nullptr, &width, &height);
		rect.x = pos.x - width / 2, rect.y = pos.y - height / 2;
		rect.w = width, rect.h = height;
	}

	~RandomProp() = default;

};
