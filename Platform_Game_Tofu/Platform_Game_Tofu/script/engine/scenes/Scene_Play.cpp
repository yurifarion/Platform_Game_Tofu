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
	//Adjust to resolution
	float cellsize = m_game->window().getView().getSize().x / 1960 * 96;
	m_gridSize = Vec2(cellsize, cellsize);
	m_scaleFactor = m_game->window().getView().getSize().x / 1960;
	init(levelPath);
}

void Scene_Play::init(const std::string& levelPath)
{
	registerAction(sf::Keyboard::Escape, "PAUSE");
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
	registerAction(sf::Keyboard::X, "DASH");

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

	
	auto mapdata = m_maplevel.getMapDataDarkestBackground();
	//Populate entities
	// Write to the file
	for (int row = 0; row < mapdata.size(); ++row)
	{
		for (int collumn = 0; collumn < mapdata[row].size(); collumn++)
		{
			if (mapdata[row][collumn] != 0)
			{
				auto spriteName = m_game->assets().spriteRef.EnumToStr(Assets::SpriteIDReference::SPRITEID(mapdata[row][collumn]));
				auto m_mapTile = m_entityManager.addEntity("darkestbackground_tile");
				m_mapTile->addComponent<CSprite>(m_game->assets().getSprite(spriteName), false);
				m_mapTile->addComponent<CTransform>(Vec2(0, 0));
				m_mapTile->getComponent<CTransform>().scale = Vec2(6,6) * m_scaleFactor;
				Vec2 position = m_game->windowToWorld(gridToMidPixel(row, collumn, m_mapTile));
				m_mapTile->getComponent<CTransform>().pos = position;
			}
		}
	}
	mapdata = m_maplevel.getMapDataBackground();
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
				m_mapTile->getComponent<CTransform>().scale = Vec2(6, 6) * m_scaleFactor;
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
				m_mapTile->getComponent<CTransform>().scale = Vec2(6, 6) * m_scaleFactor;
				m_mapTile->addComponent<CBoundingBox>(m_gridSize);
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

	//Heart UI
	auto heartuitext = m_entityManager.addEntity("UI");
	heartuitext->addComponent<CUI>("hptext", Vec2(10, 7), Vec2(88, 48));
	heartuitext->addComponent<CTextUI>("HP");
	heartuitext->getComponent<CTextUI>().textui.setfontsize(35);
	//heartuitext->addComponent<CImageUI>(m_game->assets().getSprite("hptext"), heartuitext->getComponent<CUI>().recttransform);

	auto heart_1 = m_entityManager.addEntity("UI");
	heart_1->addComponent<CUI>("heart_1", Vec2(88, 0), Vec2(48, 48));
	heart_1->addComponent<CImageUI>(m_game->assets().getSprite("fullheart"), heart_1->getComponent<CUI>().recttransform);

	auto heart_2 = m_entityManager.addEntity("UI");
	heart_2->addComponent<CUI>("heart_2", Vec2(136, 0), Vec2(48, 48));
	heart_2->addComponent<CImageUI>(m_game->assets().getSprite("fullheart"), heart_2->getComponent<CUI>().recttransform);

	auto heart_3 = m_entityManager.addEntity("UI");
	heart_3->addComponent<CUI>("heart_3", Vec2(184, 0), Vec2(48, 48));
	heart_3->addComponent<CImageUI>(m_game->assets().getSprite("emptyheart"), heart_3->getComponent<CUI>().recttransform);

	//Mana UI
	auto manauitext = m_entityManager.addEntity("UI");
	manauitext->addComponent<CUI>("manatext", Vec2(10, 55), Vec2(88, 48));
	manauitext->addComponent<CTextUI>("MP");
	manauitext->getComponent<CTextUI>().textui.setfontsize(35);
	//manauitext->addComponent<CImageUI>(m_game->assets().getSprite("manatext"), manauitext->getComponent<CUI>().recttransform);

	auto mana_1 = m_entityManager.addEntity("UI");
	mana_1->addComponent<CUI>("mana_1", Vec2(88, 48), Vec2(48, 48));
	mana_1->addComponent<CImageUI>(m_game->assets().getSprite("fullmana"), mana_1->getComponent<CUI>().recttransform);

	auto mana_2 = m_entityManager.addEntity("UI");
	mana_2->addComponent<CUI>("mana_2", Vec2(136, 48), Vec2(48, 48));
	mana_2->addComponent<CImageUI>(m_game->assets().getSprite("fullmana"), mana_2->getComponent<CUI>().recttransform);

	auto mana_3 = m_entityManager.addEntity("UI");
	mana_3->addComponent<CUI>("mana_3", Vec2(184, 48), Vec2(48, 48));
	mana_3->addComponent<CImageUI>(m_game->assets().getSprite("emptymana"), mana_3->getComponent<CUI>().recttransform);

	//Sphere count
	auto spheretext = m_entityManager.addEntity("UI");
	spheretext->addComponent<CUI>("spheretext", Vec2(0, 0), Vec2(88, 48));
	spheretext->addComponent<CTextUI>("150X");
	spheretext->getComponent<CTextUI>().textui.setfontsize(35);
	float xpos = m_game->window().getSize().x - (spheretext->getComponent<CTextUI>().textui.getfontsize() * spheretext->getComponent<CTextUI>().textui.gettext().length()) - 50;
	spheretext->getComponent<CUI>().recttransform.setposition(Vec2(xpos, 7));

	//sphere image
	auto sphereui = m_entityManager.addEntity("UI");
	sphereui->addComponent<CUI>("sphereui", Vec2(m_game->window().getSize().x - 48, 0), Vec2(48, 48));
	sphereui->addComponent<CImageUI>(m_game->assets().getSprite("sphereui"), sphereui->getComponent<CUI>().recttransform);

	//Pause Menu UI
	//Background
	m_pausemenu = m_entityManager.addEntity("UI");
	m_pausemenu->addComponent<CUI>("Pause_bg", Vec2(0, 0), Vec2(m_game->window().getSize().x, m_game->window().getSize().y));
	m_pausemenu->addComponent<CImageUI>();
	m_pausemenu->getComponent<CImageUI>().imgui.setcolor(sf::Color(0.0f, 0.0f, 0.0f, 100.0f));
	m_pausemenu->getComponent<CUI>().recttransform.SetActive(false);

	//Title
	auto ptitle = m_entityManager.addEntity("UI");
	ptitle->addComponent<CUI>("Pause_title", Vec2(825, 375), Vec2(200, 200), &m_pausemenu->getComponent<CUI>().recttransform);
	ptitle->addComponent<CTextUI>("PAUSE");
	ptitle->getComponent<CTextUI>().textui.setfontsize(48*m_scaleFactor);

	ptitle->getComponent<CUI>().recttransform.setsize(Vec2(ptitle->getComponent<CTextUI>().textui.getfontsize()* ptitle->getComponent<CTextUI>().textui.gettext().length(), ptitle->getComponent<CTextUI>().textui.getfontsize()));

	ptitle->getComponent<CUI>().recttransform.alignment = RectTransform::Align::center;
	float y =(ptitle->getComponent<CTextUI>().textui.getfontsize()*3);
	ptitle->getComponent<CUI>().recttransform.setposition(Vec2(0,-y));


	//Resume button
	auto presumebtn = m_entityManager.addEntity("UI");
	presumebtn->addComponent<CUI>("Pause_resumebtn", Vec2(0, 0), Vec2(0, 0), &m_pausemenu->getComponent<CUI>().recttransform);
	presumebtn->addComponent<CTextUI>("Resume");
	presumebtn->getComponent<CTextUI>().textui.setfontsize(30 * m_scaleFactor);

	presumebtn->getComponent<CUI>().recttransform.setsize(Vec2(presumebtn->getComponent<CTextUI>().textui.getfontsize() * presumebtn->getComponent<CTextUI>().textui.gettext().length(), presumebtn->getComponent<CTextUI>().textui.getfontsize()));
	presumebtn->getComponent<CUI>().recttransform.alignment = RectTransform::Align::center;
	presumebtn->getComponent<CUI>().recttransform.setposition(Vec2(0, 0));

	presumebtn->addComponent<CButtonUI>(presumebtn->getComponent<CUI>().recttransform);
	presumebtn->getComponent<CButtonUI>().buttonui.addlistener([]() {

		});

	//Quit button
	auto pquitbtn = m_entityManager.addEntity("UI");
	
	pquitbtn->addComponent<CUI>("Pause_quitbtn", Vec2(0, 0), Vec2(0, 0), &m_pausemenu->getComponent<CUI>().recttransform);
	pquitbtn->addComponent<CTextUI>("Quit");

	pquitbtn->getComponent<CTextUI>().textui.setfontsize(30 * m_scaleFactor);

	pquitbtn->getComponent<CUI>().recttransform.setsize(Vec2(pquitbtn->getComponent<CTextUI>().textui.getfontsize()* pquitbtn->getComponent<CTextUI>().textui.gettext().length(), pquitbtn->getComponent<CTextUI>().textui.getfontsize()));
	pquitbtn->getComponent<CUI>().recttransform.alignment = RectTransform::Align::center;
	pquitbtn->getComponent<CUI>().recttransform.setposition(Vec2(0, pquitbtn->getComponent<CTextUI>().textui.getfontsize()*3));

	pquitbtn->addComponent<CButtonUI>(pquitbtn->getComponent<CUI>().recttransform);
}

