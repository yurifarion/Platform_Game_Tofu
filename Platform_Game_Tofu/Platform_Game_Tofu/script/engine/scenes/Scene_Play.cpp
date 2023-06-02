#include  "Scene_Play.h"
#include "Physics.h"
#include "Assets.h"
#include "GameEngine.h"
#include "Component.h"
#include "Action.h"

#include <iostream>
Scene_Play::Scene_Play(GameEngine* game, const std::string& levelPath)
	:Scene(game)
{
	init(levelPath);
}

void Scene_Play::init(const std::string& levelPath)
{
	registerAction(sf::Keyboard::P, "PAUSE");
	registerAction(sf::Keyboard::Escape, "QUIT");
	registerAction(sf::Keyboard::T, "TOGGLE_TEXTURE");
	registerAction(sf::Keyboard::C, "TOGGLE_COLLISION");
	registerAction(sf::Keyboard::G, "TOGGLE_GRID");
	registerAction(sf::Keyboard::L, "TOGGLE_DEBUG");


	registerAction(sf::Keyboard::Space, "JUMP");
	registerAction(sf::Keyboard::Up, "JUMP");
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

	float x = gridX * m_gridSize.x + (spriteWidth / 2);
	float y = gridY * m_gridSize.y + (spriteHeight / 2);

	return Vec2(x, y);

}

void Scene_Play::loadLevel(const std::string& filename)
{
	//reset the entity managet every time we load a level
	m_entityManager = EntityManager();

	int rowp = 100;
	int collumnp = 100;
	m_maplevel = MapLevel(rowp, collumnp);

	m_maplevel.loadfromMapFile(filename);

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
				auto spriteName = m_game->assets().spriteRef.EnumToStr(Assets::SpriteIDReference::SPRITEID(mapdata[row][collumn]));
				auto m_mapTile = m_entityManager.addEntity("background_tile");
				m_mapTile->addComponent<CSprite>(m_game->assets().getSprite(spriteName), false);
				m_mapTile->addComponent<CTransform>(Vec2(0, 0));
				m_mapTile->getComponent<CTransform>().scale = Vec2(4, 4);
				Vec2 position = m_game->windowToWorld(gridToMidPixel(row, collumn, m_mapTile));
				m_mapTile->getComponent<CTransform>().pos = position;	
			}
		}
	}

	mapdata = m_maplevel.getMapDataForeground();
	bool isPlayerSpawned = false;
	
	// Foreground
	for (int row = 0; row < mapdata.size(); ++row)
	{
		for (int collumn = 0; collumn < mapdata[row].size(); collumn++)
		{
			if (mapdata[row][collumn] != 0)
			{

				auto spriteName = m_game->assets().spriteRef.EnumToStr(Assets::SpriteIDReference::SPRITEID(mapdata[row][collumn]));
				auto m_mapTile = m_entityManager.addEntity("foreground_tile");
				m_mapTile->addComponent<CSprite>(m_game->assets().getSprite(spriteName), false);
				m_mapTile->addComponent<CTransform>(Vec2(0, 0));
				m_mapTile->getComponent<CTransform>().scale = Vec2(4, 4);
				m_mapTile->addComponent<CBoundingBox>(Vec2(64, 64));
				Vec2 position = m_game->windowToWorld(gridToMidPixel(row, collumn, m_mapTile));
				m_mapTile->getComponent<CTransform>().pos = position;

				if (Assets::SpriteIDReference::SPRITEID(mapdata[row][collumn]) == Assets::SpriteIDReference::SPRITEID::PLAYER && !isPlayerSpawned)
				{
					isPlayerSpawned = true;
					m_mapTile->destroy();
					spawnPlayer(position);
				}

			}
		}
	}

	
}

