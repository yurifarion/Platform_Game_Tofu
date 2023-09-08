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
    m_mastervolumetemp = 10.0f;
    m_isaudioon = m_game->m_mastersound != 0;
    init();
}

void Scene_Menu::init()
{
    registerAction(sf::Keyboard::L, "LEVELEDITOR");
    registerAction(sf::Keyboard::K, "CUSTOMLEVEL");
    registerAction(sf::Keyboard::Enter, "STARTGAME");
    registerAction(sf::Keyboard::Escape, "QUIT");

    m_entityManager = EntityManager();

    m_sound.setVolume(m_game->m_mastersound);
    m_sound.setBuffer(m_game->assets().getSoundBuffer("menusfx"));

    //Background Image
    auto bgGO = m_entityManager.addEntity("UI");
    bgGO->addComponent<CUI>("Background", Vec2(0, 0), Vec2(m_game->window().getSize().x, m_game->window().getSize().y));
    bgGO->addComponent<CImageUI>(m_game->assets().getSprite("menubg"),bgGO->getComponent<CUI>().recttransform);
    bgGO->getComponent<CImageUI>().imgui.setcolor(sf::Color::Red);


    //Resume button
    auto paudiobtn = m_entityManager.addEntity("UI");
    paudiobtn->addComponent<CUI>("Audio_btn", Vec2(0, 0), Vec2(0, 0), &bgGO->getComponent<CUI>().recttransform);
    std::string audiovalue = m_isaudioon ? "Audio ON" : "Audio OFF";
    paudiobtn->addComponent<CTextUI>(audiovalue);
    paudiobtn->getComponent<CTextUI>().textui.setfontsize(15);

    paudiobtn->getComponent<CUI>().recttransform.setsize(Vec2(paudiobtn->getComponent<CTextUI>().textui.getfontsize() * paudiobtn->getComponent<CTextUI>().textui.gettext().length(), paudiobtn->getComponent<CTextUI>().textui.getfontsize()));
    paudiobtn->getComponent<CUI>().recttransform.alignment = RectTransform::Align::topleft;
    paudiobtn->getComponent<CUI>().recttransform.setposition(Vec2(0, 0));

    paudiobtn->addComponent<CButtonUI>(paudiobtn->getComponent<CUI>().recttransform);

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
    startText->addComponent<CTextUI>("Press enter...");
    startText->getComponent<CTextUI>().textui.setfontsize(24);

    //Shader
    if (!sf::Shader::isAvailable())
    {
        std::cout << "Shaders not available \n";
    }
  
    if (!m_shader.loadFromFile("Res/Shaders/circleFade_shader.frag", sf::Shader::Fragment))
    {
        std::cout << "Couldnt find shader file \n";
    }

    m_time.restart();
    m_shader.setUniform("u_time", m_time.getElapsedTime().asSeconds());
    m_shader.setUniform("u_resolution", sf::Vector2f(m_game->window().getSize().x, m_game->window().getSize().y));
    m_shader.setUniform("u_center", sf::Vector2f(0.2f, 0.0f));

    m_sound.play();


}

void Scene_Menu::update()
{
    UIupdate();
    m_entityManager.update();
}
void Scene_Menu::UIupdate()
{
    for (auto e : m_entityManager.getEntities("UI"))
    {
        if (e->hasComponent<CButtonUI>() && e->getComponent<CUI>().recttransform.isVisible())
        {
            auto& button = e->getComponent<CButtonUI>();
            button.buttonui.Update(m_game->window());

            //Check Button if is over
            if (button.buttonui.ismouseover())
            {
                //if(m_uihoversound.getStatus() != sf::Sound::Status::Playing) m_uihoversound.play();

                e->getComponent<CTextUI>().textui.setcolor(sf::Color::Yellow);
            }
            else e->getComponent<CTextUI>().textui.setcolor(sf::Color::White);

            if (button.buttonui.isreleased())
            {
                e->getComponent<CTextUI>().textui.setcolor(sf::Color::White);
                if (e->getComponent<CUI>().name == "Audio_btn")
                {
                    m_isaudioon = !m_isaudioon;
                    if (!m_isaudioon) 
                    {
                        m_game->m_mastersound = 0;
                        e->getComponent<CTextUI>().textui.settext("Audio OFF");
                        m_sound.setVolume(m_game->m_mastersound);
                    }
                    else {
                        e->getComponent<CTextUI>().textui.settext("Audio ON");
                        m_game->m_mastersound = m_mastervolumetemp;
                        m_sound.setVolume(m_game->m_mastersound);
                    }
                }
               
            }
        }
    }
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
        else if(action.name() == "STARTGAME")
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

    m_shader.setUniform("u_time", m_time.getElapsedTime().asSeconds());
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
            text.setFillColor(e->getComponent<CTextUI>().textui.getcolor());
            text.setOutlineThickness(e->getComponent<CTextUI>().textui.getoutlinethickness());
            text.setOutlineColor(e->getComponent<CTextUI>().textui.getoutlinecolor());
            m_game->window().draw(text);
        }
    }

    //Fade in shader
    sf::RectangleShape rectangle(sf::Vector2f(120, 50));
    rectangle.setSize(sf::Vector2f(m_game->window().getSize().x, m_game->window().getSize().y));
    m_game->window().draw(rectangle, &m_shader);

}

void Scene_Menu::onEnd()
{
    m_hasEnded = true;
    m_game->quit();
}