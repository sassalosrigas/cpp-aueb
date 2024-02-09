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

class Lever : public Box, public GameObject {
	graphics::Brush m_brush_Lever;
	std::vector<std::string>m_spritesLever;
	int form = 0;

public:
	Lever(float x, float y, float w, float h)
		: Box(x, y, w, h) {}
	void init() override;
	void draw() override;
	void update(float ms) override;
	bool opened = false;
	float getPosX() {
		return m_pos_x;
	}
	float getPosY() {
		return m_pos_y;
	}
	void debugDrawLever();
	~Lever() {};
};