void Scene_Play::spawnPlayer(Vec2& position)
{
	//here is a smaple player entity which you can use to construct other entities

	m_player = m_entityManager.addEntity("player");
	m_player->addComponent<CSprite>(m_game->assets().getSprite("Tofu_stand"), false);

	Sprite idle_fr(m_game->assets().getSprite("Tofu_stand"));
	Sprite walk_fr_1(m_game->assets().getSprite("Tofu_walk1_jump"));
	Sprite walk_fr_2(m_game->assets().getSprite("Tofu_walk2"));
	Sprite walk_fr_3(m_game->assets().getSprite("Tofu_walk3"));
	Sprite walk_fr_4(m_game->assets().getSprite("Tofu_walk4"));

	Animation walkAnimClip("walk", 6.0f);

	walkAnimClip.addFrame(walk_fr_1);
	walkAnimClip.addFrame(walk_fr_2);
	walkAnimClip.addFrame(walk_fr_3);
	walkAnimClip.addFrame(walk_fr_4);

	Animation jumpAnimClip("jump", 1.0f);
	jumpAnimClip.addFrame(walk_fr_1);

	Animation idleAnimClip("idle", 1.0f);
	idleAnimClip.addFrame(idle_fr);

	//Set animator
	m_player->addComponent<CAnimator>(m_player->getComponent<CSprite>().sprite);
	m_player->getComponent<CAnimator>().animator.addAnimation(walkAnimClip);
	m_player->getComponent<CAnimator>().animator.addAnimation(jumpAnimClip);
	m_player->getComponent<CAnimator>().animator.addAnimation(idleAnimClip);
	m_player->getComponent<CAnimator>().animator.setAnimation("idle");

	m_player->addComponent<CTransform>(position);
	m_player->getComponent<CTransform>().scale = Vec2(4, 4);
	m_player->addComponent<CRigidbody>(3.0f);
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
	m_debugGraph.clear();
	//TODO implement pause functionality
	sMovement();
	sLifespan();
	sAnimation();
	sCollision();
	sRender();
}
void Scene_Play::sMovement()
{
	//Update all rigibodies
	auto& rb = m_player->getComponent<CRigidbody>().rigidbody;

	rb.update();

	//Max moviment per frame the player can move
	Vec2 maxspeed(3.0f, 100.0f);
	

	if (m_player->getComponent<CInput>().up)
	{
		if (rb.isGrounded)
		{
			rb.addForce(Vec2(0.0f, -10.0f));
		}
	}
	if (m_player->getComponent<CInput>().right)
	{
		rb.addForce(Vec2(3.0f, 0.0f));
	}
	if (m_player->getComponent<CInput>().left)
	{
		rb.addForce(Vec2(-3.0f, 0.0f));
	}
	

	m_player->getComponent<CTransform>().velocity = rb.getVelocity(maxspeed);

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
	
	m_player->getComponent<CRigidbody>().rigidbody.isColliding = false;
	m_player->getComponent<CRigidbody>().rigidbody.isGrounded = false;


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
				m_player->getComponent<CRigidbody>().rigidbody.isColliding = true;
			}
		}
	}

	
	
	//Check with Raycast if Player is close to the ground
	Vec2 origin = m_player->getComponent<CTransform>().pos;
	Vec2 destiny = m_player->getComponent<CTransform>().pos + Vec2(0, 40);

	for (auto e : m_entityManager.getEntities())
	{
		if (e->hasComponent<CBoundingBox>() && e->id() != m_player->id())
		{
			if (physics.EntityIntersect(origin, destiny, e))
			{
				m_player->getComponent<CRigidbody>().rigidbody.isGrounded = true;
				debugline(origin, destiny, sf::Color::Red);
			}
		}
	}
	if(!m_player->getComponent<CRigidbody>().rigidbody.isGrounded) debugline(origin, destiny, sf::Color::Yellow);
}
void Scene_Play::drawline(Vec2 p1, Vec2 p2)
{
	sf::VertexArray lines(sf::LinesStrip, 2);
	lines[0].position = sf::Vector2f(p1.x, p1.y);
	lines[1].position = sf::Vector2f(p2.x, p2.y);

	m_game->window().draw(lines);
}

