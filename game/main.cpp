#include "sgg/graphics.h"
#include "util.h"
#include "gamestate.h"

void init()
{
	GameState::getInstance()->init();
}

void draw() 
{
	GameState::getInstance()->draw();
}

void update(float ms)
{
	GameState::getInstance()->update(ms);
}

int main(int argc, char** argv) 
{
	graphics::createWindow(800, 800, "Gay Hello Kitty in Hell");

	init();

	graphics::setDrawFunction(draw);
	graphics::setUpdateFunction(update);

	graphics::setCanvasSize(GameState::getInstance()->getCanvasWidth(), 
							GameState::getInstance()->getCanvasHeight());
	graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_FIT);

	graphics::startMessageLoop();

	return 0;
}