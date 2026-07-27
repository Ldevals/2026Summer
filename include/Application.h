#pragma once
#include "Engine.h"


class Editor;

class Application
{
public:
	~Application();

	bool Initialize(const char* _title, const sf::VideoMode& _mode, unsigned int _framerateLimite);
	void Run();

private:
	std::vector<sf::Event> ProcessEvents();

	sf::RenderWindow* m_window{ nullptr };
	sf::Clock			m_clock;
	bool				m_editorEnabled{ true };
	Editor* m_editor{ nullptr };
};
