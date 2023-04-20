#include "Game.h"

#include <iostream>
#include <fstream>

Game::Game(const std::string& config)
{
	init(config);
}

void Game::init(const std::string& path) {
	//TODO read in config file here
	// use the premade PlayerConfig, EnemyConfig, BulletConfig, variables
	// set up default window parameters
	//std::ifstream fin(path);
	//fin >> m_playerConfig.SR >> m_playerConfig.CR;

	if (!m_font.loadFromFile("fonts/tech.ttf"))
	{
		std::cerr << "Could not load font!\n";
		exit(-1);
	}
	m_text.setFont(m_font);
	m_score = 0;

	//set up default window parameters
	m_window.create(sf::VideoMode(1280, 720), "Assigment 2");
	m_window.setFramerateLimit(60);

	loadFromFile("config.txt");

	spawnPlayer();
}
void Game::run()
{
	//TODO add pause functionality
	// some systems should function while paused ( rendering )
	// some systems shouldnt (movemement / input)

	while (m_running)
	{
		m_entities.update();


		if (!m_paused)
		{
			sEnemySpawner();
			sMovement();
			sCollision();
			sUpdatePosition();
			sUpdateText();
			sUserInput();
			sLifespan();
		}
		
		sRender();

		//increment the current frame
		// may need to be moved when paused implemented
		m_currentFrame++;
	}
}
void Game::setPaused(bool paused)
{
	//TODO
}

//respawn the player in the middle of the screen
void Game::spawnPlayer()
{
	//TODO finish adding all properties of the player with the correct values from the config

	// We create every entity by calling EntityManager.addEntity(tag)
	//This returns a std::shared_ptr<Entity>, so we use "auto" to save typing
	auto entity = m_entities.addEntity("player");

	//Give this entity a Transform so it spawns at (200,200) with velocity (1,1) and angle 0
	entity->cTransform = std::make_shared<CTransform>(Vec2(m_window.getSize().x / 2.0f, m_window.getSize().y / 2.0f), Vec2(m_playerConfig.S, m_playerConfig.S), 0.0f);

	entity->cShape = std::make_shared <CShape> (m_playerConfig.SR, m_playerConfig.V, sf::Color(m_playerConfig.FR, m_playerConfig.FG, m_playerConfig.FB), sf::Color(m_playerConfig.OR, m_playerConfig.OG, m_playerConfig.OB), m_playerConfig.OT);

	entity->cInput = std::make_shared<CInput>();

	entity->cCollision = std::make_shared<CCollision>(m_playerConfig.CR);

	m_player = entity;
}
void Game::sMovement()
{
	//TODO implement all entity movement in this function
	// you should read the m_player->cInput component to determine if the player is moving
	m_player->cTransform->velocity = { 0.0f,0.0f };

	if (m_player->cInput->up) 
	{
		m_player->cTransform->velocity.y = -5;
	}
	if (m_player->cInput->down)
	{
		m_player->cTransform->velocity.y = +5;
	}
	if (m_player->cInput->left)
	{
		m_player->cTransform->velocity.x = -5;
	}
	if (m_player->cInput->right)
	{
		m_player->cTransform->velocity.x = 5;
	}



	
}
void Game::sUpdatePosition() {

	for (auto& e : m_entities.getEntities())
	{
		if (!e->cTransform == NULL)
		{
			e->cTransform->pos += e->cTransform->velocity;
		}
	}
}

