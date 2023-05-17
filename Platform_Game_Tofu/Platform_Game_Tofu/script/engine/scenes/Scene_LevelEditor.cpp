#include "Scene_LevelEditor.h"




Scene_LevelEditor::Scene_LevelEditor(GameEngine* gameEngine)
    : Scene(gameEngine)
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
	registerAction(sf::Mouse::Right , "SELECT");

	m_entityManager = EntityManager();
	m_gridText.setFont(m_game->assets().getFont("tech"));
	m_gridText.setCharacterSize(6);

	
	//Init Selected tile
	auto spriteName = m_game->assets().spriteRef.EnumToStr(Assets::SpriteIDReference::SPRITEID(m_selectedTileID));
	m_selectedTile = m_entityManager.addEntity("selectedTile");
	m_selectedTile->addComponent<CSprite>(m_game->assets().getSprite(spriteName), false);
	m_selectedTile->addComponent<CTransform>(Vec2(0, 0));
	m_selectedTile->getComponent<CTransform>().scale = Vec2(4, 4);
	m_selectedTile->getComponent<CTransform>().pos = gridToMidPixel(9, 0, m_selectedTile);

	//Init Tile pallete
	int numberOfTiles = m_game->assets().spriteRef.Count;

	//Position of tiles
	int tilex = 0;
    int tiley = 0;

	for (int i = 0; i < numberOfTiles; ++i)
	{
		if (tilex % 5 == 0)
		{
			++tiley;
			tilex = 0;
		}

		spriteName = m_game->assets().spriteRef.EnumToStr(Assets::SpriteIDReference::SPRITEID(i));
		auto m_tile = m_entityManager.addEntity("Tile_"+i);
		m_tile->addComponent<CSprite>(m_game->assets().getSprite(spriteName), false);
		m_tile->addComponent<CTransform>(Vec2(0, 0));
		m_tile->getComponent<CTransform>().scale = Vec2(4, 4);
		m_tile->getComponent<CTransform>().pos = Vec2((tilex * 64) + 32, (tiley * 64) - 32);
		m_tile->addComponent<CUI>();
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
			if (tilex % 5 == 0)
			{
				++tiley;
				tilex = 0;
			}
			Vec2 pos = Vec2((tilex * 64) + 32, (tiley * 64) - 32);
			e->getComponent<CTransform>().pos = m_game->windowToWorld(pos);
			tilex++;
		}
	}


	auto spriteName = m_game->assets().spriteRef.EnumToStr(Assets::SpriteIDReference::SPRITEID(m_selectedTileID));
	m_selectedTile->addComponent<CSprite>(m_game->assets().getSprite(spriteName), false);
	m_selectedTile->getComponent<CTransform>().pos = m_game->windowToWorld(gridToMidPixel(9, 0, m_selectedTile));
}
void Scene_LevelEditor::onEnd()
{

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
		if (action.name() == "PREVIOUS" && m_drawSelectedTile)
		{
			if(m_selectedTileID > 0) m_selectedTileID--;
		}
		if (action.name() == "TOGGLE_GRID")
		{
			m_drawGrid = !m_drawGrid;
		}
		if (action.name() == "TOGGLE_SELECTEDTILE")
		{
			m_drawSelectedTile = !m_drawSelectedTile;
		}
		if (action.name() == "TOGGLE_TILEMENU")
		{
			m_drawTileMenu = !m_drawTileMenu;
		}
		if (action.name() == "MOVE RIGHT")
		{
			auto currentpos = m_game->getCameraView().getCenter();
			float speed = m_gridSize.x;
			Vec2 newpos = Vec2(currentpos.x + speed, currentpos.y);
			m_game->moveCameraView(newpos);
		}
		if (action.name() == "MOVE LEFT")
		{
			auto currentpos = m_game->getCameraView().getCenter();
			float speed = -m_gridSize.x;
			Vec2 newpos = Vec2(currentpos.x + speed, currentpos.y);
			m_game->moveCameraView(newpos);
		}
		if (action.name() == "MOVE UP")
		{
			auto currentpos = m_game->getCameraView().getCenter();
			float speed = -m_gridSize.x;
			Vec2 newpos = Vec2(currentpos.x, currentpos.y + speed);
			m_game->moveCameraView(newpos);
		}
		if (action.name() == "MOVE DOWN")
		{
			auto currentpos = m_game->getCameraView().getCenter();
			float speed = m_gridSize.x;
			Vec2 newpos = Vec2(currentpos.x , currentpos.y + speed);
			m_game->moveCameraView(newpos);
		}
		if (action.name() == "RIGHT_CLICK")
		{
			auto m_mapTile = m_entityManager.addEntity("selectedTile");
			auto spriteName = m_game->assets().spriteRef.EnumToStr(Assets::SpriteIDReference::SPRITEID(m_selectedTileID));

			m_mapTile->addComponent<CSprite>(m_game->assets().getSprite(spriteName), false);
			m_mapTile->addComponent<CTransform>(Vec2(0, 0));
			m_mapTile->getComponent<CTransform>().scale = Vec2(4, 4);
			auto gridpos = pixelToGrid(action.pos());
			m_mapTile->getComponent<CTransform>().pos = m_game->windowToWorld(gridToMidPixel(gridpos.x, gridpos.y, m_mapTile));
		}
		
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
				m_gridText.setPosition(x + 3, height() - y - m_gridSize.y + 2);
				m_game->window().draw(m_gridText);
			}
		}
	}

	//Draw entities
	for (auto e : m_entityManager.getEntities())
	{
		auto& transform = e->getComponent<CTransform>();

		if (e->hasComponent<CSprite>() && !e->hasComponent<CUI>())
		{
			
				auto& sprite = e->getComponent<CSprite>().sprite;
				sprite.getSprite().setRotation(transform.angle);
				sprite.getSprite().setPosition(transform.pos.x, transform.pos.y);
				sprite.getSprite().setScale(transform.scale.x, transform.scale.y);
				m_game->window().draw(sprite.getSprite());
		}
	}

	//Draw UI
	if (m_drawTileMenu)
	{
		for (auto e : m_entityManager.getEntities())
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
	}
}
Vec2 Scene_LevelEditor::gridToMidPixel(float gridX, float gridY, std::shared_ptr<Entity> entity)
{
	float spriteWidth = entity->getComponent<CSprite>().sprite.getSprite().getGlobalBounds().width * entity->getComponent<CTransform>().scale.x;
	float spriteHeight = entity->getComponent<CSprite>().sprite.getSprite().getGlobalBounds().height * entity->getComponent<CTransform>().scale.y;

	float x = gridX * m_gridSize.x + (spriteWidth / 2);
	float y = m_game->window().getSize().y - (gridY * m_gridSize.y + spriteHeight / 2);

	return Vec2(x, y);

}
Vec2 Scene_LevelEditor::pixelToGrid(Vec2 pos)
{
	pos.y = m_game->window().getSize().y - pos.y;
	Vec2 gridpos = Vec2(static_cast<int>(pos.x / m_gridSize.x), static_cast<int>(pos.y / m_gridSize.y));

	return gridpos;

}