#include "Scene_LevelEditor.h"




Scene_LevelEditor::Scene_LevelEditor(const std::string& path,bool isNewLevel, GameEngine* gameEngine)
	: m_levelPath(path),m_isNewLevel(isNewLevel), Scene(gameEngine)
{
	init();
}
void Scene_LevelEditor::init()
{
	
	//Set Actions
	registerAction(sf::Keyboard::D, "MOVE RIGHT");
	registerAction(sf::Keyboard::A, "MOVE LEFT");
	registerAction(sf::Keyboard::W, "MOVE UP");
	registerAction(sf::Keyboard::S, "MOVE DOWN");
	registerAction(sf::Keyboard::Right , "NEXT");
	registerAction(sf::Keyboard::Left, "PREVIOUS");
	registerAction(sf::Keyboard::G, "TOGGLE_GRID");
	registerAction(sf::Keyboard::H, "TOGGLE_SELECTEDTILE");
	registerAction(sf::Keyboard::T, "TOGGLE_TILEMENU");
	registerAction(sf::Keyboard::L, "SAVE_MAP");
	registerAction(sf::Keyboard::Escape, "QUIT");

	m_entityManager = EntityManager();
	m_gridText.setFont(m_game->assets().getFont("tech"));
	m_gridText.setCharacterSize(6);


	//Create or Load level
	if(!m_isNewLevel)loadLevel(m_levelPath);
    
	else
	{
		m_maplevel = MapLevel(100, 100);
		m_maplevel.createMapFile(m_levelPath);
	}
	
	
	//Init Selected tile
	auto spriteName = m_game->assets().spriteRef.EnumToStr(Assets::SpriteIDReference::SPRITEID(m_selectedTileID));
	m_selectedTile = m_entityManager.addEntity("selectedTile");
	m_selectedTile->addComponent<CSprite>(m_game->assets().getSprite(spriteName), false);
	m_selectedTile->addComponent<CTransform>(Vec2(0, 0));
	m_selectedTile->getComponent<CTransform>().scale = Vec2(4, 4);
	m_selectedTile->getComponent<CTransform>().pos = gridToMidPixel(9, 0, m_selectedTile);
	m_selectedTile->addComponent<CUI>();

	//Init Tile pallete
	int numberOfTiles = m_game->assets().spriteRef.Count;

	//Position of tiles
	int tilex = 0;
    int tiley = 0;

	for (int i = 1; i < numberOfTiles; ++i)
	{
		if (tilex % 9 == 0)
		{
			++tiley;
			tilex = 0;
		}

		spriteName = m_game->assets().spriteRef.EnumToStr(Assets::SpriteIDReference::SPRITEID(i));
		auto m_tile = m_entityManager.addEntity("TilePalette");
		m_tile->addComponent<CSprite>(m_game->assets().getSprite(spriteName), false);
		m_tile->addComponent<CTransform>(Vec2(0, 0));
		m_tile->getComponent<CTransform>().scale = Vec2(4, 4);
		m_tile->getComponent<CTransform>().pos = m_game->windowToWorld(gridToMidPixel(tilex, tiley, m_tile));
		m_tile->addComponent<CUI>();
		m_tile->addComponent<CTileMap>(i);
		tilex++;
	}

	

}
void Scene_LevelEditor::update()
{
	m_entityManager.update();

	//Update position of UI
	//Position of tiles
	int tilex = 0;
	int tiley = 0;
	for (auto e : m_entityManager.getEntities())
	{
		if (e->hasComponent<CUI>())
		{
			if (e->tag() == "selectedTile")
			{
				auto spriteName = m_game->assets().spriteRef.EnumToStr(Assets::SpriteIDReference::SPRITEID(m_selectedTileID));
				m_selectedTile->addComponent<CSprite>(m_game->assets().getSprite(spriteName), false);
				m_selectedTile->getComponent<CTransform>().pos = m_game->windowToWorld(gridToMidPixel(19, 0, m_selectedTile));
			}
			else {
				if (tilex % 9 == 0)
				{
					++tiley;
					tilex = 0;
				}
				Vec2 pos = m_game->windowToWorld(gridToMidPixel(tilex, tiley, e));
				e->getComponent<CTransform>().pos = m_game->windowToWorld(pos);
				tilex++;
			}
		}
	}
	
}

