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
	/*graphics::createWindow(400, 600, "INTRO");
	while (!graphics::getKeyState(graphics::SCANCODE_SPACE)) {
		if (graphics::getKeyState(graphics::SCANCODE_SPACE)) {
			break;
		}
	}
	graphics::destroyWindow();
	*/
	graphics::createWindow(800, 800, "Hello Kitty in Hell");

	init();

	graphics::setDrawFunction(draw);
	graphics::setUpdateFunction(update);

	graphics::setCanvasSize(GameState::getInstance()->getCanvasWidth(),
	GameState::getInstance()->getCanvasHeight());
	graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_FIT);
	graphics::setFont("assets\\ARCADE_N.ttf");
	graphics::playMusic("assets\\background_music.mp3", 0.25f, true, 0.0f);
	graphics::startMessageLoop();

	return 0;
	
	
}