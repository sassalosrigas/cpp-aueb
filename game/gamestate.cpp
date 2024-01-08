#include "gamestate.h"
#include "level.h"
#include "player.h"

GameState::GameState()
{
}

void GameState::init()
{
	m_current_level = new Level();
	m_current_level->init();

	m_player = new Player("Player");
	m_player->init();

	graphics::preloadBitmaps(getAssetPath());
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

	if (!m_current_level)
		return;

	m_current_level->update(ms);
}

GameState* GameState::getInstance()
{
	if (m_instance == nullptr)
		m_instance = new GameState();

	return m_instance;
}

GameState::~GameState()
{
	if(m_player)
		delete m_player;
	if(m_current_level)
		delete m_current_level;
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