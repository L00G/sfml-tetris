#include "SoundManager.h"

void SoundManager::Init()
{
	buffer[(int)(SOUND::MOVE_LR)].loadFromFile("./resource/sound/SFX_PieceMoveLR.ogg");
	buffer[(int)(SOUND::ROTATE_LR)].loadFromFile("./resource/sound/SFX_PieceRotateLR.ogg");
	buffer[(int)(SOUND::SOFT_DROP)].loadFromFile("./resource/sound/SFX_PieceSoftDrop.ogg");
	buffer[(int)(SOUND::HARD_DROP)].loadFromFile("./resource/sound/SFX_PieceHardDrop.ogg");
	buffer[(int)(SOUND::LINE_CLEAR)].loadFromFile("./resource/sound/SFX_SpecialLineClearSingle.ogg");

	for (int i = 0; i < 6; i++) {
		sound[i].setBuffer(buffer[i]);
	}
	sound[(int)(SOUND::HARD_DROP)].setVolume(15);
}

void SoundManager::PlaySound(SOUND target){;
	sound[(int)target].play();
}