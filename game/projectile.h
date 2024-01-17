#pragma once
#include "box.h"
#include <sgg/graphics.h>
#include "gamestate.h"
#include "gamestate.h"
#include "util.h"


class Projectile : public Box, public GameObject {

public:
	float i = 0.1f;
	void init(float x,float y);
	void draw() override;
	void update(float ms) override;
	graphics::Brush m_brush_projectile;
	Projectile(float x, float y, float w, float h)
		: Box(x, y, w, h) {}
	const float speed = 0.001f;
	Projectile() {} 
	float posX() {
		return m_pos_x;
	}
	float posY() {
		return m_pos_y;
	}
	void setPosX(float x) {
		m_pos_x = x;
	}
	void setPosY(float y) {
		m_pos_y = y;
	}
};