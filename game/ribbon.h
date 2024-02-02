#pragma once
#include "box.h"
#include <sgg/graphics.h>
#include "gamestate.h"
#include "gamestate.h"
#include "util.h"
#include "projectile.h"

class Ribbon : public Projectile {
public:
    Ribbon(float x, float y, float w, float h)
        : Projectile(x, y, w, h) {        
    }
    float y_axis = 0.0f;
    void init(float x, float y);
    void draw() override;
    void update(float ms) override;
    void debugDrawProj();
    graphics::Brush m_brush_ribbon;
    bool toRemove = false;
};
