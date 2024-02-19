#pragma once 
#include "box.h"
#include "level.h"
#include "gamestate.h"
#include "player.h"
#include <sgg/graphics.h>
#include "util.h"
#include <chrono>
#include <thread>
#include "flyingpuppy.h"
#include "ribbon.h"
#include <memory>
#include <vector>
#include "necromancer.h"
#include "healthpack.h"
#include "portal.h"
#include "coin.h"
#include "lever.h"
#include "immortalguardian.h"
#include <iostream>
using namespace std;


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
	auto* player = m_state->getPlayer();

	for (int i = 0; i<puppies.size(); i++) {
		auto& p = puppies[i];
		if (player->intersect(*p)) {
			graphics::playSound("assets\\hurt.mp3", 0.25f, false);
			player->health_self -= 0.25f;
			printf("*");
			break;
		}
	}
	for (auto& h : health_packs) {
		if (player->intersect(*h)) {
			if (player->health_self + 30.0f > 100.0f) {
				player->health_self = 100.0f;
			}
			else {
				player->health_self += 30.0f;
			}
			graphics::playSound("assets\\heal.mp3", 0.25f, false);
			h->toRemove = true;
		}
	}
	for (auto& l : levers) {
		if (player->intersect(*l)) {
			guardians.clear();
			l->opened = true;
		}
	}
	for (const auto& ribbon : player->ribbons) {
		for (auto& puppy : puppies) {
			if (ribbon->intersect(*puppy)) {
				graphics::playSound("assets\\hurt.mp3", 0.25f, false);
				printf("*");
				puppy->health_p -= 50.0f;
				cout << puppy->health_p;
				ribbon->toRemove = true;
				break;
			}
		}
		for (auto& block : m_blocks) {
			if (ribbon->intersect(block)) {
				ribbon->toRemove = true;
				break;
			}
		}
		for (auto& necromancer : necromancers) {
			if (ribbon->intersect(*necromancer)) {
				graphics::playSound("assets\\hurt.mp3", 0.25f, false);
				necromancer->health_n -= 50.0f;
				if (necromancer->health_n <= 0.0f) {
					necromancer->dying = true;
				}
				ribbon->toRemove = true;
				break;
			}
		}
		for (auto& g : guardians) {
			if (ribbon->intersect(*g)) {
				graphics::playSound("assets\\hurt.mp3", 0.25f, false);
				ribbon->toRemove = true;
			}
		}
	}
		for (auto& necromancer : necromancers) {
			for (const auto& fireball : necromancer->fireballs) {
				if (fireball->intersect(*player)) {
					graphics::playSound("assets\\hurt.mp3", 0.25f, false);
					if (player->health_self > 0.0f) {
						player->health_self-=15.0f;					
					}
					fireball->toRemove = true;
					break;
				}
				for (auto& block : m_blocks) {
					if (fireball->intersect(block)) {
						fireball->toRemove = true;;
						break;
					}
				}
			}

		}
		for (auto& p : portals) {
			if (player->intersect(*p)) {
					curr_l++;
					health_packs.clear();
					puppies.clear();
					m_blocks.clear();
					necromancers.clear();
					portals.clear();
					init();
					m_state->getPlayer()->init();			
	
			}
		}
		for (auto& c : coins) {
			if (player->intersect(*c)) {
				coins.clear();
				won = true;
			}
		}
		for (auto& g : guardians) {
			if (player->intersect(*g)) {
				player->health_self = 0.0f;
			}
		}
		for (auto& block : m_blocks) {
			float offset = 0.0f;
			if (offset = player->intersectUp(block)) {
				m_state->getPlayer()->m_pos_y -= offset;
				m_state->getPlayer()->m_vy = 0.0f;
				break;
			}
		}

		for (auto& block : m_blocks) {
			float offset = 0.0f;
			if (offset = player->intersectDown(block)) {
				m_state->getPlayer()->m_pos_y += offset;
				m_state->getPlayer()->m_vy = 0.0f;
				break;
			}
		}
		for (auto& block : m_blocks)
		{
			float offset = 0.0f;
			if (offset = player->intersectSideways(block))
			{
				player->m_pos_x += offset * 2.0f;
				player->m_vx = 0.0f;
				const float gravity = 0.2f;
				player->m_pos_y += gravity;
				player->collisionDet = true;
				break;
			}
		}

	
		player->collisionDet = false;
}

