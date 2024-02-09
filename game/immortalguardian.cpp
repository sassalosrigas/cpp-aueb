#pragma once
#include "gameobject.h"
#include "Box.h"
#include <sgg/graphics.h>
#include "gamestate.h"
#include "util.h" 
#include "immortalguardian.h"
#include <memory>
#include <vector>
#include <thread>
#include <chrono>

void ImmortalGuardian::init() {
	m_brush_Imm.fill_opacity = 1.0f;
	m_brush_Imm.outline_opacity = 0.0f;
	form = 0;
	m_brush_Imm.texture = m_state->getFullAssetPath("immortalGuardian1.png");
	m_spritesImm.push_back(m_state->getFullAssetPath("immortalGuardian1.png"));
	m_spritesImm.push_back(m_state->getFullAssetPath("immortalGuardian2.png"));
	m_spritesImm.push_back(m_state->getFullAssetPath("immortalGuardian3.png"));
}

void ImmortalGuardian::draw() {
	float x = getPosX() + m_state->m_global_offset_x;
	float y = getPosY() + m_state->m_global_offset_y;
	m_brush_Imm.texture = m_spritesImm[form];
	graphics::drawRect(x, y, 1.5f, 1.5f, m_brush_Imm);
}

void ImmortalGuardian::update(float ms) {
	auto currentTime = std::chrono::high_resolution_clock::now();
	auto deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastUpdateTime).count();
	if (deltaTime >= 200) {
		form++;
		if (form > 2) {
			form = 0;
		}
		lastUpdateTime = currentTime;
	}
	GameObject::update(ms);
}

void ImmortalGuardian::debugDrawGuard() {
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