#include  "Scene_Play.h"
#include "Physics.h"
#include "Assets.h"
#include "GameEngine.h"
#include "Component.h"
#include "Action.h"

#include <iostream>
Scene_Play::Scene_Play(GameEngine* game, const std::string& levelPath)
	:Scene(game)
	, m_levelPath(levelPath)
{
	init(m_levelPath);
}

void Scene_Play::init(const std::string& levelPath)
{
	registerAction(sf::Keyboard::P, "PAUSE");
	registerAction(sf::Keyboard::Escape, "QUIT");
	registerAction(sf::Keyboard::T, "TOGGLE_TEXTURE");
	registerAction(sf::Keyboard::C, "TOGGLE_COLLISION");
	registerAction(sf::Keyboard::G, "TOGGLE_GRID");
	registerAction(sf::Keyboard::W, "UP");
	registerAction(sf::Keyboard::Up, "UP");
	registerAction(sf::Keyboard::S, "DOWN");
	registerAction(sf::Keyboard::Down, "DOWN");
	registerAction(sf::Keyboard::A, "LEFT");
	registerAction(sf::Keyboard::Left, "LEFT");
	registerAction(sf::Keyboard::D, "RIGHT");
	registerAction(sf::Keyboard::Right, "RIGHT");

	//TODO register all other gameplay Actions

	m_gridText.setCharacterSize(6);
	m_gridText.setFont(m_game->assets().getFont("tech"));
	loadLevel(levelPath);
}

Vec2 Scene_Play::gridToMidPixel(float gridX, float gridY, std::shared_ptr<Entity> entity)
{
	float spriteWidth = entity->getComponent<CSprite>().sprite.getSprite().getGlobalBounds().width * entity->getComponent<CTransform>().scale.x;
	float spriteHeight = entity->getComponent<CSprite>().sprite.getSprite().getGlobalBounds().height * entity->getComponent<CTransform>().scale.y;

	float x = gridX * m_gridSize.x + (spriteWidth/2);
	float y = m_game->window().getSize().y - (gridY * m_gridSize.y + spriteHeight/2);

	return Vec2(x,y);

}