void Level::update(float ms)
{
	if (!m_state->getPlayer()->isDead() && !won) {
		if (m_state->getPlayer()->isActive())
			m_state->getPlayer()->update(ms);
		for (auto& p : puppies) {
			p->update(ms);
		}
		for (auto& n : necromancers) {
			n->update(ms);
		}
		for (auto& g : guardians) {
			g->update(ms);
		}
		for (auto& c : coins) {
			c->update(ms);
		}
		for (auto& l : levers) {
			l->update(ms);
		}
		int c = 0;
		puppies.erase(std::remove_if(puppies.begin(), puppies.end(),
			[&c](const std::unique_ptr<FlyingPuppy>& puppy) {
				if (puppy->isDead()) {
					c += 15;
				}
				return puppy->isDead();
			}), puppies.end());

		necromancers.erase(std::remove_if(necromancers.begin(), necromancers.end(),
			[&c](const std::unique_ptr<Necromancer>& necromancer) {
				if (necromancer->isDead()) {
					c += 30;
				}
				return necromancer->isDead();
			}), necromancers.end());
		score += c;
		health_packs.erase(std::remove_if(health_packs.begin(), health_packs.end(),
			[&c](const std::unique_ptr<HealthPack>& healthpack) {
				return healthpack->toRemove;
			}), health_packs.end());
		checkCollisions();
		GameObject::update(ms);
	}
}

