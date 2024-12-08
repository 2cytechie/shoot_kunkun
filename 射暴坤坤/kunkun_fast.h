#pragma once

#include "kunkun.h"

extern Atlas atlas_kunkun_fast;

class KunKunFast :public KunKun {
public:
	KunKunFast() {
		animation_run.add_frame(&atlas_kunkun_fast);

		speed_run = 80.0f;
	}

	~KunKunFast() = default;

private:

};
