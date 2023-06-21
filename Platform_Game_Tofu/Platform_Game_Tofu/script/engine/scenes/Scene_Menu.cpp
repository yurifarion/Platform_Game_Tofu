#include "Scene_Menu.h"
#include "Scene_Play.h"
#include "Scene_Splash.h"
#include "Scene_LevelEditorMenu.h"
#include "Assets.h"
#include "GameEngine.h"
#include "Action.h"


Scene_Menu::Scene_Menu(GameEngine* gameEngine)
    : Scene(gameEngine)
{
    init();
}

void Scene_Menu::init()
{
    registerAction(sf::Keyboard::W, "UP");
    registerAction(sf::Keyboard::S, "DOWN");
    registerAction(sf::Keyboard::Enter, "CONFIRM");
    registerAction(sf::Keyboard::Escape, "QUIT");

    m_title = "Mr Tofu man";
    m_menuStrings.push_back("Play");
    m_menuStrings.push_back("Options");
    m_menuStrings.push_back("Level Editor");
    m_menuStrings.push_back("Credits");
    m_menuStrings.push_back("Quit");
    m_menuText.setFont(m_game->assets().getFont("tech"));
    m_menuText.setCharacterSize(64);

}

void Scene_Menu::update()
{
    m_entityManager.update();
}

void Scene_Menu::sDoAction(const Action& action)
{
    if (action.type() == "START")
    {
        if (action.name() == "UP")
        {
            if (m_selectedMenuIndex > 0) { m_selectedMenuIndex--; }
            else { m_selectedMenuIndex = m_menuStrings.size() - 1; }
        }
        else if (action.name() == "DOWN")
        {
            m_selectedMenuIndex = (m_selectedMenuIndex + 1) % m_menuStrings.size();
        }
        else if (action.name() == "CONFIRM")
        {
            if (m_menuStrings[m_selectedMenuIndex] == "Play")
            {
                char const* path;
                char const* fileter[2] = { "*Level","*.Level" };
                path = tinyfd_openFileDialog("Load Level", "", 0, fileter, "Level file", 0);

                if (path == NULL)
                {
                    std::cout << "Null file";
                }
                else m_game->changeScene("PLAY", std::make_shared<Scene_Play>(m_game, path));
                
            }
            if (m_menuStrings[m_selectedMenuIndex] == "Level Editor")
            {
                m_game->changeScene("EDITOR", std::make_shared<Scene_LevelEditorMenu>(m_game));
            }
            if (m_menuStrings[m_selectedMenuIndex] == "Quit")
            {
                onEnd();
            }
        }
        else if (action.name() == "QUIT"|| action.name() == "CLOSE_WINDOW")
        {
            onEnd();
        }
    }
}

void Scene_Menu::sRender()
{


    // clear the window to a blue
    m_game->window().setView(m_game->window().getDefaultView());
    m_game->window().clear();


    // draw the game title in the top-left of the screen
    m_menuText.setCharacterSize(100);
    m_menuText.setString(m_title);
    m_menuText.setFillColor(sf::Color(100, 100, 100));
    m_menuText.setPosition(sf::Vector2f(500, 20));
    m_menuText.setCharacterSize(50);
    m_game->window().draw(m_menuText);
   

    // draw all of the menu options
    for (size_t i = 0; i < m_menuStrings.size(); i++)
    {
        m_menuText.setString(m_menuStrings[i]);
        m_menuText.setFillColor(i == m_selectedMenuIndex ? sf::Color::White : sf::Color(100, 100, 100));
        m_menuText.setPosition(sf::Vector2f(500, 300 + i * 72));
        m_game->window().draw(m_menuText);
    }

    // draw the controls in the bottom-left
    m_menuText.setCharacterSize(20);
    m_menuText.setFillColor(sf::Color(100, 100, 100));
    m_menuText.setString("up: w     down: s    play: d      back: esc");
    m_menuText.setPosition(sf::Vector2f(10, 690));

    m_game->window().draw(m_menuText);
}

void Scene_Menu::onEnd()
{
    m_hasEnded = true;
    m_game->quit();
}