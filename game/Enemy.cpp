#include "enemy.h";
#include <sgg/graphics.h>
#include "gamestate.h"
#include "util.h"


void Enemy::init() {

	m_brush_enemy.fill_opacity = 1.0f;
	m_brush_enemy.outline_opacity = 0.0f;
	m_brush_enemy.texture = m_state->getFullAssetPath("woof.png");
}

void Enemy::draw() {
	// Calculate the position to draw the enemy, applying the global offset
	float x = m_pos_x + m_state->m_global_offset_x;
	float y = m_pos_y + m_state->m_global_offset_y;

	// Use the same texture as the block for the enemy
	m_brush_enemy.texture = m_state->getFullAssetPath("woof.png");

	// Draw the enemy using the same method as drawing a block
	graphics::drawRect(x, y, 1.0f, 1.0f, m_brush_enemy);
	
}

void Enemy::update(float ms){
	GameObject::update(ms);
}