void Level::draw()
{
	float w = m_state->getCanvasWidth();
	float h = m_state->getCanvasHeight();

	float offset_x = m_state->m_global_offset_x / 2.0f + w / 2.0f;
	float offset_y = m_state->m_global_offset_y / 2.0f + h / 2.0f;
	
	//if (m_state->getPlayer()->isDead()) {
		//SETCOLOR(m_brush_background.fill_color, 1, 1, 1);
		//m_brush_background.fill_opacity = 0.5f;
	//}
	
	graphics::drawRect(offset_x, offset_y, 2.0f * w, 4.0f * w, m_brush_background);
	//draw background
	//draw blocks
	for (int i = 0; i < m_blocks.size(); i++)
	{
		drawBlock(i);
	}

	for (auto& p : puppies) {
		p->draw();
	}
	
	for (auto& n : necromancers) {
		if (n->toDelete == false) {
			n->draw();
		}
	}
	for (auto& h : health_packs) {
		h->draw();
	}
	for (auto& p : portals) {
		p->draw();
	}
	for (auto& g : guardians) {
		g->draw();
	}
	for (auto& c : coins) {
		c->draw();
	}
	for (auto& l : levers) {
		l->draw();
	}
	drawScore();
	graphics::Brush br_help;
	SETCOLOR(br_help.fill_color, 1.0f, 1.0f, 1.0f);
	br_help.fill_opacity = 1.0f;
	graphics::drawText(m_state->getCanvasWidth() * 0.5f - 2.0f, m_state->getCanvasHeight() * 0.5f + 2.5f, 0.2f, "H: HELP", br_help);
	if (graphics::getKeyState(graphics::SCANCODE_H)) {
		
		graphics::drawText(m_state->getCanvasWidth() * 0.5f, m_state->getCanvasHeight() * 0.5f + 2.0f, 0.2f, "MOVE: W,A,D", br_help);
		graphics::drawText(m_state->getCanvasWidth() * 0.5f, m_state->getCanvasHeight() * 0.5f + 2.2f, 0.2f, "SHOOT: SPACE", br_help);
	}
 
	if (m_state->getPlayer()->isActive()) {
		m_state->getPlayer()->draw();
	}
	if (m_state->getPlayer()->isDead()) {
		if (!deathsound) {
			graphics::stopMusic();
			graphics::playSound("assets\\gameover.wav", 0.5f, false);
			deathsound = true;
		}
		graphics::Brush br_end;
		br_end.outline_opacity = 0.0f;
		br_end.fill_opacity = 1.0f;
		br_end.texture = m_state->getFullAssetPath("gameover.png");
		SETCOLOR(m_brush_background.fill_color, 1, 1, 1);
		m_brush_background.fill_opacity = 0.5f;
		graphics::Brush br_score;
		SETCOLOR(br_score.fill_color, 1.0f, 1.0f, 1.0f);
		br_score.fill_opacity = 1.0f;
		char s[20];
		sprintf_s(s, sizeof(s), "Score: %d", score);
		graphics::drawRect(m_state->getCanvasWidth() * 0.5f, m_state->getCanvasHeight() * 0.5f - 1.0f, 1.5f, 1.5f, br_end);
		graphics::drawText(m_state->getCanvasWidth() * 0.5f - 1.0f, m_state->getCanvasHeight() * 0.5f + 1.0f, 0.35f, s, br_score);
		graphics::drawRect(offset_x, offset_y, 2.0f * w, 4.0f * w, m_brush_background);
	}
	else if (won) {
		if (!winsound) {
			graphics::stopMusic();
			graphics::playSound("assets\\win.mp3", 0.5f, false);
			winsound = true;
		}
		graphics::Brush br_end;
		br_end.outline_opacity = 0.0f;
		br_end.fill_opacity = 1.0f;
		br_end.texture = m_state->getFullAssetPath("youwon.png");
		SETCOLOR(m_brush_background.fill_color, 1, 1, 1);
		m_brush_background.fill_opacity = 0.5f;
		graphics::Brush br_score;
		SETCOLOR(br_score.fill_color, 1.0f, 1.0f, 1.0f);
		br_score.fill_opacity = 1.0f;
		char s[20];
		sprintf_s(s, sizeof(s), "Score: %d", score);
		graphics::drawRect(m_state->getCanvasWidth() * 0.5f, m_state->getCanvasHeight() * 0.5f - 1.0f, 2.0f, 0.8f, br_end);
		graphics::drawText(m_state->getCanvasWidth() * 0.5f - 1.0f, m_state->getCanvasHeight() * 0.5f + 1.0f, 0.35f, s, br_score);
		graphics::drawRect(offset_x, offset_y, 2.0f * w, 4.0f * w, m_brush_background);
	}
	
}

