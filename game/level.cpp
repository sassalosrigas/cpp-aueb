#include "level.h"
#include "gamestate.h"
#include "player.h"
#include <sgg/graphics.h>
#include "util.h"

void Level::drawBlock(int i)
{
	Box& box = m_blocks[i];
	std::string& name = m_block_names[i];
	float x = box.m_pos_x + m_state->m_global_offset_x;
	float y = box.m_pos_y + m_state->m_global_offset_y;
	m_brush_block.texture = m_state->getFullAssetPath(m_block_names[i]);

	graphics::drawRect(x, y, m_block_size, m_block_size, m_brush_block);

	if (m_state->m_debug_mode)
		graphics::drawRect(x, y, m_block_size, m_block_size, m_brush_block_debug);
}

void Level::checkCollisions()
{
	/*for (auto& box : m_blocks)
	{
		if (m_state->getPlayer()->intersect(box))
			printf("*");
		
	}a
	*/
	for (auto& block : m_blocks) {
		float offset = 0.0f;
		if (offset = m_state->getPlayer()->intersectDown(block)) {
			m_state->getPlayer()->m_pos_y += offset;
			m_state->getPlayer()->m_vy = 0.0f;
			break;
		}
	}
	for (auto& block : m_blocks)
	{
		float offset = 0.0f;
		if (offset = m_state->getPlayer()->intersectSideways(block))
		{
			m_state->getPlayer()->m_pos_x += offset;

			m_state->getPlayer()->m_vx = 0.0f;
			break;
		}

	}
}

void Level::update(float ms)
{
	if (m_state->getPlayer()->isActive())
		m_state->getPlayer()->update(ms);

	checkCollisions();

	GameObject::update(ms);
}

void Level::draw()
{
	float w = m_state->getCanvasWidth();
	float h = m_state->getCanvasHeight();

	float offset_x = m_state->m_global_offset_x / 2.0f + w / 2.0f;
	float offset_y = m_state->m_global_offset_y / 2.0f + h / 2.0f;

	//draw background
	graphics::drawRect(offset_x, offset_y, 2.0f * w, 4.0f * w, m_brush_background);

	//draw blocks
	for (int i = 0; i < m_blocks.size(); i++)
	{
		drawBlock(i);
	}

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

	m_block_names.push_back("block.png");
	m_block_names.push_back("block.png");
	m_block_names.push_back("block.png");
	m_block_names.push_back("block.png");
	m_block_names.push_back("block.png");
	m_block_names.push_back("block.png");
	m_block_names.push_back("block.png");
	m_block_names.push_back("block.png");
	m_block_names.push_back("block.png");

	m_brush_block.outline_opacity = 0.0f;
	m_brush_block_debug.fill_opacity = 0.1f;
	SETCOLOR(m_brush_block_debug.fill_color, 0.2f, 1.0f, 0.1f);
	SETCOLOR(m_brush_block.outline_color, 0.3f, 1.0f, 0.2f);


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
