#pragma once
#include "util.h"
#include "gameobject.h"
#include "box.h"
#include "gamestate.h"

class Portal : public GameObject, public Box {

	graphics::Brush br_portal;

public:
	Portal(float x, float y, float w, float h)
		: Box(x, y, w, h) {
	}
	void init() override;
	void draw() override;
	float portalPosX() {
		return m_pos_x;
	}
	void debugDrawPortal();
	float portalPosY() {
		return m_pos_y;
	}
};