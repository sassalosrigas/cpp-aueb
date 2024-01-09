#pragma once

#include "gameobject.h"
#include "box.h"
#include <sgg/graphics.h>

class Player : public GameObject, public Box
{
	graphics::Brush m_brush_player;

	const float m_gravity = 10.0f;
	const float m_accel_vertical = 150.0f;
	const float m_accel_horizontal = 40.0f;
	const float m_max_velocity = 10.0f;

	void movePlayer(float ms);

public:
	float m_vx = 0.0f;
	float m_vy = 0.0f;

	Player(std::string name) : GameObject(name) {}

	void init() override;
	void draw() override;
	void update(float ms) override;

protected:
	void debugDraw();
};