void Scene_Play::spawnPlayer(Vec2& position)
{
	//here is a smaple player entity which you can use to construct other entities

	m_player = m_entityManager.addEntity("player");
	m_player->addComponent<CSprite>(m_game->assets().getSprite("Tofu_stand"), false);
	m_player->addComponent<CPlayer>(60.0f* m_scaleFactor, 900.0f * m_scaleFactor, 1500.0f * m_scaleFactor,0.3f);

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
	m_player->getComponent<CTransform>().scale = Vec2(6, 6) * m_scaleFactor;
	m_player->addComponent<CRigidbody>(120.0f * m_scaleFactor);
	m_player->addComponent<CBoundingBox>(m_gridSize);

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

	if (!m_paused)
	{
		sMovement();
		sLifespan();
		sAnimation();
		sCollision();
		sCameraMovement();
	}
	sUI();
	sRender();
}
void Scene_Play::sMovement()
{
	//Update all rigibodies
	auto& rb = m_player->getComponent<CRigidbody>().rigidbody;
	auto& playerData = m_player->getComponent<CPlayer>();
	rb.update(m_game->deltaTime);

	//Max moviment per frame the player can move
	Vec2 maxspeed(2000.0f * m_scaleFactor, 2000.0f * m_scaleFactor);
	

	if (m_player->getComponent<CInput>().up)
	{
		if (rb.isGrounded)
		{
			rb.addForce(Vec2(0.0f, -playerData.jumpforce));
		}
	}
	if (m_player->getComponent<CInput>().right)
	{
		if(m_player->getComponent<CTransform>().isFaceLeft) m_player->getComponent<CTransform>().flipX(false);
		rb.addForce(Vec2(playerData.speed, 0.0f));
	}
	if (m_player->getComponent<CInput>().left)
	{
		if (!m_player->getComponent<CTransform>().isFaceLeft) m_player->getComponent<CTransform>().flipX(true);
		rb.addForce(Vec2(-playerData.speed, 0.0f));
	}
	if (m_player->getComponent<CInput>().dash)
	{
		if (m_player->getComponent<CPlayer>().dashenergy > 0)
		{
			Vec2 dir = m_player->getComponent<CTransform>().isFaceLeft ? Vec2(-playerData.dashforce, 0.0f) : Vec2(playerData.dashforce, 0.0f);
			rb.addForce(dir);
		}
		
	}
	

	m_player->getComponent<CTransform>().velocity = rb.getVelocity(maxspeed);

	for (auto e : m_entityManager.getEntities())
	{
		if (e->getComponent<CTransform>().velocity != Vec2(0, 0))
		{
			e->getComponent<CTransform>().move(e->getComponent<CTransform>().velocity * m_game->deltaTime);
		}
	}
	
}
void Scene_Play::sLifespan()
{
	//Consume and recover of dash amount
	if(m_player->getComponent<CInput>().dash) m_player->getComponent<CPlayer>().addDash(-1 * m_game->deltaTime);
	else m_player->getComponent<CPlayer>().addDash(0.1f * m_game->deltaTime);
	
}
void Scene_Play::sCameraMovement()
{
	//Only move camera if player already passed half screen
	auto targetpos = m_player->getComponent<CTransform>().pos + Vec2(300.0,0); // target is slightly ahead of player
	float speed = 4.0f;
	float parallaxeMovement = 0;


	if (targetpos.x > m_game->window().getSize().x / 2)
	{
		auto currentCamPos = m_game->getCameraView().getCenter();
		float distance = m_game->window().getSize().x * 0.05;
		float distanceFromTarget = currentCamPos.x - targetpos.x;

		if (abs(distanceFromTarget) > distance)
		{
			float movement = ((targetpos.x + ((distanceFromTarget /abs(distanceFromTarget)) * distance)) - currentCamPos.x) * m_game->deltaTime * speed;
			parallaxeMovement = 0.2*movement;
			m_game->moveCameraView(Vec2(movement, 0));

		}
	}
	else 
	{
		auto currentCamPos = m_game->getCameraView().getCenter();
		float movement = (m_game->window().getSize().x / 2 - currentCamPos.x) * m_game->deltaTime * speed;
		parallaxeMovement = 0.2 * movement;
		m_game->moveCameraView(Vec2(movement, 0));
	}
	
	if (parallaxeMovement != 0)
	{
		//Parallaxe movement on the background
		for (auto e : m_entityManager.getEntities("darkestbackground_tile"))
		{
			if (e->hasComponent<CTransform>())
			{
				e->getComponent<CTransform>().move(Vec2(parallaxeMovement * 1.5f, 0));
			}
		}
		
		for (auto e : m_entityManager.getEntities("background_tile"))
		{
			if (e->hasComponent<CTransform>())
			{
				e->getComponent<CTransform>().move(Vec2(parallaxeMovement, 0));
			}
		}
	}
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
			if (overlap.x > 0.01 && overlap.y > 0.01)
			{
				auto resolveCol = physics.ResolveCollision(m_player, e);
				m_player->getComponent<CTransform>().move(Vec2(resolveCol));
				m_player->getComponent<CRigidbody>().rigidbody.isColliding = true;
			}
		}
	}

	
	
	//Check with Raycast if Player is close to the ground
	Vec2 origin = m_player->getComponent<CTransform>().pos;
	Vec2 destiny = m_player->getComponent<CTransform>().pos + (Vec2(0, m_gridSize.y/1.9));

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
		else if (action.name() == "TOGGLE_COLLISION") { m_drawCollision = !m_drawCollision; }
		else if (action.name() == "TOGGLE_GRID") { m_drawGrid = !m_drawGrid; }
		else if (action.name() == "TOGGLE_DEBUG") { m_drawDebug = !m_drawDebug; }

		//Game State Input
		else if (action.name() == "PAUSE") 
		{ 
			setPaused(!m_paused); 
			m_pausemenu->getComponent<CUI>().recttransform.SetActive(m_paused);
		}
		else if (action.name() == "QUIT") { onEnd(); }
		else if (action.name() == "JUMP")
		{
			m_player->getComponent<CInput>().up = true; 
			m_player->getComponent<CState>().state = "jump";
		}

		 //Game Controls Input
		else if (action.name() == "DOWN")
		{ 
			m_player->getComponent<CInput>().down = true; 
		}
		else if (action.name() == "RIGHT")
		{
			m_player->getComponent<CInput>().right = true; 
			m_player->getComponent<CState>().state = "walk";
		}
		else if (action.name() == "LEFT")
		{
			m_player->getComponent<CInput>().left = true; 
		}
		else if (action.name() == "DASH")
		{
			m_player->getComponent<CInput>().dash = true;
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
		 else if (action.name() == "DOWN") { m_player->getComponent<CInput>().down = false; }
		 else if (action.name() == "RIGHT") 
		{
			 m_player->getComponent<CInput>().right = false; 
		}
		 else if (action.name() == "LEFT") 
		{
			 m_player->getComponent<CInput>().left = false; 
		}
		 else if (action.name() == "DASH")
		 {
			 m_player->getComponent<CInput>().dash = false;
		 }
	}
}
void Scene_Play::sAnimation()
{

	//Set Player animation based on physics
	if (!m_player->getComponent<CRigidbody>().rigidbody.isGrounded)
		m_player->getComponent<CState>().state = "jump";
	else if (m_player->getComponent<CInput>().right || m_player->getComponent<CInput>().left)
		m_player->getComponent<CState>().state = "walk";
	else
		m_player->getComponent<CState>().state = "idle";

	
	
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
void Scene_Play::sUI()
{
	//Make UI follow the camera;
	for (auto e : m_entityManager.getEntities("UI"))
	{
		if (e->hasComponent<CUI>())
		{
			auto position = m_game->windowToWorld(e->getComponent<CUI>().recttransform.getposition());
			e->getComponent<CUI>().recttransform.setscreenposition(position);
		}
	}

	
	for (auto e : m_entityManager.getEntities("UI"))
	{
		if (e->hasComponent<CButtonUI>() && e->getComponent<CUI>().recttransform.isVisible())
		{
			auto& button = e->getComponent<CButtonUI>();
			button.buttonui.Update(m_game->window());

			//Check Button if is over
			if (button.buttonui.ismouseover())
			{
				e->getComponent<CTextUI>().textui.setcolor(sf::Color::Yellow);
			}
			else  e->getComponent<CTextUI>().textui.setcolor(sf::Color::White);

			if (button.buttonui.ispressed())
			{
				e->getComponent<CTextUI>().textui.setcolor(sf::Color::White);

				if(e->getComponent<CUI>().name == "Pause_quitbtn") onEnd();
				else if (e->getComponent<CUI>().name == "Pause_resumebtn")
				{
					setPaused(false);
					m_pausemenu->getComponent<CUI>().recttransform.SetActive(m_paused);
				}
			}
		}
	}
}
void Scene_Play::onEnd()
{
	m_hasEnded = true;
	m_game->changeScene("MENU", std::make_shared<Scene_Menu>(m_game));
}

void Scene_Play::sRender()
{
	//color the background darker so you know that the game is paused

	if (!m_paused) { m_game->window().clear(sf::Color(0, 64, 128)); }
	else { m_game->window().clear(sf::Color(50, 50, 150)); }

	
	//Draw Entities Textures 
	if (m_drawTextures)
	{
		for (auto e : m_entityManager.getEntities("darkestbackground_tile"))
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

	//Draw UI
	for (auto e : m_entityManager.getEntities("UI"))
	{
		if (e->hasComponent<CUI>())
		{
			if (e->getComponent<CUI>().recttransform.isVisible())
			{
				if (e->hasComponent<CImageUI>())
				{
					if (e->getComponent<CImageUI>().imgui.hassprite())
					{
						auto& image = e->getComponent<CImageUI>().imgui.getimage();
						image.getSprite().setRotation(e->getComponent<CUI>().recttransform.getangle());
						image.getSprite().setPosition(e->getComponent<CUI>().recttransform.getscreenposition().x, e->getComponent<CUI>().recttransform.getscreenposition().y);
						
						Vec2 currScale = Vec2(image.getSprite().getScale().x, image.getSprite().getScale().y);
						image.getSprite().setScale(currScale.x * e->getComponent<CUI>().recttransform.getscale().x, currScale.y * e->getComponent<CUI>().recttransform.getscale().y);
						m_game->window().draw(image.getSprite());
					}
					else {
						sf::RectangleShape rectangle(sf::Vector2f(e->getComponent<CUI>().recttransform.getsize().x, e->getComponent<CUI>().recttransform.getsize().y));
						rectangle.setPosition(sf::Vector2f(e->getComponent<CUI>().recttransform.getscreenposition().x, e->getComponent<CUI>().recttransform.getscreenposition().y));
						rectangle.setFillColor(e->getComponent<CImageUI>().imgui.getcolor());
						m_game->window().draw(rectangle);
					}
				}

				if (e->hasComponent<CTextUI>())
				{
					sf::Text text;
					text.setFont(m_game->assets().getFont("tech"));
					text.setCharacterSize(e->getComponent<CTextUI>().textui.getfontsize());
					text.setString(e->getComponent<CTextUI>().textui.gettext());
					text.setPosition(sf::Vector2f(e->getComponent<CUI>().recttransform.getscreenposition().x, e->getComponent<CUI>().recttransform.getscreenposition().y));
					text.setFillColor(e->getComponent<CTextUI>().textui.getcolor());
					text.setOutlineThickness(5.0f);
					text.setOutlineColor(sf::Color::Black);
					m_game->window().draw(text);
				}
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