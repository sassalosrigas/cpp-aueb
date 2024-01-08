#include "gamestate.h"

void GameState::init()
{
}

void GameState::draw()
{
}

void GameState::update(float ms)
{
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