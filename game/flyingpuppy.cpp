#include "flyingpuppy.h";
#include <sgg/graphics.h>
#include "gamestate.h"
#include "util.h"
#include <thread>
#include <chrono>
#include <iostream>
using namespace std;


void FlyingPuppy::init() {
	m_height /= 1.2f;
	m_brush_FlyingPup.fill_opacity = 1.0f;
	m_brush_FlyingPup.outline_opacity = 0.0f;
	m_brush_FlyingPup.texture = m_state->getFullAssetPath("puppies-flyr1.png");
	m_spritesFlyingPup.push_back(m_state->getFullAssetPath("puppies-flyr1.png"));
	m_spritesFlyingPup.push_back(m_state->getFullAssetPath("puppies-flyr2.png"));
	m_spritesFlyingPup.push_back(m_state->getFullAssetPath("puppies-flyr3.png"));
	m_spritesFlyingPup.push_back(m_state->getFullAssetPath("puppies-flyr4.png"));
	form = 0;

}

void FlyingPuppy::draw() {
	// Calculate the position to draw the enemy, applying the global offset
	float x = getPosX() + m_state->m_global_offset_x;
	float y = getPosY() + m_state->m_global_offset_y;
	m_brush_FlyingPup.texture = m_spritesFlyingPup[form];
	graphics::drawRect(x, y, 1.0f, 1.0f, m_brush_FlyingPup);
	if (m_state->m_debug_mode) {
		debugDrawFLP();
	}
	
}

void FlyingPuppy::update(float ms){
	// Increment the animation variable static auto lastUpdateTime = std::chrono::high_resolution_clock::now();
	static auto lastUpdateTime = std::chrono::high_resolution_clock::now();
	auto currentTime = std::chrono::high_resolution_clock::now();
	auto deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastUpdateTime).count();
	if (deltaTime >= 100) {
		form++;
		if (form >= m_spritesFlyingPup.size()) {
			form = 0;
		}

		lastUpdateTime = currentTime;
	}
	
	GameObject::update(ms);
}

void FlyingPuppy::debugDrawFLP() {
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

