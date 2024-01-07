#pragma once
#include <string>
#include "sgg/graphics.h"

class GameState
{
private:
	std::string m_asset_path = "assets\\";
	float m_canvas_width = 6.0f;
	float m_canvas_height = 6.0f;

	static GameState* m_instance;

	GameState();

	class player* m_player = 0;
	class level* m_current_level = 0;
	 
public:
	float m_global_offset_x = 0.0f;
	float m_global_offset_y = 0.0f;
	bool m_debug_mode = false;

	void init();
	void draw();
	void update(float ms); 

	static GameState* getInstance();
	~GameState();

	float getCanvasWidth() { return m_canvas_width; }
	float getCanvasHeight() { return m_canvas_height; }

	std::string getAssetPath();
	std::string getAssetPath(std::string asset);
};