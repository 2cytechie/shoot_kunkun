#pragma once

#include "prop.h"

extern SDL_Texture* tex_star_prop;

class StarProp :public Prop {
public:
	StarProp(Vector2 pos) {
		tex_prop = tex_star_prop;
		state_prop = StateProp::star;
		timer_using.set_wait_time(1.5f);

		int width, height;
		SDL_QueryTexture(tex_prop, nullptr, nullptr, &width, &height);
		rect.x = pos.x - width / 2, rect.y = pos.y - height / 2;
		rect.w = width, rect.h = height;
	}

	~StarProp() = default;

};
