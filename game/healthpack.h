#pragma once
#include "util.h"
#include "gameobject.h"
#include "box.h"
#include "gamestate.h"

class HealthPack : public GameObject, public Box {

public:
	void init() override;
	void draw() override;
	//void update(float ms) override;
	graphics::Brush m_brush_pack;
	bool toRemove = false;
	HealthPack(float x, float y, float w, float h)
		: Box(x, y, w, h) {
	}
	float packPosX() {
		return m_pos_x;
	}
	float packPosY() {
		return m_pos_y;
	}	
	void debugDrawPack();
};