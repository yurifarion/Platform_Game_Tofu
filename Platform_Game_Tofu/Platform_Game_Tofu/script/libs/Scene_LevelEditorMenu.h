#pragma once
#include "Scene.h"
#include "Common.h"
#include<map>
#include<memory>
#include <deque>

#include "EntityManager.h"
#include "tinyfiledialogs.h"

class Scene_LevelEditorMenu : public Scene
{
protected:
	std::string m_title;
	std::vector<std::string> m_menuStrings;
	std::vector<std::string> m_levelPaths;
	sf::Text m_menuText;
	size_t m_selectedMenuIndex = 0;

	void init();
	void update();
	void onEnd();
	void sDoAction(const Action& action);

public:
	Scene_LevelEditorMenu(GameEngine* gameEngine = nullptr);
	void sRender();
};