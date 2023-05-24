#include "GameEngine.h"
#include "Assets.h"
#include "Scene_Play.h"
#include "Scene_Menu.h"
#include "Scene_Splash.h"

#include <iostream>

GameEngine::GameEngine(const std::string& path)
{
	init(path);
}

void GameEngine::init(const std::string& path)
{
	m_assets.loadFromFile(path);

	m_window.create(sf::VideoMode(1280, 768), "Definitely not Mario");
	m_window.setFramerateLimit(60);
	m_camera_view = window().getDefaultView();
	changeScene("SPLASH", std::make_shared<Scene_Splash>(this));
}

std::shared_ptr<Scene> GameEngine::currentScene()
{
	return m_sceneMap[m_currentScene];
}

bool GameEngine::isRunning()
{
	return m_running && m_window.isOpen();
}

sf::RenderWindow& GameEngine::window()
{
	return m_window;
}
void GameEngine::run()
{
	while (isRunning())
	{
		update();
	}
}

void GameEngine::sUserInput()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			quit();
		}

		if (event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased)
		{
			if(currentScene()->getActionMap().find(event.key.code)==currentScene()->getActionMap().end())
			{
				continue;
			}

			const std::string actionType = (event.type == sf::Event::KeyPressed) ? "START" : "END";

			currentScene()->doAction(Action(currentScene()->getActionMap().at(event.key.code), actionType));
		}

		auto mousePos = sf::Mouse::getPosition(m_window);

		Vec2 mpos(mousePos.x, mousePos.y);

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			currentScene()->doAction(Action("LEFT_CLICK", "START", mpos));
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			currentScene()->doAction(Action("RIGHT_CLICK", "START", mpos));
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Middle))
		{
			currentScene()->doAction(Action("MIDDLE_CLICK", "START", mpos));
		}
		

		/*if (event.type == sf::Event::MouseMoved)
		{
			currentScene()->doAction(Action("MOUSE_MOVE", "START", Vec2(event.mouseMove.x, event.mouseMove.y)));
		}*/
	}
}

void GameEngine::changeScene(const std::string& sceneName, std::shared_ptr<Scene> scene, bool endCurrentScene)
{
	if (scene)
	{
		m_sceneMap[sceneName] = scene;
	}
	else
	{
		if (m_sceneMap.find(sceneName) == m_sceneMap.end())
		{
			std::cerr << "Warning: Scene does not exist: " << sceneName << std::endl;
			return;
		}
	}

	if (endCurrentScene)
	{
		m_sceneMap.erase(m_sceneMap.find(m_currentScene));
	}

	m_currentScene = sceneName;
}

void GameEngine::update()
{
	if (!isRunning()) { return; }

	if (m_sceneMap.empty()) { return; }

	sUserInput();
	currentScene()->simulate(m_simulationSpeed);
	currentScene()->sRender();
	m_window.display();
}

void GameEngine::quit()
{
	m_running = false;
}
Assets& GameEngine::assets()
{
	return m_assets;
}
void GameEngine::moveCameraView(const Vec2& center)
{
	m_camera_view.setCenter(sf::Vector2f(center.x, center.y));
	window().setView(m_camera_view);
}
void GameEngine::setCameraViewSize(const Vec2& size)
{
	m_camera_view.setSize(sf::Vector2f(size.x, size.y));
	window().setView(m_camera_view);
}
sf::View GameEngine::getCameraView() const 
{
	return m_camera_view;
}
Vec2 GameEngine::windowToWorld(const Vec2& windowpos)
{
	auto view = window().getView();
	float wx = view.getCenter().x - (window().getSize().x / 2);
	float wy = view.getCenter().y - (window().getSize().y / 2);

	return Vec2(windowpos.x + wx, windowpos.y + wy);
}