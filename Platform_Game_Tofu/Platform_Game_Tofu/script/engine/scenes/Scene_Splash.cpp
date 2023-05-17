#include "Scene_Splash.h"
#include "Scene_Menu.h"
#include "Assets.h"
#include "GameEngine.h"
#include "Action.h"
#include <cmath>

Scene_Splash::Scene_Splash(GameEngine* gameEngine)
    : Scene(gameEngine)
{
    init();
}

void Scene_Splash::init()
{
    registerAction(sf::Keyboard::Enter, "PASS");

    sf::Vector2f position;
    m_dist = 300.f;
    m_distvel = 10;

    //Load sound
    m_sound.setBuffer(m_game->assets().getSoundBuffer("splash"));
    m_titleText = "Farion Yuri";
    m_splashTitle_1.setFont(m_game->assets().getFont("tech"));
    m_splashTitle_1.setCharacterSize(64);
    m_splashTitle_1.setString(m_titleText);

    auto center = sf::Vector2f(m_splashTitle_1.getGlobalBounds().width/2, m_splashTitle_1.getGlobalBounds().height / 2);
    auto localBounds = center + m_splashTitle_1.getPosition();

    m_splashTitle_1.setOrigin(localBounds);

    m_splashTitle_2 = m_splashTitle_1;
    m_splashTitle_3 = m_splashTitle_1;

    position = sf::Vector2f(m_game->window().getSize().x / 2, (m_game->window().getSize().y / 2) - m_dist);
    m_splashTitle_1.setPosition(position);
    m_splashTitle_1.setFillColor(sf::Color(255, 0, 0, 255));

    position = sf::Vector2f(m_game->window().getSize().x / 2 + m_dist, (m_game->window().getSize().y / 2));
    m_splashTitle_2.setPosition(position);
    m_splashTitle_2.setFillColor(sf::Color(0, 255, 0, 255));

    position = sf::Vector2f(m_game->window().getSize().x / 2 - m_dist, (m_game->window().getSize().y / 2));
    m_splashTitle_3.setPosition(position);
    m_splashTitle_3.setFillColor(sf::Color(0, 0, 255, 255));

}
void Scene_Splash::update()
{
   
    if (m_dist > 0)
    {
        m_dist -= m_distvel;
        m_distvel -= m_distvel * 0.032;

        auto position = sf::Vector2f(m_game->window().getSize().x / 2, (m_game->window().getSize().y / 2) - m_dist);
        m_splashTitle_1.setPosition(position);
       
        position = sf::Vector2f(m_game->window().getSize().x / 2 + m_dist - 4, (m_game->window().getSize().y / 2) - 4);
        m_splashTitle_2.setPosition(position);

        position = sf::Vector2f(m_game->window().getSize().x / 2 - m_dist - 4, (m_game->window().getSize().y / 2));
        m_splashTitle_3.setPosition(position);
       
    }
    else if(m_frameCounter >= 0){
        m_frameCounter++;
        if (m_frameCounter > 60 && m_frameCounter < 62)
        {
            m_sound.play();
            m_splashTitle_1.setString("Farion Yuri.");
            m_splashTitle_2.setString("Farion Yuri.");
            m_splashTitle_3.setString("Farion Yuri.");
        }
        else if (m_frameCounter > 120)
        {
            m_game->changeScene("Menu", std::make_shared<Scene_Menu>(m_game));
        }
    }

   
}

void Scene_Splash::onEnd()
{

}
void Scene_Splash::sDoAction(const Action& action)
{
    if (action.type() == "START")
    {
        if (action.name() == "PASS")
        {
            m_game->changeScene("MENU", std::make_shared<Scene_Menu>(m_game));
        }
    }
}
void Scene_Splash::sRender()
{
    // clear the window to a blue
    m_game->window().setView(m_game->window().getDefaultView());
    m_game->window().clear();

    //m_game->window().draw(bg);
    m_game->window().draw(m_splashTitle_1, sf::RenderStates(sf::BlendAdd));
    m_game->window().draw(m_splashTitle_2, sf::RenderStates(sf::BlendAdd));
    m_game->window().draw(m_splashTitle_3, sf::RenderStates(sf::BlendAdd));
}