void Scene_Play::loadLevel(const std::string& filename)
{
	//reset the entity managet every time we load a level
	m_entityManager = EntityManager();

	spawnPlayer();
	int collumn = 0;
	int row = 11;
	std::ifstream file(filename);
	std::string str;

	// 0 - nothing
	// 1 - tile grass
	// 2 - Tile_big_tl
	// 3 -  Tile_big_tr
	// 4 -  Tile_big_lf
	// 5 -  Tile_big_lr
	// 6 -  Tile_big_lr

	while (file.good())
	{
		file >> str;

		if (str == "0")
		{
			collumn++;
		}
		else if (str == "1")
		{
			auto block = m_entityManager.addEntity("Tile_grass");
			block->addComponent<CSprite>(m_game->assets().getSprite("Tile_grass"), false);
			block->addComponent<CTransform>(Vec2(0, 0));
			block->getComponent<CTransform>().scale = Vec2(4, 4);
			block->getComponent<CTransform>().pos = gridToMidPixel(collumn, row, block);
			block->addComponent<CBoundingBox>(Vec2(64, 64));
			collumn++;
		}
		else if (str == "2")
		{
			auto block = m_entityManager.addEntity("Tile_big_tr");
			block->addComponent<CSprite>(m_game->assets().getSprite("Tile_big_tr"), false);
			block->addComponent<CTransform>(Vec2(0, 0));
			block->getComponent<CTransform>().scale = Vec2(4, 4);
			block->getComponent<CTransform>().pos = gridToMidPixel(collumn, row, block);
			block->addComponent<CBoundingBox>(Vec2(64, 64));
			collumn++;
		}
		else if (str == "3")
		{
			auto block = m_entityManager.addEntity("Tile_big_lf");
			block->addComponent<CSprite>(m_game->assets().getSprite("Tile_big_lf"), false);
			block->addComponent<CTransform>(Vec2(0, 0));
			block->getComponent<CTransform>().scale = Vec2(4, 4);
			block->getComponent<CTransform>().pos = gridToMidPixel(collumn, row, block);
			block->addComponent<CBoundingBox>(Vec2(64, 64));
			collumn++;
		}
		else if (str == "4")
		{
			auto block = m_entityManager.addEntity("Tile_big_lf");
			block->addComponent<CSprite>(m_game->assets().getSprite("Tile_big_lf"), false);
			block->addComponent<CTransform>(Vec2(0, 0));
			block->getComponent<CTransform>().scale = Vec2(4, 4);
			block->getComponent<CTransform>().pos = gridToMidPixel(collumn, row, block);
			block->addComponent<CBoundingBox>(Vec2(64, 64));
			collumn++;
		}
		else if (str == "5")
		{
			auto block = m_entityManager.addEntity("Tile");
			block->addComponent<CSprite>(m_game->assets().getSprite("Tile"), false);
			block->addComponent<CTransform>(Vec2(0, 0));
			block->getComponent<CTransform>().scale = Vec2(4, 4);
			block->getComponent<CTransform>().pos = gridToMidPixel(collumn, row, block);
			block->addComponent<CBoundingBox>(Vec2(64, 64));
			collumn++;
		}
		else if (str == "6")
		{
			auto block = m_entityManager.addEntity("Tile_big_lr");
			block->addComponent<CSprite>(m_game->assets().getSprite("Tile_big_lr"), false);
			block->addComponent<CTransform>(Vec2(0, 0));
			block->getComponent<CTransform>().scale = Vec2(4, 4);
			block->getComponent<CTransform>().pos = gridToMidPixel(collumn, row, block);
			block->addComponent<CBoundingBox>(Vec2(64, 64));
			collumn++;
		}
		else if (str == "|")
		{
			row--;
			collumn = 0;
		}
		std::cout << "Finish reading and loading map \n";
	}


	

	//TODO read in the level file and add the appropriate entities
	// use the plauyerconfi struct m_playerConfig to store player properties
	// this struct is defined at the top of Scene_play.h
	// 
	// NOTE: all of the code below is sample code which shows you how to
	// set up and use entities with the new syntax it should be removed
	//
	

	/*
	//Create a tile
	auto block = m_entityManager.addEntity("Tile");
	block->addComponent<CAnimation>(m_game->assets().getAnimation("Tile"), false);
	block->addComponent<CTransform>(Vec2(0,0));
	block->getComponent<CTransform>().scale = Vec2(4, 4);
	block->getComponent<CTransform>().pos = gridToMidPixel(1, 1, block);
	block->addComponent<CBoundingBox>(Vec2(64, 64));
	*/

	/*

	//some sample entities
	auto brick = m_entityManager.addEntity("tile");
	//IMPORTANT always add the CAnimation component first so that gridToMidPixel can compute correctly
	brick->addComponent<CAnimation>(m_game->assets().getAnimation("Brick"), true);
	brick->addComponent<CTransform>(Vec2(96, 480));

	//NOTE your final code should position the entity with the grid x,y position read from the file
	//brick->addComponent<CTransform>(gridToMidPixel(gridx,gridY,brick);

	if (brick->getComponent<CAnimation>().animation.getName() == "Brick")
	{
		std::cout << "This could be a good way of idetifying if a tile is a brick! \n";
	}

	auto block = m_entityManager.addEntity("tile");
	block->addComponent<CAnimation>(m_game->assets().getAnimation("Block"), true);
	block->addComponent<CTransform>(Vec2(224, 480));
	//add a bounding box, this will now show up if we press the C key
	block->addComponent<CBoundingBox>(m_game->assets().getAnimation("Block").getSize());

	auto question = m_entityManager.addEntity("tile");
	question->addComponent<CAnimation>(m_game->assets().getAnimation("Question"), true);
	question->addComponent<CTransform>(Vec2(352, 480));

	//Components are now returned as references rather than pointers
	// if you do not specify a reference variable type,it wil copy the component
	// here is an example:
	// 
	// this will copy the transform into the variabel trnasform1 it is incorrect
	// any changes you make to transform1 will not be changed inside the entity
	// auto tranform1 = entity->get<CTransform>()
	// 
	// this will reference the trnasform with the variable transform2 it is correct
	// now any changes you make to transform2 will be changed inside entity
	// auto& transform2 = entity->get<CTransform>()
	//


	*/
}

void Scene_Play::spawnPlayer()
{
	//here is a smaple player entity which you can use to construct other entities

	m_player = m_entityManager.addEntity("player");
	m_player->addComponent<CSprite>(m_game->assets().getSprite("Tofu"), false);
	m_player->addComponent<CTransform>(Vec2(224, 352));
	m_player->getComponent<CTransform>().scale = Vec2(4, 4);
	m_player->addComponent<CGravity>(3.0f);
	m_player->addComponent<CBoundingBox>(Vec2(64, 64));

	//TODO be sure to add the remianing components to the player
}

