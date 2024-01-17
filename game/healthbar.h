#pragma once

class HealthBar
{
public:
	HealthBar(int m_initial_health)

	~HealthBar();

	void setCurrentHealth(int health);
	int getCurrentHealth() const;

	void display() const;

private:
	int maxHealth;
	int currentHealth;
	int barWidth;
};