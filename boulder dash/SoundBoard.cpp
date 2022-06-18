#include "SoundBoard.h"

SoundBoard::SoundBoard()
{
	if (!buffer[hitSound].loadFromFile("sounds\\auaua.wav"))
	{
		std::cout << "cant load hit sound";
	}
	sounds[hitSound].setBuffer(buffer[hitSound]);
	sounds[hitSound].setVolume(60.f);

	if (!buffer[dirtSound].loadFromFile("sounds\\dirt.wav"))
	{
		std::cout << "cant load dirt sound";
	}
	sounds[dirtSound].setBuffer(buffer[dirtSound]);
	sounds[dirtSound].setVolume(20.f);

	if (!buffer[diamond].loadFromFile("sounds\\diamond.wav"))
	{
		std::cout << "cant load diamond sound";
	}
	sounds[diamond].setBuffer(buffer[diamond]);
	sounds[diamond].setVolume(60.f);

	if (!buffer[death].loadFromFile("sounds\\death.wav"))
	{
		std::cout << "cant load death sound";
	}
	sounds[death].setBuffer(buffer[death]);
	sounds[death].setVolume(50.f);

	if (!buffer[rockFall].loadFromFile("sounds\\rockFall.wav"))
	{
		std::cout << "cant load rockFall sound";
	}
	sounds[rockFall].setBuffer(buffer[rockFall]);
	sounds[rockFall].setVolume(70.f);

	if (!buffer[SpiderAttack].loadFromFile("sounds\\SpiderAttack.wav"))
	{
		std::cout << "cant load SpiderAttack sound";
	}
	sounds[SpiderAttack].setBuffer(buffer[SpiderAttack]);
	sounds[SpiderAttack].setVolume(70.f);

	if (!buffer[spiderDie].loadFromFile("sounds\\spiderDie.wav"))
	{
		std::cout << "cant load spiderDie sound";
	}
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
