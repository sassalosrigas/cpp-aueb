#pragma once
#include "box.h"
#include <sgg/graphics.h>>
#include <list>
#include <string>
#include "player.h"
#include "flyingpuppy.h"
#include "projectile.h"
#include <memory>
#include <vector>
#include "necromancer.h"
#include "healthpack.h"
#include <iostream>
using namespace std;

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
	int score = 0;
	std::vector<std::unique_ptr<Necromancer>> necromancers;
	std::vector<std::unique_ptr<FlyingPuppy>> puppies;
	std::vector<std::unique_ptr<HealthPack>> health_packs;
	bool deathsound = false;
	//std::vector<std::unique_ptr<Necromancer>> necromancers;
	//graphics::Brush m_brush_necromancers;
	void drawBlock(int i);

	void checkCollisions();
public:
	std::vector<Box> m_blocks;
	std::vector<std::string> m_block_names;

	void update(float ms) override;
	void draw() override;
	void init() override;
	void drawScore();
	Level(const std::string& name = "Level0");
	~Level();
};