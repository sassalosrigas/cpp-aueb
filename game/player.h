#pragma once

#include "gameobject.h"
#include "box.h"
#include <sgg/graphics.h>
#include "level.h"
#include "healthbar.h"

class Player : public GameObject, public Box
{
	graphics::Brush m_brush_player;
	std::vector<std::string> m_spritesR;
	std::vector<std::string> m_spritesL;
	const float m_gravity = 8.0f;
	const float m_accel_vertical = 4.5f;
	const float m_accel_horizontial = 3.0f;
	const float m_max_velocity = 3.0f;
	void movePlayer(float ms);
	HealthBar m_healthBar;


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