//Draw a debug line
void Scene_Play::debugline(Vec2 p1, Vec2 p2, sf::Color color)
{
	sf::VertexArray line(sf::LineStrip, 2);
	line[0].color = color;
	line[1].color = color;

	line[0].position = sf::Vector2f(p1.x, p1.y);
	line[1].position = sf::Vector2f(p2.x, p2.y);
	m_debugGraph.push_back(line);
}
void Scene_Play::sDoAction(const Action& action)
{
	//When Action start
	if (action.type() == "START")
	{
		//Toggle of textures, Debug etc
		if (action.name() == "TOGGLE_TEXTURE") { m_drawTextures = !m_drawTextures; }
		if (action.name() == "TOGGLE_COLLISION") { m_drawCollision = !m_drawCollision; }
		if (action.name() == "TOGGLE_GRID") { m_drawGrid = !m_drawGrid; }
		if (action.name() == "TOGGLE_DEBUG") { m_drawDebug = !m_drawDebug; }

		//Game State Input
		 if (action.name() == "PAUSE") { setPaused(!m_paused); }
		 if (action.name() == "QUIT") { onEnd(); }
		 if (action.name() == "JUMP") 
		{
			m_player->getComponent<CInput>().up = true; 
			m_player->getComponent<CState>().state = "jump";
		}

		 //Game Controls Input
		 if (action.name() == "DOWN") 
		{ 
			m_player->getComponent<CInput>().down = true; 
		}
		 if (action.name() == "RIGHT") 
		{
			m_player->getComponent<CInput>().right = true; 
			m_player->getComponent<CTransform>().flipX(false);
			m_player->getComponent<CState>().state = "walk";
		}
		 if (action.name() == "LEFT") 
		{
			m_player->getComponent<CInput>().left = true; 
			m_player->getComponent<CTransform>().flipX(true);
		}
	}
	//When Action end
	else if (action.type() == "END")
	{
		//Game Controls Input
		 if (action.name() == "JUMP") 
		 { 
			 m_player->getComponent<CInput>().up = false;
		 }
		 if (action.name() == "DOWN") { m_player->getComponent<CInput>().down = false; }
		 if (action.name() == "RIGHT") 
		{
			 m_player->getComponent<CInput>().right = false; 
		}
		 if (action.name() == "LEFT") 
		{
			 m_player->getComponent<CInput>().left = false; 
		}
	}
}
void Scene_Play::sAnimation()
{

	//Set Player animation based on physics
	if (m_player->getComponent<CTransform>().velocity != Vec2(0, 0) && m_player->getComponent<CRigidbody>().rigidbody.isGrounded)
		m_player->getComponent<CState>().state = "walk";

	else if (m_player->getComponent<CTransform>().velocity == Vec2(0, 0) && m_player->getComponent<CRigidbody>().rigidbody.isGrounded)
		m_player->getComponent<CState>().state = "idle";

	else if (!m_player->getComponent<CRigidbody>().rigidbody.isGrounded)
		m_player->getComponent<CState>().state = "jump";


	
	//change animations
	auto& playeranimator = m_player->getComponent<CAnimator>().animator;
	if (m_player->getComponent<CState>().state == "jump" && !m_player->getComponent<CRigidbody>().rigidbody.isGrounded)
	{
		playeranimator.setAnimation("jump");
	}
	else if (m_player->getComponent<CState>().state == "walk") 
	{
		 playeranimator.setAnimation("walk");
	}
	else if(m_player->getComponent<CState>().state == "idle") 
	{
		 playeranimator.setAnimation("idle");
	}
	else playeranimator.setAnimation("idle");

	//Update frames
	m_player->getComponent<CAnimator>().animator.update();

	//change sprites
	m_player->getComponent<CSprite>().sprite = m_player->getComponent<CAnimator>().animator.getCurrentSprite();

}
void Scene_Play::onEnd()
{
	//TODO when the scene ends change back to the MENU scene
	// use m_game->changeScene(correct params)
}

void Scene_Play::sRender()
{
	//color the background darker so you know that the game is paused

	if (!m_paused) { m_game->window().clear(sf::Color(0, 64, 128)); }
	else { m_game->window().clear(sf::Color(50, 50, 150)); }

	
	//Draw Entities Textures
	if (m_drawTextures)
	{
		for (auto e : m_entityManager.getEntities("background_tile"))
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

		for (auto e : m_entityManager.getEntities("foreground_tile"))
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

		for (auto e : m_entityManager.getEntities("player"))
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

	//Draw Entities Collision Box
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

	//Draw Debug Lines
	if (m_drawDebug)
	{
		//draw debug Graphics
		for (auto db : m_debugGraph)
		{
			m_game->window().draw(db);
		}
	}
		
}