#pragma once

#include "prop.h"

extern SDL_Texture* tex_speed_prop;

class SpeedProp :public Prop {
public:
	SpeedProp(Vector2 pos) {
		tex_prop = tex_speed_prop;
		state_prop = StateProp::speed;
		timer_using.set_wait_time(15.0f);

		int width, height;
		SDL_QueryTexture(tex_prop, nullptr, nullptr, &width, &height);
		rect.x = pos.x - width / 2, rect.y = pos.y - height / 2;
		rect.w = width, rect.h = height;
	}

	~SpeedProp() = default;

};
