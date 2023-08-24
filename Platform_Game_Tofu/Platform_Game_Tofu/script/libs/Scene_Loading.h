#pragma once
#include "Scene.h"
#include "Common.h"
#include<map>
#include<memory>
#include <deque>

#include "EntityManager.h"

class Scene_Loading : public Scene
{
protected:
	std::string m_levelpath;
	float m_framecounter = 0;
	int m_amoutOfLives = 3;
	int m_amountOfDash = 3;
	int m_amountOfSpheres = 0;

	void init();
	void update();
	void onEnd();
	void sDoAction(const Action& action);

public:
	Scene_Loading(GameEngine* gameEngine = nullptr);
	Scene_Loading(GameEngine* gameEngine, const std::string& levelPath, int amoutOfLives, int amountOfDash, int amountOfSpheres);
	void sRender();
};