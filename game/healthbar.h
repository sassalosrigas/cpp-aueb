#pragma once
#include <sgg/graphics.h>
#include "gameobject.h"
#include "gamestate.h"
#include "util.h"
#include "player.h"

class HealthBar: public GameObject {
public:
	graphics::Brush br_life;
	void init() override;
	void draw() override;
	//void update();
	HealthBar() {}
};
