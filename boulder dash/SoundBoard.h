#pragma once
#include "functions.h"

using namespace sf;

enum sound{hitSound, dirtSound ,diamond,death ,rockFall,
	SpiderAttack ,spiderDie};

class SoundBoard
{
	SoundBuffer buffer[7];
	Sound sounds[7];

public:
	SoundBoard();
	~SoundBoard();
	void playHit();
	void playGround();
	void playDiamond();
	void playdeath();
	void playRockFall();
	void playSpiderAttack();
	void playSpiderDie();
};

