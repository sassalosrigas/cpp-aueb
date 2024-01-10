#include <string>
#include "sgg/graphics.h"
#include <stdio.h>
#include "util.h"

struct GameState
{
private:
	std::string m_asset_path = "assets\\";
	float m_canvas_width = 6.0f;
	float m_canvas_height = 6.0f;

	graphics::Brush m_brush_bkgnd;
	graphics::Brush m_brush_player;
	float m_player_pos_x = m_canvas_width / 2.0f;
	float m_player_pos_y = m_canvas_height / 2.0f;
	float m_player_size = 1.0f;
	static GameState* m_instance;

	GameState();

	class Player* m_player = 0;
	class Level* m_current_level = 0;
	 
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
	std::string getFullAssetPath(std::string asset);

	class Player* getPlayer() { return m_player; }
};