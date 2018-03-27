#include "EventBuffer.h"
#include <queue>

void EventBuffer::PushKey(Event & e)
{
	keyQueue.push(e.key.code);
}

Keyboard::Key EventBuffer::popKey() {		
	Keyboard::Key key = keyQueue.front();
	keyQueue.pop();
	return key;
}

bool EventBuffer::isEmpty() {
	return keyQueue.empty();
}