void Level::init()
{
	if (curr_l == 0) {
		for (int i = -2; i <= 7; i++) {
			m_blocks.push_back(Box(i, 15, 1.0f, 1.0f));
			m_blocks.push_back(Box(i, -1, 1.0f, 1.0f));
		}
		for (int i = 0; i <= 15; i++) {
			m_blocks.push_back(Box(8, i, 1.0f, 1.0f));
			m_blocks.push_back(Box(-3, i, 1.0f, 1.0f));
		}
		m_blocks.push_back(Box(6, 14, 1.0f, 1.0f));
		m_blocks.push_back(Box(7, 14, 1.0f, 1.0f));
		m_blocks.push_back(Box(7, 13, 1.0f, 1.0f));
		m_blocks.push_back(Box(5, 12, 1.0f, 1.0f));
		m_blocks.push_back(Box(4, 12, 1.0f, 1.0f));
		m_blocks.push_back(Box(2, 12, 1.0f, 1.0f));
		m_blocks.push_back(Box(0, 12, 1.0f, 1.0f));
		m_blocks.push_back(Box(-2, 12, 1.0f, 1.0f));
		m_blocks.push_back(Box(-2, 11, 1.0f, 1.0f));
		m_blocks.push_back(Box(-1, 12, 1.0f, 1.0f));
		m_blocks.push_back(Box(0, 10, 1.0f, 1.0f));
		m_blocks.push_back(Box(1, 12, 1.0f, 1.0f));
		m_blocks.push_back(Box(1, 9, 1.0f, 1.0f));
		m_blocks.push_back(Box(2, 9, 1.0f, 1.0f));
		m_blocks.push_back(Box(3, 9, 1.0f, 1.0f));
		m_blocks.push_back(Box(4, 9, 1.0f, 1.0f));
		m_blocks.push_back(Box(5, 9, 1.0f, 1.0f));
		m_blocks.push_back(Box(5, 8, 1.0f, 1.0f));
		m_blocks.push_back(Box(6, 8, 1.0f, 1.0f));
		m_blocks.push_back(Box(7, 7, 1.0f, 1.0f));
		m_blocks.push_back(Box(7, 8, 1.0f, 1.0f));
		m_blocks.push_back(Box(1, 10, 1.0f, 1.0f));
		m_blocks.push_back(Box(5, 6, 1.0f, 1.0f));
		m_blocks.push_back(Box(4, 5, 1.0f, 1.0f));
		m_blocks.push_back(Box(7, 4, 1.0f, 1.0f));
		m_blocks.push_back(Box(3, 4, 1.0f, 1.0f));
		m_blocks.push_back(Box(2, 3, 1.0f, 1.0f));
		m_blocks.push_back(Box(1, 3, 1.0f, 1.0f));
		m_blocks.push_back(Box(0, 3, 1.0f, 1.0f));
		m_blocks.push_back(Box(-1, 3, 1.0f, 1.0f));
		m_blocks.push_back(Box(-2, 3, 1.0f, 1.0f));
		m_blocks.push_back(Box(-2, 2, 1.0f, 1.0f));
		m_blocks.push_back(Box(0, 1, 1.0f, 1.0f));
		m_blocks.push_back(Box(1, 1, 1.0f, 1.0f));
		m_blocks.push_back(Box(2, 1, 1.0f, 1.0f));
		m_blocks.push_back(Box(3, 1, 1.0f, 1.0f));
		m_blocks.push_back(Box(4, 1, 1.0f, 1.0f));
		m_blocks.push_back(Box(5, 1, 1.0f, 1.0f));
		m_blocks.push_back(Box(6, 1, 1.0f, 1.0f));
		m_blocks.push_back(Box(7, 1, 1.0f, 1.0f));
		m_blocks.push_back(Box(-2, 8, 1.0f, 1.0f));
		m_blocks.push_back(Box(4, 6, 1.0f, 1.0f));
		m_blocks.push_back(Box(3, 5, 1.0f, 1.0f));
		m_blocks.push_back(Box(2, 4, 1.0f, 1.0f));

		portals.push_back(std::make_unique<Portal>(7.0f, 0.0f, 1.0f, 1.0f));
		for (auto& p : portals) {
			p->init();
		}
		

		health_packs.push_back(std::make_unique<HealthPack>(-2.0f, 10.0f, 1.0f, 1.0f));
		health_packs.push_back(std::make_unique<HealthPack>(7.0f, 6.0f, 1.0f, 1.0f));
		health_packs.push_back(std::make_unique<HealthPack>(-2.0f, 10.0f, 1.0f, 1.0f));
		health_packs.push_back(std::make_unique<HealthPack>(-2.0f, 1.0f, 1.0f, 1.0f));

		for (auto& h : health_packs) {
			h->init();
		}

		puppies.push_back(std::make_unique<FlyingPuppy>(1.0f, 14.0f, 1.0f, 1.0f, true, 4.0f));
		puppies.push_back(std::make_unique<FlyingPuppy>(1.0f, 8.0f, 1.0f, 1.0f, true, 3.0f));
		puppies.push_back(std::make_unique<FlyingPuppy>(-1.0f, 2.0f, 1.0f, 1.0f, true, 3.0f));
		puppies.push_back(std::make_unique<FlyingPuppy>(5.0f, .0f, 1.0f, 1.0f, false, 4.0f));
		for (auto& p : puppies) {
			p->init();
		}
		necromancers.push_back(std::make_unique<Necromancer>(6.0f, 13.0f, 1.0f, 1.0f, false));
		necromancers.push_back(std::make_unique<Necromancer>(-1.0f, 11.0f, 1.0f, 1.0f, true));
		necromancers.push_back(std::make_unique<Necromancer>(7, 3, 1.0f, 1.0f, false));
		necromancers.push_back(std::make_unique<Necromancer>(-2, 7, 1.0f, 1.0f, true));

		for (auto& n : necromancers) {
			n->init();
		}


		for (int i = 0; i < m_blocks.size(); i++) {
			m_block_names.push_back("block.png");
		}
		m_brush_block.outline_opacity = 0.0f;
		m_brush_block_debug.fill_opacity = 0.1f;
		SETCOLOR(m_brush_block_debug.fill_color, 0.2f, 1.0f, 0.1f);
		SETCOLOR(m_brush_block.outline_color, 0.3f, 1.0f, 0.2f);
	}
	else if (curr_l == 1){
		for (int i = -2; i <= 7; i++) {
			m_blocks.push_back(Box(i, 15, 1.0f, 1.0f));
			m_blocks.push_back(Box(i, -1, 1.0f, 1.0f));
		}
		for (int i = 0; i <= 15; i++) {
			m_blocks.push_back(Box(8, i, 1.0f, 1.0f));
			m_blocks.push_back(Box(-3, i, 1.0f, 1.0f));
		}
		m_blocks.push_back(Box(0.0f, 14.0f, 1.0f, 1.0f));
		m_blocks.push_back(Box(1.0f, 13.0f, 1.0f, 1.0f));
		m_blocks.push_back(Box(2.0f, 13.0f, 1.0f, 1.0f));
		m_blocks.push_back(Box(3.0f, 13.0f, 1.0f, 1.0f));
		m_blocks.push_back(Box(1.0f, 14.0f, 1.0f, 1.0f));
		m_blocks.push_back(Box(4.0f, 13.0f, 1.0f, 1.0f));
		m_blocks.push_back(Box(5.0f, 13.0f, 1.0f, 1.0f));
		m_blocks.push_back(Box(6.0f, 12.0f, 1.0f, 1.0f));
		m_blocks.push_back(Box(6.0f, 13.0f, 1.0f, 1.0f));
		m_blocks.push_back(Box(7.0f, 12.0f, 1.0f, 1.0f));
		m_blocks.push_back(Box(5.0f, 10.0f, 1.0f, 1.0f));
		m_blocks.push_back(Box(3.0f, 10.0f, 1.0f, 1.0f));
		m_blocks.push_back(Box(1.0f, 10.0f, 1.0f, 1.0f));
		m_blocks.push_back(Box(-1.0f, 10.0f, 1.0f, 1.0f));
		m_blocks.push_back(Box(-2.0f, 10.0f, 1.0f, 1.0f));
		m_blocks.push_back(Box(0.0f, 10.0f, 1.0f, 1.0f));
		m_blocks.push_back(Box(1.0f, 9.0f, 1.0f, 1.0f));
		m_blocks.push_back(Box(0.0f, 9.0f, 1.0f, 1.0f));
		m_blocks.push_back(Box(0.0f, 8.0f, 1.0f, 1.0f));
		m_blocks.push_back(Box(-1.0f, 8.0f, 1.0f, 1.0f));
		m_blocks.push_back(Box(-2.0f, 8.0f, 1.0f, 1.0f));
		m_blocks.push_back(Box(-2.0f, 7.0f, 1.0f, 1.0f));
		m_blocks.push_back(Box(0.0f, 6.0f, 1.0f, 1.0f));
		m_blocks.push_back(Box(1.0f, 6.0f, 1.0f, 1.0f));
		m_blocks.push_back(Box(2.0f, 6.0f, 1.0f, 1.0f));
		m_blocks.push_back(Box(3.0f, 6.0f, 1.0f, 1.0f));
		m_blocks.push_back(Box(4.0f, 6.0f, 1.0f, 1.0f));
		m_blocks.push_back(Box(5.0f, 6.0f, 1.0f, 1.0f));
		m_blocks.push_back(Box(6.0f, 6.0f, 1.0f, 1.0f));
		m_blocks.push_back(Box(7.0f, 6.0f, 1.0f, 1.0f));
		m_blocks.push_back(Box(1.0f, 5.0f, 1.0f, 1.0f));
		m_blocks.push_back(Box(3.0f, 5.0f, 1.0f, 1.0f));
		m_blocks.push_back(Box(5.0f, 5.0f, 1.0f, 1.0f));
		m_blocks.push_back(Box(7.0f, 5.0f, 1.0f, 1.0f));
		m_blocks.push_back(Box(7.0f, 11.0f, 1.0f, 1.0f));
		m_blocks.push_back(Box(6.0f, 5.0f, 1.0f, 1.0f));
		m_blocks.push_back(Box(6.0f, 4.0f, 1.0f, 1.0f));
		m_blocks.push_back(Box(7.0f, 4.0f, 1.0f, 1.0f));
		m_blocks.push_back(Box(7.0f, 3.0f, 1.0f, 1.0f));
		m_blocks.push_back(Box(5.0f, 2.0f, 1.0f, 1.0f));
		m_blocks.push_back(Box(4.0f, 1.0f, 1.0f, 1.0f));
		m_blocks.push_back(Box(3.0f, 2.0f, 1.0f, 1.0f));
		m_blocks.push_back(Box(1.0f, 2.0f, 1.0f, 1.0f));
		m_blocks.push_back(Box(2.0f, 2.0f, 1.0f, 1.0f));
		m_blocks.push_back(Box(0.0f, -1.0f, 1.0f, 1.0f));
		m_blocks.push_back(Box(0.0f, 3.0f, 1.0f, 1.0f));
		m_blocks.push_back(Box(-2.0f, 3.0f, 1.0f, 1.0f));
		m_blocks.push_back(Box(-1.0f, 3.0f, 1.0f, 1.0f));
		m_blocks.push_back(Box(4.0f, 2.0f, 1.0f, 1.0f));
		m_blocks.push_back(Box(-2.0f, 2.0f, 1.0f, 1.0f));
		m_blocks.push_back(Box(-2.0f, 1.0f, 1.0f, 1.0f));




		

		for (int i = 0; i < m_blocks.size(); i++) {
			m_block_names.push_back("block.png");
		}

		puppies.push_back(std::make_unique<FlyingPuppy>(1.0f, 12.0f, 1.0f, 1.0f, true, 4.0f));
		puppies.push_back(std::make_unique<FlyingPuppy>(-1.0f, 9.0f, 1.0f, 1.0f, true, 7.0f));
		puppies.push_back(std::make_unique<FlyingPuppy>(5.0f, 4.0f, 1.0f, 1.0f, false, 5.0f));
		puppies.push_back(std::make_unique<FlyingPuppy>(1.0f, 1.0f, 1.0f, 1.0f, true, 2.0f));

		for (auto& p : puppies) {
			p->init();
		}
		necromancers.push_back(std::make_unique<Necromancer>(1.0f, 8.0f, 1.0f, 1.0f, true));
		necromancers.push_back(std::make_unique<Necromancer>(5.0f, 4.0f, 1.0f, 1.0f, false));
		necromancers.push_back(std::make_unique<Necromancer>(-2.0f, 0.0f, 1.0f, 1.0f, true));
		for (auto& n : necromancers) {
			n->init();
		}
		health_packs.push_back(std::make_unique<HealthPack>(-2.0f, 6.0f, 1.0f, 1.0f));
		health_packs.push_back(std::make_unique<HealthPack>(4.0f, 5.0f, 1.0f, 1.0f));
		for (auto& h : health_packs) {
			h->init();
		}
		portals.push_back(std::make_unique<Portal>(-1.0f, 2.0f, 1.0f, 1.0f));
		for (auto& p : portals) {
			p->init();
		}
		m_brush_block.outline_opacity = 0.0f;
		m_brush_block_debug.fill_opacity = 0.1f;
		SETCOLOR(m_brush_block_debug.fill_color, 0.2f, 1.0f, 0.1f);
		SETCOLOR(m_brush_block.outline_color, 0.3f, 1.0f, 0.2f);
	}
	else {
		for (int i = -2; i <= 7; i++) {
			m_blocks.push_back(Box(i, 15, 1.0f, 1.0f));
			m_blocks.push_back(Box(i, -1, 1.0f, 1.0f));
		}
		for (int i = 0; i <= 15; i++) {
			m_blocks.push_back(Box(8, i, 1.0f, 1.0f));
			m_blocks.push_back(Box(-3, i, 1.0f, 1.0f));
		}
		m_blocks.push_back(Box(-2.0f, 13.0f, 1.0f, 1.0f));
		m_blocks.push_back(Box(-2.0f, 11.0f, 1.0f, 1.0f));
		m_blocks.push_back(Box(1.0f, 14.0f, 1.0f, 1.0f));
		m_blocks.push_back(Box(2.0f, 14.0f, 1.0f, 1.0f));
		m_blocks.push_back(Box(2.0f, 13.0f, 1.0f, 1.0f));
		m_blocks.push_back(Box(3.0f, 13.0f, 1.0f, 1.0f));
		m_blocks.push_back(Box(3.0f, 12.0f, 1.0f, 1.0f));
		m_blocks.push_back(Box(4.0f, 12.0f, 1.0f, 1.0f));
		m_blocks.push_back(Box(4.0f, 11.0f, 1.0f, 1.0f));
		m_blocks.push_back(Box(5.0f, 11.0f, 1.0f, 1.0f));
		m_blocks.push_back(Box(5.0f, 10.0f, 1.0f, 1.0f));
		m_blocks.push_back(Box(6.0f, 10.0f, 1.0f, 1.0f));
		m_blocks.push_back(Box(6.0f, 9.0f, 1.0f, 1.0f));
		m_blocks.push_back(Box(7.0f, 9.0f, 1.0f, 1.0f));
		m_blocks.push_back(Box(4.0f, 8.0f, 1.0f, 1.0f));
		m_blocks.push_back(Box(3.0f, 8.0f, 1.0f, 1.0f));
		m_blocks.push_back(Box(3.0f, 7.0f, 1.0f, 1.0f));
		m_blocks.push_back(Box(2.0f, 6.0f, 1.0f, 1.0f));
		m_blocks.push_back(Box(2.0f, 7.0f, 1.0f, 1.0f));
		m_blocks.push_back(Box(1.0f, 6.0f, 1.0f, 1.0f));
		m_blocks.push_back(Box(0.0f, 6.0f, 1.0f, 1.0f));
		m_blocks.push_back(Box(-1.0f, 6.0f, 1.0f, 1.0f));
		m_blocks.push_back(Box(-2.0f, 6.0f, 1.0f, 1.0f));
		m_blocks.push_back(Box(4.0f, 5.0f, 1.0f, 1.0f));
		m_blocks.push_back(Box(5.0f, 5.0f, 1.0f, 1.0f));
		m_blocks.push_back(Box(6.0f, 5.0f, 1.0f, 1.0f));
		m_blocks.push_back(Box(6.0f, 4.0f, 1.0f, 1.0f));
		m_blocks.push_back(Box(7.0f, 3.0f, 1.0f, 1.0f));
		m_blocks.push_back(Box(7.0f, 4.0f, 1.0f, 1.0f));
		m_blocks.push_back(Box(6.0f, 5.0f, 1.0f, 1.0f));
		m_blocks.push_back(Box(5.0f, 2.0f, 1.0f, 1.0f));
		m_blocks.push_back(Box(4.0f, 1.0f, 1.0f, 1.0f));
		m_blocks.push_back(Box(4.0f, 2.0f, 1.0f, 1.0f));
		m_blocks.push_back(Box(3.0f, 1.0f, 1.0f, 1.0f));
		m_blocks.push_back(Box(2.0f, 1.0f, 1.0f, 1.0f));
		m_blocks.push_back(Box(1.0f, 1.0f, 1.0f, 1.0f));
		m_blocks.push_back(Box(0.0f, 1.0f, 1.0f, 1.0f));
		m_blocks.push_back(Box(0.0f, 0.0f, 1.0f, 1.0f));

		for (int i = 0; i < m_blocks.size(); i++) {
			m_block_names.push_back("block.png");
		}
		guardians.push_back(std::make_unique<ImmortalGuardian>(-1.0f, 5.0f, 1.0f, 1.0f));
		necromancers.push_back(std::make_unique<Necromancer>(-2.0f, 12.0f, 1.0f, 1.0f,true));
		necromancers.push_back(std::make_unique<Necromancer>(-2.0f, 10.0f, 1.0f, 1.0f, true));
		necromancers.push_back(std::make_unique<Necromancer>(2.0f, 0.0f, 1.0f, 1.0f, true));
		health_packs.push_back(std::make_unique<HealthPack>(7.0f, 8.0f, 1.0f, 1.0f));
		coins.push_back(std::make_unique<Coin>(-2.0f, 5.0f, 1.0f, 1.0f));
		levers.push_back(std::make_unique<Lever>(1.0f, 0.2f, 1.0f, 1.0f));
		puppies.push_back(std::make_unique<FlyingPuppy>(5.0f, 4.0f, 1.0f, 1.0f, false, 1.0f));
		m_brush_block.outline_opacity = 0.0f;
		m_brush_block_debug.fill_opacity = 0.1f;
		SETCOLOR(m_brush_block_debug.fill_color, 0.2f, 1.0f, 0.1f);
		SETCOLOR(m_brush_block.outline_color, 0.3f, 1.0f, 0.2f);
	}

	for (auto& p : puppies) {
		p->init();
	}
	for (auto& g : guardians) {
		g->init();
	}
	for (auto& n : necromancers) {
		n->init();
	}
	for (auto& p : portals) {
		p->init();
	}
	for (auto& h : health_packs) {
		h->init();
	}
	for (auto& p : puppies) {
		p->init();
	}
	for (auto& c : coins) {
		c->init();
	}
	for (auto& l : levers) {
		l->init();
	}
	


}