void Game::spawnEnemy()
{
	//TODO make sure the enemy is spawned properly with the m_enemyConfig variable
	// the enemy must be spawned completely within the bounds of the window
	//record when the most recent enemy was spawned

	
	//random color
	int r = rand() % 255;
	int g = rand() % 255;
	int b = rand() % 255;

	//random position
	int posx = rand() % m_window.getSize().x;
	int posy = rand() % m_window.getSize().y;

	//random vertices
	int vertices = rand() % m_enemyConfig.VMAX + m_enemyConfig.VMIN;

	//random speed
	int speed = rand() % m_enemyConfig.SMAX + m_enemyConfig.SMIN;

	auto entity = m_entities.addEntity("enemy");
	entity->cTransform = std::make_shared<CTransform>(Vec2(posx, posy), Vec2(speed, speed), 0.0f);
	entity->cTransform->velocity = Vec2(1.0f, 1.0f);
	entity->cShape = std::make_shared <CShape>(m_enemyConfig.SR, vertices, sf::Color(r, g, b), sf::Color(m_enemyConfig.OR, m_enemyConfig.OG, m_enemyConfig.OB), m_enemyConfig.OT);
	entity->cCollision = std::make_shared <CCollision>(m_enemyConfig.CR);
	

	m_lastEnemySpawnTime = m_currentFrame;
}
void Game::spawnSmallEnemies(std::shared_ptr<Entity> e)
{

	std::cout << "Spawn small enemies \n";
	//TODO spawn small enemies at the location of the input enemy e
	//small enemies are worth double the points of the original enemy
	int numberOfSides = e->cShape->circle.getPointCount();
	float angleIncrement = (365.0f / numberOfSides) * 3.14159f / 180;
	int count = 0;//couting how many smalls enemies were born

	while (count < numberOfSides) {

		auto entity = m_entities.addEntity("smallenemy");
		Vec2 position = e->cTransform->pos;
		float radius = e->cShape->circle.getRadius() / 2;
		//calculating direction
		Vec2 dir = Vec2(cos(angleIncrement * count), sin(angleIncrement * count));
		float speed = 1.0f;
		entity->cTransform = std::make_shared<CTransform>(position, dir.normalized() * speed, 0.0f);
		entity->cShape = std::make_shared <CShape>(radius, numberOfSides, e->cShape->circle.getFillColor(), e->cShape->circle.getOutlineColor(), 4.0f);
		entity->cCollision = std::make_shared <CCollision>(radius);
		entity->cLifepan = std::make_shared<CLifespan>(m_enemyConfig.L);

		++count;
	}
}
void Game::spawnBullet(std::shared_ptr<Entity> entity, const Vec2 & target)
{
	float speed = m_bulletConfig.S;
	Vec2 dir = target - entity->cTransform->pos;

	//TODO implement the spawning of a bullet which trabels toward target
	auto bullet = m_entities.addEntity("bullet");
	bullet->cTransform = std::make_shared<CTransform>(m_player->cTransform->pos, dir.normalized()*speed, 0);
	bullet->cShape = std::make_shared<CShape>(m_bulletConfig.SR, m_bulletConfig.V, sf::Color(m_bulletConfig.FR, m_bulletConfig.FG, m_bulletConfig.FB), sf::Color(m_bulletConfig.OR, m_bulletConfig.OG, m_bulletConfig.OB), m_bulletConfig.OT);
	bullet->cCollision = std::make_shared<CCollision>(m_bulletConfig.CR);
	bullet->cLifepan = std::make_shared<CLifespan>(m_bulletConfig.L);

}
void Game::spawnSpecialWeapon(std::shared_ptr<Entity> entity, const Vec2& target)
{
	float speed = m_bulletConfig.S;
	Vec2 dir = target - entity->cTransform->pos;

	//TODO implement the spawning of a bullet which trabels toward target
	auto bullet = m_entities.addEntity("bullet");
	bullet->cTransform = std::make_shared<CTransform>(m_player->cTransform->pos, dir.normalized() * speed, 0);
	bullet->cShape = std::make_shared<CShape>(m_bulletConfig.SR * 10, m_bulletConfig.V, sf::Color(m_bulletConfig.FR, m_bulletConfig.FG, m_bulletConfig.FB), sf::Color(m_bulletConfig.OR, m_bulletConfig.OG, m_bulletConfig.OB), m_bulletConfig.OT);
	bullet->cCollision = std::make_shared<CCollision>(m_bulletConfig.CR * 10);
	bullet->cLifepan = std::make_shared<CLifespan>(m_bulletConfig.L);
}
void Game::sCollision()
{
	//Player Collision with all
	if ((m_player->cTransform->pos.x + m_player->cCollision->radius) > m_window.getSize().x)
	{
		float reactionPush = -10.0f;
		m_player->cTransform->velocity.x = reactionPush;
	}
	if ((m_player->cTransform->pos.x - m_player->cCollision->radius) < 0)
	{
		float reactionPush = +10.0f;
		m_player->cTransform->velocity.x = reactionPush;
	}
	if ((m_player->cTransform->pos.y - m_player->cCollision->radius) < 0)
	{
		float reactionPush = +10.0f;
		m_player->cTransform->velocity.y = reactionPush;
	}
	if ((m_player->cTransform->pos.y + m_player->cCollision->radius) > m_window.getSize().y)
	{
		float reactionPush = -10.0f;
		m_player->cTransform->velocity.y = reactionPush;
	}
	
	//enemy Collision with wall
	for (auto e : m_entities.getEntities("enemy"))
	{
		if ((e->cTransform->pos.x + e->cCollision->radius) > m_window.getSize().x)
		{
			e->cTransform->velocity.x = -1 * abs(e->cTransform->velocity.x);
		}
		if ((e->cTransform->pos.x - e->cCollision->radius) < 0)
		{
			e->cTransform->velocity.x = +1 * abs(e->cTransform->velocity.x);
		}
		if ((e->cTransform->pos.y - e->cCollision->radius) < 0)
		{
			e->cTransform->velocity.y = +1 * abs(e->cTransform->velocity.y);
		}
		if ((e->cTransform->pos.y + e->cCollision->radius) > m_window.getSize().y)
		{
			e->cTransform->velocity.y = -1 * abs(e->cTransform->velocity.y);
		}
	}

	//collision Enemy Player
	for (auto e : m_entities.getEntities("enemy"))
	{
		for (auto p : m_entities.getEntities("player"))
		{
			float dist = e->cTransform->pos.dist(p->cTransform->pos);
			if (dist < (e->cCollision->radius + p->cCollision->radius))
			{
				//respawn
				p->cTransform->pos = Vec2(m_window.getSize().x/2,m_window.getSize().y/2);
			}
		}
	}


	//collision Enemy Bullet
	for (auto b : m_entities.getEntities("bullet"))
	{
		for (auto e : m_entities.getEntities("enemy"))
		{
			float dist = b->cTransform->pos.dist(e->cTransform->pos);
			if (dist < (b->cCollision->radius + e->cCollision->radius))
			{
				e->destroy();
				b->destroy();
				m_score++;
				spawnSmallEnemies(e);
			}
		}
	}

	//collision smallenemy Bullet
	for (auto b : m_entities.getEntities("bullet"))
	{
		for (auto se : m_entities.getEntities("smallenemy"))
		{
			float dist = b->cTransform->pos.dist(se->cTransform->pos);
			if (dist < (b->cCollision->radius + se->cCollision->radius) && b->isActive())
			{
				se->destroy();
				b->destroy();
				m_score+=2;
			}
		}
	}
}
void Game::sLifespan()
{
	//TODO implement all lifespan functionality
	//if entity has no lifespan component skip it
	//if entity has > 0 remaining lifespan subtract 1
	//if it has lifespan and is alive
		//scale its alopha channel properly
	//if it has lifespan and its time its up
	// destroy the entity

	for (auto& e : m_entities.getEntities())
	{
		if (!e->cLifepan == NULL)
		{
			e->cLifepan->remaining--;

				sf::Color n_fillcolor = e->cShape->circle.getFillColor();
				n_fillcolor.a = 255 * (e->cLifepan->remaining/ e->cLifepan->total);

				sf::Color n_outLinecolor = e->cShape->circle.getOutlineColor();
				n_outLinecolor.a = 255 * (e->cLifepan->remaining / e->cLifepan->total);

			e->cShape->circle.setFillColor(n_fillcolor);
			e->cShape->circle.setOutlineColor(n_outLinecolor);

			if (e->cLifepan->remaining <= 0)
			{
				e->destroy();
			}
		}
	}
}
void Game::sEnemySpawner()
{
	
	float cooldown = m_enemyConfig.SP;
	
	if (m_currentFrame - m_lastEnemySpawnTime < cooldown) return;
	
	spawnEnemy();

	//TODO code which implements enemy spawning should go here
	// (use m_currentFrame - m_lastEnemySpawnTime) to determine
	// how long it has been since the last enemy spawned
}
void Game::sRender() 
{
	//TODO change the code below to draw all of the entities
	// sample drawing of the player Entity that we have created
	m_window.clear();

	m_window.draw(m_text);
	for (auto e : m_entities.getEntities())
	{
		m_window.draw(e->cShape->circle);
		e->cShape->circle.setPosition(e->cTransform->pos.x, e->cTransform->pos.y);

		e->cTransform->angle += 1.0f;
		e->cShape->circle.setRotation(e->cTransform->angle);
	}

	m_window.display();
}
void Game::sUpdateText() {
	m_text.setString("Score: " + std::to_string(m_score));
}
void Game::sUserInput()
{
	//TODO handle user input here
	// note that you should only be setting the players input component variables here
	// you should not implement the players movement logic here
	//the movement system will read the variables you set in this function

	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_running = false;
		}

		if (event.type == sf::Event::KeyPressed)
		{
			switch (event.key.code)
			{
			case sf::Keyboard::W:
				m_player->cInput->up = true;
					break;
			case sf::Keyboard::S:
				m_player->cInput->down = true;
				break;
			case sf::Keyboard::D:
				m_player->cInput->right = true;
				break;
			case sf::Keyboard::A:
				m_player->cInput->left = true;
				break;
			default: break;

			}
		}

		if (event.type == sf::Event::KeyReleased)
		{
			switch (event.key.code)
			{
			case sf::Keyboard::W:
				m_player->cInput->up = false;
				break;
			case sf::Keyboard::S:
				m_player->cInput->down = false;
				break;
			case sf::Keyboard::D:
				m_player->cInput->right = false;
				break;
			case sf::Keyboard::A:
				m_player->cInput->left = false;
				break;

			default: break;

			}
		}
		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				
				std::cout << "Left mouse button clicket at" << event.mouseButton.x << ", " << event.mouseButton.y << "\n";
				spawnBullet(m_player, Vec2(event.mouseButton.x, event.mouseButton.y));
			}
			if (event.mouseButton.button == sf::Mouse::Right)
			{
				
				std::cout << "Right mouse button clicket at" << event.mouseButton.x << ", " << event.mouseButton.y << "\n";
				spawnSpecialWeapon(m_player, Vec2(event.mouseButton.x, event.mouseButton.y));
			}
		}
	}
	
}
void Game::loadFromFile(const std::string& path)
{
	std::ifstream fin(path);
	std::string config;

	while (fin >> config)
	{
		if (config == "Window")
		{
			int width, height,fps,isFullscreen;
			fin >> width >> height >> fps >> isFullscreen;
			
			m_window.create(sf::VideoMode(width, height), "Assigment 2",isFullscreen == 1 ? sf::Style::Fullscreen : sf::Style::Default);
			m_window.setFramerateLimit(fps);
		}
		if (config == "Font")
		{
			std::string path;
			int size,r,g,b;
			fin >> path >> size >> r >> g >> b;

			if (!m_font.loadFromFile(path))
			{
				std::cerr << "Could not load font!\n";
				exit(-1);
			}

			m_text.setFont(m_font);
			m_text.setCharacterSize(size);
			m_text.setFillColor(sf::Color(r, g, b));

		}
		if (config == "Player")
		{
			int SR, CR, FR, FG, FB, OR, OG, OB, OT, V; 
			float S;
			fin >> SR >> CR >> S >> FR >> FG >> FB >> OR >> OG >> OB >> OT >> V;

			m_playerConfig.SR = SR;
			m_playerConfig.CR = CR;
			m_playerConfig.FR = FR;
			m_playerConfig.FB = FB;
			m_playerConfig.OR = OR;
			m_playerConfig.OG = OG;
			m_playerConfig.OB = OB;
			m_playerConfig.OT = OT;
			m_playerConfig.V = V;
			m_playerConfig.S = S;
		}
		if (config == "Enemy")
		{
			int SR, CR, OR, OG, OB, OT, VMIN,VMAX,L,SP;
			int SMIN,SMAX;
			fin >> SR >> CR >> SMIN >> SMAX >> OR >> OG >> OB >> OT >> VMIN >> VMAX >>L >> SP;
			m_enemyConfig.SR = SR;
			m_enemyConfig.CR = CR;
			m_enemyConfig.SMIN = SMIN;
			m_enemyConfig.SMAX = SMAX;
			m_enemyConfig.OR = OR;
			m_enemyConfig.OG = OG;
			m_enemyConfig.OB = OB;
			m_enemyConfig.OT = OT;
			m_enemyConfig.VMIN = VMIN;
			m_enemyConfig.VMAX = VMAX;
			m_enemyConfig.L = L;
			m_enemyConfig.SP = SP;
		}
		if (config == "Bullet")
		{
			int SR, CR, FR, FG, FB, OR, OG, OB, OT, V, L; 
			float S;
			fin >> SR >> CR >> S >> FR >> FG >> FB >> OR >> OG >> OB >> OT >> V >> L;

			m_bulletConfig.SR = SR;
			m_bulletConfig.CR = CR;
			m_bulletConfig.S = S;
			m_bulletConfig.FR = FR;
			m_bulletConfig.FG = FG;
			m_bulletConfig.FB = FB;
			m_bulletConfig.OR = OR;
			m_bulletConfig.OG = OG;
			m_bulletConfig.OB = OB;
			m_bulletConfig.OT = OT;
			m_bulletConfig.V = V;
			m_bulletConfig.L = L;

		}
	}
}