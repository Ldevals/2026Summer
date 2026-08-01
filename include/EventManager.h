#pragma once

#include "common.h"
enum class EventType
{
	VehicleHasArrived
};

struct Event
{
	EventType eventType;
	sf::Vector2f position = {0.0f,0.0f};

};
class EventListener
{
public:
	virtual void OnEvent(Event _event) {};
};

class EventManager
{
public:
	static void CreateInstance();
	static EventManager* GetInstance();
	void Broadcast(Event _event);
	void AddListener(Event _event, EventListener* _listener);
private:
	EventManager(){}

	static EventManager* instance;
	//std::vector<EventListener*> listeners;
	std::unordered_map<EventType, std::vector<EventListener*>> listeners;
	//std::vector<EventListener*> event;
};