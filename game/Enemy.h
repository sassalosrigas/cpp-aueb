#pragma once
#include "gameobject.h"
#include "Box.h"
#include <sgg/graphics.h>
#include "gamestate.h"

class Enemy : public GameObject, public Box {
	graphics::Brush m_brush_enemy;
	
public:
	//const float m_vx = 2.0f;
	//const float m_vy = 2.0f;
	Enemy(std::string name) : GameObject(name) {}
	void init() override;
	void draw() override;
	void update(float ms) override;
	Box(float x, float y, float w, float h)
		: m_pos_x(x), m_pos_y(y), m_width(w), m_height(h) {}
};

