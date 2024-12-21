#pragma once

#include "prop.h"

extern SDL_Texture* tex_random_prop;

class RandomProp : public Prop {
public:
	RandomProp(Vector2 pos) {
		tex_prop = tex_gift_prop;
		state_prop = StateProp::random;
		timer_using.set_wait_time(10.0f);

		int width, height;
		SDL_QueryTexture(tex_prop, nullptr, nullptr, &width, &height);
		rect.x = pos.x - width / 2, rect.y = pos.y - height / 2;
		rect.w = width, rect.h = height;
	}

	~RandomProp() = default;

};
