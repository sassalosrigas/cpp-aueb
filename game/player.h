#pragma once
#include "gameobject.h"
#include "box.h"
#include <sgg/graphics.h>
#include "level.h"
#include "ribbon.h"
#include <memory>
#include <vector>
#include <iostream>
using namespace std;


class Player : public GameObject, public Box
{
	graphics::Brush m_brush_player;
	std::vector<std::string> m_spritesR;
	std::vector<std::string> m_spritesL;
	const float m_gravity = 8.0f;
	const float m_accel_vertical = 4.5f;
	const float m_accel_horizontial = 3.0f;
	const float m_max_velocity = 3.0f;
	void movePlayer(float ms);
	bool projActive = false;
	int counter = 0;
	bool left = false;
	bool can_shoot = false;
	float shoot_cooldown = 0.0f;
	bool canTakeDMG = true;


public:
	bool collisionDet = false;
	float health_self = 100.0f;
	float m_vx = 0.0f;
	float m_vy = 0.0f;
	std::vector<std::unique_ptr<Ribbon>> ribbons;
	Player(std::string name) : GameObject(name) {}
	void init() override;
	void draw() override;
	void update(float ms) override;
	float PlayerPosX() {
		return m_pos_x;
	}
	float PlayerPosY() {
		return m_pos_y;
	}
	void takeDamage(float dmg) {
		if (canTakeDMG) {
			health_self -= dmg;
		}
	}
	
protected:
	void debugDraw();
	void drawHealth();
	
};