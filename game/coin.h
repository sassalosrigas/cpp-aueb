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

class Coin : public Box, public GameObject {
	graphics::Brush m_brush_Coin;
	std::vector<std::string>m_spritesCoin;
	int form = 0;

	std::chrono::time_point<std::chrono::high_resolution_clock> lastUpdateTime;
public:
	Coin(float x, float y, float w, float h)
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
	void debugDrawCoin();
	~Coin() {};
};
