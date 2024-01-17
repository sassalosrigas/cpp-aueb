#pragma once

#include <sgg/graphics.h>
#include <string>

class HealthBar : public GameObject
{
private:
    float m_maxHealth;
    float m_currentHealth;
    graphics::Brush m_healthBarBrush;

public:
    HealthBar();

    void setCurrentHealth(float health);
    float getCurrentHealth() const;

    void draw(float canvasWidth, float canvasHeight) const;

    HealthBar() = default;
};
