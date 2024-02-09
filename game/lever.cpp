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
#include "lever.h"

void Lever::init() {
	m_width = 0.5f;
	m_height = 0.5f;
	m_brush_Lever.fill_opacity = 1.0f;
	m_brush_Lever.outline_opacity = 0.0f;
	m_brush_Lever.texture = m_state->getFullAssetPath("leverclose.png");
	m_spritesLever.push_back(m_state->getFullAssetPath("leverclose.png"));
	m_spritesLever.push_back(m_state->getFullAssetPath("leveropen.png"));
}

void Lever::draw() {
	float x = getPosX() + m_state->m_global_offset_x;
	float y = getPosY() + m_state->m_global_offset_y;
	m_brush_Lever.texture = m_spritesLever[form];
	graphics::drawRect(x, y, 0.8f, 0.6f, m_brush_Lever);
	if (m_state->m_debug_mode) {
		debugDrawLever();
	}
}

void Lever::update(float ms) {
	if (opened) {
		form = 1;
	}
	GameObject::update(ms);
}

void Lever::debugDrawLever() {
	graphics::Brush debug_brush;
	SETCOLOR(debug_brush.fill_color, 1, 0.3f, 0);
	SETCOLOR(debug_brush.outline_color, 1, 0.1f, 0);
	debug_brush.fill_opacity = 0.1f;
	debug_brush.outline_opacity = 1.0f;
	float x = getPosX() + m_state->m_global_offset_x;
	float y = getPosY() + m_state->m_global_offset_y;
	graphics::drawRect(x, y, m_width, m_height, debug_brush);
	char s[20];
	sprintf_s(s, "(%5.2f, %5.2f", m_pos_x, m_pos_y);
	SETCOLOR(debug_brush.fill_color, 1, 0, 0);
	debug_brush.fill_opacity = 1.0f;
	graphics::drawText(m_state->getCanvasWidth() * 0.5f - 0.4f, m_state->getCanvasHeight() * 0.5f - 0.6f, 0.15f, s, debug_brush);
}