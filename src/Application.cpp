    #include "Application.h"
    #include "Editor.h"


    Application::~Application()
    {
        if (m_window)
            delete m_window;
    }

    bool Application::Initialize(const char* _title, const sf::VideoMode& _mode, unsigned int _framerateLimite)
    {
        std::srand(std::time(nullptr));

        m_window = new sf::RenderWindow(_mode, _title);
        m_window->setFramerateLimit(_framerateLimite);

        if (!Engine::CreateInstance())
            return false;

        // TODO initialize the Editor here
        Engine::GetInstance()->Initialize(m_window);
        return true;
    }

    void Application::Run()
    {
        while (m_window->isOpen())
        {
            // Events
            std::vector<sf::Event> inputs = ProcessEvents();

            // TODO
            // In the lines below, call the Editor's functions so that
            // everything works as intented.

            Engine::GetInstance()->Inputs(inputs,sf::Mouse::getPosition(*m_window));

            const float deltaTime = m_clock.restart().asSeconds();
            Engine::GetInstance()->Update(deltaTime);

            m_window->clear(sf::Color::Black);
            Engine::GetInstance()->Render(*m_window);
            m_window->display();
        }
    }

    std::vector<sf::Event> Application::ProcessEvents()
    {
        std::vector<sf::Event> inputs;
        {
            
            while (const std::optional event = m_window->pollEvent())
            {
                if (event->is<sf::Event::Closed>())
                {
                    m_window->close();
                }
                else if (const sf::Event::Resized* resize = event->getIf<sf::Event::Resized>())
                {
                    sf::FloatRect visibleArea(sf::Vector2f(0,0), sf::Vector2f(resize->size));
                    m_window->setView(sf::View(visibleArea));
                }
                else if (const sf::Event::KeyPressed* keyPressed = event->getIf<sf::Event::KeyPressed>())
                {
                    /*event.type == sf::Event::KeyReleased ||
                    event.type == sf::Event::MouseButtonPressed ||
                    event.type == sf::Event::MouseButtonReleased ||
                    event.type == sf::Event::MouseMoved ||
                    event.type == sf::Event::MouseWheelMoved*/
                    if (keyPressed->scancode == sf::Keyboard::Scancode::F1 &&
                        m_editor)
                    {
                        m_editorEnabled = !m_editorEnabled;
                    }
                    else
                    {
                        inputs.push_back(*event);
                    }
                }
            }
        }

        return inputs;
    }