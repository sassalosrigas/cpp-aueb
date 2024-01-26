#include "enemy.h";
#include <sgg/graphics.h>
#include "gamestate.h"
#include "util.h"


void Enemy::init() {

	m_brush_enemy.fill_opacity = 1.0f;
	m_brush_enemy.outline_opacity = 0.0f;
	m_brush_enemy.texture = m_state->getFullAssetPath("puppies-flyr1.png");
	m_spritesFly.push_back(m_state->getFullAssetPath("puppies-flyr1.png"));
	m_spritesFly.push_back(m_state->getFullAssetPath("puppies-flyr2.png"));
	m_spritesFly.push_back(m_state->getFullAssetPath("puppies-flyr3.png"));
	m_spritesFly.push_back(m_state->getFullAssetPath("puppies-flyr4.png"));
	form = 0;
}

void Enemy::draw() {
	// Calculate the position to draw the enemy, applying the global offset
	float x = getPosX() + m_state->m_global_offset_x;
	float y = getPosY() + m_state->m_global_offset_y;
	//int sprite = (int)fmod(100.0f - m_pos_x * 4.0f, m_spritesFly.size());
	
	/*m_brush_enemy.texture = m_spritesFly[form];
	form++;
	if (form >= m_spritesFly.size()) {
		form = 0;
	}
	*/
	// Use the same texture as the block for the enemy
	
	// Draw the enemy using the same method as drawing a block
	m_brush_enemy.texture = m_state->getFullAssetPath("puppies-flyr3.png");
	graphics::drawRect(x, y, 1.0f, 1.0f, m_brush_enemy);
	
}

void Enemy::update(float ms){
	// Increment the animation variable
	GameObject::update(ms);
}


