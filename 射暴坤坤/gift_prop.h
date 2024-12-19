#pragma once

#include "prop.h"

extern SDL_Texture* tex_gift_prop;

class GiftProp :public Prop {
public:
	GiftProp() {
		tex_prop = tex_gift_prop;

		int width, height;
		SDL_QueryTexture(tex_prop, nullptr, nullptr, &width, &height);
		rect.w = width, rect.h = height;
	}

	~GiftProp() = default;

private:

};
