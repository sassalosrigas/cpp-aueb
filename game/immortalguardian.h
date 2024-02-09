#pragma once
#include "gameobject.h"
#include "Box.h"
#include <sgg/graphics.h>
#include "gamestate.h"
#include "util.h" 
#include <memory>
#include <vector>
#include <thread>
#include <chrono>

class ImmortalGuardian : public Box, public GameObject {
	
	graphics::Brush m_brush_Imm;
	std::vector<std::string>m_spritesImm;
	int form = 0;
	
	std::chrono::time_point<std::chrono::high_resolution_clock> lastUpdateTime;
public:
	ImmortalGuardian(float x, float y, float w, float h)
		: Box(x, y, w, h) {}
	void init() override;
	void draw() override;
	void update(float ms) override;
	float getPosX() {
		return m_pos_x;
	}
	float getPosY() {
		return m_pos_y;
	}
	void debugDrawGuard();
	~ImmortalGuardian() {};
};