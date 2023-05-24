#pragma once
#include "Scene.h"
#include "Common.h"
#include "Assets.h"
#include "MapLevel.h"
#include "GameEngine.h"
#include "Action.h"
#include<map>
#include<memory>
#include <deque>

#include "EntityManager.h"

class Scene_LevelEditor : public Scene
{
protected:

	int m_selectedTileID = 1;
	MapLevel m_maplevel;
	std::shared_ptr<Entity> m_selectedTile;
	const Vec2 m_gridSize = { 64,64 };
	sf::Text m_gridText;

	bool m_drawGrid = true;
	bool m_drawSelectedTile = true;
	bool m_drawUI = false;

	void init();
	void update();
	void onEnd();
	void sDoAction(const Action& action);

public:
	Scene_LevelEditor(GameEngine* gameEngine = nullptr);
	void sRender();
	void drawline(Vec2 p1, Vec2 p2);
	Vec2 gridToMidPixel(float gridX, float gridY, std::shared_ptr<Entity> entity);
	Vec2 pixelToGrid(Vec2 pos);
	void loadLevel(const std::string& path);
};