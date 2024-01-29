#pragma once
#include "gameobject.h"
#include "Box.h"
#include <sgg/graphics.h>
#include "gamestate.h"
#include "util.h"
#include "fireball.h"
#include <memory>
#include <vector>

class Necromancer : public GameObject, public Box {
public:
	void init() override;
	void draw() override;
	void update(float ms) override;
	graphics::Brush m_brush_Nec;
	std::vector<std::string>m_spritesNec;
	//bool right;
	int form = 0;
	int counter = 0;
	bool can_shoot = false;
	float shoot_cooldown = 0.0f;
	bool right;
	bool dying = false;
	float health_n = 100.0f;
	std::vector<std::unique_ptr<Fireball>> fireballs;
	Necromancer(float x, float y, float w, float h, bool r)
		: Box(x, y, w, h) {
		right = r;
	}
	Necromancer() {}
	float getPosX(){
		return m_pos_x;
	}

	float getPosY(){
		return m_pos_y;
	}
	bool isDead() {
		return health_n <= 0.0f;
	}
	void debugDrawNec();
	~Necromancer() {};
};
