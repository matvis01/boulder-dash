#include "SoundBoard.h"

SoundBoard::SoundBoard()
{
	if (!buffer[hitSound].loadFromFile("sounds\\auaua.wav"))
	{
	}
	sounds[hitSound].setBuffer(buffer[hitSound]);
	sounds[hitSound].setVolume(60.f);

	if (!buffer[dirtSound].loadFromFile("sounds\\dirt.wav"))
	{
	}
	sounds[dirtSound].setBuffer(buffer[dirtSound]);
	sounds[dirtSound].setVolume(20.f);

	if (!buffer[diamond].loadFromFile("sounds\\diamond.wav"))
	{
	}
	sounds[diamond].setBuffer(buffer[diamond]);
	sounds[diamond].setVolume(50.f);

	if (!buffer[death].loadFromFile("sounds\\death.wav"))
	{
	}
	sounds[death].setBuffer(buffer[death]);
	sounds[death].setVolume(50.f);

	if (!buffer[rockFall].loadFromFile("sounds\\rockFall.wav"))
	{
	}
	sounds[rockFall].setBuffer(buffer[rockFall]);
	sounds[rockFall].setVolume(70.f);

	if (!buffer[SpiderAttack].loadFromFile("sounds\\SpiderAttack.wav"))
	{
	}
	sounds[SpiderAttack].setBuffer(buffer[SpiderAttack]);
	sounds[SpiderAttack].setVolume(70.f);

	buffer[spiderDie].loadFromFile("sounds\\spiderDie.wav");
	sounds[spiderDie].setBuffer(buffer[spiderDie]);
	sounds[spiderDie].setVolume(70.f);
}

SoundBoard::~SoundBoard()
{
}

void SoundBoard::playHit()
{
	sounds[hitSound].play();
}

void SoundBoard::playGround()
{
	sounds[dirtSound].play();
}

void SoundBoard::playDiamond()
{
	sounds[diamond].play();
}

void SoundBoard::playdeath()
{
	sounds[death].play();
}

void SoundBoard::playRockFall()
{
	sounds[rockFall].play();
}

void SoundBoard::playSpiderAttack()
{
	sounds[SpiderAttack].play();
}

void SoundBoard::playSpiderDie()
{
	sounds[spiderDie].play();
}
