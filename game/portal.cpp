#pragma once
#include "util.h"
#include "gameobject.h"
#include "box.h"
#include "gamestate.h"
#include "portal.h"


void Portal::init() {
	br_portal.fill_opacity = 1.0f;
	br_portal.outline_opacity = 0.0f;
	br_portal.texture = m_state->getFullAssetPath("portal.png");
}

void Portal::draw() {
	float x = portalPosX() + m_state->m_global_offset_x;
	float y = portalPosY() + m_state->m_global_offset_y;
	br_portal.texture = m_state->getFullAssetPath("portal.png");
	graphics::drawRect(x, y, 1.0f, 1.0f, br_portal);
	if (m_state->m_debug_mode) {
		debugDrawPortal();
	}
}

void Portal::debugDrawPortal() {
	graphics::Brush debug_brush;
	SETCOLOR(debug_brush.fill_color, 1, 0.3f, 0);
	SETCOLOR(debug_brush.outline_color, 1, 0.1f, 0);
	debug_brush.fill_opacity = 0.1f;
	debug_brush.outline_opacity = 1.0f;
	float x = portalPosX() + m_state->m_global_offset_x;
	float y = portalPosY() + m_state->m_global_offset_y;
	graphics::drawRect(x, y, m_width, m_height, debug_brush);
}