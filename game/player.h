#pragma once

#include "gameobject.h"
#include "box.h"
#include <sgg/graphics.h>

class Player : public GameObject, public Box
{
	graphics::Brush m_brush_player;

	std::vector<GameObject*> m_static_object;
	std::vector<GameObject*> m_dynamic_object;

	graphics::Brush m_brush_player_debug;

	const float m_gravity = 10.0f;
	const float m_accel_vertical = 300.0f;
	const float m_accel_horizontial = 20.0f;
	const float m_max_velocity = 5.0f;
	void movePlayer(float ms);

public:
	Player(std::string name) : GameObject(name) {}
	float m_vx = 0.0f;
	float m_vy = 0.0f;
	void init() override;
	void draw() override;
	void update(float ms) override;

protected: 
	void debugDraw();
};