#pragma once
#include <sgg/graphics.h>
#include "gamestate.h"
#include "util.h"
#include "level.h"
#include "player.h"
#include "ribbon.h"
#include <thread>
#include <chrono>
#include <cmath>
#include "iostream"
using namespace std;




void Player::movePlayer(float ms) {
	if (!collisionDet) {
		float speed = ms / 1000.0f;
		float move = 0.0f;
		if (graphics::getKeyState(graphics::SCANCODE_A)) {
			move -= 1.0f;
			left = true;
		}
		else if (graphics::getKeyState(graphics::SCANCODE_D)) {
			move += 1.0f;
			left = false;
		}
		m_vx = std::min<float>(m_max_velocity, m_vx + speed * move * m_accel_horizontial);
		m_vx = std::max<float>(-m_max_velocity, m_vx);
		m_pos_x += speed * m_vx;
		m_vx -= 3.0f * m_vx * speed;

		if (fabs(m_vx) < 0.01f) {
			m_vx = 0;
		}
		m_pos_x += m_vx * speed;
		if (m_vy == 0.0f) {
			m_vy -= (graphics::getKeyState(graphics::SCANCODE_W) ? m_accel_vertical : 0.0f);
		}

		m_vy += speed * m_gravity;
		m_pos_y += m_vy * speed;
		if (graphics::getKeyState(graphics::SCANCODE_SPACE)) {
			if (can_shoot) {
				ribbons.push_back(std::make_unique<Ribbon>(m_pos_x, m_pos_y, 1.0f, 1.0f));
				ribbons[counter]->init(m_pos_x, m_pos_y);
				//cout << projectiles.size();
				if (left) {
					ribbons[counter]->setLeft();
				}
				counter++;
				can_shoot = false;
			}
		}
	}
}


void Player::update(float ms)
{	
	static auto lastUpdateTime = std::chrono::high_resolution_clock::now();
	auto currentTime = std::chrono::high_resolution_clock::now();
	auto deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastUpdateTime).count();
	movePlayer(ms);		
	if (!can_shoot) {
		shoot_cooldown -= ms / 400.00f;
		if (shoot_cooldown <= 0) {
			can_shoot = true;
			shoot_cooldown = 1.0f;
		}
	}
	if (ribbons.size() >= 1) {
		for (int i = 0; i < ribbons.size(); i++) {
			ribbons[i]->update(ms);
		}
	}
	ribbons.erase(std::remove_if(ribbons.begin(), ribbons.end(),
		[](const std::unique_ptr<Ribbon>& ribbon) {
			return ribbon->outOfRange() || ribbon -> toRemove;
		}), ribbons.end());
	counter = ribbons.size();
	/*if (deltaTime >= 1000) {
		for (int i = 0; i < projectiles.size(); i++) {
			cout << "PROJECTILE " << i << " " << projectiles[i]->posX() << endl;
			cout << "PLAYER" << m_pos_x << endl;
		}
		lastUpdateTime = currentTime;
	}
	*/
	m_state->m_global_offset_x = m_state->getCanvasWidth() / 2.0f - m_pos_x;
	m_state->m_global_offset_y = m_state->getCanvasHeight() / 2.0f - m_pos_y;
	//if (health_self <= 0.0f) {
		//delete this;
	//}
	GameObject::update(ms);
}

void Player::init()
{
	m_pos_x = 5.0f;
	m_pos_y = 5.0f;
	m_width /= 1.4f;
	m_height /= 1.2f;
	m_state->m_global_offset_x = m_state->getCanvasWidth() / 2.0f - m_pos_x;
	m_state->m_global_offset_y = m_state->getCanvasHeight() / 2.0f - m_pos_y;
	m_brush_player.fill_opacity = 1.0f;
	m_brush_player.outline_opacity = 0.0f;
	m_brush_player.texture = m_state->getFullAssetPath("hk0.png");
	m_spritesR.push_back(m_state->getFullAssetPath("hk-right2.png"));
	m_spritesR.push_back(m_state->getFullAssetPath("hk-right1.png"));
	m_spritesR.push_back(m_state->getFullAssetPath("hk-right3.png"));
	m_spritesR.push_back(m_state->getFullAssetPath("hk-right4.png"));
	m_spritesL.push_back(m_state->getFullAssetPath("hk-left1.png"));
	m_spritesL.push_back(m_state->getFullAssetPath("hk-left2.png"));
	m_spritesL.push_back(m_state->getFullAssetPath("hk-left3.png"));
	m_spritesL.push_back(m_state->getFullAssetPath("hk-left4.png"));
	//hp = new HealthBar();
	//hp->init();
}

void Player::draw()
{
	int sprite = (int)fmod(100.0f - m_pos_x * 4.0f, m_spritesR.size());
	if (graphics::getKeyState(graphics::SCANCODE_D)) {
		m_brush_player.texture = m_spritesR[sprite];
	}
	if (graphics::getKeyState(graphics::SCANCODE_A)) {
		m_brush_player.texture = m_spritesL[sprite];  
	}
	if (m_vx == 0) {
		m_brush_player.texture = m_state->getFullAssetPath("hk0.png");
	}
	graphics::drawRect(m_state->getCanvasWidth() * 0.5f, m_state->getCanvasHeight() * 0.5f, 1.0f, 1.0f, m_brush_player);
	if (m_state->m_debug_mode) {
		debugDraw();
	}
	//hp->draw();
	if (ribbons.size() >= 1) {
		for (int i = 0; i < ribbons.size(); i++) {
			ribbons[i]->draw();
 		}
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
	sprintf_s(s, "(%5.2f, %5.2f)", m_pos_x, m_pos_y);
	SETCOLOR(debug_brush.fill_color, 1.0f, 1.0f, 1.0f);
	debug_brush.fill_opacity = 1.0f;
	graphics::drawText(m_state->getCanvasWidth() * 0.5f - 0.4f, m_state->getCanvasHeight() * 0.5f - 0.6f, 0.15f, s, debug_brush);
}







