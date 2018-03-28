#include "EventBuffer.h"

void EventBuffer::PushKey(sf::Event & e)
{
	keyQueue.push(e.key.code);
}

sf::Keyboard::Key EventBuffer::popKey() {
	sf::Keyboard::Key key = keyQueue.front();
	keyQueue.pop();
	return key;
}

bool EventBuffer::isEmpty() {
	return keyQueue.empty();
}