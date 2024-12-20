#pragma once

#include "prop.h"
#include "vector2.h"

extern SDL_Texture* tex_gift_prop;

class GiftProp :public Prop {
public:
	GiftProp(Vector2 pos) {
		tex_prop = tex_gift_prop;

		int width, height;
		SDL_QueryTexture(tex_prop, nullptr, nullptr, &width, &height);
		rect.x = pos.x - width / 2, rect.y = pos.y - height / 2;
		rect.w = width, rect.h = height;
	}

	~GiftProp() = default;

	void on_update(float delta) {
		if (is_idle) {
			timer_idle.on_update(delta);
		}
		else {
			timer_blink.on_update(delta);
			timer_interval.on_update(delta);
		}
		if (is_disappear) {
			tex_prop = nullptr;
		}
		else {
			tex_prop = tex_gift_prop;
		}
	}

private:

};
