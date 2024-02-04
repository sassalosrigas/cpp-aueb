#pragma once
#include "util.h"
#include "gameobject.h"
#include "box.h"
#include "gamestate.h"
#include "healthpack.h"

void HealthPack::init() {
	m_width = 0.5f;
	m_height = 0.5f;
	m_brush_pack.fill_opacity = 1.0f;
	m_brush_pack.outline_opacity = 0.0f;
	m_brush_pack.texture = m_state->getFullAssetPath("healthpack.png");
}

void HealthPack::draw() {
	float x = packPosX() + m_state->m_global_offset_x;
	float y = packPosY() + m_state->m_global_offset_y;
	m_brush_pack.texture = m_state->getFullAssetPath("healthpack.png");
	graphics::drawRect(x, y, 0.8f, 0.6f, m_brush_pack);
	if (m_state->m_debug_mode) {
		debugDrawPack();
	}
}

void HealthPack::debugDrawPack() {
	graphics::Brush debug_brush;
	SETCOLOR(debug_brush.fill_color, 1, 0.3f, 0);
	SETCOLOR(debug_brush.outline_color, 1, 0.1f, 0);
	debug_brush.fill_opacity = 0.1f;
	debug_brush.outline_opacity = 1.0f;
	float x = packPosX() + m_state->m_global_offset_x;
	float y = packPosY() + m_state->m_global_offset_y;
	graphics::drawRect(x, y, m_width, m_height, debug_brush);
}