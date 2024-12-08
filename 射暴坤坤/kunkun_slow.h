#pragma once

#include "kunkun.h"

extern Atlas atlas_kunkun_slow;

class KunKunSlow :public KunKun {
public:
	KunKunSlow() {
		animation_run.add_frame(&atlas_kunkun_slow);

		speed_run = 30.0f;
	}

	~KunKunSlow() = default;

private:

};
