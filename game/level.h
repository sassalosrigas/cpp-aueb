#pragma once
#include <sgg/graphics.h>
#include <vector>
#include <list>
#include <string>
#include "player.h"

class Level : public GameObject
{
	graphics::Brush m_brush_background;

	float m_center_x = 5.0f;
	float m_center_y = 5.0f;

	std::vector<GameObject*> m_static_object;
	std::vector<GameObject*> m_dynamic_object;

	std::vector<Box> m_blocks;
	std::vector<std::string> m_block_names;
	const float m_block_size = 1.0f;
	graphics::Brush m_brush_block;
	graphics::Brush m_brush_block_debug;

	void drawBlock(int i);

	void checkCollisions();

public:
	void update(float ms) override;
	void draw() override;
	void init() override;

	Level(const std::string& name = "Level0");
	~Level();
};