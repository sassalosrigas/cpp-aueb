#include "enemy.h";
#include <sgg/graphics.h>
#include "gamestate.h"
#include "util.h"


void Enemy::init() {
	
		//e_width /= 1.5f;
		
		//m_state->m_global_offset_x = m_state->getCanvasWidth() / 2.0f - m_pos_x;
		//m_state->m_global_offset_y = m_state->getCanvasHeight() / 2.0f - m_pos_y;
		
		m_brush_enemy.fill_opacity = 1.0f;
		m_brush_enemy.outline_opacity = 0.0f;
		m_brush_enemy.texture = m_state->getFullAssetPath("woof.png");
}

void Enemy::draw() {
	m_brush_enemy.texture = m_state->getFullAssetPath("woof.png");
	float x = m_pos_x + m_state->m_global_offset_x;
	float y = m_pos_y + m_state->m_global_offset_y;
	graphics::drawRect(x, y, 1.0f, 1.0f, m_brush_enemy);
	
}

void Enemy::update(float ms){
	GameObject::update(ms);
}

