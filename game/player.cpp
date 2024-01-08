#include "player.h"
#include <sgg/graphics.h>
#include "gamestate.h"
#include "util.h"

void Player::update(float ms)
{
	float speed = ms / 1000.0f;

	const float velocity = 10.f;
	if (graphics::getKeyState(graphics::SCANCODE_A))
		m_pos_x += speed * velocity;
	if (graphics::getKeyState(graphics::SCANCODE_D))
		m_pos_x -= speed * velocity;
	if (graphics::getKeyState(graphics::SCANCODE_W))
		m_pos_y += speed * velocity;
	if (graphics::getKeyState(graphics::SCANCODE_S))
		m_pos_y -= speed * velocity;

	m_state->m_global_offset_x = m_state->getCanvasWidth() / 2.0f - m_pos_x;
	m_state->m_global_offset_y = m_state->getCanvasHeight() / 2.0f - m_pos_y;

	GameObject::update(ms);
}

void Player::init()
{
	m_pos_x = 5.0f;
	m_pos_y = 5.0f;

	m_state->m_global_offset_x = m_state->getCanvasWidth() / 2.0f - m_pos_x;
	m_state->m_global_offset_y = m_state->getCanvasHeight() / 2.0f - m_pos_y;

	m_brush_player.fill_opacity = 1.0f;
	m_brush_player.outline_opacity = 0.0f;
	m_brush_player.texture = m_state->getFullAssetPath("player.png");

	m_brush_player_debug.fill_opacity = 0.1f;
	SETCOLOR(m_brush_player_debug.fill_color, 0.2f, 1.0f, 0.1f);
}

void Player::draw()
{
	graphics::drawRect(m_state->getCanvasWidth() * 0.5f, m_state->getCanvasHeight() * 0.5f, 1.0f, 1.0f, m_brush_player);

	float x = m_state->getCanvasWidth() * 0.5f;
	float y = m_state->getCanvasHeight() * 0.5f;

	if (m_state->m_debug_mode)
		graphics::drawRect(x, y, 1.0f, 1.0f, m_brush_player_debug);
}