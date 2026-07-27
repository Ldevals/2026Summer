#include "EventManager.h"

EventManager* EventManager::instance = nullptr;

void EventManager::CreateInstance()
{
	if (!instance)
		instance = new EventManager();
}

EventManager* EventManager::GetInstance()
{
	return instance;
}

void EventManager::Broadcast(Event _event)
{
	/*auto it = listeners.find(_event);

	if (it == listeners.end())
		return;

	for (EventListener* listener : it->second)
		listener->OnEvent(_event);*/

	for(EventListener* listener : listeners[_event.eventType])
		listener->OnEvent(_event);

}

void EventManager::AddListener(Event _event, EventListener* _listener)
{
	listeners[_event.eventType].push_back(_listener);
}
