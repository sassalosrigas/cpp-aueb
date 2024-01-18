#include "gamestate.h"
#include "level.h"
#include "player.h"
#include <thread>
#include <chrono>
#include "flyingpuppy.h"

GameState::GameState()
{
}
GameState::~GameState()
{
	if (m_current_level)
		delete m_current_level;
}
bool GameState::init()
{
	m_current_level = new Level("1.lvl");
	m_current_level->init();

	m_player = new Player("Player");
	m_player->init();
	graphics::preloadBitmaps(getAssetPath());
	return true;
}

void GameState::draw()
{
	if (!m_current_level)
		return;

	m_current_level->draw();
}

void GameState::update(float ms)
{
	if (ms > 500)
		return;
	float sleep_time = std::max(0.0f, 17.0f - ms);
	if(sleep_time > 0.0f){
		std::this_thread::sleep_for(std::chrono::duration<float, std::milli>(sleep_time));
	}
	if (!m_current_level)
		return;

	m_current_level->update(ms);

	m_debug_mode = graphics::getKeyState(graphics::SCANCODE_0);
}

GameState* GameState::getInstance()
{
	if (!m_instance)
	{
		m_instance = new GameState();
	}
	return m_instance;
}

/*GameState::~GameState()
{
	if(m_player)
		delete m_player;
	if(m_current_level)
		delete m_current_level;
}*/
Level* GameState::getLevel() const{
	return m_current_level;
}

std::string GameState::getAssetPath()
{
	return m_asset_path;
}

std::string GameState::getFullAssetPath(std::string asset)
{
	return m_asset_path + asset;
}

GameState* GameState::m_instance = nullptr;


