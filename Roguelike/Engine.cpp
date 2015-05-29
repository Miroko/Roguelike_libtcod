#include "Engine.h"
#include "iostream"

void Engine::startMainLoop(){
	while (!TCODConsole::isWindowClosed())
	{
		render();
		update(TCODConsole::checkForKeypress(TCOD_KEY_PRESSED), TCODSystem::getLastFrameLength());
	}
}

void Engine::update(TCOD_key_t key, float elapsed){
	DynamicObject *playerObject = world.playerObject.get();
	Point2D moveLocation = playerObject->location;
	switch (key.vk)
	{
	case TCODK_KP4:
		moveLocation.x -= 1;
		world.moveDynamicObject(*playerObject, moveLocation);
		break;
	case TCODK_KP8:
		moveLocation.y -= 1;
		world.moveDynamicObject(*playerObject, moveLocation);
		break;
	case TCODK_KP6: 
		moveLocation.x += 1;
		world.moveDynamicObject(*playerObject, moveLocation);
		break;
	case TCODK_KP2:
		moveLocation.y += 1;
		world.moveDynamicObject(*playerObject, moveLocation);
		break;
	default:
		break;
	}

	world.update(elapsed);

	camera.centerOn(world.playerObject->location);
}

void Engine::render(){
	TCODConsole::root->clear();

	for (int x = camera.location.x; x < camera.location.x + camera.getWidth(); x++){		
		for (int y = camera.location.y; y < camera.location.y + camera.getHeight(); y++){
			if (world.area.bounds.contains(Point2D(x, y))){
				world.area.staticObjects[x][y]->render(x - camera.location.x, y - camera.location.y);
			}
		}
	}

	for (auto &dynamicObject : world.area.dynamicObjects){
		int renderX = dynamicObject->location.x - camera.location.x;
		int renderY = dynamicObject->location.y - camera.location.y;
		dynamicObject->render(renderX, renderY);
	}
	
	TCODConsole::flush();
}