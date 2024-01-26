#pragma once
#include "gameobject.h"
#include "Box.h"
#include <sgg/graphics.h>
#include "gamestate.h"

class Enemy : public GameObject, public Box {
	
public:
	//const float m_vx = 2.0f;
	//const float m_vy = 2.0f;
	Enemy(std::string name) : GameObject(name) {}
	void init() override;
	void draw() override;
	void update(float ms) override;
	graphics::Brush m_brush_enemy;
	std::vector<std::string>m_spritesFly;
	int form = 0;
	Enemy(float x, float y, float w, float h)
		: Box(x, y, w, h) {}

	float getPosX() {
		return m_pos_x;
	}

	float getPosY() {
		return m_pos_y;
	}
	
};

