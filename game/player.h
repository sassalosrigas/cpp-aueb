#pragma once

#include "gameobject.h"
#include "box.h"
#include <sgg/graphics.h>
#include "level.h"
#include "projectile.h"

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
	
public:
	float m_vx = 0.0f;
	float m_vy = 0.0f;
	std::vector<Projectile> projectiles;
	Player(std::string name) : GameObject(name) {}
	void init() override;
	void draw() override;
	void update(float ms) override;
	/*vector<Projectile> getProj() {
		return projectiles;
	}
	*/
	float PlayerPosX() {
		return m_pos_x;
	}
	float PlayerPosY() {
		return m_pos_y;
	}

protected:
	void debugDraw();
};