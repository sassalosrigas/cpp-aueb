#pragma once
#include "box.h"
#include <sgg/graphics.h>
#include "gamestate.h"
//#include "level.h"
#include "gameobject.h"
#include "projectile.h"
#include "util.h"
#include "iostream"
#include "player.h"
using namespace std;


void Projectile::init(float x,float y) {
	setPosX(x);
	setPosY(y);
	m_brush_projectile.fill_opacity = 1.0f;
	m_brush_projectile.outline_opacity = 0.0f;
	m_brush_projectile.texture = m_state->getFullAssetPath("ribbon.png");
	
}

void Projectile::draw() {
		//graphics::drawRect(posX(), posY(), 1.0f, 1.0f, m_brush_projectile);
		graphics::drawRect(m_state->getCanvasHeight()*0.5f + i, m_state->getCanvasWidth() * 0.5f, 1.0f, 1.0f, m_brush_projectile);
		i += 0.1f;
}

void Projectile::update(float ms){
	setPosX(posX() + speed);
	GameObject::update(ms);
}

