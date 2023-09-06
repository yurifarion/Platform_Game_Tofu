#pragma once
#include "Scene.h"
#include "Common.h"
#include<map>
#include<memory>
#include <deque>

#include "EntityManager.h"

class Scene_Menu : public Scene
{
protected:
	std::string m_title;
	std::vector<std::string> m_menuStrings;
	std::vector<std::string> m_levelPaths;
	sf::Text m_menuText;
	size_t m_selectedMenuIndex = 0;
	sf::Sound m_sound;

	sf::Shader m_shader;
	sf::Clock m_time;

	bool m_isaudioon = true;
	float m_mastervolumetemp;

	void init();
	void update();
	void UIupdate();
	void onEnd();
	void sDoAction(const Action& action);

public:
	Scene_Menu(GameEngine* gameEngine = nullptr);
	void sRender();
};