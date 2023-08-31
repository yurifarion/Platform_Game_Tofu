#include "Scene_Menu.h"
#include "Scene_Loading.h"
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
    registerAction(sf::Keyboard::L, "LEVELEDITOR");
    registerAction(sf::Keyboard::K, "CUSTOMLEVEL");
    registerAction(sf::Keyboard::Escape, "QUIT");

    m_entityManager = EntityManager();

    m_sound.setVolume(m_game->m_mastersound);
    m_sound.setBuffer(m_game->assets().getSoundBuffer("menusfx"));

    //Background Image
    auto bgGO = m_entityManager.addEntity("UI");
    bgGO->addComponent<CUI>("Background", Vec2(0, 0), Vec2(m_game->window().getSize().x, m_game->window().getSize().y));
    bgGO->addComponent<CImageUI>(m_game->assets().getSprite("menubg"),bgGO->getComponent<CUI>().recttransform);
    bgGO->getComponent<CImageUI>().imgui.setcolor(sf::Color::Red);

    //Logo image
    auto logoGO = m_entityManager.addEntity("UI");
    Vec2 logosize = Vec2(m_game->window().getSize().x / 2, m_game->window().getSize().y / 2);
    Vec2 logoposition = Vec2(0, 0);

    logoGO->addComponent<CUI>("Logo", logoposition, logosize, &bgGO->getComponent<CUI>().recttransform);
    logoGO->getComponent<CUI>().recttransform.alignment = RectTransform::Align::topcenter;
    logoGO->getComponent<CUI>().recttransform.setposition(Vec2(0, 0));
    logoGO->addComponent<CImageUI>(m_game->assets().getSprite("logo"), logoGO->getComponent<CUI>().recttransform);
    logoGO->getComponent<CImageUI>().imgui.setcolor(sf::Color::Blue);

    auto versionText = m_entityManager.addEntity("UI");
    versionText->addComponent<CUI>("versionText", Vec2(0,0), Vec2(0, 0), &bgGO->getComponent<CUI>().recttransform);
    versionText->addComponent<CTextUI>("Version 0.0 - Alpha");
    versionText->getComponent<CUI>().recttransform.setscreenposition(Vec2(0, m_game->window().getSize().y - (versionText->getComponent<CTextUI>().textui.getfontsize() * 2)));

    auto startText = m_entityManager.addEntity("UI");
    float offset = 150;
    startText->addComponent<CUI>("startText",  Vec2(m_game->window().getSize().x /2.0f - offset, m_game->window().getSize().y / 1.5f), Vec2(0, 0), &bgGO->getComponent<CUI>().recttransform);
    startText->addComponent<CTextUI>("Click to start...");
    startText->getComponent<CTextUI>().textui.setfontsize(24);

    m_sound.play();

}

void Scene_Menu::update()
{
    m_entityManager.update();
}

void Scene_Menu::sDoAction(const Action& action)
{
    if (action.type() == "START")
    {
        if (action.name() == "LEVELEDITOR")
        {
            m_sound.stop();
            m_game->changeScene("EDITOR", std::make_shared<Scene_LevelEditorMenu>(m_game));
        }
        else if (action.name() == "CUSTOMLEVEL")
        {
            m_sound.stop();
            char const* path;
            char const* fileter[2] = { "*Level","*.Level" };
            path = tinyfd_openFileDialog("Load Level", "", 0, fileter, "Level file", 0);

            if (path == NULL)
            {
                std::cout << "Null file";
            }
            else m_game->changeScene("PLAY", std::make_shared<Scene_Play>(m_game, path,3,3,0));
        }
        else if (action.name() == "QUIT"|| action.name() == "CLOSE_WINDOW")
        {
            onEnd();
        }
        else
        {
            m_sound.stop();
            char const* path = "Levels/level";
            m_game->changeScene("PLAY", std::make_shared<Scene_Loading>(m_game, path, 3, 3, 0));
        }
    }
}

void Scene_Menu::sRender()
{


    // clear the window to a blue
    m_game->window().setView(m_game->window().getDefaultView());
    m_game->window().clear();


    //Draw UI
    for (auto e : m_entityManager.getEntities("UI"))
    {
        if (e->hasComponent<CUI>())
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
        }
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

}

void Scene_Menu::onEnd()
{
    m_hasEnded = true;
    m_game->quit();
}