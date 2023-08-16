#pragma once
#include "Assets.h"
#include "Common.h"
#include "Scene.h"
#include <memory>

typedef std::map<std::string, std::shared_ptr<Scene>> SceneMap;

class GameEngine
{
protected:
	sf::RenderWindow m_window;
	Assets m_assets;
	std::string m_currentScene;
	SceneMap m_sceneMap;
	size_t m_simulationSpeed = 1;
	bool m_running = true;
	sf::View m_camera_view;
	sf::Clock m_clock;
	

	void init(const std::string& path);
	void sUserInput();
	void update();
	std::shared_ptr<Scene> currentScene();

public:
	float deltaTime = 0;
	GameEngine(const std::string& path);
	void changeScene(const std::string& sceneName, std::shared_ptr<Scene> scene, bool endCurrentScene = false);
	void quit();
	void run();
	sf::RenderWindow& window();
	Assets& assets();
	bool isRunning();
	void moveCameraView(const Vec2& movement);
	void setCameraPosition(const Vec2& position);
	void setCameraViewSize(const Vec2& size);
	sf::View getCameraView() const;
	Vec2 windowToWorld(const Vec2& window);
	bool isObjectVisible(const Vec2& pos);
};