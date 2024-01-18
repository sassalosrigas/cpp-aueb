#pragma once
#include <sgg/graphics.h>>
#include <list>
#include <string>
#include "player.h"
#include "flyingpuppy.h"
#include "projectile.h"
#include <memory>
#include <vector>
#include <iostream>

class Level : public GameObject
{
	graphics::Brush m_brush_background;

	float m_center_x = 5.0f;
	float m_center_y = 5.0f;

	std::vector<GameObject*> m_static_object;
	std::vector<GameObject*> m_dynamic_object;

	const float m_block_size = 1.0f;
	graphics::Brush m_brush_block;
	graphics::Brush m_brush_block_debug;
	graphics::Brush m_brush_puppies;
	graphics::Brush m_brush_puppies_debug;
	std::vector<std::unique_ptr<FlyingPuppy>> puppies;

	void drawBlock(int i);
	void drawEnemy(int i);

	void checkCollisions();

	std::vector<Box> getVec();

public:
	std::vector<Box> m_blocks;
	std::vector<std::string> m_block_names;
	std::vector<FlyingPuppy> m_enemies;
	std::vector<std::string> m_enemy_names;
	class Projectile* t;
	void update(float ms) override;
	void draw() override;
	void init() override;

	Level(const std::string& name = "Level0");
	~Level();
};