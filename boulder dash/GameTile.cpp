#include "GameTile.h"

void GameTile::SetupSprite()
{
	if (!texture.loadFromFile(this->textureFile))
	{
		std::cout << "could not load tile texture";
	}
	sprite.setTexture(texture);

	sprite.setOrigin(40.f, 40.f);
}

Vector2f GameTile::getPos()
{
	return sprite.getPosition();
}

Name GameTile::getName()
{
	return name;
}

float GameTile::getTileSize()
{
	return tileSize;
}

void GameTile::render(RenderTarget* target)
{
	target->draw(this->sprite);

}