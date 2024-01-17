#include "healthbar.h"
#include "util.h"
#include "gamestate.h"  

HealthBar::HealthBar() : m_currentHealth(1.0f) {
    // Set up the health bar brush (you may need to adjust color and size)
    SETCOLOR(m_healthBarBrush.fill_color, 0, 1, 0);
    m_healthBarBrush.fill_opacity = 1.0f;
    m_healthBarBrush.outline_opacity = 0.0f;
}

void HealthBar::setCurrentHealth(float health) {
    m_maxHealth = 1.0f;
    m_currentHealth = std::max(0.0f, std::min(health, m_maxHealth));
}

float HealthBar::getCurrentHealth() const {
    return m_currentHealth;
}

void HealthBar::draw(float canvasWidth, float canvasHeight) const {
    // Calculate the width of the health bar based on the current health
    float healthBarWidth = (m_currentHealth / m_maxHealth) * canvasWidth;

    // Draw the health bar at the top of the screen
    graphics::drawRect(m_state->getCanvasWidth() * 0.5f, m_state->getCanvasHeight() * 0.1f, healthBarWidth, 10.0f, m_healthBarBrush);
}
