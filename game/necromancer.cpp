#pragma once
#include "necromancer.h"
#include "gameobject.h"
#include "gamestate.h"
#include <thread>
#include <chrono>
#include "util.h"
#include "fireball.h"
#include <iostream>
using namespace std;


void Necromancer::init() {
	m_brush_Nec.fill_opacity = 1.0f;
	m_brush_Nec.outline_opacity = 0.0f;
	if (right) {
		m_brush_Nec.texture = m_state->getFullAssetPath("NecR1.png");
		m_spritesNec.push_back(m_state->getFullAssetPath("NecR1.png"));
		m_spritesNec.push_back(m_state->getFullAssetPath("NecR2.png"));
		m_spritesNec.push_back(m_state->getFullAssetPath("NecR3.png"));
		m_spritesNec.push_back(m_state->getFullAssetPath("NecR4.png"));
		m_spritesNec.push_back(m_state->getFullAssetPath("NecR5.png"));
		m_spritesNec.push_back(m_state->getFullAssetPath("NecR6.png"));
		m_spritesNec.push_back(m_state->getFullAssetPath("NecR7.png"));
		m_spritesNec.push_back(m_state->getFullAssetPath("NecR8.png"));
		m_spritesNec.push_back(m_state->getFullAssetPath("NecR9.png"));
		m_spritesNec.push_back(m_state->getFullAssetPath("NecR10.png"));
		m_spritesNec.push_back(m_state->getFullAssetPath("NecR11.png"));
		m_spritesNec.push_back(m_state->getFullAssetPath("NecR12.png"));
		m_spritesNec.push_back(m_state->getFullAssetPath("NecDyingR1.png"));
		m_spritesNec.push_back(m_state->getFullAssetPath("NecDyingR2.png"));
		m_spritesNec.push_back(m_state->getFullAssetPath("NecDyingR3.png"));
		m_spritesNec.push_back(m_state->getFullAssetPath("NecDyingR4.png"));
		m_spritesNec.push_back(m_state->getFullAssetPath("NecDyingR5.png"));
		m_spritesNec.push_back(m_state->getFullAssetPath("NecDyingR6.png"));
		m_spritesNec.push_back(m_state->getFullAssetPath("NecDyingR7.png"));
	}
	else {
		m_brush_Nec.texture = m_state->getFullAssetPath("NecL1.png");
		m_spritesNec.push_back(m_state->getFullAssetPath("NecL1.png"));
		m_spritesNec.push_back(m_state->getFullAssetPath("NecL2.png"));
		m_spritesNec.push_back(m_state->getFullAssetPath("NecL3.png"));
		m_spritesNec.push_back(m_state->getFullAssetPath("NecL4.png"));
		m_spritesNec.push_back(m_state->getFullAssetPath("NecL5.png"));
		m_spritesNec.push_back(m_state->getFullAssetPath("NecL6.png"));
		m_spritesNec.push_back(m_state->getFullAssetPath("NecL7.png"));
		m_spritesNec.push_back(m_state->getFullAssetPath("NecL8.png"));
		m_spritesNec.push_back(m_state->getFullAssetPath("NecL9.png"));
		m_spritesNec.push_back(m_state->getFullAssetPath("NecL10.png"));
		m_spritesNec.push_back(m_state->getFullAssetPath("NecL11.png"));
		m_spritesNec.push_back(m_state->getFullAssetPath("NecL12.png"));
		m_spritesNec.push_back(m_state->getFullAssetPath("NecDyingL1.png"));
		m_spritesNec.push_back(m_state->getFullAssetPath("NecDyingL2.png"));
		m_spritesNec.push_back(m_state->getFullAssetPath("NecDyingL3.png"));
		m_spritesNec.push_back(m_state->getFullAssetPath("NecDyingL4.png"));
		m_spritesNec.push_back(m_state->getFullAssetPath("NecDyingL5.png"));
		m_spritesNec.push_back(m_state->getFullAssetPath("NecDyingL6.png"));
		m_spritesNec.push_back(m_state->getFullAssetPath("NecDyingL7.png"));
		
	}
	
	form = 0;
	counter = 0;
}

void Necromancer::draw() {
	if (toDelete) {
		return;
	}
	float x = getPosX() + m_state->m_global_offset_x;
	float y = getPosY() + m_state->m_global_offset_y;
	m_brush_Nec.texture = m_spritesNec[form];
	graphics::drawRect(x, y, 1.5f, 1.5f, m_brush_Nec);
	if (fireballs.size() >= 1) {
		for (int i = 0; i < fireballs.size(); i++) {
			fireballs[i]->draw();
		}
	}
	if (m_state->m_debug_mode) {
		debugDrawNec();
	}
	
}

void Necromancer::update(float ms) {
	//static auto lastUpdateTime = std::chrono::high_resolution_clock::now();
	auto currentTime = std::chrono::high_resolution_clock::now();
	auto deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastUpdateTime).count();
	if (can_shoot && form == 10) {
		fireballs.push_back(std::make_unique<Fireball>(getPosX(), getPosY(), 1.0f, 1.0f));
		fireballs[counter]->init(getPosX(), getPosY());
		if (!right) {
			fireballs[counter]->setLeft();
		}
		can_shoot = false; // Set the flag to false to prevent shooting until cooldown is over
		counter++;
	}
	if (!can_shoot) {
		shoot_cooldown -= ms / 400.0f;
		if (shoot_cooldown <= 0) {
			can_shoot = true;
			shoot_cooldown = 1.0f; // Reset the cooldown for the next shot
		}
	}
	if (health_n <= 0.0f && !dying) {
		dying = true;
		form = 12;
	}
	
	if (deltaTime >= 100) {
		form++;
		if (!dying) {
			if (form >= 11) {
				form = 0;
			}
		}
		else {
			if (form == 12) {
				graphics::playSound("assets\\death.mp3", 0.5f, false);
			}
			if (form >= 18) {
				form = 0;
				toDelete = true;
			}
		}
			
		cout << fireballs.size();
		lastUpdateTime = currentTime;
	}
	
	
	if (fireballs.size() >= 1) {
		for (int i = 0; i < fireballs.size(); i++) {
			fireballs[i]->update(ms);
		}
	}
	fireballs.erase(std::remove_if(fireballs.begin(), fireballs.end(),
		[](const std::unique_ptr<Fireball>& fireball) {
			return fireball->outOfRange() || fireball->toRemove;
		}), fireballs.end());
	counter = fireballs.size();
	
	GameObject::update(ms);
}

void Necromancer::debugDrawNec() {
	graphics::Brush debug_brush;
	SETCOLOR(debug_brush.fill_color, 1, 0.3f, 0);
	SETCOLOR(debug_brush.outline_color, 1, 0.1f, 0);
	debug_brush.fill_opacity = 0.1f;
	debug_brush.outline_opacity = 1.0f;
	float x = getPosX() + m_state->m_global_offset_x;
	float y = getPosY() + m_state->m_global_offset_y;
	graphics::drawRect(x, y, m_width, m_height, debug_brush);
	char s[20];
	sprintf_s(s, "(%5.2f, %5.2f", m_pos_x, m_pos_y);
	SETCOLOR(debug_brush.fill_color, 1, 0, 0);
	debug_brush.fill_opacity = 1.0f;
	graphics::drawText(m_state->getCanvasWidth() * 0.5f - 0.4f, m_state->getCanvasHeight() * 0.5f - 0.6f, 0.15f, s, debug_brush);
}