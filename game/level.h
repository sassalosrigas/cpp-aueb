#pragma once
#include "gameobject.h"
#include "sgg/graphics.h"
#include <list>

class Level : public GameObject
{
	graphics::Brush m_brush_background;

	float m_center_x = 5.0f;
	float m_center_y = 5.0f;

	std::vector<GameObject*> m_static_object;
	std::vector<GameObject*> m_dynamic_object;

public:
	void update(float ms) override;
	void draw() override;
	void init() override;
	Level(const std::string& name = "Level0");
	~Level();
};