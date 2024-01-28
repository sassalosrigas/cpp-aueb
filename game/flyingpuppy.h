#pragma once
#include "gameobject.h"
#include "Box.h"
#include <sgg/graphics.h>
#include "gamestate.h"

class FlyingPuppy : public GameObject, public Box {
	
public:
	//const float m_vy = 2.0f;
	float distance_trav = 0.0f;
	bool right;
	float range;
	float health_p = 100.0f;
	const float m_vx = 0.01f;
	FlyingPuppy(std::string name) : GameObject(name) {}
	void init() override;
	void draw() override;
	void update(float ms) override;
	graphics::Brush m_brush_FlyingPup;
	std::vector<std::string>m_spritesFlyingPup;
	int form = 0;
	
	FlyingPuppy(float x, float y, float w, float h, bool r,float rangeP)
		: Box(x, y, w, h) {
		right = r;
		range = rangeP;
	}
	void switchDir () {
		right = !right;
	}

	float getPosX() {
		return m_pos_x;
	}

	float getPosY() {
		return m_pos_y;
	}
	void movePup() {
		if (right) {
			m_pos_x += 0.01f;
		}
		else {
			m_pos_x -= 0.01f;
		}
		distance_trav += 0.01f;
		if (distance_trav >= range) {
			distance_trav = 0.0f;
			switchDir();
		}
	}
	bool isDead() {
		return health_p <= 0;
	}
	void debugDrawFLP();
	~FlyingPuppy() {};

};