void Scene_Play::spawnBullet(std::shared_ptr<Entity> entity)
{
	//TODO this should spawn a bullet at the given entity, going in the direction the enity is facing
}
void Scene_Play::update()
{
	m_entityManager.update();

	//TODO implement pause functionality
	sMovement();
	sLifespan();
	sAnimation();
	sCollision();
	sRender();
}
void Scene_Play::sMovement()
{

	//Player Moviment
	Vec2 playerVelocity(0, 0);

	if (m_player->getComponent<CInput>().up)
	{
		playerVelocity.y += -10;
	}
	if (m_player->hasComponent<CGravity>())
	{
		playerVelocity.y += m_player->getComponent<CGravity>().gravity;
	}
	if (m_player->getComponent<CInput>().right)
	{
		playerVelocity.x += 3;
	}
	if (m_player->getComponent<CInput>().left)
	{
		playerVelocity.x += -3;
	}
	m_player->getComponent<CTransform>().velocity = playerVelocity;

	for (auto e : m_entityManager.getEntities())
	{
		if (e->getComponent<CTransform>().velocity != Vec2(0, 0))
		{
			e->getComponent<CTransform>().move(e->getComponent<CTransform>().velocity);
		}
	}
}
void Scene_Play::sLifespan()
{
	//TODO check lifespawn of entities that have them, destroy them if they go over
}
void Scene_Play::sCollision()
{
	Physics physics;


	//Check collision with player
	for (auto e : m_entityManager.getEntities())
	{
		if (e->hasComponent<CBoundingBox>() && e->id() != m_player->id())
		{
			auto overlap = physics.GetOverlap(m_player, e);
			if (overlap.x > 0 && overlap.y > 0)
			{
				auto resolveCol = physics.ResolveCollision(m_player, e);
				m_player->getComponent<CTransform>().move(Vec2(resolveCol));
			}
		}
	}
}
void Scene_Play::drawline(Vec2 p1, Vec2 p2)
{
	sf::VertexArray lines(sf::LinesStrip, 2);
	lines[0].position = sf::Vector2f(p1.x, p1.y);
	lines[1].position = sf::Vector2f(p2.x, p2.y);

	m_game->window().draw(lines);
}
void Scene_Play::sDoAction(const Action& action)
{
	if (action.type() == "START")
	{
		if (action.name() == "TOGGLE_TEXTURE") { m_drawTextures = !m_drawTextures; }
		else if (action.name() == "TOGGLE_COLLISION") { m_drawCollision = !m_drawCollision; }
		else if (action.name() == "TOGGLE_GRID") { m_drawGrid = !m_drawGrid; }
		else if (action.name() == "PAUSE") { setPaused(!m_paused); }
		else if (action.name() == "QUIT") { onEnd(); }
		else if (action.name() == "UP") { m_player->getComponent<CInput>().up = true; }
		else if (action.name() == "DOWN") { m_player->getComponent<CInput>().down = true; }
		else if (action.name() == "RIGHT") 
		{
			m_player->getComponent<CInput>().right = true; 
			m_player->getComponent<CTransform>().flipX(false);
		}
		else if (action.name() == "LEFT") 
		{
			m_player->getComponent<CInput>().left = true; 
			m_player->getComponent<CTransform>().flipX(true);
		}
	}
	else if (action.type() == "END")
	{
		 if (action.name() == "UP") { m_player->getComponent<CInput>().up = false; }
		else if (action.name() == "DOWN") { m_player->getComponent<CInput>().down = false; }
		else if (action.name() == "RIGHT") { m_player->getComponent<CInput>().right = false; }
		else if (action.name() == "LEFT") { m_player->getComponent<CInput>().left = false; }
	}
}
void Scene_Play::sAnimation()
{
	//TODO Complete the animation class code first
	//TODO set the animaton of the player based on tis CState component
	//TODO for each entity with an animation call entity->getComponent<CAnimation>().animation.update()
	// if the animation is not repeated and it has ended destroy the entity
}
void Scene_Play::onEnd()
{
	//TODO when the scene ends change back to the MENU scene
	// use m_game->changeScene(correct params)
}

void Scene_Play::sRender()
{
	//color the background darker so you know that the game is paused

	if (!m_paused) { m_game->window().clear(sf::Color(100, 100, 255)); }
	else { m_game->window().clear(sf::Color(50, 50, 150)); }

	//set the viewport of the window to be cented on the player if its far enough right
	//auto& pPos = m_player->getComponent<CTransform>().pos;
	//float windowCenterX = std::max(m_game->window().getSize().x / 2.0f, pPos.x);
	//sf::View view = m_game->window().getView();
	//view.setCenter(windowCenterX, m_game->window().getSize().y - view.getCenter().y);
	//draw all entity textures / animations
	if (m_drawTextures)
	{
		for (auto e : m_entityManager.getEntities())
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

	if (m_drawCollision)
	{
		for (auto e : m_entityManager.getEntities())
		{
			if (e->hasComponent<CBoundingBox>())
			{
				auto& box = e->getComponent<CBoundingBox>();
				auto& transform = e->getComponent<CTransform>();
				sf::RectangleShape rect;
				rect.setSize(sf::Vector2f(box.size.x - 1, box.size.y - 1));
				rect.setOrigin(sf::Vector2f(box.halfSize.x, box.halfSize.y));
				rect.setPosition(transform.pos.x, transform.pos.y);
				rect.setFillColor(sf::Color(0, 0, 0, 0));
				rect.setOutlineColor(sf::Color(255, 255, 255, 255));
				rect.setOutlineThickness(1);
				m_game->window().draw(rect);

			}
		}
	}

	//draw the grid so that students can easily debug

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

}