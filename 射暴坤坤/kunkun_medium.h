#pragma once

#include "kunkun.h"

extern Atlas atlas_kunkun_medium;

class KunKunMedium :public KunKun {
public:
	KunKunMedium() {
		animation_run.add_frame(&atlas_kunkun_medium);

		speed_run = 50.0f;
	}

	~KunKunMedium() = default;

private:

};
