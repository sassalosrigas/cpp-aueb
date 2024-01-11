#include "player.h"
#include <sgg/graphics.h>
#include "gamestate.h"
#include "util.h"

void Player::movePlayer(float ms) {
	float speed = ms / 1000.0f;
	float move = 0.0f;
	if (graphics::getKeyState(graphics::SCANCODE_A))
		move -= 1.0f;
	if (graphics::getKeyState(graphics::SCANCODE_D))
		move += 1.0f;

	m_vx = std::min<float>(m_max_velocity,m_vx+speed*move*m_accel_horizontial);
	m_vx = std::max<float>(-m_max_velocity, m_vx);
	m_pos_x += speed * m_vx;
	//m_vx -= 0.2f * m_vx / (0.1f + fabs(m_vx));

	if (fabs(m_vx) < 0.01f) {
		m_vx = 0;
	}
	m_pos_x += m_vx * speed;

	if (m_vy == 0.0f) {
		m_vy -= (graphics::getKeyState(graphics::SCANCODE_W) ? m_accel_vertical : 0.0f);
	}
	m_vy += speed * m_gravity;
	m_pos_y += m_vy * speed;
}


void Player::update(float ms)
{
	
	/*float speed = ms / 1000.0f;
	const float velocity = 10.0f;
	if (graphics::getKeyState(graphics::SCANCODE_A))
		m_pos_x -= speed * velocity;
	if (graphics::getKeyState(graphics::SCANCODE_D))
		m_pos_x += speed * velocity;
	if (graphics::getKeyState(graphics::SCANCODE_W))
		m_pos_y -= speed * velocity;
	if (graphics::getKeyState(graphics::SCANCODE_S))
		m_pos_y += speed * velocity;
	*/
	movePlayer(ms);
	m_state->m_global_offset_x = m_state->getCanvasWidth() / 2.0f - m_pos_x;
	m_state->m_global_offset_y = m_state->getCanvasHeight() / 2.0f - m_pos_y;

	GameObject::update(ms);
}

void Player::init()
{
	m_pos_x = 5.0f;
	m_pos_y = 5.0f;
	m_width /= 2.0f;

	m_state->m_global_offset_x = m_state->getCanvasWidth() / 2.0f - m_pos_x;
	m_state->m_global_offset_y = m_state->getCanvasHeight() / 2.0f - m_pos_y;

	m_brush_player.fill_opacity = 1.0f;
	m_brush_player.outline_opacity = 0.0f;
	m_brush_player.texture = m_state->getFullAssetPath("player.png");
}

void Player::draw()
{
	graphics::drawRect(m_state->getCanvasWidth() * 0.5f, m_state->getCanvasHeight() * 0.5f, 1.0f, 1.0f, m_brush_player);
	if (m_state->m_debug_mode) {
		debugDraw();
	}
	
}

void Player::debugDraw() {
	graphics::Brush debug_brush;
	SETCOLOR(debug_brush.fill_color, 1, 0.3f, 0);
	SETCOLOR(debug_brush.outline_color, 1, 0.1f, 0);
	debug_brush.fill_opacity = 0.1f;
	debug_brush.outline_opacity = 1.0f;
	graphics::drawRect(m_state->getCanvasWidth() * 0.5f, m_state->getCanvasHeight() * 0.5f, m_width, m_height, debug_brush);
	char s[20];
	sprintf_s(s, "(%5.2f, %5.2f", m_pos_x, m_pos_y);
	SETCOLOR(debug_brush.fill_color, 1, 0, 0);
	debug_brush.fill_opacity = 1.0f;
	graphics::drawText(m_state->getCanvasWidth() * 0.5f - 0.4f, m_state->getCanvasHeight() * 0.5f - 0.6f, 0.15f, s, debug_brush);
}