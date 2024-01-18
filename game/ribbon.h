#pragma once
#pragma once
#include "box.h"
#include <sgg/graphics.h>
#include "gamestate.h"
#include "gamestate.h"
#include "util.h"
#include "projectile.h"

class Ribbon : public Projectile {
    Ribbon(float x, float y, float w, float h)
        : Projectile(x, y, w, h) {        
    }
};