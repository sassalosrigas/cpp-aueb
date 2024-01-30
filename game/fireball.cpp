#pragma once
#include "box.h"
#include <sgg/graphics.h>
#include "gamestate.h"
//#include "level.h"
#include "gameobject.h"
#include "fireball.h"
#include "util.h"
#include "iostream"
#include "necromancer.h"
using namespace std;

void Fireball::init(float x, float y) {
	setPosX(x);
	setPosY(y);
	m_height = 0.2f;
	m_width = 0.2f;
	m_brush_fireball.fill_opacity = 1.0f;
	m_brush_fireball.outline_opacity = 0.0f;
	m_brush_fireball.texture = m_state->getFullAssetPath("fireball.png");

}

void Fireball::draw() {

	float x = posX() + m_state->m_global_offset_x;
	float y = posY() + m_state->m_global_offset_y;
	graphics::drawRect(x, y, 0.3f, 0.3f, m_brush_fireball);
	
	if (m_state->m_debug_mode) {
		debugDrawProj();
	}

}

void Fireball::update(float ms) {
	if (left) {
		setPosX(posX() - speed);
	}
	else {
		setPosX(posX() + speed);
	}
	dist += speed;
	GameObject::update(ms);
}

bool Fireball::outOfRange() {
	return dist > 20.0f;
}
void Fireball::debugDrawProj() {
	graphics::Brush debug_brush;
	SETCOLOR(debug_brush.fill_color, 1, 0.3f, 0);
	SETCOLOR(debug_brush.outline_color, 1, 0.1f, 0);
	debug_brush.fill_opacity = 0.1f;
	debug_brush.outline_opacity = 1.0f;
	float x = posX() + m_state->m_global_offset_x;
	float y = posY() + m_state->m_global_offset_y;
	graphics::drawRect(x ,y, m_width, m_height, debug_brush);
	/*char s[20];
	sprintf_s(s, "(%5.2f, %5.2f", m_pos_x, m_pos_y);
	SETCOLOR(debug_brush.fill_color, 1, 0, 0);
	debug_brush.fill_opacity = 1.0f;
	float drawX, drawY;
	if (left) {
		// Adjust the position based on the projectile's position and direction
		drawX = posX() - i;
		drawY = posY();
	}
	else {
		// Adjust the position based on the projectile's position and direction
		drawX = posX() + i;
		drawY = posY() - 0.6f;
	}
	graphics::drawText(drawX + m_state->m_global_offset_x, drawY + m_state->m_global_offset_y, 0.15f, s, debug_brush);
	*/
}
