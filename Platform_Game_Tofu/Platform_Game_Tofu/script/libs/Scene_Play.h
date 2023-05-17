#pragma once
#include "Scene.h"
#include <map>
#include <memory>

#include "EntityManager.h"

class Scene_Play : public Scene
{
	struct PlayerConfig
	{
		float X, Y, CX, CY, SPEED, MAXSPEED, JUMP, GRAVITY;
		std::string WEAPON;
	};
protected:

	std::shared_ptr<Entity> m_player;
	std::string m_levelPath;
	PlayerConfig m_playerConfig;
	bool m_drawTextures = true;
	bool m_drawCollision = false;
	bool m_drawGrid = false;
	bool m_drawDebug = false;

	const Vec2 m_gridSize = { 64,64 };
	sf::Text m_gridText;

	std::vector<sf::VertexArray> m_debugGraph;

	void init(const std::string& levelPath);
	Vec2 gridToMidPixel(float gridX, float gridY, std::shared_ptr<Entity> entity);
	void loadLevel(const std::string& filename);
	void sDoAction(const Action& action);
	void update();

public:
	Scene_Play(GameEngine * gameEngine, const std::string& levelPath);
	void spawnPlayer();
	void spawnBullet(std::shared_ptr<Entity> entity);
	void sMovement();
	void sLifespan();
	void sCollision();
	void sAnimation();
	void onEnd();
	void sRender();
	void drawline(Vec2 p1,Vec2 p2);
	void debugline(Vec2 p1, Vec2 p2,sf::Color color = sf::Color::Blue);
};