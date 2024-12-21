#pragma once

#include "prop.h"

extern SDL_Texture* tex_stop_prop;

class StopProp : public Prop {
public:
	StopProp(Vector2 pos) {
		tex_prop = tex_stop_prop;
		state_prop = StateProp::stop;
		timer_using.set_wait_time(10.0f);

		int width, height;
		SDL_QueryTexture(tex_prop, nullptr, nullptr, &width, &height);
		rect.x = pos.x - width / 2, rect.y = pos.y - height / 2;
		rect.w = width, rect.h = height;
	}

	~StopProp() = default;

};