void Level::drawScore() {
	graphics::Brush br_score;
	SETCOLOR(br_score.fill_color, 1.0f, 1.0f, 1.0f);
	br_score.fill_opacity = 1.0f;
	char s[20];
	sprintf_s(s, sizeof(s), "%d", score);
	graphics::drawText(m_state->getCanvasWidth() * 0.5f + 2.0f, m_state->getCanvasHeight() * 0.5f - 2.0f, 0.35f, s, br_score);
}
std::vector<Box> getVec() {
	Level l;
	return l.m_blocks;
}

Level::Level(const std::string& name)
{
	m_brush_background.outline_opacity = 0.0f;
	m_brush_background.texture = m_state->getFullAssetPath("background.png");
	
}

Level::~Level()
{
	/*health_packs.erase(std::remove_if(health_packs.begin(), health_packs.end(), true, health_packs.end());
	necromancers.erase(std::remove_if(necromancers.begin(), necromancers.end(), true, necromancers.end());
	puppies.erase(std::remove_if(puppies.begin(), puppies.end(), true,puppies.end());
	m_blocks.erase(std::remove_if(m_blocks.begin(), m_blocks.end(), true, m_blocks.end());
	*/
	health_packs.clear();
	m_blocks.clear();
	puppies.clear();
	necromancers.clear();
	init();
	m_state->getPlayer()->init();

}
