#include "sgg/graphics.h"
#include <stdio.h>
#include "util.h"
#include <string>

struct GameState
{
	std::string m_asset_path = "assets\\";
	float m_canvas_width = 8.0f;
	float m_canvas_height = 8.0f;

	graphics::Brush m_brush_background;
	graphics::Brush m_brush_player;

	float m_player_x = m_canvas_width / 2.0f;
	float m_player_y = m_canvas_height / 2.0f;
	float m_player_size = 1.0f;
};

GameState state;

void init()
{
	SETCOLOR(state.m_brush_player.fill_color, 1.0f, 1.0f, 1.0f);
	state.m_brush_player.fill_opacity = 1.0f;
	state.m_brush_player.outline_opacity = 0.0f;
	state.m_brush_player.texture = state.m_asset_path + "player.png";

	SETCOLOR(state.m_brush_background.fill_color, 1.0f, 1.0f, 1.0f);
	state.m_brush_background.outline_opacity = 0.0f;
	state.m_brush_background.texture = state.m_asset_path + "background.png";
	printf("%s\n", state.m_brush_background.texture.c_str());
}

void draw() 
{
	graphics::drawRect(state.m_canvas_width / 2.0f, state.m_canvas_height / 2.0f, state.m_canvas_width, state.m_canvas_height, state.m_brush_background);

	graphics::drawRect(state.m_player_x, state.m_player_y, state.m_player_size, state.m_player_size, state.m_brush_player);
}

void update(float ms) 
{
	float p = 0.5f + fabs(sin(graphics::getGlobalTime() / 1000.0f)) / 2.0f;

	SETCOLOR(state.m_brush_background.fill_color, p, p, p);
}

int main(int argc, char** argv) 
{
	graphics::createWindow(800, 800, "Gay Hello Kitty in Hell");

	init();

	graphics::setDrawFunction(draw);
	graphics::setUpdateFunction(update);

	graphics::setCanvasSize(state.m_canvas_width, state.m_canvas_height);
	graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_FIT);

	graphics::startMessageLoop();

	return 0;
}