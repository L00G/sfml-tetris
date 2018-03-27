#ifndef EVENTBUFFER_H
#define EVENTBUFFER_H

#include <SFML/Graphics.hpp>
#include <queue>
using namespace std;
using namespace sf;

namespace EventBuffer {
	static queue<Keyboard::Key> keyQueue;

	void PushKey(Event &e);
	Keyboard::Key popKey();
	bool isEmpty();
}

#endif