#ifndef _SOUND_MANAGER_H_
#define _SOUND_MANAGER_H_

#include<SFML/Audio.hpp>

namespace SoundManager {
	enum SOUND {
		MOVE_LR,
		ROTATE_LR,
		SOFT_DROP,
		HARD_DROP,
		LINE_CLEAR
	};
	void Init();
	void PlaySound(SOUND target);
	static sf::Sound sound[6];
	static sf::SoundBuffer buffer[6];
}

#endif // !_SOUND_MANAGER_H_