#include "healthbar.h"
#include <iostream>
#include <algorithm>

HealthBar::HealthBar(int m_intitial_health) : maxHealth(100), currentHealth(m_intitial_health), barWidth(30) 
{
}

HealthBar::~HealthBar()
{
}

void HealthBar::setCurrentHealth(int health)
{
	currentHealth = std::max(0, std::min(health, maxHealth));
}

int HealthBar::getCurrentHealth() const
{
	return currentHealth;
}

void HealthBar::drawBar(int i)
{
	float x = .m_pos_x + m_state->m_global_offset_x;
	float y = box.m_pos_y + m_state->m_global_offset_y;
	m_brush_block.texture = m_state->getFullAssetPath(m_block_names[i]);

	graphics::drawRect(x, y, m_block_size, m_block_size, m_brush_block);

	if (m_state->m_debug_mode)
		graphics::drawRect(x, y, m_block_size, m_block_size, m_brush_block_debug);
}
