#pragma once
#include "gameobject.h"
#include "Box.h"
#include <sgg/graphics.h>
#include "gamestate.h"
#include "util.h" 
#include "coin.h"
#include <memory>
#include <vector>
#include <thread>
#include <chrono>

void Coin::init() {
	m_width = 0.5f;
	m_height = 0.5f;
	m_brush_Coin.fill_opacity = 1.0f;
	m_brush_Coin.outline_opacity = 0.0f;
	m_brush_Coin.texture = m_state->getFullAssetPath("healthpack.png");
	m_spritesCoin.push_back(m_state->getFullAssetPath("coin1.png"));
	m_spritesCoin.push_back(m_state->getFullAssetPath("coin2.png"));
	m_spritesCoin.push_back(m_state->getFullAssetPath("coin3.png"));
	m_spritesCoin.push_back(m_state->getFullAssetPath("coin4.png"));
	m_spritesCoin.push_back(m_state->getFullAssetPath("coin5.png"));
	m_spritesCoin.push_back(m_state->getFullAssetPath("coin6.png"));
}

void Coin::draw() {
	float x = getPosX() + m_state->m_global_offset_x;
	float y = getPosY() + m_state->m_global_offset_y;
	m_brush_Coin.texture = m_spritesCoin[form];
	graphics::drawRect(x, y, 0.8f, 0.6f, m_brush_Coin);
	if (m_state->m_debug_mode) {
		debugDrawCoin();
	}
}

void Coin::update(float ms) {
	auto currentTime = std::chrono::high_resolution_clock::now();
	auto deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastUpdateTime).count();
	if (deltaTime >= 200) {
		form++;
		if (form > 5) {
			form = 0;
		}
		lastUpdateTime = currentTime;
	}
	GameObject::update(ms);
}

void Coin::debugDrawCoin() {
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