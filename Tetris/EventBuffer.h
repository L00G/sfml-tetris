#ifndef _EVENTBUFFER_H_
#define _EVENTBUFFER_H_

#include <SFML/Graphics.hpp>
#include <queue>

namespace EventBuffer {
	static std::queue<sf::Keyboard::Key> keyQueue;

	void PushKey(sf::Event &e);
	sf::Keyboard::Key popKey();
	bool isEmpty();
}

#endif