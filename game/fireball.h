#pragma once
#include "box.h"
#include <sgg/graphics.h>
#include "gamestate.h"
#include "gamestate.h"
#include "util.h"
#include "projectile.h"

class Fireball : public Projectile {
public:
    Fireball(float x, float y, float w, float h)
        : Projectile(x, y, w, h) {
    }
    void init(float x, float y);
    void draw() override;
    void update(float ms) override;
    void debugDrawProj();
    graphics::Brush m_brush_fireball;
    bool toRemove = false;
    float speed = 0.05f;
    bool outOfRange();
    float dist = 0.0f;
};
