#include "level.h"
#include "gamestate.h"
#include "player.h"
#include <sgg/graphics.h>

void Level::update(float ms)
{
	if (m_state->getPlayer()->isActive())
		m_state->getPlayer()->update(ms);

	GameObject::update(ms);
}

void Level::draw()
{
	float w = m_state->getCanvasWidth();
	float h = m_state->getCanvasHeight();

	float offset_x = m_state->m_global_offset_x + w / 2.0f;
	float offset_y = m_state->m_global_offset_y + h / 2.0f;

	graphics::drawRect(offset_x, offset_y, 2.0f * w, 4.0f * w, m_brush_background);

	if (m_state->getPlayer()->isActive())
		m_state->getPlayer()->draw();

	for (auto p_gob : m_static_object)
		if (p_gob)
			p_gob->draw();

	for (auto p_gob : m_dynamic_object)
		if (p_gob)
			p_gob->draw();
}

void Level::init()
{
	for (auto p_gob : m_static_object)
		if (p_gob)
			p_gob->init();

	for (auto p_gob : m_dynamic_object)
		if (p_gob)
			p_gob->init();

	m_blocks.push_back(Box(5*m_block_size, 6*m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(4*m_block_size, 6*m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(3*m_block_size, 6*m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(2*m_block_size, 5*m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(6*m_block_size, 6*m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(7*m_block_size, 6*m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(7*m_block_size, 5*m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(3*m_block_size, 2*m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(4*m_block_size, 3*m_block_size, m_block_size, m_block_size));

	m_block_names.push_back("Block0");
	m_block_names.push_back("Block1");
	m_block_names.push_back("Block2");
	m_block_names.push_back("Block3");
	m_block_names.push_back("Block4");
	m_block_names.push_back("Block5");
	m_block_names.push_back("Block6");
	m_block_names.push_back("Block7");
	m_block_names.push_back("Block8");


}

Level::Level(const std::string& name)
{
	m_brush_background.outline_opacity = 0.0f;
	m_brush_background.texture = m_state->getFullAssetPath("background.png");
}

Level::~Level()
{
	for (auto p_gob : m_static_object)
		if (p_gob)
			delete p_gob;

	for (auto p_gob : m_dynamic_object)
		if (p_gob)
			delete p_gob;
}