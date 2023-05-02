#pragma once
#include "Scene.h"
#include "Common.h"
#include<map>
#include<memory>
#include <deque>

#include "EntityManager.h"

class Scene_LevelEditor : public Scene
{
protected:
	void init();
	void update();
	void onEnd();
	void sDoAction(const Action& action);

public:
	Scene_LevelEditor(GameEngine* gameEngine = nullptr);
	void sRender();
};