void Scene_LevelEditor::sDoAction(const Action& action)
{
	if (action.type() == "START")
	{
		if (action.name() == "NEXT" && m_drawSelectedTile)
		{
			auto spriteID = Assets::SpriteIDReference::SPRITEID(m_selectedTileID);
			if(spriteID != Assets::SpriteIDReference::SPRITEID::LAST)m_selectedTileID++;
		}
		else if (action.name() == "PREVIOUS" && m_drawSelectedTile)
		{
			if(m_selectedTileID > 0) m_selectedTileID--;
		}
		else if (action.name() == "TOGGLE_GRID")
		{
			m_drawGrid = !m_drawGrid;
		}
		else if (action.name() == "TOGGLE_SELECTEDTILE")
		{
			m_drawSelectedTile = !m_drawSelectedTile;
		}
		else if (action.name() == "TOGGLE_TILEMENU")
		{
			m_drawUI = !m_drawUI;
		}
		else if (action.name() == "SAVE_MAP")
		{
			m_maplevel.saveMapFile();
			m_isLevelSaved = true;
		}
		else if (action.name() == "QUIT")
		{
			onEnd();
		}
		else if (action.name() == "CLOSE_WINDOW")
		{
			if (!m_isLevelSaved && m_isLevelModified)
			{
				auto warning = tinyfd_messageBox("Leaving Level Editor?", "You are leaving the editor without saving, are you sure?", "okcancel", "question", 0);
				if (warning == 1)
				{
					m_hasEnded = true;
					m_game->changeScene("MENU", std::make_shared<Scene_Menu>(m_game));
				}
			}
			else {
			    m_game->quit();
			}
		}
		else if (action.name() == "MOVE RIGHT")
		{
			auto currentpos = m_game->getCameraView().getCenter();
			float speed = m_gridSize.x;
			Vec2 newpos = Vec2(currentpos.x + speed, currentpos.y);
			m_game->moveCameraView(newpos);
		}
		else if (action.name() == "MOVE LEFT")
		{
			auto currentpos = m_game->getCameraView().getCenter();
			float speed = -m_gridSize.x;
			Vec2 newpos = Vec2(currentpos.x + speed, currentpos.y);
			m_game->moveCameraView(newpos);
		}
		else if (action.name() == "MOVE UP")
		{
			auto currentpos = m_game->getCameraView().getCenter();
			float speed = -m_gridSize.x;
			Vec2 newpos = Vec2(currentpos.x, currentpos.y + speed);
			m_game->moveCameraView(newpos);
		}
		else if (action.name() == "MOVE DOWN")
		{
			auto currentpos = m_game->getCameraView().getCenter();
			float speed = m_gridSize.x;
			Vec2 newpos = Vec2(currentpos.x , currentpos.y + speed);
			m_game->moveCameraView(newpos);
		}

		//If we select with left click
		else if (action.name() == "LEFT_CLICK")
		{
			//Select Tile based on Location x,y
			if (m_drawUI)
			{
				m_drawUI = false;
			}
			else
			{
				auto m_mapTile = m_entityManager.addEntity("TileMap");
				auto spriteName = m_game->assets().spriteRef.EnumToStr(Assets::SpriteIDReference::SPRITEID(m_selectedTileID));

				m_mapTile->addComponent<CSprite>(m_game->assets().getSprite(spriteName), false);
				m_mapTile->addComponent<CTransform>(Vec2(0, 0));
				m_mapTile->getComponent<CTransform>().scale = Vec2(4, 4);
				auto gridpos = pixelToGrid(action.pos());
				m_mapTile->getComponent<CTransform>().pos = m_game->windowToWorld(gridToMidPixel(gridpos.x, gridpos.y, m_mapTile));
				m_mapTile->addComponent<CTileMap>(m_selectedTileID);

				if (spriteName.find("dark") == std::string::npos)
				{
					m_maplevel.setIndexForeground(gridpos.x, gridpos.y, m_selectedTileID);
				}
				else
				{
					m_maplevel.setIndexBackground(gridpos.x, gridpos.y, m_selectedTileID);
				}
				m_isLevelModified = true;
			}
		}
		
	}

	//Copy id to selected ID if clicked with right click
	if (action.name() == "RIGHT_CLICK")
	{
		
			if (!m_drawUI)
			{
				for (auto e : m_entityManager.getEntities("TileMap"))
				{
					auto& transform = e->getComponent<CTransform>();

					if (e->hasComponent<CSprite>() && e->hasComponent<CTileMap>())
					{
							Vec2 mousepos = m_game->windowToWorld(action.pos());
							Vec2 Tilepos = e->getComponent<CTransform>().pos;
							float halfwidth = e->getComponent<CSprite>().sprite.getSize().x / 2 * e->getComponent<CTransform>().scale.x;
							float halfheight = e->getComponent<CSprite>().sprite.getSize().y / 2 * e->getComponent<CTransform>().scale.y;
							bool  isInside = mousepos.x > (Tilepos.x - halfwidth) && mousepos.x < (Tilepos.x + halfwidth)
								&& mousepos.y >(Tilepos.y - halfheight) && mousepos.y < (Tilepos.y + halfheight);
							if (isInside) m_selectedTileID = e->getComponent<CTileMap>().spriteID;
					}
				}
			}
			else
			{
				for (auto e : m_entityManager.getEntities("TilePalette"))
				{
					auto& transform = e->getComponent<CTransform>();

					if (e->hasComponent<CSprite>() && e->hasComponent<CTileMap>())
					{
						Vec2 mousepos = m_game->windowToWorld(action.pos());
						Vec2 Tilepos = e->getComponent<CTransform>().pos;
						float halfwidth = e->getComponent<CSprite>().sprite.getSize().x / 2 * e->getComponent<CTransform>().scale.x;
						float halfheight = e->getComponent<CSprite>().sprite.getSize().y / 2 * e->getComponent<CTransform>().scale.y;
						bool  isInside = mousepos.x > (Tilepos.x - halfwidth) && mousepos.x < (Tilepos.x + halfwidth)
							&& mousepos.y >(Tilepos.y - halfheight) && mousepos.y < (Tilepos.y + halfheight);
						if (isInside) m_selectedTileID = e->getComponent<CTileMap>().spriteID;
					}
				}
			}
		
	}

	//Delete Tile of that position
	if (action.name() == "MIDDLE_CLICK")
	{
		if (!m_drawUI)
		{
			for (auto e : m_entityManager.getEntities())
			{
				auto& transform = e->getComponent<CTransform>();

				if (e->hasComponent<CSprite>() && e->hasComponent<CTileMap>() && !e->hasComponent<CUI>())
				{
					Vec2 mousepos = m_game->windowToWorld(action.pos());
					Vec2 Tilepos = e->getComponent<CTransform>().pos;
					float halfwidth = e->getComponent<CSprite>().sprite.getSize().x / 2 * e->getComponent<CTransform>().scale.x;
					float halfheight = e->getComponent<CSprite>().sprite.getSize().y / 2 * e->getComponent<CTransform>().scale.y;
					bool  isInside = mousepos.x > (Tilepos.x - halfwidth) && mousepos.x < (Tilepos.x + halfwidth)
						&& mousepos.y >(Tilepos.y - halfheight) && mousepos.y < (Tilepos.y + halfheight);

					if (isInside)
					{
						auto gridpos = pixelToGrid(action.pos());
						if (m_maplevel.getMapDataForeground()[gridpos.x][gridpos.y] != 0)
						{
							e->destroy();
							m_maplevel.setIndexForeground(gridpos.x, gridpos.y, 0);
							m_isLevelModified = true;
						}
						else
						{
							e->destroy();
							m_maplevel.setIndexBackground(gridpos.x, gridpos.y, 0);
							m_isLevelModified = true;
						}
						
					}
				}
			}
		}
		else m_drawUI = false;
	}
}
void Scene_LevelEditor::drawline(Vec2 p1, Vec2 p2)
{
	sf::VertexArray lines(sf::LinesStrip, 2);
	lines[0].position = sf::Vector2f(p1.x, p1.y);
	lines[1].position = sf::Vector2f(p2.x, p2.y);

	m_game->window().draw(lines);
}
void Scene_LevelEditor::sRender()
{
	m_game->window().clear(sf::Color(50, 50, 150));

	

	//Draw entities
	for (auto e : m_entityManager.getEntities())
	{
		auto& transform = e->getComponent<CTransform>();

		if (e->hasComponent<CSprite>() && e->tag() != "TilePalette")
		{
			
				auto& sprite = e->getComponent<CSprite>().sprite;
				sprite.getSprite().setRotation(transform.angle);
				sprite.getSprite().setPosition(transform.pos.x, transform.pos.y);
				sprite.getSprite().setScale(transform.scale.x, transform.scale.y);
				m_game->window().draw(sprite.getSprite());
		}
	}
	//Draw grid
	if (m_drawGrid)
	{
		float leftX = m_game->window().getView().getCenter().x - width() / 2;
		float rightX = leftX + width() + m_gridSize.x;
		float nextGridX = leftX - ((int)leftX % (int)m_gridSize.x);

		for (float x = nextGridX; x < rightX; x += m_gridSize.x)
		{
			drawline(Vec2(x, 0), Vec2(x, height()));
		}

		for (float y = 0; y < height(); y += m_gridSize.y)
		{
			drawline(Vec2(leftX, height() - y), Vec2(rightX, height() - y));

			for (float x = nextGridX; x < rightX; x += m_gridSize.x)
			{
				std::string xCell = std::to_string((int)x / (int)m_gridSize.x);
				std::string yCell = std::to_string((int)y / (int)m_gridSize.y);
				m_gridText.setString("(" + xCell + "," + yCell + ")");
				m_gridText.setPosition(x + 3, y + 2);
				m_game->window().draw(m_gridText);
			}
		}
	}

	//Draw UI
	
	if (m_drawUI)
	{ 
		auto windowPos = m_game->windowToWorld(Vec2(0,0));
		sf::RectangleShape UI_BG(sf::Vector2f(windowPos.x, windowPos.y));
		UI_BG.setSize(sf::Vector2f(m_game->window().getSize().x, m_game->window().getSize().y));
		UI_BG.setFillColor(sf::Color(0, 0, 0, 200));
		m_game->window().draw(UI_BG);
		for (auto e : m_entityManager.getEntities("TilePalette"))
		{
			auto& transform = e->getComponent<CTransform>();

			if (e->hasComponent<CSprite>() && e->hasComponent<CUI>())
			{
				auto& sprite = e->getComponent<CSprite>().sprite;
				sprite.getSprite().setRotation(transform.angle);
				sprite.getSprite().setPosition(transform.pos.x, transform.pos.y);
				sprite.getSprite().setScale(transform.scale.x, transform.scale.y);
				m_game->window().draw(sprite.getSprite());
			}
		}

		for (auto e : m_entityManager.getEntities("selectedTile"))
		{
			auto& transform = e->getComponent<CTransform>();

			if (e->hasComponent<CSprite>())
			{
				auto& sprite = e->getComponent<CSprite>().sprite;
				sprite.getSprite().setRotation(transform.angle);
				sprite.getSprite().setPosition(transform.pos.x, transform.pos.y);
				sprite.getSprite().setScale(transform.scale.x, transform.scale.y);
				m_game->window().draw(sprite.getSprite());
			}
		}
	}
}
Vec2 Scene_LevelEditor::gridToMidPixel(float gridX, float gridY, std::shared_ptr<Entity> entity)
{
	float spriteWidth = entity->getComponent<CSprite>().sprite.getSprite().getGlobalBounds().width * entity->getComponent<CTransform>().scale.x;
	float spriteHeight = entity->getComponent<CSprite>().sprite.getSprite().getGlobalBounds().height * entity->getComponent<CTransform>().scale.y;

	float x = gridX * m_gridSize.x + (spriteWidth / 2);
	float y = gridY * m_gridSize.y + (spriteHeight / 2);

	return Vec2(x, y);

}
Vec2 Scene_LevelEditor::pixelToGrid(Vec2 pos)
{
	Vec2 gridpos = Vec2(static_cast<int>(pos.x / m_gridSize.x), static_cast<int>(pos.y / m_gridSize.y));

	return gridpos;

}
void Scene_LevelEditor::loadLevel(const std::string& path)
{
	int rowp = 100;
	int collumnp = 100;
	m_maplevel = MapLevel(rowp, collumnp);
	//m_maplevel.createMapFile(path);
	m_maplevel.loadfromMapFile(path);

	auto mapdata = m_maplevel.getMapDataBackground();

	//Populate entities
	// Write to the file
	//Background
	for (int row = 0; row < mapdata.size(); ++row)
	{
		for (int collumn = 0; collumn < mapdata[row].size(); collumn++)
		{
			if (mapdata[row][collumn] != 0)
			{
				auto m_mapTile = m_entityManager.addEntity("TileMap");
				auto spriteName = m_game->assets().spriteRef.EnumToStr(Assets::SpriteIDReference::SPRITEID(mapdata[row][collumn]));

				m_mapTile->addComponent<CSprite>(m_game->assets().getSprite(spriteName), false);
				m_mapTile->addComponent<CTransform>(Vec2(0, 0));
				m_mapTile->getComponent<CTransform>().scale = Vec2(4, 4);
				m_mapTile->getComponent<CTransform>().pos = m_game->windowToWorld(gridToMidPixel(row, collumn, m_mapTile));
				m_mapTile->addComponent<CTileMap>(mapdata[row][collumn]);
			}
		}
	}
	mapdata = m_maplevel.getMapDataForeground();
	for (int row = 0; row < mapdata.size(); ++row)
	{
		for (int collumn = 0; collumn < mapdata[row].size(); collumn++)
		{
			if (mapdata[row][collumn] != 0)
			{
				auto m_mapTile = m_entityManager.addEntity("TileMap");
				auto spriteName = m_game->assets().spriteRef.EnumToStr(Assets::SpriteIDReference::SPRITEID(mapdata[row][collumn]));

				m_mapTile->addComponent<CSprite>(m_game->assets().getSprite(spriteName), false);
				m_mapTile->addComponent<CTransform>(Vec2(0, 0));
				m_mapTile->getComponent<CTransform>().scale = Vec2(4, 4);
				m_mapTile->getComponent<CTransform>().pos = m_game->windowToWorld(gridToMidPixel(row, collumn, m_mapTile));
				m_mapTile->addComponent<CTileMap>(mapdata[row][collumn]);
			}
		}
	}


}
void Scene_LevelEditor::onEnd()
{
	if (!m_isLevelSaved && m_isLevelModified)
	{
		auto warning = tinyfd_messageBox("Leaving Level Editor?", "You are leaving the editor without saving, are you sure?", "okcancel", "question", 0);
		if (warning == 1)
		{
			m_hasEnded = true;
			m_game->changeScene("MENU", std::make_shared<Scene_Menu>(m_game));
		}
	}
	else {
		m_hasEnded = true;
		m_game->changeScene("MENU", std::make_shared<Scene_Menu>(m_game));
		//m_game->quit();
	}
}