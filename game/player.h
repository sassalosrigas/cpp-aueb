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

public:
	Player(std::string name) : GameObject(name) {}

	void init() override;
	void draw() override;
	void update(float ms) override;
};