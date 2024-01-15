#pragma once
#include "GameObject.h"
#include "Box.h"
#include <sgg/graphics.h>

class Enemy : public GameObject, public Box {
	graphics::Brush m_brush_player;
	
public:
	const float m_vx = 2.0f;
	const float m_vy = 2.0f;
	Enemy(std::string name) : GameObject(name) {}
	void init() override;
	void draw() override;
	void update(float ms) override;

};