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
	if (right) {
		m_brush_FlyingPup.texture = m_state->getFullAssetPath("puppies-flyr1.png");
		form = 0;
	}
	else {
		m_brush_FlyingPup.texture = m_state->getFullAssetPath("puppies-flyl1.png");
		form = 4;
	}
	m_brush_FlyingPup.texture = m_state->getFullAssetPath("puppies-flyr1.png");
	m_spritesFlyingPup.push_back(m_state->getFullAssetPath("puppies-flyr1.png"));
	m_spritesFlyingPup.push_back(m_state->getFullAssetPath("puppies-flyr2.png"));
	m_spritesFlyingPup.push_back(m_state->getFullAssetPath("puppies-flyr3.png"));
	m_spritesFlyingPup.push_back(m_state->getFullAssetPath("puppies-flyr4.png"));
	m_spritesFlyingPup.push_back(m_state->getFullAssetPath("puppies-flyl1.png"));
	m_spritesFlyingPup.push_back(m_state->getFullAssetPath("puppies-flyl2.png"));
	m_spritesFlyingPup.push_back(m_state->getFullAssetPath("puppies-flyl3.png"));
	m_spritesFlyingPup.push_back(m_state->getFullAssetPath("puppies-flyl4.png"));
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
	//static auto lastUpdateTime = std::chrono::high_resolution_clock::now();
	auto currentTime = std::chrono::high_resolution_clock::now();
	auto deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastUpdateTime).count();
	if (deltaTime >= 100) {
		form++;
		if (right) {
			if (form > 3) {
				form = 0;
			}
		}
		else {
			if (form >= m_spritesFlyingPup.size()) {
				form = 4;
			}
		}
	
		lastUpdateTime = currentTime;
	}
	if (health_p <= 0.0f) {
		graphics::playSound("assets\\death.mp3", 0.5f, false);
	}
	movePup();
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
	sprintf_s(s, "(%5.2f, %5.2f", x, y);
	SETCOLOR(debug_brush.fill_color, 1, 0, 0);
	debug_brush.fill_opacity = 1.0f;
	graphics::drawText(x - 0.4f, y - 0.6f, 0.15f, s, debug_brush);
}

