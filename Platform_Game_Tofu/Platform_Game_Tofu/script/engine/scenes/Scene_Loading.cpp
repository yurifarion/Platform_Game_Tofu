#include "Scene_Loading.h"
#include "Scene_Play.h"
#include "Assets.h"
#include "GameEngine.h"
#include "Action.h"


Scene_Loading::Scene_Loading(GameEngine* gameEngine)
    : Scene(gameEngine)
{
    init();
}
Scene_Loading::Scene_Loading(GameEngine* gameEngine, const std::string& levelPath, int amoutOfLives, int amountOfDash, int amountOfSpheres)
    :Scene(gameEngine), m_levelpath(levelPath), m_amoutOfLives(amoutOfLives), m_amountOfDash(amountOfDash), m_amountOfSpheres(amountOfSpheres)
{
    init();
}
void Scene_Loading::init()
{
    m_entityManager = EntityManager();
    
    //Loading text
 
    auto loadingtext = m_entityManager.addEntity("UI");
    loadingtext->addComponent<CUI>("LoadingText", Vec2(m_game->window().getSize().x / 2.0f , m_game->window().getSize().y / 1.5f), Vec2(0, 0));
    loadingtext->addComponent<CTextUI>("Loading...");
    loadingtext->getComponent<CTextUI>().textui.setfontsize(24);
    loadingtext->getComponent<CUI>().recttransform.setposition(Vec2(m_game->window().getSize().x / 2.0f - ((loadingtext->getComponent<CTextUI>().textui.getfontsize()* loadingtext->getComponent<CTextUI>().textui.gettext().length())/2), m_game->window().getSize().y / 2.0f));
}

void Scene_Loading::update()
{
    m_entityManager.update();
}

void Scene_Loading::sRender()
{
    m_game->showCursor(false);

    // clear the window to a blue
    m_game->window().setView(m_game->window().getDefaultView());
    m_game->window().clear();


    //Draw UI
    for (auto e : m_entityManager.getEntities("UI"))
    {
        if (e->hasComponent<CTextUI>())
        {
            sf::Text text;
            text.setFont(m_game->assets().getFont("tech"));
            text.setCharacterSize(e->getComponent<CTextUI>().textui.getfontsize());
            text.setString(e->getComponent<CTextUI>().textui.gettext());
            text.setPosition(sf::Vector2f(e->getComponent<CUI>().recttransform.getscreenposition().x, e->getComponent<CUI>().recttransform.getscreenposition().y));
            text.setOutlineColor(sf::Color::Black);
            text.setOutlineThickness(1);
            m_game->window().draw(text);
        }
    }
    if (m_framecounter > 1)
    {
        m_game->changeScene("PLAY", std::make_shared<Scene_Play>(m_game, m_levelpath,m_amoutOfLives, m_amountOfDash, m_amountOfSpheres));
    }
    else m_framecounter++;
}
void Scene_Loading::sDoAction(const Action& action)
{

}
void Scene_Loading::onEnd()
{
    m_hasEnded = true;
    m_game->quit();
}