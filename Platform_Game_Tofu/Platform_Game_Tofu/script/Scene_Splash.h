#pragma once
#include "Scene.h"
#include "Common.h"
#include<map>
#include<memory>
#include <deque>
#include "EntityManager.h"

class Scene_Splash : public Scene
{
protected:

	sf::Text m_splashTitle_1;
	sf::Text m_splashTitle_2;
	sf::Text m_splashTitle_3;

	sf::Sprite m_splashblur_1;
	sf::Sprite m_splashblur_2;
	sf::Sprite m_splashblur_3;

	sf::Texture blur_tex;

	sf::SoundBuffer m_soundbuffer;
	sf::Sound m_sound;

	float m_dist = 0;
	float m_distvel = 0;

	float m_frameCounter = 0;
	std::string m_titleText;

	void init();
	void update();
	void onEnd();
	void sDoAction(const Action& action);

public:
	Scene_Splash(GameEngine* gameEngine = nullptr);
	void sRender();
};