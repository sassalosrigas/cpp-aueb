#pragma once
#include <sgg/graphics.h>
#include "gameobject.h"
#include "gamestate.h"
#include "util.h"
#include "healthbar.h"
#include "player.h"


void HealthBar::init() {
	SETCOLOR(br_life.fill_color, 0, 1, 0);
	SETCOLOR(br_life.outline_color, 0, 1, 0);
	br_life.fill_opacity = 0.1f;
	br_life.outline_opacity = 1.0f;
}

void HealthBar::draw() {
	graphics::drawRect(m_state->getCanvasHeight() * 0.5f, m_state->getCanvasWidth() * 0.5f, 1.0f, 1.0f, br_life);
}